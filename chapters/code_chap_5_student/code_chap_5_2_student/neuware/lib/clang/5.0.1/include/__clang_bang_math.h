/*===--- __clang_bang_math.h - Device-side MLU math operations wrappers ----===
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
#ifndef __CLANG_BANG_MATH_H__
#define __CLANG_BANG_MATH_H__

#ifndef __BANG__
#error "This file is for BANG compilation only."
#endif  // __BANG__

#ifdef __BANG_ARCH__

#ifndef __MLU_H__
#include <mlu.h>
#endif  // __MLU_H__

#define __DEVICE__ static __inline__ __mlu_func__

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector add operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_add(half* dst,
                           half* src0,
                           half* src1,
                           int elem_count) {
  __mlvm_stream_add_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_add(float* dst,
                           float* src0,
                           float* src1,
                           int elem_count) {
  __mlvm_stream_add_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector sub operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_sub(half* dst,
                           half* src0,
                           half* src1,
                           int elem_count) {
  __mlvm_stream_sub_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_sub(float* dst,
                           float* src0,
                           float* src1,
                           int elem_count) {
  __mlvm_stream_sub_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector mul operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_mul(half* dst,
                           half* src0,
                           half* src1,
                           int elem_count) {
  __mlvm_stream_mul_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_mul(float* dst,
                           float* src0,
                           float* src1,
                           int elem_count) {
  __mlvm_stream_mul_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector mul const value operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_mul_const(half* dst,
                                 half* src,
                                 half const_value,
                                 int elem_count) {
  __mlvm_stream_mul_const_f16(dst, src, const_value, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_mul_const(float* dst,
                                 float* src,
                                 float const_value,
                                 int elem_count) {
  __mlvm_stream_mul_const_f32(dst, src, const_value, elem_count);
}
#endif

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_eq(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_eq_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_eq(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_eq_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector not-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_ne(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_ne_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_ne(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_ne_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector greater comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_gt(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_gt_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_gt(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_gt_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector greater-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_ge(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_ge_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_ge(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_ge_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector little comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_lt(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_lt_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_lt(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_lt_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector little-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_le(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_le_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_le(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_le_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200


// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_eq_bitindex(half* dst,
                                   half* src0,
                                   half* src1,
                                   int elem_count) {
  __mlvm_stream_eq_bitindex_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_eq_bitindex(float* dst,
                                   float* src0,
                                   float* src1,
                                   int elem_count) {
  __mlvm_stream_eq_bitindex_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector not-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_ne_bitindex(half* dst,
                                   half* src0,
                                   half* src1,
                                   int elem_count) {
  __mlvm_stream_ne_bitindex_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_ne_bitindex(float* dst,
                                   float* src0,
                                   float* src1,
                                   int elem_count) {
  __mlvm_stream_ne_bitindex_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector greater comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_gt_bitindex(half* dst,
                                   half* src0,
                                   half* src1,
                                   int elem_count) {
  __mlvm_stream_gt_bitindex_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_gt_bitindex(float* dst,
                                   float* src0,
                                   float* src1,
                                   int elem_count) {
  __mlvm_stream_gt_bitindex_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector greater-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_ge_bitindex(half* dst,
                                   half* src0,
                                   half* src1,
                                   int elem_count) {
  __mlvm_stream_ge_bitindex_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_ge_bitindex(float* dst,
                                   float* src0,
                                   float* src1,
                                   int elem_count) {
  __mlvm_stream_ge_bitindex_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector little comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_lt_bitindex(half* dst,
                                   half* src0,
                                   half* src1,
                                   int elem_count) {
  __mlvm_stream_lt_bitindex_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_lt_bitindex(float* dst,
                                   float* src0,
                                   float* src1,
                                   int elem_count) {
  __mlvm_stream_lt_bitindex_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector little-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_le_bitindex(half* dst,
                                   half* src0,
                                   half* src1,
                                   int elem_count) {
  __mlvm_stream_le_bitindex_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_le_bitindex(float* dst,
                                   float* src0,
                                   float* src1,
                                   int elem_count) {
  __mlvm_stream_le_bitindex_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector or operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_or(half* dst,
                          half* src0,
                          half* src1,
                          int elem_count) {
  __mlvm_stream_or_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_or(float* dst,
                          float* src0,
                          float* src1,
                          int elem_count) {
  __mlvm_stream_or_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector and operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_and(half* dst,
                           half* src0,
                           half* src1,
                           int elem_count) {
  __mlvm_stream_and_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_and(float* dst,
                           float* src0,
                           float* src1,
                           int elem_count) {
  __mlvm_stream_and_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector xor operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_xor(half* dst,
                           half* src0,
                           half* src1,
                           int elem_count) {
  __mlvm_stream_xor_f16(dst, src0, src1, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_xor(float* dst,
                           float* src0,
                           float* src1,
                           int elem_count) {
  __mlvm_stream_xor_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector bit operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_bor(char* dst,
                           char* src0,
                           char* src1,
                           int elem_count) {
  __mlvm_stream_bor_b8(dst, src0, src1, elem_count);
}
__DEVICE__ void __bang_band(char* dst,
                            char* src0,
                            char* src1,
                            int elem_count) {
  __mlvm_stream_band_b8(dst, src0, src1, elem_count);
}
__DEVICE__ void __bang_bxor(char* dst,
                            char* src0,
                            char* src1,
                            int elem_count) {
  __mlvm_stream_bxor_b8(dst, src0, src1, elem_count);
}
__DEVICE__ void __bang_bnot(char* dst,
                            char* src,
                            int elem_count) {
  __mlvm_stream_bnot_b8(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle add operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_add(half* dst,
                                 half* src,
                                 half* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_add_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_add(float* dst,
                                 float* src,
                                 float* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_add_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle sub operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_sub(half* dst,
                                 half* src,
                                 half* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_sub_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_sub(float* dst,
                                 float* src,
                                 float* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_sub_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector max-equal operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_maxequal(half* dst,
                                half* src0,
                                half* src1,
                                int elem_count) {
  __mlvm_stream_maxequal_f16(dst, src0, src1, elem_count);
}
__DEVICE__ void __bang_maxequal(float* dst,
                                float* src0,
                                float* src1,
                                int elem_count) {
  __mlvm_stream_maxequal_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector min-equal operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_minequal(half* dst,
                                half* src0,
                                half* src1,
                                int elem_count) {
  __mlvm_stream_minequal_f16(dst, src0, src1, elem_count);
}
__DEVICE__ void __bang_minequal(float* dst,
                                float* src0,
                                float* src1,
                                int elem_count) {
  __mlvm_stream_minequal_f32(dst, src0, src1, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle max-equal operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_maxequal(half* dst,
                                      half* src,
                                      half* seg,
                                      int src_elem_count,
                                      int seg_elem_count) {
  __mlvm_stream_cycle_maxequal_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
__DEVICE__ void __bang_cycle_maxequal(float* dst,
                                      float* src,
                                      float* seg,
                                      int src_elem_count,
                                      int seg_elem_count) {
  __mlvm_stream_cycle_maxequal_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle min-equal operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_minequal(half* dst,
                                      half* src,
                                      half* seg,
                                      int src_elem_count,
                                      int seg_elem_count) {
  __mlvm_stream_cycle_minequal_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
__DEVICE__ void __bang_cycle_minequal(float* dst,
                                      float* src,
                                      float* seg,
                                      int src_elem_count,
                                      int seg_elem_count) {
  __mlvm_stream_cycle_minequal_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle mul operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_mul(half* dst,
                                 half* src,
                                 half* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_mul_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_mul(float* dst,
                                 float* src,
                                 float* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_mul_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_eq(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_eq_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_eq(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_eq_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle not-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_ne(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_ne_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_ne(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_ne_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle greater comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_gt(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_gt_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_gt(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_gt_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle greater-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_ge(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_ge_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_ge(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_ge_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle little comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_lt(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_lt_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_lt(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_lt_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle little-equal comparison operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_le(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_le_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_le(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_le_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle and operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_and(half* dst,
                                 half* src,
                                 half* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_and_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_and(float* dst,
                                 float* src,
                                 float* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_and_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle or operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_or(half* dst,
                                half* src,
                                half* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_or_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_or(float* dst,
                                float* src,
                                float* seg,
                                int src_elem_count,
                                int seg_elem_count) {
  __mlvm_stream_cycle_or_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle xor operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_cycle_xor(half* dst,
                                 half* src,
                                 half* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_xor_f16(dst, src, seg, src_elem_count, seg_elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_xor(float* dst,
                                 float* src,
                                 float* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_xor_f32(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cycle bit operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_cycle_bxor(char* dst,
                                  char* src,
                                  char* seg,
                                  int src_elem_count,
                                  int seg_elem_count) {
  __mlvm_stream_cycle_bxor_b8(dst, src, seg, src_elem_count, seg_elem_count);
}
__DEVICE__ void __bang_cycle_band(char* dst,
                                  char* src,
                                  char* seg,
                                  int src_elem_count,
                                  int seg_elem_count) {
  __mlvm_stream_cycle_band_b8(dst, src, seg, src_elem_count, seg_elem_count);
}
__DEVICE__ void __bang_cycle_bor(char* dst,
                                 char* src,
                                 char* seg,
                                 int src_elem_count,
                                 int seg_elem_count) {
  __mlvm_stream_cycle_bor_b8(dst, src, seg, src_elem_count, seg_elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector select operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_select(half* dst,
                              half* src,
                              half* index,
                              int elem_count) {
  __mlvm_stream_select_f16(dst, src, index, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_select(float* dst,
                              float* src,
                              float* index,
                              int elem_count) {
  __mlvm_stream_select_f32(dst, src, index, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector select with bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_select_bitindex(half* dst,
                                       half* src,
                                       void* bitindex,
                                       int elem_count) {
  __mlvm_stream_select_bitindex_f16(dst, src, bitindex, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_select_bitindex(float* dst,
                                       float* src,
                                       void* bitindex,
                                       int elem_count) {
  __mlvm_stream_select_bitindex_f32(dst, src, bitindex, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector collect operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_collect(half* dst,
                               half* src,
                               half* mask,
                               int elem_count) {
  __mlvm_stream_collect_f16(dst, src, mask, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_collect(float* dst,
                               float* src,
                               float* mask,
                               int elem_count) {
  __mlvm_stream_collect_f32(dst, src, mask, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector collect with bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_collect_bitindex(half* dst,
                                        half* src,
                                        void* bitmask,
                                        int elem_count) {
  __mlvm_stream_collect_bitindex_f16(dst, src, bitmask, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_collect_bitindex(float* dst,
                                        float* src,
                                        void* bitmask,
                                        int elem_count) {
  __mlvm_stream_collect_bitindex_f32(dst, src, bitmask, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector maskmove operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_maskmove(half* dst,
                                half* src,
                                half* mask,
                                int elem_count) {
  __mlvm_stream_maskmove_f16(dst, src, mask, elem_count);
}
__DEVICE__ void __bang_maskmove(float* dst,
                                float* src,
                                float* mask,
                                int elem_count) {
  __mlvm_stream_maskmove_f32(dst, src, mask, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector maskmove with bit index operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_maskmove_bitindex(half* dst,
                                         half* src,
                                         void* bitmask,
                                         int elem_count) {
  __mlvm_stream_collect_bitindex_f16(dst, src, bitmask, elem_count);
}
__DEVICE__ void __bang_maskmove_bitindex(float* dst,
                                         float* src,
                                         void* bitmask,
                                         int elem_count) {
  __mlvm_stream_collect_bitindex_f32(dst, src, bitmask, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector max operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_max(half* dst,
                           half* src,
                           int elem_count) {
  __mlvm_stream_max_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_max(float* dst,
                           float* src,
                           int elem_count) {
  __mlvm_stream_max_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector min operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_min(half* dst,
                           half* src,
                           int elem_count) {
  __mlvm_stream_min_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_min(float* dst,
                           float* src,
                           int elem_count) {
  __mlvm_stream_min_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector not operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_not(half* dst,
                           half* src,
                           int elem_count) {
  __mlvm_stream_not_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_not(float* dst,
                           float* src,
                           int elem_count) {
  __mlvm_stream_not_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

//-----------------------------------------------------------------------------
// Bang c/c++ math function: strem vector rand operation
// ----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_rand(short* dst,
                            int elem_count) {
  __mlvm_stream_rand_s16(dst, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector count operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_count(unsigned int* dst,
                             half* src,
                             int elem_count) {
  __mlvm_stream_count_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_count(unsigned int* dst,
                             float* src,
                             int elem_count) {
  __mlvm_stream_count_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector count with bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_count_bitindex(unsigned int* dst,
                                      half* src,
                                      int elem_count) {
  __mlvm_stream_count_bitindex_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_count_bitindex(unsigned int* dst,
                                      float* src,
                                      int elem_count) {
  __mlvm_stream_count_bitindex_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector square operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_square(half* dst,
                              half* src,
                              int elem_count) {
  __mlvm_stream_square_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_square(float* dst,
                              float* src,
                              int elem_count) {
  __mlvm_stream_square_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector find first one operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_findfirst1(unsigned int* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_findfirst1_f16(dst, src, elem_count);
}
__DEVICE__ void __bang_findfirst1(unsigned int* dst,
                                  float* src,
                                  int elem_count) {
  __mlvm_stream_findfirst1_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector find last one operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_findlast1(unsigned int* dst,
                                 half* src,
                                 int elem_count) {
  __mlvm_stream_findlast1_f16(dst, src, elem_count);
}
__DEVICE__ void __bang_findlast1(unsigned int* dst,
                                 float* src,
                                 int elem_count) {
  __mlvm_stream_findlast1_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector reduce_sum operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_reduce_sum(half* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_reduce_sum_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_reduce_sum(float* dst,
                                  float* src,
                                  int elem_count) {
  __mlvm_stream_reduce_sum_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector write zero operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_write_zero(half* dst,
                                  int elem_count) {
  __mlvm_stream_write_zero_f16(dst, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_write_zero(float* dst,
                                  int elem_count) {
  __mlvm_stream_write_zero_f32(dst, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector relu active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_relu(half* dst,
                                   half* src,
                                   int elem_count) {
  __mlvm_stream_active_relu_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_relu(float* dst,
                                   float* src,
                                   int elem_count) {
  __mlvm_stream_active_relu_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector gelu active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_gelu(half* dst,
                                   half* src,
                                   int elem_count) {
  __mlvm_stream_active_gelu_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_gelu(float* dst,
                                   float* src,
                                   int elem_count) {
  __mlvm_stream_active_gelu_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector gelu precision active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_gelup(half* dst,
                                    half* src,
                                    int elem_count) {
  __mlvm_stream_active_gelup_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_gelup(float* dst,
                                    float* src,
                                    int elem_count) {
  __mlvm_stream_active_gelup_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector tanh active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_tanh(half* dst,
                                   half* src,
                                   int elem_count) {
  __mlvm_stream_active_tanh_f16(dst, src, elem_count);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream abs active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_abs(half* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_active_abs_f16(dst, src, elem_count);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector sigmoid active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_sigmoid(half* dst,
                                      half* src,
                                      int elem_count) {
  __mlvm_stream_active_sigmoid_f16(dst, src, elem_count);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_sigmoid(float* dst,
                                      float* src,
                                      int elem_count) {
  __mlvm_stream_active_sigmoid_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector exp active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_exp(half* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_active_exp_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_exp(float* dst,
                                  float* src,
                                  int elem_count) {
  __mlvm_stream_active_exp_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector exp less 0 active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_exp_less_0(half* dst,
                                         half* src,
                                         int elem_count) {
  __mlvm_stream_active_explt0_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_exp_less_0(float* dst,
                                         float* src,
                                         int elem_count) {
  __mlvm_stream_active_explt0_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector sqrt active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_sqrt(half* dst,
                                   half* src,
                                   int elem_count) {
  __mlvm_stream_active_sqrt_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_sqrt(float* dst,
                                   float* src,
                                   int elem_count) {
  __mlvm_stream_active_sqrt_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector sqrt and reciprocal active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_rsqrt(half* dst,
                                    half* src,
                                    int elem_count) {
  __mlvm_stream_active_rsqrt_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_rsqrt(float* dst,
                                    float* src,
                                    int elem_count) {
  __mlvm_stream_active_rsqrt_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector reciprocal active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_recip(half* dst,
                                    half* src,
                                    int elem_count) {
  __mlvm_stream_active_recip_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_recip(float* dst,
                                    float* src,
                                    int elem_count) {
  __mlvm_stream_active_recip_f32(dst, src,
                                 elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector reciprocal greater 1 active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_recip_greater_1(half* dst,
                                              half* src,
                                              int elem_count) {
  __mlvm_stream_active_recipgt1_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_recip_greater_1(float* dst,
                                              float* src,
                                              int elem_count) {
  __mlvm_stream_active_recipgt1_f32(dst, src,
                                    elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector sine active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_sin(half* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_active_sin_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_sin(float* dst,
                                  float* src,
                                  int elem_count) {
  __mlvm_stream_active_sin_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector cosine active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_cos(half* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_active_cos_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_cos(float* dst,
                                  float* src,
                                  int elem_count) {
  __mlvm_stream_active_cos_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector log active operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_active_log(half* dst,
                                  half* src,
                                  int elem_count) {
  __mlvm_stream_active_log_f16(dst, src, elem_count);
}

#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_active_log(float* dst,
                                  float* src,
                                  int elem_count) {
  __mlvm_stream_active_log_f32(dst, src, elem_count);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream vector maximum operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_maximum(half* dst,
                               half* src,
                               int distance,
                               int size) {
  __mlvm_stream_maximum_f16(dst, src, distance, size);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream matrix pad operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_pad(half* dst,
                           half* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b16(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(half* dst,
                           half* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b16(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(short* dst,
                           short* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b16(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(short* dst,
                           short* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b16(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(unsigned short* dst,
                           unsigned short* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b16(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(unsigned short* dst,
                           unsigned short* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b16(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_pad(int8* dst,
                           int8* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b8(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(int8* dst,
                           int8* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b8(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(char* dst,
                           char* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b8(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(char* dst,
                           char* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b8(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(unsigned char* dst,
                           unsigned char* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b8(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(unsigned char* dst,
                           unsigned char* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b8(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(float* dst,
                           float* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b32(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(float* dst,
                           float* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b32(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(int* dst,
                           int* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b32(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(int* dst,
                           int* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b32(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
__DEVICE__ void __bang_pad(unsigned int* dst,
                           unsigned int* src,
                           int channel,
                           int height,
                           int width,
                           int pad_height,
                           int pad_width) {
  __mlvm_stream_pad_b32(dst, src, channel, height, width, pad_height,
                        pad_height, pad_width, pad_width);
}
__DEVICE__ void __bang_pad(unsigned int* dst,
                           unsigned int* src,
                           int channel,
                           int height,
                           int width,
                           int pad_top,
                           int pad_bottom,
                           int pad_left,
                           int pad_right) {
  __mlvm_stream_pad_b32(dst, src, channel, height, width, pad_top,
                        pad_bottom, pad_left, pad_right);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream matrix transpose operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_transpose(half* dst,
                                 half* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b16(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(short* dst,
                                 short* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b16(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(unsigned short* dst,
                                 unsigned short* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b16(dst, src, height, width);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_transpose(int8* dst,
                                 int8* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b8(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(char* dst,
                                 char* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b8(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(unsigned char* dst,
                                 unsigned char* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b8(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(float* dst,
                                 float* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b32(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(int* dst,
                                 int* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b32(dst, src, height, width);
}
__DEVICE__ void __bang_transpose(unsigned int* dst,
                                 unsigned int* src,
                                 int height,
                                 int width) {
  __mlvm_stream_trans_b32(dst, src, height, width);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream matrix rotate operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_rotate90(int8* dst,
                                int8* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(char* dst,
                                char* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(unsigned char* dst,
                                unsigned char* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(half* dst,
                                half* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(short* dst,
                                short* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(unsigned short* dst,
                                unsigned short* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(float* dst,
                                float* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b32(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(int* dst,
                                int* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b32(dst, src, height, width);
}
__DEVICE__ void __bang_rotate90(unsigned int* dst,
                                unsigned int* src,
                                int height,
                                int width) {
  __mlvm_stream_rotate1pi_b32(dst, src, height, width);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_rotate180(int8* dst,
                                 int8* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(char* dst,
                                 char* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(unsigned char* dst,
                                 unsigned char* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(half* dst,
                                 half* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(short* dst,
                                 short* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(unsigned short* dst,
                                 unsigned short* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(float* dst,
                                 float* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b32(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(int* dst,
                                 int* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b32(dst, src, height, width);
}
__DEVICE__ void __bang_rotate180(unsigned int* dst,
                                 unsigned int* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate2pi_b32(dst, src, height, width);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_rotate270(int8* dst,
                                 int8* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(char* dst,
                                 char* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(unsigned char* dst,
                                 unsigned char* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b8(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(half* dst,
                                 half* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(short* dst,
                                 short* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(unsigned short* dst,
                                 unsigned short* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b16(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(float* dst,
                                 float* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b32(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(int* dst,
                                 int* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b32(dst, src, height, width);
}
__DEVICE__ void __bang_rotate270(unsigned int* dst,
                                 unsigned int* src,
                                 int height,
                                 int width) {
  __mlvm_stream_rotate3pi_b32(dst, src, height, width);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: mirror the input matrix along w axis
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_mirror(int8* dst,
                              int8* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b8(dst, src, height, width);
}
__DEVICE__ void __bang_mirror(char* dst,
                              char* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b8(dst, src, height, width);
}
__DEVICE__ void __bang_mirror(unsigned char* dst,
                              unsigned char* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b8(dst, src, height, width);
}
__DEVICE__ void __bang_mirror(unsigned short* dst,
                              unsigned short* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b16(dst, src, height, width);
}
__DEVICE__ void __bang_mirror(short* dst,
                              short* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b16(dst, src, height, width);
}
__DEVICE__ void __bang_mirror(half* dst,
                              half* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b16(dst, src, height, width);
}
__DEVICE__ void __bang_mirror(unsigned int* dst,
                              unsigned int* src,
                              int height,
                              int width) {
  __mlvm_stream_mirror_b32(dst, src, height, width);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream reshape operation
// -----------------------------------------------------------------------------
// filter_reshape: 16bit
__DEVICE__ void __bang_reshape_filter(half* dst,
                                      half* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b16(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_filter(short* dst,
                                      short* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b16(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_filter(unsigned short* dst,
                                      unsigned short* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b16(dst, src, n, h, w, c);
}
// filter_reshape: 8bit
__DEVICE__ void __bang_reshape_filter(int8* dst,
                                      int8* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b8(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_filter(char* dst,
                                      char* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b8(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_filter(unsigned char* dst,
                                      unsigned char* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b8(dst, src, n, h, w, c);
}
// filter_reshape: 32bit
__DEVICE__ void __bang_reshape_filter(float* dst,
                                      float* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b32(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_filter(int* dst,
                                      int* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b32(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_filter(unsigned int* dst,
                                      unsigned int* src,
                                      int n,
                                      int h,
                                      int w,
                                      int c) {
  __mlvm_stream_reshape_filter_b32(dst, src, n, h, w, c);
}

// nhwc2nchw: 16bit
__DEVICE__ void __bang_reshape_nhwc2nchw(half* dst,
                                         half* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b16(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nhwc2nchw(short* dst,
                                         short* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b16(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nhwc2nchw(unsigned short* dst,
                                         unsigned short* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b16(dst, src, n, h, w, c);
}
// nhwc2nchw: 8bit
__DEVICE__ void __bang_reshape_nhwc2nchw(int8* dst,
                                         int8* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b8(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nhwc2nchw(char* dst,
                                         char* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b8(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nhwc2nchw(unsigned char* dst,
                                         unsigned char* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b8(dst, src, n, h, w, c);
}
// nhwc2nchw: 32bit
__DEVICE__ void __bang_reshape_nhwc2nchw(float* dst,
                                         float* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b32(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nhwc2nchw(int* dst,
                                         int* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b32(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nhwc2nchw(unsigned int* dst,
                                         unsigned int* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nhwc2nchw_b32(dst, src, n, h, w, c);
}

// nchw2nhwc: 16bit
__DEVICE__ void __bang_reshape_nchw2nhwc(half* dst,
                                         half* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b16(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nchw2nhwc(short* dst,
                                         short* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b16(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nchw2nhwc(unsigned short* dst,
                                         unsigned short* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b16(dst, src, n, h, w, c);
}
// nchw2nhwc: 8bit
__DEVICE__ void __bang_reshape_nchw2nhwc(int8* dst,
                                         int8* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b8(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nchw2nhwc(char* dst,
                                         char* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b8(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nchw2nhwc(unsigned char* dst,
                                         unsigned char* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b8(dst, src, n, h, w, c);
}
// nchw2nhwc: 32bit
__DEVICE__ void __bang_reshape_nchw2nhwc(float* dst,
                                         float* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b32(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nchw2nhwc(int* dst,
                                         int* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b32(dst, src, n, h, w, c);
}
__DEVICE__ void __bang_reshape_nchw2nhwc(unsigned int* dst,
                                         unsigned int* src,
                                         int n,
                                         int h,
                                         int w,
                                         int c) {
  __mlvm_stream_reshape_nchw2nhwc_b32(dst, src, n, h, w, c);
}

#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_sumpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width) {
  __mlvm_stream_pool_sum_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             kernel_width, kernel_height);
}
__DEVICE__ void __bang_sumpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_sum_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_sumpool(float* dst,
                               float* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_sum_f32(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_unpool(half* dst,
                              half* src,
                              int channel,
                              int height,
                              int width,
                              int kernel_height,
                              int kernel_width,
                              int stride_x,
                              int stride_y,
                              int index) {
  __mlvm_stream_unpool_f16(dst, src, channel, height, width,
                           kernel_height, kernel_width,
                           stride_x, stride_y, index);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_unpool(float* dst,
                              float* src,
                              int channel,
                              int height,
                              int width,
                              int kernel_height,
                              int kernel_width,
                              int stride_x,
                              int stride_y,
                              int index) {
  __mlvm_stream_unpool_f32(dst, src, channel, height, width,
                           kernel_height, kernel_width,
                           stride_x, stride_y, index);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_maxpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width) {
  __mlvm_stream_pool_max_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             kernel_width, kernel_height);
}

__DEVICE__ void __bang_maxpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_max_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_maxpool(float* dst,
                               float* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_max_f32(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_maxpool_index(unsigned short* dst,
                                     half* src,
                                     int channel,
                                     int height,
                                     int width,
                                     int kernel_height,
                                     int kernel_width) {
  __mlvm_stream_pool_max_index_f16(dst, src, channel, height, width,
                                   kernel_height, kernel_width,
                                   kernel_width, kernel_height);
}

__DEVICE__ void __bang_maxpool_index(unsigned short* dst,
                                     half* src,
                                     int channel,
                                     int height,
                                     int width,
                                     int kernel_height,
                                     int kernel_width,
                                     int stride_x,
                                     int stride_y) {
  __mlvm_stream_pool_max_index_f16(dst, src, channel, height, width,
                                   kernel_height, kernel_width,
                                   stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_maxpool_index(unsigned int* dst,
                                     float* src,
                                     int channel,
                                     int height,
                                     int width,
                                     int kernel_height,
                                     int kernel_width,
                                     int stride_x,
                                     int stride_y) {
  __mlvm_stream_pool_max_index_f32(dst, src, channel, height, width,
                                   kernel_height, kernel_width,
                                   stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_minpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width) {
  __mlvm_stream_pool_min_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             kernel_width, kernel_height);
}

__DEVICE__ void __bang_minpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_min_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_minpool(float* dst,
                               float* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_min_f32(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream select wit bit index operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_minpool_index(unsigned short* dst,
                                     half* src,
                                     int channel,
                                     int height,
                                     int width,
                                     int kernel_height,
                                     int kernel_width) {
  __mlvm_stream_pool_min_index_f16(dst, src, channel, height, width,
                                   kernel_height, kernel_width,
                                   kernel_width, kernel_height);
}

__DEVICE__ void __bang_minpool_index(unsigned short* dst,
                                     half* src,
                                     int channel,
                                     int height,
                                     int width,
                                     int kernel_height,
                                     int kernel_width,
                                     int stride_x,
                                     int stride_y) {
  __mlvm_stream_pool_min_index_f16(dst, src, channel, height, width,
                                   kernel_height, kernel_width,
                                   stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_minpool_index(unsigned int* dst,
                                     float* src,
                                     int channel,
                                     int height,
                                     int width,
                                     int kernel_height,
                                     int kernel_width,
                                     int stride_x,
                                     int stride_y) {
  __mlvm_stream_pool_min_index_f32(dst, src, channel, height, width,
                                   kernel_height, kernel_width,
                                   stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream avgpool operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_avgpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width) {
  __mlvm_stream_pool_avg_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             kernel_width, kernel_height);
}
__DEVICE__ void __bang_avgpool(half* dst,
                               half* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_avg_f16(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_avgpool(float* dst,
                               float* src,
                               int channel,
                               int height,
                               int width,
                               int kernel_height,
                               int kernel_width,
                               int stride_x,
                               int stride_y) {
  __mlvm_stream_pool_avg_f32(dst, src, channel, height, width,
                             kernel_height, kernel_width,
                             stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream avgpool backward operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_avgpool_bp(half* dst,
                                  half* src,
                                  int channel,
                                  int height,
                                  int width,
                                  int kernel_height,
                                  int kernel_width,
                                  int stride_x,
                                  int stride_y) {
  __mlvm_stream_pool_avg_bp_f16(dst, src, channel, height, width,
                                kernel_height, kernel_width,
                                stride_x, stride_y);
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_avgpool_bp(float* dst,
                                  float* src,
                                  int channel,
                                  int height,
                                  int width,
                                  int kernel_height,
                                  int kernel_width,
                                  int stride_x,
                                  int stride_y) {
  __mlvm_stream_pool_avg_bp_f32(dst, src, channel, height, width,
                                kernel_height, kernel_width,
                                stride_x, stride_y);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream histogram operation
// -----------------------------------------------------------------------------
//   | dst-type | src-type | kernel-type | __BANG_ARCH__ |
//   +----------+----------+-------------+---------------+
//   |   int    |   int8   |    int8     |     == 220    |
//   |   int    |   int16  |    int16    |     == 220    |
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ == 220
__DEVICE__ void __bang_histogram(int* dst,
                                 int8* src,
                                 int8* kernel,
                                 int size) {
  __mlvm_stream_histogram_s32_fix8_fix8(dst, src, kernel, size);
}
__DEVICE__ void __bang_histogram(int* dst,
                                 int16* src,
                                 int16* kernel,
                                 int size) {
  __mlvm_stream_histogram_s32_fix16_fix16(dst, src, kernel, size);
}
#endif

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream conv operation
// -----------------------------------------------------------------------------
//   | dst-type | src-type | kernel-type | bias-type | __BANG_ARCH__ |
//   +----------+----------+-------------+-----------+---------------+
//   |   half   |   half   |    half     |   half    |     <  200    |
//   |   half   |   int8   |    int8     |   half    |     >= 100    |
//   |   half   |   int16  |    int16    |   half    |     >= 200    |
//   |   half   |   int16  |    int8     |   half    |     >= 200    |
//   |   float  |   int8   |    int8     |   float   |     >= 200    |
//   |   float  |   int16  |    int8     |   float   |     >= 200    |
//   |   float  |   int16  |    int16    |   float   |     >= 200    |
//   |   int16  |   int8   |    int8     |   int16   |     >= 200    |
//   |   int16  |   int16  |    int8     |   int16   |     >= 200    |
//   |   int16  |   int16  |    int16    |   int16   |     >= 200    |
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_conv(half* dst,
                            int8* src,
                            int8* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f16_fix8_fix8(dst, src, kernel,
                                   channal_input, height, width,
                                   kernel_height, kernel_width,
                                   stride_x, stride_y,
                                   channal_output, fix_position);
}
__DEVICE__ void __bang_conv(half* dst,
                            int8* src,
                            int8* kernel,
                            half* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f16_fix8_fix8_f16(dst, src, kernel, bias,
                                       channal_input, height, width,
                                       kernel_height, kernel_width,
                                       stride_x, stride_y,
                                       channal_output, fix_position);
}
__DEVICE__ void __bang_conv(half* dst,
                            int16* src,
                            int16* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f16_fix16_fix16(dst, src, kernel,
                                     channal_input, height, width,
                                     kernel_height, kernel_width,
                                     stride_x, stride_y,
                                     channal_output, fix_position);
}
__DEVICE__ void __bang_conv(half* dst,
                            int16* src,
                            int16* kernel,
                            half* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f16_fix16_fix16_f16(dst, src, kernel, bias,
                                         channal_input, height, width,
                                         kernel_height, kernel_width,
                                         stride_x, stride_y,
                                         channal_output, fix_position);
}
__DEVICE__ void __bang_conv(half* dst,
                            int16* src,
                            int8* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f16_fix16_fix8(dst, src, kernel,
                                    channal_input, height, width,
                                    kernel_height, kernel_width,
                                    stride_x, stride_y,
                                    channal_output, fix_position);
}
__DEVICE__ void __bang_conv(half* dst,
                            int16* src,
                            int8* kernel,
                            half* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f16_fix16_fix8_f16(dst, src, kernel, bias,
                                        channal_input, height, width,
                                        kernel_height, kernel_width,
                                        stride_x, stride_y,
                                        channal_output, fix_position);
}
__DEVICE__ void __bang_conv(float* dst,
                            int8* src,
                            int8* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f32_fix8_fix8(dst, src, kernel,
                                   channal_input, height, width,
                                   kernel_height, kernel_width,
                                   stride_x, stride_y,
                                   channal_output, fix_position);
}
__DEVICE__ void __bang_conv(float* dst,
                            int8* src,
                            int8* kernel,
                            float* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f32_fix8_fix8_f32(dst, src, kernel, bias,
                                       channal_input, height, width,
                                       kernel_height, kernel_width,
                                       stride_x, stride_y,
                                       channal_output, fix_position);
}
__DEVICE__ void __bang_conv(float* dst,
                            int16* src,
                            int8* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f32_fix16_fix8(dst, src, kernel,
                                    channal_input, height, width,
                                    kernel_height, kernel_width,
                                    stride_x, stride_y,
                                    channal_output, fix_position);
}
__DEVICE__ void __bang_conv(float* dst,
                            int16* src,
                            int8* kernel,
                            float* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f32_fix16_fix8_f32(dst, src, kernel, bias,
                                        channal_input, height, width,
                                        kernel_height, kernel_width,
                                        stride_x, stride_y,
                                        channal_output, fix_position);
}
__DEVICE__ void __bang_conv(float* dst,
                            int16* src,
                            int16* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f32_fix16_fix16(dst, src, kernel,
                                     channal_input, height, width,
                                     kernel_height, kernel_width,
                                     stride_x, stride_y,
                                     channal_output, fix_position);
}
__DEVICE__ void __bang_conv(float* dst,
                            int16* src,
                            int16* kernel,
                            float* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_f32_fix16_fix16_f32(dst, src, kernel, bias,
                                         channal_input, height, width,
                                         kernel_height, kernel_width,
                                         stride_x, stride_y,
                                         channal_output, fix_position);
}
__DEVICE__ void __bang_conv(int16* dst,
                            int8* src,
                            int8* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_fix16_fix8_fix8(dst, src, kernel,
                                     channal_input, height, width,
                                     kernel_height, kernel_width,
                                     stride_x, stride_y,
                                     channal_output, fix_position);
}
__DEVICE__ void __bang_conv(int16* dst,
                            int8* src,
                            int8* kernel,
                            int16* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_fix16_fix8_fix8_fix16(dst, src, kernel, bias,
                                           channal_input, height, width,
                                           kernel_height, kernel_width,
                                           stride_x, stride_y,
                                           channal_output, fix_position);
}
__DEVICE__ void __bang_conv(int16* dst,
                            int16* src,
                            int8* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_fix16_fix16_fix8(dst, src, kernel,
                                      channal_input, height, width,
                                      kernel_height, kernel_width,
                                      stride_x, stride_y,
                                      channal_output, fix_position);
}
__DEVICE__ void __bang_conv(int16* dst,
                            int16* src,
                            int8* kernel,
                            int16* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_fix16_fix16_fix8_fix16(dst, src, kernel, bias,
                                            channal_input, height, width,
                                            kernel_height, kernel_width,
                                            stride_x, stride_y,
                                            channal_output, fix_position);
}
__DEVICE__ void __bang_conv(int16* dst,
                            int16* src,
                            int16* kernel,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_fix16_fix16_fix16(dst, src, kernel,
                                       channal_input, height, width,
                                       kernel_height, kernel_width,
                                       stride_x, stride_y,
                                       channal_output, fix_position);
}
__DEVICE__ void __bang_conv(int16* dst,
                            int16* src,
                            int16* kernel,
                            int16* bias,
                            const int channal_input,
                            const int height,
                            const int width,
                            const int kernel_height,
                            const int kernel_width,
                            const int stride_x,
                            const int stride_y,
                            const int channal_output,
                            int fix_position) {
  __mlvm_stream_conv_fix16_fix16_fix16_fix16(dst, src, kernel, bias,
                                             channal_input, height, width,
                                             kernel_height, kernel_width,
                                             stride_x, stride_y,
                                             channal_output, fix_position);
}

#else  // __BANG_ARCH__ < 200

#define __conv_f16(dst, src, kernel,                              \
                   channal_input, height, width,                  \
                   kernel_height, kernel_width,                   \
                   stride_x, stride_y, channal_output)            \
  ({ __mlvm_stream_conv_f16_f16_f16(dst, src, kernel,             \
                                    channal_input, height, width, \
                                    kernel_height, kernel_width,  \
                                    stride_x, stride_y,           \
                                    channal_output);              \
  })

#define __conv_type(dst, src, kernel,                             \
                    channal_input, height, width,                 \
                    kernel_height, kernel_width,                  \
                    stride_x, stride_y, channal_output,           \
                    Type, fix_position)                           \
  __conv_##Type(dst, src, kernel, channal_input, height, width,   \
                kernel_height, kernel_width, stride_x, stride_y,  \
                channal_output, fix_position)

#define __conv_F16_F16_F16(dst, src, kernel,                      \
                           channal_input, height, width,          \
                           kernel_height, kernel_width,           \
                           stride_x, stride_y,                    \
                           channal_output, fix_position)          \
  ({ __mlvm_stream_conv_f16_f16_f16(dst, src, kernel,             \
                                    channal_input, height, width, \
                                    kernel_height, kernel_width,  \
                                    stride_x, stride_y,           \
                                    channal_output);              \
  })

#define __conv_F16_FIX16_FIX16(dst, src, kernel,                        \
                               channal_input, height, width,            \
                               kernel_height, kernel_width,             \
                               stride_x, stride_y,                      \
                               channal_output, fix_position)            \
  ({ __mlvm_stream_conv_f16_fix16_fix16(dst, src, kernel,               \
                                        channal_input, height, width,   \
                                        kernel_height, kernel_width,    \
                                        stride_x, stride_y,             \
                                        channal_output, fix_position);  \
  })

#define __conv_F16_INT16_INT16(dst, src, kernel,                      \
                               channal_input, height, width,          \
                               kernel_height, kernel_width,           \
                               stride_x, stride_y,                    \
                               channal_output, fix_position)          \
  ({ __mlvm_stream_conv_f16_fix16_fix16(dst, src, kernel,             \
                                        channal_input, height, width, \
                                        kernel_height, kernel_width,  \
                                        stride_x, stride_y,           \
                                        channal_output,               \
                                        fix_position);                \
  })

#define __conv_F16_FIX8_FIX8(dst, src, kernel,                        \
                             channal_input, height, width,            \
                             kernel_height, kernel_width,             \
                             stride_x, stride_y,                      \
                             channal_output, fix_position)            \
  ({ __mlvm_stream_conv_f16_fix8_fix8(dst, src, kernel,               \
                                      channal_input, height, width,   \
                                      kernel_height, kernel_width,    \
                                      stride_x, stride_y,             \
                                      channal_output, fix_position);  \
  })

#define __conv_F16_INT8_INT8(dst, src, kernel,                        \
                             channal_input, height, width,            \
                             kernel_height, kernel_width,             \
                             stride_x, stride_y,                      \
                             channal_output, fix_position)            \
  ({ __mlvm_stream_conv_f16_fix8_fix8(dst, src, kernel,               \
                                      channal_input, height, width,   \
                                      kernel_height, kernel_width,    \
                                      stride_x, stride_y,             \
                                      channal_output, fix_position);  \
  })

#define CONV_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, NAME, ...) NAME  // NOLINT

#define __bang_conv(...) CONV_MACRO(__VA_ARGS__,                  \
                                    __conv_type,                  \
                                    __conv_type,                  \
                                    __conv_f16, ...)(__VA_ARGS__)
#endif  // __BANG_ARCH__ >= 200

typedef enum {
  F16_FIX8_FIX8 = 0,
  F16_INT8_INT8 = 0,
  F16_FIX16_FIX16 = 1,
  F16_INT16_INT16 = 1,
} ConvDataType_t;

typedef enum {
  F16_FIX8_F16_FIX8 = 0,
  F16_INT8_F16_INT8,
  F16_FIX16_F16_FIX16,
} MlpDateType_t;

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream mlp operation
// -----------------------------------------------------------------------------
//   | dst-type | src-type | bias-type | kernel-type | __BANG_ARCH__ |
//   +----------+----------+-----------+-------------+---------------+
//   |   half   |   half   |    half   |    half     |     <  200    |
//   |   half   |   int8   |    half   |    int8     |     >= 100    |
//   |   half   |   int16  |    half   |    int16    |     >= 200    |
//   |   half   |   int16  |    half   |    int8     |     >= 200    |
//   |   float  |   int8   |    float  |    int8     |     >= 200    |
//   |   float  |   int16  |    float  |    int8     |     >= 200    |
//   |   float  |   int16  |    float  |    int16    |     >= 200    |
//   |   int16  |   int8   |    int16  |    int8     |     >= 200    |
//   |   int16  |   int16  |    int16  |    int8     |     >= 200    |
//   |   int16  |   int16  |    int16  |    int16    |     >= 200    |
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_mlp(half* dst,
                           int8* src,
                           half* bias,
                           int8* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_f16_fix8_f16_fix8(dst, src, bias, weight,
                                      height, width, fix_position);
}
__DEVICE__ void __bang_mlp(half* dst,
                           int16* src,
                           half* bias,
                           int16* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_f16_fix16_f16_fix16(dst, src, bias, weight,
                                        height, width, fix_position);
}
__DEVICE__ void __bang_mlp(half* dst,
                           int16* src,
                           half* bias,
                           int8* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_f16_fix16_f16_fix8(dst, src, bias, weight,
                                       height, width, fix_position);
}
__DEVICE__ void __bang_mlp(float* dst,
                           int8* src,
                           float* bias,
                           int8* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_f32_fix8_f32_fix8(dst, src, bias, weight,
                                      height, width, fix_position);
}
__DEVICE__ void __bang_mlp(float* dst,
                           int16* src,
                           float* bias,
                           int8* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_f32_fix16_f32_fix8(dst, src, bias, weight,
                                       height, width, fix_position);
}
__DEVICE__ void __bang_mlp(float* dst,
                           int16* src,
                           float* bias,
                           int16* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_f32_fix16_f32_fix16(dst, src, bias, weight,
                                        height, width, fix_position);
}
__DEVICE__ void __bang_mlp(int16* dst,
                           int8* src,
                           int16* bias,
                           int8* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_fix16_fix8_fix16_fix8(dst, src, bias, weight,
                                          height, width, fix_position);
}
__DEVICE__ void __bang_mlp(int16* dst,
                           int16* src,
                           int16* bias,
                           int8* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_fix16_fix16_fix16_fix8(dst, src, bias, weight,
                                           height, width, fix_position);
}
__DEVICE__ void __bang_mlp(int16* dst,
                           int16* src,
                           int16* bias,
                           int16* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __mlvm_stream_mlp_fix16_fix16_fix16_fix16(dst, src, bias, weight,
                                            height, width, fix_position);
}


#else  // __BANG_ARCH__ < 200

#define __mlp_f16(dst, src, bias, weight, height, width)                \
  ({ __mlvm_stream_mlp_f16_f16_f16_f16(dst, src, bias, weight, height, width); })  // NOLINT

#define __mlp_type(dst, src, bias, weight, height, width,           \
                   Type, fix_position)                              \
  __mlp_##Type(dst, src, bias, weight, height, width, fix_position)

#define __mlp_F16_F16_F16_F16(dst, src, bias, weight,                   \
                              height, width, fix_position)              \
  ({ __mlvm_stream_mlp_f16_f16_f16_f16(dst, src, bias, weight, height, width); })  // NOLINT

#define __mlp_F16_FIX16_F16_FIX16(dst, src, bias, weight,               \
                                  height, width, fix_position)          \
  ({ __mlvm_stream_mlp_f16_fix16_f16_fix16(dst, src, bias, weight,      \
                                           height, width, fix_position); \
  })

#define __mlp_F16_FIX8_F16_FIX8(dst, src, bias, weight,                 \
                                height, width, fix_position)            \
  ({ __mlvm_stream_mlp_f16_fix8_f16_fix8(dst, src, bias, weight,        \
                                         height, width, fix_position);  \
  })

#define __mlp_F16_INT8_F16_INT8(dst, src, bias, weight,                 \
                                height, width, fix_position)            \
  ({ __mlvm_stream_mlp_f16_fix8_f16_fix8(dst, src, bias, weight,        \
                                         height, width, fix_position);  \
  })

#define MLP_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define __bang_mlp(...) MLP_MACRO(__VA_ARGS__,                  \
                                  __mlp_type,                   \
                                  __mlp_type,                   \
                                  __mlp_f16, ...)(__VA_ARGS__)
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar convert half to int operation
// -----------------------------------------------------------------------------
__DEVICE__ int __half2int_tz(half a) {
  return __mlvm_scalar_cvti32_f16_tz(a);
}
__DEVICE__ int __half2int_oz(half a) {
  return __mlvm_scalar_cvti32_f16_oz(a);
}
__DEVICE__ int __half2int_up(half a) {
  return __mlvm_scalar_cvti32_f16_up(a);
}
__DEVICE__ int __half2int_dn(half a) {
  return __mlvm_scalar_cvti32_f16_dn(a);
}
__DEVICE__ int __half2int_rd(half a) {
  return __mlvm_scalar_cvti32_f16_rd(a);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar convert half to short operation
// -----------------------------------------------------------------------------
__DEVICE__ short __half2short_tz(half a) {
  return __mlvm_scalar_cvti16_f16_tz(a);
}
__DEVICE__ short __half2short_oz(half a) {
  return __mlvm_scalar_cvti16_f16_oz(a);
}
__DEVICE__ short __half2short_up(half a) {
  return __mlvm_scalar_cvti16_f16_up(a);
}
__DEVICE__ short __half2short_dn(half a) {
  return __mlvm_scalar_cvti16_f16_dn(a);
}
__DEVICE__ short __half2short_rd(half a) {
  return __mlvm_scalar_cvti16_f16_rd(a);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar convert float to int operation
// -----------------------------------------------------------------------------
__DEVICE__ int __float2int_tz(float a) {
  return __mlvm_scalar_cvti32_f32_tz(a);
}
__DEVICE__ int __float2int_oz(float a) {
  return __mlvm_scalar_cvti32_f32_oz(a);
}
__DEVICE__ int __float2int_up(float a) {
  return __mlvm_scalar_cvti32_f32_up(a);
}
__DEVICE__ int __float2int_dn(float a) {
  return __mlvm_scalar_cvti32_f32_dn(a);
}
__DEVICE__ int __float2int_rd(float a) {
  return __mlvm_scalar_cvti32_f32_rd(a);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar convert float to short operation
// -----------------------------------------------------------------------------
__DEVICE__ short __float2short_tz(float a) {
  return __mlvm_scalar_cvti16_f32_tz(a);
}
__DEVICE__ short __float2short_oz(float a) {
  return __mlvm_scalar_cvti16_f32_oz(a);
}
__DEVICE__ short __float2short_up(float a) {
  return __mlvm_scalar_cvti16_f32_up(a);
}
__DEVICE__ short __float2short_dn(float a) {
  return __mlvm_scalar_cvti16_f32_dn(a);
}
__DEVICE__ short __float2short_rd(float a) {
  return __mlvm_scalar_cvti16_f32_rd(a);
}
__DEVICE__ half __float2half_tz(float a) {
  return __mlvm_scalar_cvtf16_f32_tz(a);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar convert float to half operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ half __float2half_oz(float a) {
  return __mlvm_scalar_cvtf16_f32_oz(a);
}
__DEVICE__ half __float2half_up(float a) {
  return __mlvm_scalar_cvtf16_f32_up(a);
}
__DEVICE__ half __float2half_dn(float a) {
  return __mlvm_scalar_cvtf16_f32_dn(a);
}
__DEVICE__ half __float2half_rd(float a) {
  return __mlvm_scalar_cvtf16_f32_rd(a);
}
#endif  // __BANG_ARCH__ >= 200

#define STREAM_CVT_FIX8(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define STREAM_CVT_OTHERS(_1, _2, _3, _4, _5, _6, NAME, ...) NAME

#define __bang_fix82half(...)                                   \
  STREAM_CVT_FIX8(__VA_ARGS__,                                  \
                  __mlvm_stream_cvtf16_fix8_stride,             \
                  __mlvm_stream_cvtf16_fix8_stride,             \
                  __mlvm_stream_cvtf16_fix8_stride,             \
                  __mlvm_stream_cvtf16_fix8, ...)(__VA_ARGS__)
#ifndef __bang_fix82half
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert fix8 to half operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_fix82half(half* dst,
                                 fix8* src,
                                 int src_count,
                                 int fix_position) {
  __mlvm_stream_cvtf16_fix8(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_fix82half(half* dst,
                                 fix8* src,
                                 int src_count,
                                 int fix_position,
                                 int dst_stride,
                                 int src_stride,
                                 int count) {
  __mlvm_stream_cvtf16_fix8_stride(dst, src, src_count, fix_position,
                                   dst_stride, src_stride, count);
}
#endif

#define __bang_int82half(...)                                   \
  STREAM_CVT_FIX8(__VA_ARGS__,                                  \
                  __mlvm_stream_cvtf16_fix8_stride,             \
                  __mlvm_stream_cvtf16_fix8_stride,             \
                  __mlvm_stream_cvtf16_fix8_stride,             \
                  __mlvm_stream_cvtf16_fix8, ...)(__VA_ARGS__)
#ifndef __bang_int82half
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert int8 to half operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_int82half(half* dst,
                                 int8* src,
                                 int src_count,
                                 int fix_position) {
  __mlvm_stream_cvtf16_fix8(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_int82half(half* dst,
                                 int8* src,
                                 int src_count,
                                 int fix_position,
                                 int dst_stride,
                                 int src_stride,
                                 int count) {
  __mlvm_stream_cvtf16_fix8_stride(dst, src, src_count, fix_position,
                                   dst_stride, src_stride, count);
}
#endif
#define __bang_fix82half __bang_int82half

#define __bang_uchar2half(...)                                  \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                \
                    __mlvm_stream_cvtf16_u8_stride,             \
                    __mlvm_stream_cvtf16_u8_stride,             \
                    __mlvm_stream_cvtf16_u8_stride,             \
                    __mlvm_stream_cvtf16_u8, ...)(__VA_ARGS__)
#ifndef __bang_uchar2half
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert uchar to half operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_uchar2half(half* dst,
                                  unsigned char* src,
                                  int src_count) {
  __mlvm_stream_cvtf16_u8(dst, src, src_count);
}
__DEVICE__ void __bang_uchar2half(half* dst,
                                  unsigned char* src,
                                  int src_count,
                                  int fix_position,
                                  int dst_stride,
                                  int src_stride,
                                  int count) {
  __mlvm_stream_cvtf16_u8_stride(dst, src, src_count,
                                 dst_stride, src_stride, count);
}
#endif

#define __bang_short2half(...)                                    \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                  \
                    __mlvm_stream_cvtf16_i16_stride,              \
                    __mlvm_stream_cvtf16_i16_stride,              \
                    __mlvm_stream_cvtf16_i16_stride,              \
                    __mlvm_stream_cvtf16_i16, ...)(__VA_ARGS__)
#ifndef __bang_short2half
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert short to half operation
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_short2half(half* dst,
                                  short* src,
                                  int src_count) {
  __mlvm_stream_cvtf16_i16(dst, src, src_count);
}
__DEVICE__ void __bang_short2half(half* dst,
                                  short*src,
                                  int src_count,
                                  int dst_stride,
                                  int src_stride,
                                  int count) {
  __mlvm_stream_cvtf16_i16_stride(dst, src, src_count,
                                  dst_stride, src_stride, count);
}
#endif

#define __bang_float2half_tz(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvtf16_f32_tz_stride,             \
                    __mlvm_stream_cvtf16_f32_tz_stride,             \
                    __mlvm_stream_cvtf16_f32_tz_stride,             \
                    __mlvm_stream_cvtf16_f32_tz, ...)(__VA_ARGS__)
#ifndef __bang_float2half_tz
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to half (round to zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2half_tz(half* dst,
                                     float* src,
                                     int src_count) {
  __mlvm_stream_cvtf16_f32_tz(dst, src, src_count);
}
__DEVICE__ void __bang_float2half_tz(half* dst,
                                     float* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvtf16_f32_stride_tz(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif


#define __bang_float2half_dn(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvtf16_f32_dn_stride,             \
                    __mlvm_stream_cvtf16_f32_dn_stride,             \
                    __mlvm_stream_cvtf16_f32_dn_stride,             \
                    __mlvm_stream_cvtf16_f32_dn, ...)(__VA_ARGS__)
#ifndef __bang_float2half_dn
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to half (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2half_dn(half* dst,
                                     float* src,
                                     int src_count) {
  __mlvm_stream_cvtf16_f32_dn(dst, src, src_count);
}
__DEVICE__ void __bang_float2half_dn(half* dst,
                                     float* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvtf16_f32_stride_dn(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_float2half_oz(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvtf16_f32_oz_stride,             \
                    __mlvm_stream_cvtf16_f32_oz_stride,             \
                    __mlvm_stream_cvtf16_f32_oz_stride,             \
                    __mlvm_stream_cvtf16_f32_oz, ...)(__VA_ARGS__)
#ifndef __bang_float2half_oz
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to half (round off zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2half_oz(half* dst,
                                     float* src,
                                     int src_count) {
  __mlvm_stream_cvtf16_f32_oz(dst, src, src_count);
}
__DEVICE__ void __bang_float2half_oz(half* dst,
                                     float* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvtf16_f32_stride_oz(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_float2half_up(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvtf16_f32_up_stride,             \
                    __mlvm_stream_cvtf16_f32_up_stride,             \
                    __mlvm_stream_cvtf16_f32_up_stride,             \
                    __mlvm_stream_cvtf16_f32_up, ...)(__VA_ARGS__)
#ifndef __bang_float2half_up
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to half (round up)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2half_up(half* dst,
                                     float* src,
                                     int src_count) {
  __mlvm_stream_cvtf16_f32_up(dst, src, src_count);
}
__DEVICE__ void __bang_float2half_up(half* dst,
                                     float* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvtf16_f32_stride_up(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_float2half_rd(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvtf16_f32_rd_stride,             \
                    __mlvm_stream_cvtf16_f32_rd_stride,             \
                    __mlvm_stream_cvtf16_f32_rd_stride,             \
                    __mlvm_stream_cvtf16_f32_rd, ...)(__VA_ARGS__)
#ifndef __bang_float2half_rd
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to half (middle round)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2half_rd(half* dst,
                                     float* src,
                                     int src_count) {
  __mlvm_stream_cvtf16_f32_rd(dst, src, src_count);
}
__DEVICE__ void __bang_float2half_rd(half* dst,
                                     float* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvtf16_f32_stride_rd(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int16 (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2int16_dn(int16* dst,
                                     half* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix16_f16_dn(dst, src, src_count, fix_position);
}
#define __bang_half2fix16_dn __bang_half2int16_dn

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int16 (round to zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2int16_tz(int16* dst,
                                     half* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix16_f16_tz(dst, src, src_count, fix_position);
}
#define __bang_half2fix16_tz __bang_half2int16_tz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int16 (round off zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2int16_oz(int16* dst,
                                     half* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix16_f16_oz(dst, src, src_count, fix_position);
}
#define __bang_half2fix16_oz __bang_half2int16_oz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int16 (round up)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2int16_up(int16* dst,
                                     half* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix16_f16_up(dst, src, src_count, fix_position);
}
#define __bang_half2fix16_up __bang_half2int16_up

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int16 (middle round)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2int16_rd(int16* dst,
                                     half* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix16_f16_rd(dst, src, src_count, fix_position);
}
#define __bang_half2fix16_rd __bang_half2int16_rd

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert int16 to half
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_int162half(half* dst,
                                  int16* src,
                                  int src_count,
                                  int fix_position) {
  __mlvm_stream_cvtf16_fix16(dst, src, src_count, fix_position);
}
#define __bang_fix162half __bang_int162half

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int16 (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int16_dn(int16* dst,
                                      float* src,
                                      int src_count,
                                      int fix_position) {
  __mlvm_stream_cvtfix16_f32_dn(dst, src, src_count, fix_position);
}
#define __bang_float2fix16_dn __bang_float2int16_dn

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int16 (round to zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int16_tz(int16* dst,
                                      float* src,
                                      int src_count,
                                      int fix_position) {
  __mlvm_stream_cvtfix16_f32_tz(dst, src, src_count, fix_position);
}
#define __bang_float2fix16_tz __bang_float2int16_tz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int16 (round off zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int16_oz(int16* dst,
                                      float* src,
                                      int src_count,
                                      int fix_position) {
  __mlvm_stream_cvtfix16_f32_oz(dst, src, src_count, fix_position);
}
#define __bang_float2fix16_oz __bang_float2int16_oz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int16 (round up)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int16_up(int16* dst,
                                      float* src,
                                      int src_count,
                                      int fix_position) {
  __mlvm_stream_cvtfix16_f32_up(dst, src, src_count, fix_position);
}
#define __bang_float2fix16_up __bang_float2int16_up

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int16 (middle round)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int16_rd(int16* dst,
                                      float* src,
                                      int src_count,
                                      int fix_position) {
  __mlvm_stream_cvtfix16_f32_rd(dst, src, src_count, fix_position);
}
#define __bang_float2fix16_rd __bang_float2int16_rd

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert int16 to float
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_int162float(float* dst,
                                   int16* src,
                                   int src_count,
                                   int fix_position) {
  __mlvm_stream_cvtf32_fix16(dst, src, src_count, fix_position);
}
#define __bang_fix162float __bang_int162float

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int8 (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int8_dn(int8* dst,
                                     float* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix8_f32_dn(dst, src, src_count, fix_position);
}
#define __bang_float2fix8_dn __bang_float2int8_dn

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int8 (round to zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int8_tz(int8* dst,
                                     float* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix8_f32_tz(dst, src, src_count, fix_position);
}
#define __bang_float2fix8_tz __bang_float2int8_tz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int8 (round off zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int8_oz(int8* dst,
                                     float* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix8_f32_oz(dst, src, src_count, fix_position);
}
#define __bang_float2fix8_oz __bang_float2int8_oz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int8 (round up)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int8_up(int8* dst,
                                     float* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix8_f32_up(dst, src, src_count, fix_position);
}
#define __bang_float2fix8_up __bang_float2int8_up

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert float to int8 (middle round)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_float2int8_rd(int8* dst,
                                     float* src,
                                     int src_count,
                                     int fix_position) {
  __mlvm_stream_cvtfix8_f32_rd(dst, src, src_count, fix_position);
}
#define __bang_float2fix8_rd __bang_float2int8_rd

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert int8 to float
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_int82float(float* dst,
                                  int8* src,
                                  int src_count,
                                  int fix_position) {
  __mlvm_stream_cvtf32_fix8(dst, src, src_count, fix_position);
}
#define __bang_fix82float __bang_int82float


// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int8 (round down)
// -----------------------------------------------------------------------------
#define __bang_half2int8_dn(...)                                  \
  STREAM_CVT_FIX8(__VA_ARGS__,                                    \
                  __mlvm_stream_cvtfix8_f16_dn_stride,            \
                  __mlvm_stream_cvtfix8_f16_dn_stride,            \
                  __mlvm_stream_cvtfix8_f16_dn_stride,            \
                  __mlvm_stream_cvtfix8_f16_dn, ...)(__VA_ARGS__)
#ifndef __bang_half2int8_dn
__DEVICE__ void __bang_half2int8_dn(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position) {
  __mlvm_stream_cvtfix8_f16_dn(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_half2int8_dn(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position,
                                    int dst_stride,
                                    int src_stride,
                                    int count) {
  __mlvm_stream_cvtfix8_f16_dn_stride(dst, src, src_count, fix_position,
                                      dst_stride, src_stride, count);

}
#endif
#define __bang_half2fix8_dn __bang_half2int8_dn

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int8 (round to zero)
// -----------------------------------------------------------------------------
#define __bang_half2int8_tz(...)                                  \
  STREAM_CVT_FIX8(__VA_ARGS__,                                    \
                  __mlvm_stream_cvtfix8_f16_tz_stride,            \
                  __mlvm_stream_cvtfix8_f16_tz_stride,            \
                  __mlvm_stream_cvtfix8_f16_tz_stride,            \
                  __mlvm_stream_cvtfix8_f16_tz, ...)(__VA_ARGS__)
#ifndef __bang_half2int8_tz
__DEVICE__ void __bang_half2int8_tz(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position) {
  __mlvm_stream_cvtfix8_f16_tz(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_half2int8_tz(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position,
                                    int dst_stride,
                                    int src_stride,
                                    int count) {
  __mlvm_stream_cvtfix8_f16_tz_stride(dst, src, src_count, fix_position,
                                      dst_stride, src_stride, count);
}
#endif
#define __bang_half2fix8_tz __bang_half2int8_tz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int8 (round off zero)
// -----------------------------------------------------------------------------
#define __bang_half2int8_oz(...)                                  \
  STREAM_CVT_FIX8(__VA_ARGS__,                                    \
                  __mlvm_stream_cvtfix8_f16_oz_stride,            \
                  __mlvm_stream_cvtfix8_f16_oz_stride,            \
                  __mlvm_stream_cvtfix8_f16_oz_stride,            \
                  __mlvm_stream_cvtfix8_f16_oz, ...)(__VA_ARGS__)
#ifndef __bang_half2int8_oz
__DEVICE__ void __bang_half2int8_oz(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position) {
  __mlvm_stream_cvtfix8_f16_oz(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_half2int8_oz(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position,
                                    int dst_stride,
                                    int src_stride,
                                    int count) {
  __mlvm_stream_cvtfix8_f16_oz_stride(dst, src, src_count, fix_position,
                                      dst_stride, src_stride, count);
}
#endif
#define __bang_half2fix8_oz __bang_half2int8_oz

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int8 (round up)
// -----------------------------------------------------------------------------
#define __bang_half2int8_up(...)                                  \
  STREAM_CVT_FIX8(__VA_ARGS__,                                    \
                  __mlvm_stream_cvtfix8_f16_up_stride,            \
                  __mlvm_stream_cvtfix8_f16_up_stride,            \
                  __mlvm_stream_cvtfix8_f16_up_stride,            \
                  __mlvm_stream_cvtfix8_f16_up, ...)(__VA_ARGS__)
#ifndef __bang_half2int8_up
__DEVICE__ void __bang_half2int8_up(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position) {
  __mlvm_stream_cvtfix8_f16_up(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_half2int8_up(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position,
                                    int dst_stride,
                                    int src_stride,
                                    int count) {
  __mlvm_stream_cvtfix8_f16_up_stride(dst, src, src_count, fix_position,
                                      dst_stride, src_stride, count);
}
#endif
#define __bang_half2fix8_up __bang_half2int8_up

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to int8 (middle round)
// -----------------------------------------------------------------------------
#define __bang_half2int8_rd(...)                                  \
  STREAM_CVT_FIX8(__VA_ARGS__,                                    \
                  __mlvm_stream_cvtfix8_f16_rd_stride,            \
                  __mlvm_stream_cvtfix8_f16_rd_stride,            \
                  __mlvm_stream_cvtfix8_f16_rd_stride,            \
                  __mlvm_stream_cvtfix8_f16_rd, ...)(__VA_ARGS__)
#ifndef __bang_half2int8_rd
__DEVICE__ void __bang_half2int8_rd(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position) {
  __mlvm_stream_cvtfix8_f16_rd(dst, src, src_count, fix_position);
}
__DEVICE__ void __bang_half2int8_rd(int8* dst,
                                    half* src,
                                    int src_count,
                                    int fix_position,
                                    int dst_stride,
                                    int src_stride,
                                    int count) {
  __mlvm_stream_cvtfix8_f16_rd_stride(dst, src, src_count, fix_position,
                                      dst_stride, src_stride, count);
}
#endif
#define __bang_half2fix8_rd __bang_half2int8_rd

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to uchar (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2uchar_dn(unsigned char* dst,
                                     half* src,
                                     half* src_addition,
                                     int src_count) {
  __mlvm_memset_nram_f16((half*)dst, 64, 128);
  __mlvm_stream_cycle_ge_f16(src_addition, src, (half *)dst, src_count, 64);
  __mlvm_stream_mul_const_f16(src_addition, src_addition, 256, src_count);
  __mlvm_stream_sub_f16(src_addition, src, src_addition, src_count);
  __mlvm_stream_cvtfix8_f16_dn((int8 *)dst, src_addition, src_count, 0);
}

__DEVICE__ void __bang_half2uchar_dn(signed char* dst,
                                     half* src,
                                     int src_count) {
  __mlvm_stream_cvtfix8_f16_dn(dst, src, src_count, 0);
}

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to char (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2char_dn(signed char* dst,
                                    half* src,
                                    int src_count) {
  __mlvm_stream_cvtfix8_f16_dn(dst, src, src_count, 0);
}

#define __bang_half2short_dn(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvti16_f16_dn_stride,             \
                    __mlvm_stream_cvti16_f16_dn_stride,             \
                    __mlvm_stream_cvti16_f16_dn_stride,             \
                    __mlvm_stream_cvti16_f16_dn, ...)(__VA_ARGS__)
#ifndef __bang_half2short_dn
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to short (round down)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2short_dn(short* dst,
                                     half* src,
                                     int src_count) {
  __mlvm_stream_cvti16_f16_dn(dst, src, src_count);
}
__DEVICE__ void __bang_half2short_dn(short* dst,
                                     half* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvti16_f16_dn_stride(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif


#define __bang_half2short_tz(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvti16_f16_tz_stride,             \
                    __mlvm_stream_cvti16_f16_tz_stride,             \
                    __mlvm_stream_cvti16_f16_tz_stride,             \
                    __mlvm_stream_cvti16_f16_tz, ...)(__VA_ARGS__)
#ifndef __bang_half2short_tz
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to short (round to zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2short_tz(short* dst,
                                     half* src,
                                     int src_count) {
  __mlvm_stream_cvti16_f16_tz(dst, src, src_count);
}
__DEVICE__ void __bang_half2short_tz(short* dst,
                                     half* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvti16_f16_tz_stride(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_half2short_oz(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvti16_f16_oz_stride,             \
                    __mlvm_stream_cvti16_f16_oz_stride,             \
                    __mlvm_stream_cvti16_f16_oz_stride,             \
                    __mlvm_stream_cvti16_f16_oz, ...)(__VA_ARGS__)
#ifndef __bang_half2short_oz
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to short (round off zero)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2short_oz(short* dst,
                                     half* src,
                                     int src_count) {
  __mlvm_stream_cvti16_f16_oz(dst, src, src_count);
}
__DEVICE__ void __bang_half2short_oz(short* dst,
                                     half* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvti16_f16_oz_stride(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_half2short_up(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvti16_f16_up_stride,             \
                    __mlvm_stream_cvti16_f16_up_stride,             \
                    __mlvm_stream_cvti16_f16_up_stride,             \
                    __mlvm_stream_cvti16_f16_up, ...)(__VA_ARGS__)
#ifndef __bang_half2short_up
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to short (round up)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2short_up(short* dst,
                                     half* src,
                                     int src_count) {
  __mlvm_stream_cvti16_f16_up(dst, src, src_count);
}
__DEVICE__ void __bang_half2short_up(short* dst,
                                     half* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvti16_f16_up_stride(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_half2short_rd(...)                                   \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                    \
                    __mlvm_stream_cvti16_f16_rd_stride,             \
                    __mlvm_stream_cvti16_f16_rd_stride,             \
                    __mlvm_stream_cvti16_f16_rd_stride,             \
                    __mlvm_stream_cvti16_f16_rd, ...)(__VA_ARGS__)
#ifndef __bang_half2short_rd
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to short (middle round)
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2short_rd(short* dst,
                                     half* src,
                                     int src_count) {
  __mlvm_stream_cvti16_f16_rd(dst, src, src_count);
}
__DEVICE__ void __bang_half2short_rd(short* dst,
                                     half* src,
                                     int src_count,
                                     int dst_stride,
                                     int src_stride,
                                     int count) {
  __mlvm_stream_cvti16_f16_rd_stride(dst, src, src_count,
                                     dst_stride, src_stride, count);
}
#endif

#define __bang_half2float(...)                                    \
  STREAM_CVT_OTHERS(__VA_ARGS__,                                  \
                    __mlvm_stream_cvtf32_f16_stride,              \
                    __mlvm_stream_cvtf32_f16_stride,              \
                    __mlvm_stream_cvtf32_f16_stride,              \
                    __mlvm_stream_cvtf32_f16, ...)(__VA_ARGS__)
#ifndef __bang_half2float
// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream convert half to float
// -----------------------------------------------------------------------------
__DEVICE__ void __bang_half2float(float* dst,
                                  half* src,
                                  int src_count) {
  __mlvm_stream_cvtf32_f16(dst, src, src_count);
}
__DEVICE__ void __bang_half2float(float* dst,
                                  half* src,
                                  int src_count,
                                  int dst_stride,
                                  int src_stride,
                                  int count) {
  __mlvm_stream_cvtf32_f16_stride(dst, src, src_count,
                                  dst_stride, src_stride, count);
}
#endif

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic add operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_add(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_add_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_add(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_add_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_add(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_add_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_add(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_add_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_add(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_add_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_add(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_add_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic increase operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_inc(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_inc_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_inc(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_inc_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_inc(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_inc_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_inc(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_inc_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_inc(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_inc_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_inc(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_inc_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic decrease operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_dec(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_dec_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_dec(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_dec_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_dec(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_dec_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_dec(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_dec_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_dec(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_dec_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_dec(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_dec_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic max operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_max(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_max_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_max(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_max_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_max(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_max_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_max(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_max_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_max(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_max_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_max(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_max_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic min operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_min(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_min_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_min(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_min_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_min(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_min_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_min(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_min_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_min(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_min_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_min(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_min_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic and operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_and(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_and_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_and(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_and_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_and(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_and_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_and(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_and_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_and(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_and_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_and(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_and_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic or operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_or(unsigned short* dst,
                                 unsigned short* src1,
                                 unsigned short src2) {
  __mlvm_scalar_atom_or_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_or(short* dst,
                                 short* src1,
                                 short src2) {
  __mlvm_scalar_atom_or_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_or(unsigned int* dst,
                                 unsigned int* src1,
                                 unsigned int src2) {
  __mlvm_scalar_atom_or_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_or(int* dst,
                                 int* src1,
                                 int src2) {
  __mlvm_scalar_atom_or_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_or(half* dst,
                                 half* src1,
                                 half src2) {
  __mlvm_scalar_atom_or_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_or(float* dst,
                                 float* src1,
                                 float src2) {
  __mlvm_scalar_atom_or_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic xor operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_xor(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2) {
  __mlvm_scalar_atom_xor_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_xor(short* dst,
                                  short* src1,
                                  short src2) {
  __mlvm_scalar_atom_xor_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_xor(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2) {
  __mlvm_scalar_atom_xor_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_xor(int* dst,
                                  int* src1,
                                  int src2) {
  __mlvm_scalar_atom_xor_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_xor(half* dst,
                                  half* src1,
                                  half src2) {
  __mlvm_scalar_atom_xor_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_xor(float* dst,
                                  float* src1,
                                  float src2) {
  __mlvm_scalar_atom_xor_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic compare-and-swap operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_cas(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short src2,
                                  unsigned short src3) {
  __mlvm_scalar_atom_cas_u16(dst, src1, src2, src3);
}
__DEVICE__ void __bang_atomic_cas(short* dst,
                                  short* src1,
                                  short src2,
                                  short src3) {
  __mlvm_scalar_atom_cas_s16(dst, src1, src2, src3);
}
__DEVICE__ void __bang_atomic_cas(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int src2,
                                  unsigned int src3) {
  __mlvm_scalar_atom_cas_u32(dst, src1, src2, src3);
}
__DEVICE__ void __bang_atomic_cas(int* dst,
                                  int* src1,
                                  int src2,
                                  int src3) {
  __mlvm_scalar_atom_cas_s32(dst, src1, src2, src3);
}
__DEVICE__ void __bang_atomic_cas(half* dst,
                                  half* src1,
                                  half src2,
                                  half src3) {
  __mlvm_scalar_atom_cas_f16(dst, src1, src2, src3);
}
__DEVICE__ void __bang_atomic_cas(float* dst,
                                  float* src1,
                                  float src2,
                                  float src3) {
  __mlvm_scalar_atom_cas_f32(dst, src1, src2, src3);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: scalar atomic exchange operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_exch(unsigned short* dst,
                                   unsigned short* src1,
                                   unsigned short src2) {
  __mlvm_scalar_atom_exch_u16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_exch(short* dst,
                                   short* src1,
                                   short src2) {
  __mlvm_scalar_atom_exch_s16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_exch(unsigned int* dst,
                                   unsigned int* src1,
                                   unsigned int src2) {
  __mlvm_scalar_atom_exch_u32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_exch(int* dst,
                                   int* src1,
                                   int src2) {
  __mlvm_scalar_atom_exch_s32(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_exch(half* dst,
                                   half* src1,
                                   half src2) {
  __mlvm_scalar_atom_exch_f16(dst, src1, src2);
}
__DEVICE__ void __bang_atomic_exch(float* dst,
                                   float* src1,
                                   float src2) {
  __mlvm_scalar_atom_exch_f32(dst, src1, src2);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic add operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_add(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_add_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_add(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_add_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_add(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  unsigned int size) {
  __mlvm_stream_atom_add_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_add(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_add_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_add(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_add_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_add(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_add_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic increase operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_inc(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_inc_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_inc(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_inc_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_inc(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_inc_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_inc(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_inc_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_inc(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_inc_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_inc(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_inc_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic decrease operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_dec(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_dec_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_dec(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_dec_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_dec(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_dec_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_dec(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_dec_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_dec(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_dec_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_dec(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_dec_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic max operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_max(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_max_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_max(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_max_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_max(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_max_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_max(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_max_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_max(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_max_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_max(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_max_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic min operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_min(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_min_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_min(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_min_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_min(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_min_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_min(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_min_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_min(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_min_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_min(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_min_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic and operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_and(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_and_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_and(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_and_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_and(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_and_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_and(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_and_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_and(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_and_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_and(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_and_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic or operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_or(unsigned short* dst,
                                 unsigned short* src1,
                                 unsigned short* src2,
                                 int size) {
  __mlvm_stream_atom_or_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_or(short* dst,
                                 short* src1,
                                 short* src2,
                                 int size) {
  __mlvm_stream_atom_or_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_or(unsigned int* dst,
                                 unsigned int* src1,
                                 unsigned int* src2,
                                 int size) {
  __mlvm_stream_atom_or_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_or(int* dst,
                                 int* src1,
                                 int* src2,
                                 int size) {
  __mlvm_stream_atom_or_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_or(half* dst,
                                 half* src1,
                                 half* src2,
                                 int size) {
  __mlvm_stream_atom_or_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_or(float* dst,
                                 float* src1,
                                 float* src2,
                                 int size) {
  __mlvm_stream_atom_or_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic xor operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_xor(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_xor_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_xor(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_xor_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_xor(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_xor_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_xor(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_xor_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_xor(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_xor_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_xor(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_xor_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic compare-and-swap operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_cas(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  unsigned short* src3,
                                  int size) {
  __mlvm_stream_atom_cas_u16(dst, src1, src2, src3, size);
}
__DEVICE__ void __bang_atomic_cas(short* dst,
                                  short* src1,
                                  short* src2,
                                  short* src3,
                                  int size) {
  __mlvm_stream_atom_cas_s16(dst, src1, src2, src3, size);
}
__DEVICE__ void __bang_atomic_cas(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  unsigned int* src3,
                                  int size) {
  __mlvm_stream_atom_cas_u32(dst, src1, src2, src3, size);
}
__DEVICE__ void __bang_atomic_cas(int* dst,
                                  int* src1,
                                  int* src2,
                                  int* src3,
                                  int size) {
  __mlvm_stream_atom_cas_s32(dst, src1, src2, src3, size);
}
__DEVICE__ void __bang_atomic_cas(half* dst,
                                  half* src1,
                                  half* src2,
                                  half* src3,
                                  int size) {
  __mlvm_stream_atom_cas_f16(dst, src1, src2, src3, size);
}
__DEVICE__ void __bang_atomic_cas(float* dst,
                                  float* src1,
                                  float* src2,
                                  float* src3,
                                  int size) {
  __mlvm_stream_atom_cas_f32(dst, src1, src2, src3, size);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ math function: stream atomic exchange operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_atomic_exch(unsigned short* dst,
                                  unsigned short* src1,
                                  unsigned short* src2,
                                  int size) {
  __mlvm_stream_atom_exch_u16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_exch(short* dst,
                                  short* src1,
                                  short* src2,
                                  int size) {
  __mlvm_stream_atom_exch_s16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_exch(unsigned int* dst,
                                  unsigned int* src1,
                                  unsigned int* src2,
                                  int size) {
  __mlvm_stream_atom_exch_u32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_exch(int* dst,
                                  int* src1,
                                  int* src2,
                                  int size) {
  __mlvm_stream_atom_exch_s32(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_exch(half* dst,
                                  half* src1,
                                  half* src2,
                                  int size) {
  __mlvm_stream_atom_exch_f16(dst, src1, src2, size);
}
__DEVICE__ void __bang_atomic_exch(float* dst,
                                  float* src1,
                                  float* src2,
                                  int size) {
  __mlvm_stream_atom_exch_f32(dst, src1, src2, size);
}
#endif  // __BANG_ARCH__ >= 200
// -----------------------------------------------------------------------------
#endif  // __BANG_ARCH__

#endif  //__CLANG_BANG_MATH_H__
