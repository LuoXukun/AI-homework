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
#ifndef CNSCCL_GATHER_H_
#define CNSCCL_GATHER_H_

// -----------------------------------------------------------------------------
// GatherKernel algorithm (clusterDim = 4 for example)
// -----------------------------------------------------------------------------
// ----------- Start: input saved in sendbuff and recvbuff is NULL -------------
// recv buff:  [0 0 0 0 , 0 0 0 0 , 0 0 0 0 , 0 0 0 0]
// send buff:  [1 1 1 1] [2 2 2 2] [3 3 3 3] [4 4 4 4]
//                                  ^
//                                 root
//
// -------------------------------- Loop: 0 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [3 3 3 3 , 4 4 4 4 , 1 1 1 1 , 2 2 2 2 ]
//              ^
//             root
// send buff:  [1 1 1 1] [2 2 2 2] [3 3 3 3] [4 4 4 4]
//                                  ^
//                                 root
// ----------------------- End: Result in all recv buff ------------------------
// recv buff:  [2 2 2 2 , 3 3 3 3 , 4 4 4 4 , 1 1 1 1]
// send buff:  [1 1 1 1] [2 2 2 2] [3 3 3 3] [4 4 4 4]
// -----------------------------------------------------------------------------


template<class FUNC, typename T>
__mlu_func__ cnscclResult_t GatherKernel(const void* sendBuff,
                                         void* recvBuff,
                                         int count,
                                         int root)
{
  const int clusterIdPrev = getPrevClusterID(clusterId);
  const int clusterIdNext = getNextClusterID(clusterId);
  int idx =
    (clusterId - root) > 0 ? clusterId - root : (clusterDim - root + clusterId);

  if (clusterId == root)  {
    __memcpy((T*)recvBuff, (T*)sendBuff, count * sizeof(T), SRAM2SRAM, root);
  } else {
    __memcpy((T*)recvBuff + idx * count, (T*)sendBuff, count * sizeof(T),
             SRAM2SRAM, root);
  }

  __sync_all();

  return cnscclSuccess;
}

template<typename T, template<typename> class RedOp>
class GatherFunctor {
 public:
  __mlu_func__ static cnscclResult_t entry(const void* sendBuff,
                                           void* recvBuff,
                                           int count,
                                           int sendRoot,
                                           int recvRoot) {
    if (count == 0 || clusterDim == 1) {
      return cnscclUnsupportedClusterCount;
    }

    return GatherKernel<RedOp<T>, T>(sendBuff, recvBuff, count, recvRoot);
  }
};

__mlu_func__ cnscclResult_t cnscclGather(const void* sendBuff,
                                         void* recvBuff,
                                         int count,
                                         cnscclDataType_t type,
                                         int root)
{
  return enqueue<GatherFunctor>(sendBuff, recvBuff, count, type,
                                cnscclFuncNull, (int)NULL, root);
}

#endif
