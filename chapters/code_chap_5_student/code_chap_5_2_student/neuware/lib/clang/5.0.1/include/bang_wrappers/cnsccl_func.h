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
#ifndef FUNC_H_
#define FUNC_H_

// -----------------------------------------------------------------------------
// Operation Null
// -----------------------------------------------------------------------------
template<typename T>
struct FuncNull {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncNull<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {}
};

template<>
struct FuncNull<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {}
};

template<>
struct FuncNull<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {}
};

template<>
struct FuncNull<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {}
};

template<>
struct FuncNull<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {}
};

// -----------------------------------------------------------------------------
// Operation Sum
// -----------------------------------------------------------------------------
template<typename T>
struct FuncSum {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncSum<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] + y[i];
    }
  }
};

template<>
struct FuncSum<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __mlvm_stream_add_f16(z, x, y, s);
  }
};

template<>
struct FuncSum<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
#if __BANG_ARCH__ == 270
    __mlvm_stream_add_s16(z, x, y, s);
#else
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] + y[i];
    }
#endif
  }
};

template<>
struct FuncSum<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
#if __BANG_ARCH__ == 270
    __mlvm_stream_add_s32(z, x, y, s);
#else
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] + y[i];
    }
#endif
  }
};

template<>
struct FuncSum<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __mlvm_stream_add_f32(z, x, y, s);
  }
};

// -----------------------------------------------------------------------------
// Operation Prod
// -----------------------------------------------------------------------------
template<typename T>
struct FuncProd {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncProd<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] * y[i];
    }
  }
};

template<>
struct FuncProd<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __bang_mul(z, x, y, s);
  }
};

template<>
struct FuncProd<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
#if __BANG_ARCH__ == 270
    __mlvm_stream_mul_s16(z, x, y, s);
#else
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] * y[i];
    }
#endif
  }
};

template<>
struct FuncProd<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
#if __BANG_ARCH__ == 270
    __mlvm_stream_mul_s32(z, x, y, s);
#else
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] * y[i];
    }
#endif
  }
};

template<>
struct FuncProd<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __bang_mul(z, x, y, s);
  }
};

// -----------------------------------------------------------------------------
// Operation Max
// -----------------------------------------------------------------------------
template<typename T>
struct FuncMax {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {
  }
};

template<>
struct FuncMax<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] > y[i] ? x[i] : y[i];
    }
  }
};

template<>
struct FuncMax<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __mlvm_stream_maxequal_f16(z, x, y, s);
  }
};

template<>
struct FuncMax<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] > y[i] ? x[i] : y[i];
    }
  }
};

template<>
struct FuncMax<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] > y[i] ? x[i] : y[i];
    }
  }
};

template<>
struct FuncMax<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __mlvm_stream_maxequal_f32(z, x, y, s);
  }
};

// -----------------------------------------------------------------------------
// Operation Min
// -----------------------------------------------------------------------------
template<typename T>
struct FuncMin {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncMin<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] < y[i] ? x[i] : y[i];
    }
  }
};

template<>
struct FuncMin<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __mlvm_stream_minequal_f16(z, x, y, s);
  }
};

template<>
struct FuncMin<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] < y[i] ? x[i] : y[i];
    }
  }
};

template<>
struct FuncMin<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] < y[i] ? x[i] : y[i];
    }
  }
};

template<>
struct FuncMin<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __mlvm_stream_minequal_f32(z, x, y, s);
  }
};

// -----------------------------------------------------------------------------
// Operation And
// -----------------------------------------------------------------------------
template<typename T>
struct FuncAnd {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncAnd<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] && y[i];
    }
  }
};

template<>
struct FuncAnd<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __mlvm_stream_and_f16(z, x, y, s);
  }
};

template<>
struct FuncAnd<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] && y[i];
    }
  }
};

template<>
struct FuncAnd<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] && y[i];
    }
  }
};

template<>
struct FuncAnd<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __mlvm_stream_and_f32(z, x, y, s);
  }
};

// -----------------------------------------------------------------------------
// Operation Or
// -----------------------------------------------------------------------------
template<typename T>
struct FuncOr {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncOr<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] || y[i];
    }
  }
};

template<>
struct FuncOr<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __mlvm_stream_or_f16(z, x, y, s);
  }
};

template<>
struct FuncOr<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] || y[i];
    }
  }
};

template<>
struct FuncOr<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] || y[i];
    }
  }
};

template<>
struct FuncOr<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __mlvm_stream_or_f32(z, x, y, s);
  }
};

// -----------------------------------------------------------------------------
// Operation Xor
// -----------------------------------------------------------------------------
template<typename T>
struct FuncXor {
  __mlu_func__ void operator()(T* z, T* x, T* y, int s) {}
};

template<>
struct FuncXor<char> {
  __mlu_func__ void operator()(char* z, char* x, char* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] ^ y[i];
    }
  }
};

template<>
struct FuncXor<half> {
  __mlu_func__ void operator()(half* z, half* x, half* y, int s) {
    __mlvm_stream_xor_f16(z, x, y, s);
  }
};

template<>
struct FuncXor<short> {
  __mlu_func__ void operator()(short* z, short* x, short* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] ^ y[i];
    }
  }
};

template<>
struct FuncXor<int> {
  __mlu_func__ void operator()(int* z, int* x, int* y, int s) {
    // TODO(zhouxiaoyong): to be vectorized
    for (int i = 0; i < s; ++i) {
      z[i] = x[i] ^ y[i];
    }
  }
};

template<>
struct FuncXor<float> {
  __mlu_func__ void operator()(float* z, float* x, float* y, int s) {
    __mlvm_stream_xor_f32(z, x, y, s);
  }
};

#endif  // FUNC_H_
