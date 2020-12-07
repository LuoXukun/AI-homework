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
#ifndef CNSCCL_ALL_REDUCE_H_
#define CNSCCL_ALL_REDUCE_H_

// -----------------------------------------------------------------------------
// AllReduceKernel ring reduce algorithm (clusterDim = 4 for example)
// -----------------------------------------------------------------------------
// ----------- Start: input saved in sendbuff and recvbuff is NULL -------------
// send buff:  1  2  3  4 (const)
// recv buff:  0  0  0  0
//
// -------------------------------- Loop: 0 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// send buff:  1  2  3  4 (const)
//             ^
// recv buff:  4  1  2  3
//                ^
// -------------------------------- Loop: 1 ------------------------------------
// --- Phase1: "nram src0 buff" <- "local recv buff"
// send buff:  1  2  3  4 (const)
// recv buff:  4  1  2  3
// src0 buff:  4  1  2  3
// src1 buff:  0  0  0  0
//
// --- Phase2: "nram src1 buff" <- "local send buff"
// send buff:  1  2  3  4 (const)
// recv buff:  4  1  2  3
// src0 buff:  4  1  2  3
// src1 buff:  1  2  3  4
//
// --- Phase3: "nram dst buff" <- "nram src0 buff" + "nram src1 buff"
// send buff:  1  2  3  4 (const)
// recv buff:  4  1  2  3
// src0 buff:  4  1  2  3
// src1 buff:  1  2  3  4
// nram buff:  5  3  5  7
//
// --- Phase4: "local send buff" <- "nram dst buff"
// send buff:  5  3  5  7 (const)
// recv buff:  4  1  2  3
// src0 buff:  4  1  2  3
// src1 buff:  1  2  3  4
// nram buff:  5  3  5  7
//
// --- Phase5: "remote recv buff" <- "local send buff"
// send buff:  5  3  5  7 (const)
//                ^
// recv buff:  7  5  3  5
//                   ^
// src0 buff:  4  1  2  3
// src1 buff:  1  2  3  4
// nram buff:  5  3  5  7
//
// --- Phase6: "local send buff" <- "nram src1 buff"
// send buff:  1  2  3  4 (const)
// recv buff:  7  5  3  5
// src0 buff:  4  1  2  3
// src1 buff:  1  2  3  4
// nram buff:  5  3  5  7
//
// -------------------------------- Loop: 1 ------------------------------------
// --- Phase1: "nram src0 buff" <- "local recv buff"
// send buff:  1  2  3  4 (const)
// recv buff:  7  5  3  5
// src0 buff:  7  5  3  5
// src1 buff:  1  2  3  4
// nram buff:  5  3  5  7
//
// --- Phase2: "nram src1 buff" <- "local send buff"
// send buff:  1  2  3  4 (const)
// recv buff:  7  5  3  5
// src0 buff:  7  5  3  5
// src1 buff:  1  2  3  4
// nram buff:  5  3  5  7
//
// --- Phase3: "nram dst buff" <- "nram src0 buff" + "nram src1 buff"
// send buff:  1  2  3  4 (const)
// recv buff:  7  5  3  5
// src0 buff:  7  5  3  5
// src1 buff:  1  2  3  4
// nram buff:  8  7  6  9
//
// --- Phase4: "local send buff" <- "nram dst buff"
// send buff:  8  7  6  9 (const)
// recv buff:  7  5  3  5
// src0 buff:  7  5  3  5
// src1 buff:  1  2  3  4
// nram buff:  8  7  6  9
//
// --- Phase5: "remote recv buff" <- "local send buff"
// send buff:  8  7  6  9 (const)
//                   ^
// recv buff:  9  8  7  6
//                      ^
// src0 buff:  7  5  3  5
// src1 buff:  1  2  3  4
// nram buff:  8  7  6  9
//
// --- Phase6: "local send buff" <- "nram src1 buff"
// send buff:  1  2  3  4 (const)
// recv buff:  9  8  7  6
// src0 buff:  7  5  3  5
// src1 buff:  1  2  3  4
// nram buff:  8  7  6  9
//
// -------------------------------- Loop: 2 ------------------------------------
// --- Phase1: "nram src0 buff" <- "local recv buff"
// send buff:  1  2  3  4 (const)
// recv buff:  9  8  7  6
// src0 buff:  9  8  7  6
// src1 buff:  1  2  3  4
// nram buff:  8  7  6  9
//
// --- Phase2: "nram src1 buff" <- "local send buff"
// send buff:  1  2  3  4 (const)
// recv buff:  9  8  7  6
// src0 buff:  9  8  7  6
// src1 buff:  1  2  3  4
// nram buff:  8  7  6  9
//
// --- Phase3: "nram dst buff" <- "nram src0 buff" + "nram src1 buff"
// send buff:  1  2  3  4 (const)
// recv buff:  9  8  7  6
// src0 buff:  9  8  7  6
// src1 buff:  1  2  3  4
// nram buff: 10 10 10 10
//
// --- Phase4: "local send buff" <- "nram dst buff"
// send buff: 10 10 10 10 (const)
// recv buff:  9  8  7  6
// src0 buff:  9  8  7  6
// src1 buff:  1  2  3  4
// nram buff: 10 10 10 10
//
// --- Phase5: "remote recv buff" <- "local send buff"
// send buff: 10 10 10 10 (const)
//                      ^
// recv buff: 10 10 10 10
//             ^
// src0 buff:  9  8  7  6
// src1 buff:  1  2  3  4
// nram buff: 10 10 10 10
//
// --- Phase6: "local send buff" <- "nram src1 buff"
// send buff:  1  2  3  4 (const)
// recv buff: 10 10 10 10
// src0 buff:  9  8  7  6
// src1 buff:  1  2  3  4
// nram buff: 10 10 10 10
//
// -------------End: Result in recv buff and send buff is origin ---------------
// send buff:  1  2  3  4 (const)
// recv buff: 10 10 10 10
// -----------------------------------------------------------------------------

template<class FUNC, typename T>
__mlu_func__ cnscclResult_t AllReduceKernel(const void* sendBuff,
                                            void* recvBuff,
                                            int count) {
  const int clusterIdRemote = getNextClusterID(clusterId);
  const int slice = SLICE_SIZE / sizeof(T);
  const int chunk = count / slice;
  const int tile = slice / 4;  // coreDim = 4

  __nram__ T nDataSrc0[tile];
  __nram__ T nDataSrc1[tile];
  __nram__ T nDataDst[tile];

  for (int j = 0; j < clusterDim; j++) {
    T * baseRecvRemote = (T *)recvBuff + count * clusterIdRemote;
    T * baseSendRemote = (T *)sendBuff + count * clusterIdRemote;
    T * baseRecvLocal = (T *)recvBuff + count * clusterId;
    T * baseSendLocal = (T *)sendBuff + count * clusterId;
    int offsetTile = coreId * tile;

    // slice of chunk is for 1 cluster(with 4 core), tile of slice is for 1 core
    for (int i = 0; i < chunk; i++) {
      if (j == 0) {
        // -------------------------- Loop: 0 ----------------------------------
        // --- Phase0: "remote recv buff" <- "local send buff"
        __memcpy(baseRecvRemote + i * slice, baseSendLocal + i * slice,
                 slice * sizeof(T), SRAM2SRAM, clusterIdRemote);
        __sync_all();
      } else {
        // ---------------------- Loop: 1 ~ clusterDim-2 -----------------------
        // --- Phase1: "nram src0 buff" <- "local recv buff"
        __memcpy(nDataSrc0, baseRecvLocal + i * slice + offsetTile,
                 tile * sizeof(T), SRAM2NRAM);
        // --- Phase2: "nram src1 buff" <- "local send buff"
        __memcpy(nDataSrc1, baseSendLocal + i * slice + offsetTile,
                 tile * sizeof(T), SRAM2NRAM);
        // --- Phase3: "nram dst buff" <- "nram src0 buff" + "nram src1 buff"
        FUNC()(nDataDst, nDataSrc0, nDataSrc1, tile);
        // --- Phase4: "local send buff" <- "nram dst buff"
        __memcpy(baseSendLocal + i * slice + offsetTile, nDataDst,
                 tile * sizeof(T), NRAM2SRAM);
        // --- Phase5: "remote recv buff" <- "local send buff"
        __sync_all();
        __memcpy(baseRecvRemote + i * slice, baseSendLocal + i * slice,
                 slice * sizeof(T), SRAM2SRAM, clusterIdRemote);
        __sync_all();
        // --- Phase6: "local send buff" <- "nram src1 buff"
        __memcpy(baseSendLocal + i * slice + offsetTile, nDataSrc1,
                 tile * sizeof(T), NRAM2SRAM);
      }
    }
  }

  return cnscclSuccess;
}

template<typename T, template<typename> class RedOp>
class AllReduceFunctor {
 public:
  __mlu_func__ static cnscclResult_t entry(const void* sendBuff,
                                           void* recvBuff,
                                           int count,
                                           int sendRoot,
                                           int recvRoot) {
    if (count == 0 || clusterDim == 1) {
      return cnscclUnsupportedClusterCount;
    }
    if (count == 0 || count * sizeof(T) % SLICE_SIZE != 0) {
      __assert("Input count's byte size should be muliple of 512B",
               __FILE__, __LINE__);
      return cnscclInvalidArgument;
    }

    return AllReduceKernel<RedOp<T>, T>(sendBuff, recvBuff, count);
  }
};

__mlu_func__ cnscclResult_t cnscclAllReduce(const void* sendBuff,
                                            void* recvBuff,
                                            int count,
                                            cnscclDataType_t type,
                                            cnscclRedOp_t op)
{
  return enqueue<AllReduceFunctor>(sendBuff, recvBuff, count, type, op,
                                   (int)NULL, (int)NULL);
}

#endif  // CNSCCL_ALL_REDUCE_H_
