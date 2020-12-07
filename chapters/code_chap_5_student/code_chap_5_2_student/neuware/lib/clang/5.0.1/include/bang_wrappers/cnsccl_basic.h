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
#ifndef CNSCCL_BASIC_H_
#define CNSCCL_BASIC_H_

#include <stddef.h>
#include <stdint.h>

#include "mlu.h"

#ifndef COMPUTE_SIZE
#define COMPUTE_SIZE 128  // Byte
#endif

#ifndef SLICE_SIZE
#define SLICE_SIZE (COMPUTE_SIZE * 4)  // Byte * coreDim
#endif

#define ID_IPU_0 0
#define ID_IPU_1 1
#define ID_IPU_2 2
#define ID_IPU_3 3
#define ID_MPU 128

#define ID_CLUSTER_0 0
#define ID_CLUSTER_1 1
#define ID_CLUSTER_2 2
#define ID_CLUSTER_3 3
#define ID_CLUSTER_4 4
#define ID_CLUSTER_5 5
#define ID_CLUSTER_6 6
#define ID_CLUSTER_7 7
#define ID_CLUSTER_8 8
#define ID_CLUSTER_9 9
#define ID_CLUSTER_10 10
#define ID_CLUSTER_11 11
#define ID_CLUSTER_12 12
#define ID_CLUSTER_13 13
#define ID_CLUSTER_14 14
#define ID_CLUSTER_15 15

__mlu_func__ int getNextClusterID(int idx) {
  return (idx + 1 >= clusterDim) ? (idx + 1 - clusterDim) : (idx + 1);
}

__mlu_func__ int getPrevClusterID(int idx) {
  return (idx - 1 < 0) ? (idx + clusterDim - 1) : (idx - 1);
}

#endif  // CNSCCL_BASIC_H_
