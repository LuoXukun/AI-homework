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
#ifndef CNSCCL_REDUCE_H_
#define CNSCCL_REDUCE_H_

// -----------------------------------------------------------------------------
// ReduceKernel reduce algorithm (clusterDim = 4 for example)
// -----------------------------------------------------------------------------
// ----------- Start: input saved in sendbuff and recvbuff ---------------------
// send buff:  [1 1 1 1] [2 2 2 2] [3 3 3 3] [4 4 4 4]
// recv buff:  [0 0 0 0] [0 0 0 0] [0 0 0 0] [0 0 0 0]
//                                  ^
//                                 root
//
// -------------End: Result in recv buff and send buff is origin ---------------
// send buff:  [1 1 1 1] [2 2 2 2] [ 3  3  3  3] [4 4 4 4]
// recv buff:  [0 0 0 0] [0 0 0 0] [10 10 10 10] [0 0 0 0]
// -----------------------------------------------------------------------------

template<class FUNC, typename T>
__mlu_func__ cnscclResult_t ReduceKernel(const void* sendBuff,
                                         void* recvBuff,
                                         int count,
                                         int root)
{
  const int clusterIdPrev = getPrevClusterID(clusterId);
  const int clusterIdNext = getNextClusterID(clusterId);
  const int slice = SLICE_SIZE / sizeof(T);
  const int chunk = count / slice;
  const int tile = slice / 4;  // coreDim = 4
  const int offsetTile = coreId * tile;

  __nram__ T nDataSrc0[tile];
  __nram__ T nDataSrc1[tile];
  __nram__ T nDataDst[tile];

  // --- Phase0: "root recv buff" <- "root send buff"
  if (clusterId == root) {
    __memcpy((T*)recvBuff, (T*)sendBuff, count * sizeof(T), SRAM2SRAM, root);
  }
  __sync_all();

  for (int j = 0; j < clusterDim - 1; ++j) {
    for (int i = 0; i < chunk; i++) {
      int idx = getNextClusterID(root + j);

      // --- Phase1: "nram src0 buff" <- "local recv buff"
      if (clusterId == root) {
        __memcpy((T*)nDataSrc0, (T*)recvBuff + i * slice + offsetTile,
                 tile * sizeof(T), SRAM2NRAM);
      }
      __sync_all();

      // --- Phase2: "root recv buff" <- "remote send buff"
      if (clusterId == idx) {
        __memcpy((T*)recvBuff + i * slice, (T*)sendBuff + i * slice,
                 slice * sizeof(T), SRAM2SRAM, root);
      }
      __sync_all();

      if (clusterId == root) {
        // --- Phase3: "nram src1 buff" <- "local send buff"
        __memcpy((T*)nDataSrc1, (T*)recvBuff + i * slice + offsetTile,
                 tile * sizeof(T), SRAM2NRAM);

        // --- Phase4: "nram dst buff" <- "nram src0 buff" + "nram src1 buff"
        FUNC()((T*)nDataDst, (T*)nDataSrc0, (T*)nDataSrc1, tile);

        // --- Phase5: "local send buff" <- "nram dst buff"
        __memcpy((T*)recvBuff + i * slice + offsetTile, (T*)nDataDst,
                 tile * sizeof(T), NRAM2SRAM);
      }
      __sync_all();
    }
  }

  return cnscclSuccess;
}

template<typename T, template<typename> class RedOp>
class ReduceFunctor {
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

    return ReduceKernel<RedOp<T>, T>(sendBuff, recvBuff, count, recvRoot);
  }
};

__mlu_func__ cnscclResult_t cnscclReduce(const void* sendBuff,
                                         void* recvBuff,
                                         int count,
                                         cnscclDataType_t type,
                                         cnscclRedOp_t op,
                                         int root)
{
  return enqueue<ReduceFunctor>(sendBuff, recvBuff, count, type, op,
                                (int)NULL, root);
}

#endif  // CNSCCL_REDUCE_H_
