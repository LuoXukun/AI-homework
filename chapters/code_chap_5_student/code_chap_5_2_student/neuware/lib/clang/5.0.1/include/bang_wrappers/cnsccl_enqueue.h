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
#ifndef CNSCCL_ENQUEUE_H_
#define CNSCCL_ENQUEUE_H_

// Decode data type
template< template<typename, template<typename> class> class ColFunc,
          template<typename> class Op >
__mlu_func__ cnscclResult_t enqueue(const void* sendbuff,
                                    void* recvbuff,
                                    int count,
                                    cnscclDataType_t type,
                                    int sendRoot,
                                    int recvRoot)
{
  switch(type) {
  case cnscclChar:
    return ColFunc<char, Op>::entry(sendbuff, recvbuff, count,
                                    sendRoot, recvRoot);
  case cnscclShort:
    return ColFunc<short, Op>::entry(sendbuff, recvbuff, count,
                                     sendRoot, recvRoot);
  case cnscclInt:
    return ColFunc<int, Op>::entry(sendbuff, recvbuff, count,
                                   sendRoot, recvRoot);
  case cnscclHalf:
    return ColFunc<half, Op>::entry(sendbuff, recvbuff, count,
                                    sendRoot, recvRoot);
  case cnscclFloat:
    return ColFunc<float, Op>::entry(sendbuff, recvbuff, count,
                                     sendRoot, recvRoot);
  default:
    return cnscclInvalidType;
  }
}

// Decode both data type and reduction op
template< template<typename, template<typename> class> class ColFunc>
__mlu_func__ cnscclResult_t enqueue(const void* sendbuff,
                                    void* recvbuff,
                                    int count,
                                    cnscclDataType_t type,
                                    cnscclRedOp_t op,
                                    int sendRoot,
                                    int recvRoot)
{
  switch(op) {
  case cnscclSum:
    return enqueue<ColFunc, FuncSum>(sendbuff, recvbuff, count, type,
                                     sendRoot, recvRoot);
  case cnscclProd:
    return enqueue<ColFunc, FuncProd>(sendbuff, recvbuff, count, type,
                                      sendRoot, recvRoot);
  case cnscclMax:
    return enqueue<ColFunc, FuncMax>(sendbuff, recvbuff, count, type,
                                     sendRoot, recvRoot);
  case cnscclMin:
    return enqueue<ColFunc, FuncMin>(sendbuff, recvbuff, count, type,
                                     sendRoot, recvRoot);
  case cnscclAnd:
    return enqueue<ColFunc, FuncAnd>(sendbuff, recvbuff, count, type,
                                     sendRoot, recvRoot);
  case cnscclOr:
    return enqueue<ColFunc, FuncOr>(sendbuff, recvbuff, count, type,
                                    sendRoot, recvRoot);
  case cnscclXor:
    return enqueue<ColFunc, FuncXor>(sendbuff, recvbuff, count, type,
                                     sendRoot, recvRoot);
  case cnscclFuncNull:
    return enqueue<ColFunc, FuncNull>(sendbuff, recvbuff, count, type,
                                      sendRoot, recvRoot);
  default:
    return cnscclInvalidOperation;
  }
}

#endif  // CNSCCL_ENQUEUE_H_
