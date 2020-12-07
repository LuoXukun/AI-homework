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
#ifndef __CLANG_BANG_EXTRA_H__
#define __CLANG_BANG_EXTRA_H__

#ifndef __BANG__
#error "This file is for BANG compilation only."
#endif  // __BANG__

#ifdef __BANG_ARCH__

#ifndef __MLU_H__
#include <mlu.h>
#endif  // __MLU_H__
#include <__clang_bang_cmath.h>
#define __DEVICE__ static __inline__ __mlu_func__
#define MAX_CONV_INPUT_BUFFER 12800
#define MAX_CONV_OUTPUT_BUFFER 9216
#define MAX_MLP_INPUT_BUFFER 2048
#define MAX_MLP_OUTPUT_BUFFER 2048
#if __BANG_ARCH__ >= 200
//bang_conv with input of int32, int16 kernel
//for devivation of formula, see split number doc
__DEVICE__ void Conv_Splitnum(float* dst,
                            int* src,
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
  __nram__ int16 src1[MAX_CONV_INPUT_BUFFER], src2[MAX_CONV_INPUT_BUFFER];
  __nram__ float dst1[MAX_CONV_OUTPUT_BUFFER], dst2[MAX_CONV_OUTPUT_BUFFER];
  int i, s, output_height, output_width, output_count, j, input_count, maxabs;
  float a, b, c;
  a = 2;
  b = 30;
  c = 15;
  input_count = channal_input * height * width;
  maxabs = abs(src[0]);
  for(j = 1; j < input_count; j++) {
    if (abs(src[j]) > maxabs) {
      maxabs = abs(src[j]);
    }
  }
  if (maxabs == 1) {
    s = -29;
  } else if (maxabs == 2) {
    s = -28;
  } else if (maxabs == 4) {
    s = -27;
  } else {
    s = ceilf(log2f(maxabs/(powf(a, b) - 1)));
  }

  for(i = 0; i < input_count; i++) {
    src1[i] = floorf(src[i] / powf(a, c+s));
    src2[i] = roundf(src[i] / powf(a, s) - src1[i] * powf(a, c));
  }
  __mlvm_stream_conv_f32_fix16_fix16(dst1, src1, kernel,
                                     channal_input, height, width,
                                     kernel_height, kernel_width,
                                     stride_x, stride_y,
                                     channal_output, fix_position);
  __mlvm_stream_conv_f32_fix16_fix16(dst2, src2, kernel,
                                     channal_input, height, width,
                                     kernel_height, kernel_width,
                                     stride_x, stride_y,
                                     channal_output, fix_position);
  output_height = (height - kernel_height) / stride_y + 1;
  output_width = (width - kernel_width) / stride_x + 1;
  output_count = channal_output * output_height * output_width;
  for(i = 0; i < output_count; i++) {
    *(dst + i) = (dst1[i] * powf(a, c) + dst2[i]) * powf(a, s);
  }
}
//bang_conv with input of int32, int16 kernel
__DEVICE__ void __bang_conv(float* dst,
                            int* src,
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
  int output_height, output_width, output_count, m, input_count;
  __nram__ float tmp[MAX_CONV_OUTPUT_BUFFER];
  input_count = channal_input * height * width;
  output_height = (height - kernel_height) / stride_y + 1;
  output_width = (width - kernel_width) / stride_x + 1;
  output_count = channal_output * output_height * output_width;
  if (input_count <= MAX_CONV_INPUT_BUFFER) {
    Conv_Splitnum(dst, src, kernel, channal_input, height, width,
                  kernel_height, kernel_width, stride_x, stride_y,
                  channal_output, fix_position);
  } else {
   int i = input_count / MAX_CONV_INPUT_BUFFER;
   int j = input_count % MAX_CONV_INPUT_BUFFER;
   int n = kernel_height * kernel_width * channal_input * channal_output;
   for (m = 0; m < i; m++) {
      Conv_Splitnum(tmp, &(src[m * MAX_CONV_INPUT_BUFFER]),
                    &(kernel[(n * m * MAX_CONV_INPUT_BUFFER) / (input_count * 64)]),
                    (channal_input * MAX_CONV_INPUT_BUFFER) / input_count, height,
                    width, kernel_height, kernel_width, stride_x, stride_y,
                    channal_output, fix_position);
      __bang_add(dst, dst, tmp, output_count);
   }
    if (j != 0) {
      Conv_Splitnum(tmp, &(src[m * MAX_CONV_INPUT_BUFFER]),
                    &(kernel[(m * n * MAX_CONV_INPUT_BUFFER) / (input_count * 64)]),
                    (channal_input * j) / input_count, height, width,
                    kernel_height, kernel_width, stride_x, stride_y,
                    channal_output, fix_position);
      __bang_add(dst, dst, tmp, output_count);
    }
 }
}
//bang_mlp with input of int32, int16 weight
//for devivation of formula, see split number doc
__DEVICE__ void Mlp_Splitnum(float* dst,
                           int* src,
                           float* bias,
                           int16* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  __nram__ int16 src1[MAX_MLP_INPUT_BUFFER], src2[MAX_MLP_INPUT_BUFFER];
  int i, s, j, maxabs;
  float a, b, c;
  __nram__ float dst1[MAX_MLP_OUTPUT_BUFFER], dst2[MAX_MLP_OUTPUT_BUFFER];
  a = 2;
  b = 30;
  c = 15;
  maxabs = abs(src[0]);
  for (j = 1; j < width; j++) {
    if (abs(src[j]) > maxabs) {
       maxabs = abs(src[j]);
    }
  }
  if (maxabs == 1) {
    s = -29;
  } else if (maxabs == 2) {
    s = -28;
  } else if (maxabs == 4) {
    s = -27;
  } else {
    s = ceilf(log2f(maxabs / (powf(a, b) - 1)));
  }
  for (i=0; i < width; i++) {
    src1[i] = floorf(src[i] / powf(a, c + s));
    src2[i] = roundf(src[i] / powf(a, s) - src1[i] * powf(a, c));
  }
  __mlvm_stream_mlp_f32_fix16_f32_fix16(dst1, src1, bias, weight,
                                        height, width, fix_position);
  __mlvm_stream_mlp_f32_fix16_f32_fix16(dst2, src2, bias, weight,
                                        height, width, fix_position);
  for (i = 0; i < height; i++) {
    *(dst + i) = ((dst1[i] - bias[i]) * powf(a, c) + dst2[i] - bias[i])
                 * powf(a, s) + bias[i];
  }
}
//bang_mlp with input of int32, int16 weight
__DEVICE__ void __bang_mlp(float* dst,
                           int* src,
                           float* bias,
                           int16* weight,
                           const int height,
                           const int width,
                           int fix_position) {
  if (width <= MAX_MLP_INPUT_BUFFER) {
    Mlp_Splitnum(dst, src, bias, weight, height, width, fix_position);
  } else {
    int m;
    int i = width / MAX_MLP_INPUT_BUFFER;
    int j = width - i * MAX_MLP_INPUT_BUFFER;
    __nram__ float tmp[MAX_CONV_OUTPUT_BUFFER];
    for (m = 0; m < width / MAX_MLP_INPUT_BUFFER; m++) {
      Mlp_Splitnum(tmp, &(src[m * MAX_MLP_INPUT_BUFFER]), bias,
                   &(weight[m * MAX_MLP_INPUT_BUFFER*height / 64]), height,
                   MAX_MLP_INPUT_BUFFER, fix_position);
      __bang_add(dst, dst, tmp, height);
      if (m != 0) {
        __bang_sub(dst, dst, bias, height);
      }
    }

    if (j != 0) {
      Mlp_Splitnum(tmp, &(src[m * MAX_MLP_INPUT_BUFFER]), bias,
                   &(weight[m * MAX_MLP_INPUT_BUFFER * height / 64]),
                   height, j, fix_position);
      __bang_add(dst, dst, tmp, height);
      __bang_sub(dst, dst, bias, height);
    }
  }
}

#endif
#endif
#endif
