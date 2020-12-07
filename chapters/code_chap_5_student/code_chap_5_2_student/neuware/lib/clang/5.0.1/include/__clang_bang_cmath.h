/*===-------- __clang_bang_cmath.h - Device-side MLU cmath support ---------===
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
#ifndef __CLANG_BANG_CMATH_H__
#define __CLANG_BANG_CMATH_H__

#ifndef __BANG__
#error "This file is for BANG compilation only."
#endif  // __BANG__

#if !(__BANG_ARCH__ >= 100)
#error "cmath header only supported by arch >= MLU100."
#endif  // !(__BANG_ARCH__ >= 100)

#ifndef __MLU_H__
#include <mlu.h>
#endif  // __MLU_H__

#define __DEVICE__ static __inline__ __mlu_func__

__DEVICE__ int32_t abs(int32_t __x) {
  return __mlvm_scalar_abs_s32(__x);
}
__DEVICE__ int16_t abs(int16_t __x) {
  return __mlvm_scalar_abs_s16(__x);
}
__DEVICE__ uint16_t max(uint16_t __x, uint16_t __y) {
  return __mlvm_scalar_max_u16(__x, __y);
}
__DEVICE__ uint32_t max(uint32_t __x, uint32_t __y) {
  return __mlvm_scalar_max_u32(__x, __y);
}
__DEVICE__ int16_t max(int16_t __x, int16_t __y) {
  return __mlvm_scalar_max_s16(__x, __y);
}
__DEVICE__ int32_t max(int32_t __x, int32_t __y) {
  return __mlvm_scalar_max_s32(__x, __y);
}
__DEVICE__ half max(half __x, half __y) {
  return __mlvm_scalar_max_f16(__x, __y);
}
__DEVICE__ float max(float __x, float __y) {
  return __mlvm_scalar_max_f32(__x, __y);
}
__DEVICE__ uint16_t min(uint16_t __x, uint16_t __y) {
  return __mlvm_scalar_min_u16(__x, __y);
}
__DEVICE__ uint32_t min(uint32_t __x, uint32_t __y) {
  return __mlvm_scalar_min_u32(__x, __y);
}
__DEVICE__ int16_t min(int16_t __x, int16_t __y) {
  return __mlvm_scalar_min_s16(__x, __y);
}
__DEVICE__ int32_t min(int32_t __x, int32_t __y) {
  return __mlvm_scalar_min_s32(__x, __y);
}
__DEVICE__ half min(half __x, half __y) {
  return __mlvm_scalar_min_f16(__x, __y);
}
__DEVICE__ float min(float __x, float __y) {
  return __mlvm_scalar_min_f32(__x, __y);
}

// Begin of cmath functions
__DEVICE__ half ceil(half __x) {
  return (half)__mlvm_scalar_cvti32_f16_up(__x);
}
__DEVICE__ float ceilf(float __x) {
  return (float)__mlvm_scalar_cvti32_f32_up(__x);
}
__DEVICE__ float cosf(float __x) {
  float r;
  __asm__ volatile("cos.gpr.f32 %[r], %[x];\n\t"
                   :[r]"+&r"(r)
                   :[x]"r"(__x));
  return r;
}
__DEVICE__ half floor(half __x) {
  return (half)__mlvm_scalar_cvti32_f16_dn(__x);
}
__DEVICE__ float floorf(float __x) {
  return (float)__mlvm_scalar_cvti32_f32_dn(__x);
}
__DEVICE__ float fabsf(float __x) {
  float r;
  __asm__ volatile("abs.gpr.f32 %[r], %[x];\n\t"
                   :[r]"+&r"(r)
                   :[x]"r"(__x));
  return r;
}
__DEVICE__ float fmaxf(float __x, float __y) {
  return __mlvm_scalar_max_f32(__x, __y);
}
__DEVICE__ float fminf(float __x, float __y) {
  return __mlvm_scalar_min_f32(__x, __y);
}
__DEVICE__ float log2f(float __x) {
  float r;
  __asm__ volatile("log2.gpr.f32 %[r], %[x];\n\t"
                   :[r]"+&r"(r)
                   :[x]"r"(__x));
  return r;
}

#if __BANG_ARCH__ >= 200
__DEVICE__ float powf(float __x, float __y) {
  float r;
  assert(__x == 2.0);
  __asm__ volatile("pow2.gpr.f32 %[r], %[y];\n\t"
                   :[r]"+&r"(r)
                   :[y]"r"(__y));
  return r;
}
#endif

__DEVICE__ half round(half __x) {
  return (half)__mlvm_scalar_cvti32_f16_rd(__x);
}
__DEVICE__ float roundf(float __x) {
  return (float)__mlvm_scalar_cvti32_f32_rd(__x);
}
__DEVICE__ float sinf(float __x) {
  float r;
  __asm__ volatile("sin.gpr.f32 %[r], %[x];\n\t"
                   :[r]"+&r"(r)
                   :[x]"r"(__x));
  return r;
}
__DEVICE__ float sqrtf(float __x) {
  float r;
  __asm__ volatile("sqrt.gpr.f32 %[r], %[x];\n\t"
                   :[r]"+&r"(r)
                   :[x]"r"(__x));
  return r;
}
__DEVICE__ float truncf(float __x) {
  return (float)__mlvm_scalar_cvti32_f32_up(__x);
}
// End of cmath functions

// We need to define these overloads in exactly the namespace our standard
// library uses (including the right inline namespace), otherwise they won't be
// picked up by other functions in the standard library (e.g. functions in
// <complex>).  Thus the ugliness below.
#ifdef _LIBCPP_BEGIN_NAMESPACE_STD
_LIBCPP_BEGIN_NAMESPACE_STD
#else
namespace std {
#ifdef _GLIBCXX_BEGIN_NAMESPACE_VERSION
_GLIBCXX_BEGIN_NAMESPACE_VERSION
#endif
#endif

// Pull the new overloads we defined above into namespace std.
// using ::acos;
// using ::acosh;
// using ::asin;
// using ::asinh;
// using ::atan;
// using ::atan2;
// using ::atanh;
// using ::cbrt;
// using ::ceil;
// using ::copysign;
// using ::cos;
// using ::cosh;
// using ::erf;
// using ::erfc;
// using ::exp;
// using ::exp2;
// using ::expm1;
// using ::fabs;
// using ::fdim;
// using ::floor;
// using ::fma;
// using ::fmax;
// using ::fmin;
// using ::fmod;
// using ::fpclassify;
// using ::frexp;
// using ::hypot;
// using ::ilogb;
// using ::isfinite;
// using ::isgreater;
// using ::isgreaterequal;
// using ::isless;
// using ::islessequal;
// using ::islessgreater;
// using ::isnormal;
// using ::isunordered;
// using ::ldexp;
// using ::lgamma;
// using ::llrint;
// using ::llround;
// using ::log;
// using ::log10;
// using ::log1p;
// using ::log2;
// using ::logb;
// using ::lrint;
// using ::lround;
// using ::nearbyint;
// using ::nextafter;
// using ::nexttoward;
// using ::pow;
// using ::remainder;
// using ::remquo;
// using ::rint;
// using ::round;
// using ::scalbln;
// using ::scalbn;
// using ::signbit;
// using ::sin;
// using ::sinh;
// using ::sqrt;
// using ::tan;
// using ::tanh;
// using ::tgamma;
// using ::trunc;

// Well this is fun: We need to pull these symbols in for libc++, but we can't
// pull them in with libstdc++, because its ::isinf and ::isnan are different
// than its std::isinf and std::isnan.
#ifndef __GLIBCXX__
// using ::isinf;
// using ::isnan;
#endif

// Finally, pull the "foobarf" functions that CUDA defines in its headers into
// namespace std.
// using ::acosf;
// using ::acoshf;
// using ::asinf;
// using ::asinhf;
// using ::atan2f;
// using ::atanf;
// using ::atanhf;
// using ::cbrtf;
using ::ceilf;
// using ::copysignf;
// using ::cosf;
// using ::coshf;
// using ::erfcf;
// using ::erff;
// using ::exp2f;
// using ::expf;
// using ::expm1f;
using ::fabsf;
// using ::fdimf;
using ::floorf;
// using ::fmaf;
using ::fmaxf;
using ::fminf;
// using ::fmodf;
// using ::frexpf;
// using ::hypotf;
// using ::ilogbf;
// using ::ldexpf;
// using ::lgammaf;
// using ::llrintf;
// using ::llroundf;
// using ::log10f;
// using ::log1pf;
// using ::log2f;
// using ::logbf;
// using ::logf;
// using ::lrintf;
// using ::lroundf;
// using ::modff;
// using ::nearbyintf;
// using ::nextafterf;
// using ::nexttowardf;
// using ::nexttowardf;
#if __BANG_ARCH__ >= 200
using ::powf;
#endif
// using ::remainderf;
// using ::remquof;
// using ::rintf;
using ::roundf;
// using ::scalblnf;
// using ::scalbnf;
// using ::sinf;
// using ::sinhf;
// using ::sqrtf;
// using ::tanf;
// using ::tanhf;
// using ::tgammaf;
using ::truncf;

#ifdef _LIBCPP_END_NAMESPACE_STD
_LIBCPP_END_NAMESPACE_STD
#else
#ifdef _GLIBCXX_BEGIN_NAMESPACE_VERSION
_GLIBCXX_END_NAMESPACE_VERSION
#endif
} // namespace std
#endif

#endif  // __CLANG_BANG_CMATH_H__
