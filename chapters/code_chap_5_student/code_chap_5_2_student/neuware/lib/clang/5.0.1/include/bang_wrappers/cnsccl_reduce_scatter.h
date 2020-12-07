/*************************************************************************
 * Copyright (C) [2019] by Cambricon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/
#ifndef CNSCCL_REDUCE_SCATTER_H_
#define CNSCCL_REDUCE_SCATTER_H_

// -----------------------------------------------------------------------------
// ReduceScatterKernel reduce algorithm (clusterDim = 4 for example)
// -----------------------------------------------------------------------------
// ----------- Start: input saved in sendbuff and recvbuff ---------------------
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [ 0         ] [ 0         ] [ 0         ] [ 0         ]
//
// -------------------------------- Loop: 0 ------------------------------------
// --- Phase0: "nram dst buff" <- "local send buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [ 0         ] [ 0         ] [ 0         ] [ 0         ]
// nram dst:   [ 1         ] [ 6         ] [10         ] [16         ]
//
// -------------------------------- Loop: 1 ------------------------------------
// --- Phase1: "local recv buff" <- "remote send buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// (offset,tid):   (3, 3)        (0, 0)        (1, 1)        (2, 2)
// recv buff:  [ 5         ] [10         ] [15         ] [ 4         ]
// nram dst:   [ 1         ] [ 6         ] [11         ] [16         ]
//
// --- Phase2: "nram src buff" <- "local recv buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [ 5         ] [10         ] [15         ] [ 4         ]
// nram src:   [ 5         ] [10         ] [15         ] [ 4         ]
// nram dst:   [ 1         ] [ 6         ] [11         ] [16         ]
//
// --- Phase3: "nram dst buff" += "nram src buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [ 5         ] [10         ] [15         ] [ 4         ]
// nram src:   [ 5         ] [10         ] [15         ] [ 4         ]
// nram dst:   [ 6         ] [16         ] [26         ] [20         ]
//
// -------------------------------- Loop: 2 ------------------------------------
// --- Phase1: "local recv buff" <- "remote send buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// (offset,tid):   (2, 2)        (3, 3)        (0, 0)        (1, 1)
// recv buff:  [ 9         ] [14         ] [ 3         ] [ 8         ]
// nram dst:   [ 6         ] [16         ] [26         ] [20         ]
//
// --- Phase2: "nram src buff" <- "local recv buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [ 9         ] [14         ] [ 3         ] [ 8         ]
// nram src:   [ 9         ] [14         ] [ 3         ] [ 8         ]
// nram dst:   [ 6         ] [16         ] [26         ] [20         ]
//
// --- Phase3: "nram dst buff" += "nram src buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [ 9         ] [14         ] [ 3         ] [ 8         ]
// nram src:   [ 9         ] [14         ] [ 3         ] [ 8         ]
// nram dst:   [15         ] [30         ] [29         ] [28         ]
//
// -------------------------------- Loop: 3 ------------------------------------
// --- Phase1: "local recv buff" <- "remote send buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// (offset,tid):   (1, 1)        (2, 2)        (3, 3)        (0, 0)
// recv buff:  [13         ] [ 2         ] [ 7         ] [12         ]
// nram dst:   [15         ] [30         ] [29         ] [28         ]
//
// --- Phase2: "nram src buff" <- "local recv buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [13         ] [ 2         ] [ 7         ] [12         ]
// nram src:   [13         ] [ 2         ] [ 7         ] [12         ]
// nram dst:   [15         ] [30         ] [29         ] [28         ]
//
// --- Phase3: "nram dst buff" += "nram src buff"
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [13         ] [ 2         ] [ 7         ] [12         ]
// nram src:   [13         ] [ 2         ] [ 7         ] [12         ]
// nram dst:   [28         ] [32         ] [36         ] [40         ]
//
// ----------------- End: "recv buff" <- "nram dst buff ------------------------
// send buff:  [ 1  2  3  4] [ 5  6  7  8] [ 9 10 11 12] [13 14 15 16]
// recv buff:  [28         ] [32         ] [36         ] [40         ]
// -----------------------------------------------------------------------------

template<class FUNC, typename T>
__mlu_func__ cnscclResult_t ReduceScatterKernel(const void* sendBuff,
                                                void* recvBuff,
                                                int count)
{
  const int clusterIdPrev = getPrevClusterID(clusterId);
  const int clusterIdNext = getNextClusterID(clusterId);
  const int slice = SLICE_SIZE / sizeof(T);
  const int chunk = count / slice;
  const int tile = slice / 4;  // coreDim = 4
  const int offsetTile = coreId * tile;

  __nram__ T nDataSrc[tile];
  __nram__ T nDataDst[tile];

  for (int i = 0; i < chunk; i++) {
    for (int j = 0; j < clusterDim; ++j) {
      int idx = clusterId + j;
      int tid = idx % clusterDim;
      int offsetRemote = tid * count / clusterDim;
      int offsetLocal = clusterId * count / clusterDim;

      if (j == 0) {
        // --- Phase0: "nram dst buff" <- "local send buff"
        __memcpy((T*)nDataDst,
                 (T*)sendBuff + offsetLocal + i * slice + offsetTile,
                 tile * sizeof(T), SRAM2NRAM);
        __sync_all();
      } else {
        // --- Phase1: "local recv buff" <- "remote send buff"
        __memcpy((T*)recvBuff + i * slice,
                 (T*)sendBuff + offsetRemote + i * slice,
                 count / clusterDim * sizeof(T), SRAM2SRAM, tid);
        __sync_all();

        // --- Phase2: "nram src buff" <- "local recv buff"
        __memcpy((T*)nDataSrc, (T*)recvBuff + i * slice + offsetTile,
                 tile * sizeof(T), SRAM2NRAM);

        // --- Phase3: "nram dst buff" += "nram src buff"
        FUNC()((T*)nDataDst, (T*)nDataDst, (T*)nDataSrc, tile);
      }
      __sync_all();
    }
    __memcpy((T*)recvBuff + i * slice + offsetTile, (T*)nDataDst,
             tile * sizeof(T), NRAM2SRAM);
  }

  return cnscclSuccess;
}

template<typename T, template<typename> class RedOp>
class ReduceScatterFunctor {
 public:
  __mlu_func__ static cnscclResult_t entry(const void* sendBuff,
                                           void* recvBuff,
                                           int count,
                                           int sendRoot,
                                           int recvRoot) {
    if (clusterDim == 1) {
      return cnscclUnsupportedClusterCount;
    }
    if (count == 0 || count * sizeof(T) % SLICE_SIZE != 0) {
      __assert("Input byte size should be muliple of 512B",
               __FILE__, __LINE__);
      return cnscclInvalidArgument;
    }

    return ReduceScatterKernel<RedOp<T>, T>(sendBuff, recvBuff, count);
  }
};

__mlu_func__ cnscclResult_t cnscclReduceScatter(const void* sendBuff,
                                                void* recvBuff,
                                                int count,
                                                cnscclDataType_t type,
                                                cnscclRedOp_t op)
{
  return enqueue<ReduceScatterFunctor>(sendBuff, recvBuff, count, type, op,
                                       (int)NULL, (int)NULL);
}

#endif
