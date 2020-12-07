/*===-----------------------------------------------------------------------===
 *
 * Copyright (C) [2018] by Cambricon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */
#ifndef __MLU_H__
#define __MLU_H__

#include <stdint.h>

typedef int8_t  fix8;
typedef int8_t  int8;
typedef int16_t int16;

#define BANG_VERSION 200

#if defined(__BANG__) && defined(__clang__)

#define __mlu_host__    __attribute__((mlu_host))
#define __mlu_global__  __attribute__((mlu_global))
#define __mlu_entry__   __attribute__((mlu_global))
#define __mlu_device__  __attribute__((mlu_device))
#define __mlu_func__    __attribute__((mlu_device, always_inline))
#define __mlu_builtin__ __attribute__((mlu_builtin, always_inline))
#define __mlu_generic__ __attribute__(mlu_generic)

#define __nram__        __attribute__((mlu_device, mlu_nram))
#define __wram__        __attribute__((mlu_device, mlu_wram))
#define __ldram__       __attribute__((mlu_device, mlu_ldram))
#define __mlu_shared__  __attribute__((mlu_device, mlu_shared))
#define __mlu_const__   __attribute__((mlu_device, mlu_const))

#else  // defined(__BANG__) && defined(__clang__)

#define __mlu_host__
#define __mlu_global__
#define __mlu_entry__
#define __mlu_device__
#define __mlu_func__
#define __mlu_builtin__

#define __nram__
#define __wram__
#define __ldram__
#define __mlu_shared__
#define __mlu_const__


#endif  // defined(__BANG__) && defined(__clang__)

#endif // __MLU_H__
