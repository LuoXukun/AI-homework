/*===---- __clang_bang_runtime_wrapper.h - MLU runtime support -------------===
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
#ifndef __CLANG_BANG_RUNTIME_WRAPPER_H__
#define __CLANG_BANG_RUNTIME_WRAPPER_H__

#if defined(__BANG__) && defined(__clang__)

// Include some forward declares that must come before cmath.
#include <__clang_bang_math_forward_declares.h>

// Include some standard headers to avoid MLU headers including them
// while some required macros (like __THROW) are in a weird state.
#include <stdint.h>

#ifndef __MLU_H__
#include <mlu.h>
#endif // __MLU_H__

#define __DEVICE__ static __inline__ __mlu_func__

#if !defined(BANG_VERSION)
#error "mlu.h did not define BANG_VERSION"
#elif BANG_VERSION < 100 || BANG_VERSION > 200
#error "Unsupported BANG version!"
#endif

// -----------------------------------------------------------------------------
// BANG C/C++ definition: builtin task index variables
// -----------------------------------------------------------------------------
#include "__clang_bang_builtin_vars.h"

#pragma push_macro("__THROW")
#pragma push_macro("__BANG_ARCH__")

// -----------------------------------------------------------------------------
// BANG C/C++ definition: EOF and NULL
// -----------------------------------------------------------------------------
#ifndef EOF
# define EOF (-1)
#endif
#ifndef NULL
# if defined __GNUG__ &&                                    \
  (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8))
#  define NULL (__null)
# else
#  if !defined(__cplusplus)
#   define NULL ((void*)0)
#  else
#   define NULL (0)
#  endif
# endif
#endif

extern "C" {
// -----------------------------------------------------------------------------
// BANG C builtin function: printf
// -----------------------------------------------------------------------------
// Clang will convert printf into vprintf, but we still need
// device-side declaration for it.
__mlu_device__ int printf(const char *, ...);
__mlu_device__ int vprintf(const char *, const char *);

// -----------------------------------------------------------------------------
// BANG C builtin function: exit from the kernel
// -----------------------------------------------------------------------------
__DEVICE__ void exit(int status) {
  __asm__ volatile("exit %[status];\n\t"
                   ::[status]"ri"(status));
}

__DEVICE__ void __abort() { exit(-1); }

// -----------------------------------------------------------------------------
// BANG C builtin function: device-side assert
// -----------------------------------------------------------------------------
__DEVICE__ void __assert_fail(const char *__message,
                              const char *__file,
                              unsigned __line,
                              const char *__function) {
  printf("%s:%d: %s: BANG Assertion \'%s\' failed.\n",
         __file, __line, __function, __message);
  __abort();
}

__DEVICE__ void __assert(const char *__assertion,
                         const char *__file,
                         int __line) {
  printf("%s:%d: BANG Assertion \'%s\'.\n",
         __file, __line, __assertion);
}

#ifdef NDEBUG
# define assert(expr) static_cast<void>(0)
#else
# define assert(expr)                                               \
  ((expr)                                                           \
   ? static_cast<void>(0)                                           \
   : __assert_fail (#expr, __FILE__, __LINE__, __func__))
#endif

} // extern "C"


// -----------------------------------------------------------------------------
// BANG C/C++ declaration: TODO(all): mix of host code
// -----------------------------------------------------------------------------
#if 0
#include "cnrt.h"

__mlu_host__ cnrtDim3_t dim;
__mlu_host__ cnrtKernelParamsBuffer_t params;
__mlu_host__ cnrtStream_t stream;

#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus*/

__mlu_host__ cnrtRet_t bangConfigureCall(unsigned dimx,
                                         unsigned dimy,
                                         unsigned dimz,
                                         cnrtStream_t stream,
                                         size_t localSize,
                                         size_t sharedSize);

__mlu_host__ cnrtRet_t bangLaunch(const void *func);

__mlu_host__ cnrtRet_t bangSetupArgument(const void* arg,
                                         size_t size,
                                         size_t offset);
#if defined(__cplusplus)
}
#endif /*__cplusplus*/

__mlu_host__ cnrtRet_t bangConfigureCall(unsigned dimx,
                                         unsigned dimy,
                                         unsigned dimz,
                                         cnrtStream_t stream,
                                         size_t localSize,
                                         size_t sharedSize)
{
  dim.x = dimx;
  dim.y = dimy;
  dim.z = dimz;

  return cnrtCreateStream(&stream);
}

__mlu_host__ cnrtRet_t bangSetupArgument(const void* arg,
                                         size_t size,
                                         size_t offset)
{
  cnrtRet_t ret;
  ret = cnrtGetKernelParamsBuffer(&params);
  if (ret != CNRT_RET_SUCCESS) {
    return CNRT_RET_ERR_INVALID;
  }
  ret = cnrtKernelParamsBufferAddParam(params, &arg, size);
  return ret;
}

template<class T>
__mlu_host__ cnrtRet_t bangSetupArgument(T arg, size_t offset)
{
  return ::bangSetupArgument((const void*)&arg, sizeof(T), offset);
}

__mlu_host__ cnrtRet_t bangLaunch(const void *func)
{
  cnrtFunctionType_t type = CNRT_FUNC_TYPE_MUTABLE;
  switch (dim.x) {
    case 1:  type = CNRT_FUNC_TYPE_BLOCK;  break;
    case 4:  type = CNRT_FUNC_TYPE_UNION1; break;
    case 8:  type = CNRT_FUNC_TYPE_UNION2; break;
    case 16: type = CNRT_FUNC_TYPE_UNION4; break;
    case 32: type = CNRT_FUNC_TYPE_UNION8; break;
  }

  return cnrtInvokeKernel(func, dim, params, type, stream);
}
#endif

// Restore state of __BANG_ARCH__ and __THROW we had on entry.
#pragma pop_macro("__BANG_ARCH__")
#pragma pop_macro("__THROW")

// -----------------------------------------------------------------------------
// BANG C/C++ builtin function: gettimeofday
// -----------------------------------------------------------------------------
#ifndef _SYS_TIME_H
#if __BANG_ARCH__ >= 200
#include <sys/time.h>
__mlu_func__ int gettimeofday(struct timeval *__restrict __tv,
                              __timezone_ptr_t __tz) {
  unsigned int time_low = 0;
  unsigned int time_high = 0;
  unsigned int time_usec = 0;
  __asm__ volatile("mv.sreg.gpr %%perf_read, 1;\n\t"
                   "mv.gpr.sreg %[time_low], %%perf_time_stample_low;\n\t"
                   "div.gpr.u32 %[time_low], %[time_low], 25;\n\t"
                   "mv.gpr.sreg %[time_high], %%perf_time_stample_high;\n\t"
                   "div.gpr.u32 %[time_high], %[time_high], 25;\n\t"
                   "sll.gpr.u48 %[time_high], %[time_high], 32;\n\t"
                   "add.gpr.u48 %[time_usec], %[time_high], %[time_low];\n\t"
                   :[time_usec]"+&r"(time_usec),
                    [time_low]"+&r"(time_low),
                    [time_high]"+&r"(time_high)
                   );
  (__tv)->tv_usec = time_usec;
  (__tv)->tv_sec = 0;
  return 0;
}
#endif  // __BANG_ARCH__ >= 200
#endif  // _SYS_TIME_H

// -----------------------------------------------------------------------------
// BANG C definition: macros used in device-side variadic function
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
typedef char * _mlu_va_list;
#define _MLU_ADDRESSOF(v)   (&(v) )
#define _MLU_ALIGNOF(n)     ((sizeof(n) + 8 - 1) & ~(8 - 1))
#define _mlu_va_start(ap,v) (ap = (_mlu_va_list)_MLU_ADDRESSOF(v) +  _MLU_ALIGNOF(v)) // NOLINT
#define _mlu_va_arg(ap,t)   (*((t*)((ap += _MLU_ALIGNOF(t)) - _MLU_ALIGNOF(t))))
#define _mlu_va_end(ap)     (ap = (_mlu_va_list)0 )
#define _mlu_va_ptr(ap,t)   (((t*)((ap += _MLU_ALIGNOF(t)) - _MLU_ALIGNOF(t))))
#endif  //  __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// BANG C/C++ builtin function: memory, math, cmath, complex
// -----------------------------------------------------------------------------
#if defined(__BANG_ARCH__)
#include <__clang_bang_intrinsics.h>
#include <__clang_bang_math.h>
#ifdef __cplusplus
#include <__clang_bang_cmath.h>
#endif  // __cplusplus
// TODO(all): support complex for arch >= MLU200
// #include <__clang_bang_complex_builtins.h>

#endif  // __BANG_ARCH__

#endif  //  defined(__BANG__) && defined(__clang__)

#endif  // __CLANG_BANG_RUNTIME_WRAPPER_H__
