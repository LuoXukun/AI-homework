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
#ifndef CNSCCL_BROADCAST_H_
#define CNSCCL_BROADCAST_H_

// -----------------------------------------------------------------------------
// BroadcastKernel ring broadcast algorithm (clusterDim = 4 for example)
// -----------------------------------------------------------------------------
// ----------- Start: input saved in sendbuff and recvbuff is NULL -------------
// recv buff:  [1 1 1 1] [0 0 0 0] [0 0 0 0] [0 0 0 0]
//
// -------------------------------- Loop: 0 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [1 1 1 1] [1 0 0 0] [0 0 0 0] [0 0 0 0]
//                        ^
// -------------------------------- Loop: 1 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [1 1 1 1] [1 1 0 0] [1 0 0 0] [0 0 0 0]
//                          ^       ^
//
// -------------------------------- Loop: 2 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [1 1 1 1] [1 1 1 0] [1 1 0 0] [1 0 0 0]
//                            ^       ^       ^
//
// -------------------------------- Loop: 3 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [1 1 1 1] [1 1 1 1] [1 1 1 0] [1 1 0 0]
//                              ^       ^       ^
//
// -------------------------------- Loop: 4 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [1 1 1 1] [1 1 1 1] [1 1 1 1] [1 1 1 0]
//                                        ^       ^
//
// -------------------------------- Loop: 5 ------------------------------------
// --- Phase0: "remote recv buff" <- "local send buff"
// recv buff:  [1 1 1 1] [1 1 1 1] [1 1 1 1] [1 1 1 1]
//                                                  ^
//
// ----------------------- End: Result in all recv buff ------------------------
// recv buff:  [1 1 1 1] [1 1 1 1] [1 1 1 1] [1 1 1 1]
// -----------------------------------------------------------------------------

template<class FUNC, typename T>
__mlu_func__ cnscclResult_t BroadcastKernel(void* buff,
                                            int count,
                                            int root)
{
  const int clusterIdPrev = getPrevClusterID(clusterId);
  const int clusterIdNext = getNextClusterID(clusterId);

  switch (clusterDim) {
  case 2: {
    if (clusterId == root) {
      __memcpy((T*)buff, (T*)buff, count * sizeof(T), SRAM2SRAM, clusterIdNext);
    }
    break;
  }
  case 4: {
    if (clusterId == root) {
      __memcpy((T*)buff, (T*)buff, count * sizeof(T), SRAM2SRAM,
               clusterIdNext);
      __memcpy((T*)buff, (T*)buff, count * sizeof(T), SRAM2SRAM,
               getNextClusterID(clusterIdNext));
      __memcpy((T*)buff, (T*)buff, count * sizeof(T), SRAM2SRAM,
               getNextClusterID(getNextClusterID(clusterIdNext)));
    }
    __sync_all();
    break;
  }
  case 8: {
    // TODO(zhouxiaoyong): only MLU290 supported
    break;
  }
  case 16: {
    // TODO(zhouxiaoyong): only MLU290 supported
    break;
  }
  }

  return cnscclSuccess;
}

template<typename T, template<typename> class RedOp>
class BroadcastFunctor {
 public:
  __mlu_func__ static cnscclResult_t entry(const void* sendBuff,
                                           void* recvBuff,
                                           int count,
                                           int sendRoot,
                                           int recvRoot) {
    if (count == 0 || clusterDim == 1) {
      return cnscclUnsupportedClusterCount;
    }

    return BroadcastKernel<RedOp<T>, T>(recvBuff, count, sendRoot);
  }
};

__mlu_func__ cnscclResult_t cnscclBroadcast(void* buff,
                                            int count,
                                            cnscclDataType_t type,
                                            int root)
{
  return enqueue<BroadcastFunctor>(NULL, buff, count, type, cnscclFuncNull,
                                   root, (int)NULL);
}

#endif  // CNSCCL_BROADCAST_H_
