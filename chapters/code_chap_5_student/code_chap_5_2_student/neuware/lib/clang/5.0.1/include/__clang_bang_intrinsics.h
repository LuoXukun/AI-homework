/*===--- __clang_bang_intrinsics.h - Device-side MLU intrinsic wrappers ----===
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
#ifndef __CLANG_BANG_INTRINSICS_H__
#define __CLANG_BANG_INTRINSICS_H__

#ifndef __BANG__
#error "This file is for BANG compilation only."
#endif  // __BANG__

#ifndef __MLU_H__
#include <mlu.h>
#endif  // __MLU_H__

#ifndef __CLANG_BANG_BUILTIN_VARS_H__
#include <__clang_bang_builtin_vars.h>
#endif  // __CLANG_BANG_BUILTIN_VARS_H__

#include <stdint.h>

#ifdef __BANG_ARCH__

#define __DEVICE__ static __inline__ __mlu_func__

// Begin of debug operations
#define __BUILTIN_BREAKDUMP1(a) \
  ({ __asm__ volatile("breakdump.gpr \t%[src];\n\t" : : [src] "r"(a)); })
#define __BUILTIN_BREAKDUMP2(a, b)                           \
  ({                                                         \
    __asm__ volatile("breakdump.gpr \t%[src0], %[src1];\n\t" \
                     :                                       \
                     : [src0] "r"(a), [src1] "r"(b));        \
  })
#define __BUILTIN_BREAKDUMP3(a, b, c)                                 \
  ({                                                                  \
    __asm__ volatile("breakdump.gpr \t%[src0], %[src1], %[src2];\n\t" \
                     :                                                \
                     : [src0] "r"(a), [src1] "r"(b), [src2] "r"(c));  \
  })
#define __BUILTIN_BREAKDUMP4(a, b, c, d)                                       \
  ({                                                                           \
    __asm__ volatile("breakdump.gpr \t%[src0], %[src1], %[src2], %[src3];\n\t" \
                     :                                                         \
                     : [src0] "r"(a), [src1] "r"(b), [src2] "r"(c),            \
                       [src3] "r"(d));                                         \
  })
#define __BUILTIN_BREAKDUMP5(a, b, c, d, e)                                \
  ({                                                                       \
    __asm__ volatile(                                                      \
        "breakdump.gpr \t%[src0], %[src1], %[src2], %[src3], %[src4];\n\t" \
        :                                                                  \
        : [src0] "r"(a), [src1] "r"(b), [src2] "r"(c), [src3] "r"(d),      \
          [src4] "r"(e));                                                  \
  })
#define __BUILTIN_BREAKDUMP6(a, b, c, d, e, f)                        \
  ({                                                                  \
    __asm__ volatile(                                                 \
        "breakdump.gpr \t%[src0], %[src1], %[src2], %[src3], "        \
        "%[src4], %[src5];\n\t"                                       \
        :                                                             \
        : [src0] "r"(a), [src1] "r"(b), [src2] "r"(c), [src3] "r"(d), \
          [src4] "r"(e), [src5] "r"(f));                              \
  })
#define GetMacro(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define __breakdump_scalar(...)                                              \
  GetMacro(__VA_ARGS__, __BUILTIN_BREAKDUMP6, __BUILTIN_BREAKDUMP5,          \
           __BUILTIN_BREAKDUMP4, __BUILTIN_BREAKDUMP3, __BUILTIN_BREAKDUMP2, \
           __BUILTIN_BREAKDUMP1, ...)(__VA_ARGS__)
#define __breakdump_vector(src, Bytes, AddrSpace) \
  __breakdump_vector_##AddrSpace(src, Bytes)
#define __breakdump_vector_GDRAM(src, Bytes) \
  ({ __mlvm_stream_breakdump_gdram(src, Bytes); })
#define __breakdump_vector_NRAM(src, Bytes) \
  ({ __mlvm_stream_breakdump_nram(src, Bytes); })
#define __breakdump_vector_LDRAM(src, Bytes) \
  ({ __mlvm_stream_breakdump_ldram(src, Bytes); })
// End of debug operations

// begin printf
#define __BANG_PRINTF0(f)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt];\n\t"  \
                    ::[fmt]"p"(f));  \
   })

#define __BANG_PRINTF1(f, a)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a));  \
   })

 #define __BANG_PRINTF2(f, a, b)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b));  \
   })

 #define __BANG_PRINTF3(f, a, b, c)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b), [src3]"r"(c));  \
   })

 #define __BANG_PRINTF4(f, a, b, c, d)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3]"  \
                    ", %[src4];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d)); \
   })

 #define __BANG_PRINTF5(f, a, b, c, d, e)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                    "%[src4], %[src5];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e));  \
   })

 #define __BANG_PRINTF6(f, a, b, c, d, e, g)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g));  \
   })

 #define __BANG_PRINTF7(f, a, b, c, d, e, g, h)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h));  \
   })

 #define __BANG_PRINTF8(f, a, b, c, d, e, g, h, i)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8]"  \
                     ";\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i));  \
   })

 #define __BANG_PRINTF9(f, a, b, c, d, e, g, h, i, j)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j));  \
   })

 #define __BANG_PRINTF10(f, a, b, c, d, e, g, h, i, j, k)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k));  \
   })

 #define __BANG_PRINTF11(f, a, b, c, d, e, g, h, i, j, k, l)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10], %[src11];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k), [src11]"r"(l));  \
   })

 #define __BANG_PRINTF12(f, a, b, c, d, e, g, h, i, j, k, l, m)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10], %[src11], %[src12];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k), [src11]"r"(l),  \
                      [src12]"r"(m));  \
   })

 #define __BANG_PRINTF13(f, a, b, c, d, e, g, h, i, j, k, l, m, n)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10], %[src11], %[src12], %[src13];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k), [src11]"r"(l),  \
                      [src12]"r"(m), [src13]"r"(n));  \
   })

 #define __BANG_PRINTF14(f, a, b, c, d, e, g, h, i, j, k, l, m, n, o)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10], %[src11], %[src12], %[src13], "  \
                     "%[src14];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k), [src11]"r"(l),  \
                      [src12]"r"(m), [src13]"r"(n), [src14]"r"(o));  \
   })

 #define __BANG_PRINTF15(f, a, b, c, d, e, g, h, i, j, k, l, m, n, o, p)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10], %[src11], %[src12], %[src13], "  \
                     "%[src14], %[src15];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k), [src11]"r"(l),  \
                      [src12]"r"(m), [src13]"r"(n), [src14]"r"(o),  \
                      [src15]"r"(p));  \
   })

 #define __BANG_PRINTF16(f, a, b, c, d, e, g, h, i, j, k, l, m, n, o, p, q)  \
   ({  \
   __asm__ volatile("dumpprintf %[fmt], %[src1], %[src2], %[src3], "  \
                     "%[src4], %[src5], %[src6], %[src7], %[src8], "  \
                     "%[src9], %[src10], %[src11], %[src12], %[src13], "  \
                     "%[src14], %[src15], %[src16];\n\t"  \
                    ::[fmt]"p"(f), [src1]"r"(a), [src2]"r"(b),  \
                      [src3]"r"(c), [src4]"r"(d), [src5]"r"(e),  \
                      [src6]"r"(g), [src7]"r"(h), [src8]"r"(i),  \
                      [src9]"r"(j), [src10]"r"(k), [src11]"r"(l),  \
                      [src12]"r"(m), [src13]"r"(n), [src14]"r"(o),  \
                      [src15]"r"(p), [src16]"r"(q));  \
   })

 #define PrintfMacro(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10,  \
                     _11, _12, _13, _14, _15, _16, _17,  NAME, ...) NAME
 #define __bang_printf(...)  \
   PrintfMacro(__VA_ARGS__, __BANG_PRINTF16, __BANG_PRINTF15,  \
            __BANG_PRINTF14, __BANG_PRINTF13, __BANG_PRINTF12,  \
            __BANG_PRINTF11, __BANG_PRINTF10, __BANG_PRINTF9,  \
            __BANG_PRINTF8, __BANG_PRINTF7, __BANG_PRINTF6,  \
            __BANG_PRINTF5, __BANG_PRINTF4, __BANG_PRINTF3,  \
            __BANG_PRINTF2, __BANG_PRINTF1, __BANG_PRINTF0, ...)(__VA_ARGS__)
// end printf

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: pv
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __bang_lock(int lock_id_0, int lock_id_1) {
  __asm__ __volatile__("pv.p.dma0_sync.dma1_sync %[id0], %[id1];\n\t"
                       ::[id0]"r"(lock_id_0),[id1]"r"(lock_id_1));
}

__DEVICE__ void __bang_unlock(int lock_id_0, int lock_id_1) {
  __asm__ __volatile__("pv.v.dma0_sync.dma1_sync %[id0], %[id1];\n\t"
                       ::[id0]"r"(lock_id_0),[id1]"r"(lock_id_1));
}
#endif  // __BANG_ARCH__ >= 200

#define __BARRIER(count) __asm__ __volatile__("barrier %0;" : : "i"(count))

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: sync all Intelligent Process Unit
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __sync_all_ipu() {
  if (clusterDim == 0) { return; }
  if (clusterDim == 1) {
    __asm__ __volatile__("barrier.sync.local 1, %[cnt];\n\t"
                         ::[cnt]"r"(coreDim));
  } else {
    __asm__ __volatile__("barrier.sync.global 0, %[cnt];\n\t"
                         ::[cnt]"r"(clusterDim * coreDim));
  }
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: sync all Memory Process Unit
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __sync_all_mpu() {
  if (clusterDim == 0 || clusterDim == 1) { return; }
  __asm__ __volatile__("barrier.sync.global 0, %[cnt];\n\t"
                       ::[cnt]"r"(clusterDim));
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: sync the threads in HW cluster
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __sync_cluster() {
  if (clusterDim == 0) { return; }
  __asm__ __volatile__("barrier.sync.local 1, %[cnt];\n\t"
                       ::[cnt]"r"(coreDim + 1));
}
#elif __BANG_ARCH__ == 100
__DEVICE__ void __sync_cluster() {
  if (clusterDim == 0) { return; }
  switch (clusterId) {
    case 0:
      __BARRIER(4);
      break;
    case 1:
      __BARRIER(4);
      break;
    case 2:
      __BARRIER(4);
      break;
    case 3:
      __BARRIER(4);
      break;
    case 4:
      __BARRIER(4);
      break;
    case 5:
      __BARRIER(4);
      break;
    case 6:
      __BARRIER(4);
      break;
    case 7:
      __BARRIER(4);
      break;
    case 8:
      __BARRIER(4);
      break;
    default:
      break;
  }
}
#else
__DEVICE__ void __sync_cluster() {}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: sync all threads in one task
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
__DEVICE__ void __sync_all() {
  if (clusterDim == 0) { return; }
  if (clusterDim == 1) {
    __asm__ __volatile__("barrier.sync.local 1, %[cnt];\n\t"
                         ::[cnt]"r"(coreDim + 1));
  } else {
    __asm__ __volatile__("barrier.sync.global 0, %[cnt];\n\t"
                         ::[cnt]"r"(clusterDim * (coreDim + 1)));
  }
}
#elif __BANG_ARCH__ == 100
__DEVICE__ void __sync_all() {
  switch (clusterDim) {
    case 0:
      return;
    case 1:
      if (taskDim == 2) {
        __BARRIER(2);  // only for MLU100 cnPlugin DP=2 mode
      } else {
        __BARRIER(4);
      }
      break;
    case 2:
      __BARRIER(8);
      break;
    case 4:
      __BARRIER(16);
      break;
    case 8:
      __BARRIER(32);
      break;
    default:
      break;
  }
}
#else
__DEVICE__ void __sync_all() {}
#endif  // __BANG_ARCH__ >= 200

typedef enum {
  GDRAM2NRAM = 0,
  NRAM2GDRAM,
  LDRAM2NRAM,
  NRAM2LDRAM,
  GDRAM2WRAM,
  WRAM2GDRAM,
  LDRAM2WRAM,
  WRAM2LDRAM,
  NRAM2NRAM,
  NRAM2WRAM,
  WRAM2NRAM,
  GDRAM2SRAM,
  SRAM2GDRAM,
  LDRAM2SRAM,
  SRAM2LDRAM,
  SRAM2NRAM,
  NRAM2SRAM,
  SRAM2WRAM,
  WRAM2SRAM,
  GDRAM2GDRAM,
  GDRAM2LDRAM,
  LDRAM2GDRAM,
  SRAM2SRAM,
} mluMemcpyDirection_t;

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: memory copy operation
// -----------------------------------------------------------------------------
__DEVICE__ void __memcpy(void* dst,
                         void* src,
                         int size,
                         mluMemcpyDirection_t dir) {
  switch (dir) {
    default : {
      __assert_fail("Unsupport memcpy direction",
                    __FILE__, __LINE__, __func__);
      break;
    }
    case GDRAM2NRAM:  { __mlvm_memcpy_gdram_to_nram(dst, src, size); break; }
    case NRAM2GDRAM:  { __mlvm_memcpy_nram_to_gdram(dst, src, size); break; }
    case LDRAM2NRAM:  { __mlvm_memcpy_ldram_to_nram(dst, src, size); break; }
    case NRAM2LDRAM:  { __mlvm_memcpy_nram_to_ldram(dst, src, size); break; }
    case GDRAM2WRAM:  { __mlvm_memcpy_gdram_to_wram(dst, src, size); break; }
    case WRAM2GDRAM:  { __mlvm_memcpy_wram_to_gdram(dst, src, size); break; }
    case LDRAM2WRAM:  { __mlvm_memcpy_ldram_to_wram(dst, src, size); break; }
    case WRAM2LDRAM:  { __mlvm_memcpy_wram_to_ldram(dst, src, size); break; }
    case NRAM2NRAM:   { __mlvm_memcpy_nram_to_nram(dst, src, size); break; }
    case NRAM2WRAM:   { __mlvm_memcpy_nram_to_wram(dst, src, size); break; }
    case WRAM2NRAM:   { __mlvm_memcpy_wram_to_nram(dst, src, size); break; }
#if __BANG_ARCH__ >= 200
    case LDRAM2SRAM:  { __mlvm_memcpy_ldram_to_sram(dst, src, size); break; }
    case SRAM2LDRAM:  { __mlvm_memcpy_sram_to_ldram(dst, src, size); break; }
    case SRAM2NRAM:   { __mlvm_memcpy_sram_to_nram(dst, src, size); break; }
    case NRAM2SRAM:   { __mlvm_memcpy_nram_to_sram(dst, src, size); break; }
    case SRAM2WRAM:   { __mlvm_memcpy_sram_to_wram(dst, src, size); break; }
    case WRAM2SRAM:   { __mlvm_memcpy_wram_to_sram(dst, src, size); break; }
    case GDRAM2SRAM:  { __mlvm_memcpy_gdram_to_sram(dst, src, size); break; }
    case SRAM2GDRAM:  { __mlvm_memcpy_sram_to_gdram(dst, src, size); break; }
#endif  // __BANG_ARCH__ >= 200
    case GDRAM2GDRAM: { __mlvm_memcpy_gdram_to_gdram(dst, src, size); break; }
    case GDRAM2LDRAM: { __mlvm_memcpy_gdram_to_ldram(dst, src, size); break; }
    case LDRAM2GDRAM: { __mlvm_memcpy_ldram_to_gdram(dst, src, size); break; }
  }
}

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: stride memory copy operation
// -----------------------------------------------------------------------------
__DEVICE__ void __memcpy(void* dst,
                         void* src,
                         int size,
                         mluMemcpyDirection_t dir,
                         int dst_stride,
                         int src_stride,
                         int segnum) {
  switch (dir) {
    default : {
      __assert_fail("Unsupport stride memcpy direction",
                    __FILE__, __LINE__, __func__);
      break;
    }
    case GDRAM2NRAM: {
      __mlvm_memcpy_stride_gdram_to_nram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case NRAM2GDRAM: {
      __mlvm_memcpy_stride_nram_to_gdram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case LDRAM2NRAM: {
      __mlvm_memcpy_stride_ldram_to_nram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case NRAM2LDRAM: {
      __mlvm_memcpy_stride_nram_to_ldram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case NRAM2NRAM:  {
      __mlvm_memcpy_stride_nram_to_nram(dst, src, size,
                                        dst_stride, src_stride, segnum);
      break;
    }
#if __BANG_ARCH__ >= 200
    case SRAM2NRAM:  {
      __mlvm_memcpy_stride_sram_to_nram(dst, src, size,
                                        dst_stride, src_stride, segnum);
      break;
    }
    case NRAM2SRAM:  {
      __mlvm_memcpy_stride_nram_to_sram(dst, src, size,
                                        dst_stride, src_stride, segnum);
      break;
    }
    case SRAM2GDRAM:  {
      __mlvm_memcpy_stride_sram_to_gdram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case GDRAM2SRAM:  {
      __mlvm_memcpy_stride_gdram_to_sram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case SRAM2LDRAM:  {
      __mlvm_memcpy_stride_sram_to_ldram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case LDRAM2SRAM:  {
      __mlvm_memcpy_stride_ldram_to_sram(dst, src, size,
                                         dst_stride, src_stride, segnum);
      break;
    }
    case LDRAM2GDRAM:  {
      __mlvm_memcpy_stride_ldram_to_gdram(dst, src, size,
                                          dst_stride, src_stride, segnum);
    }
    case GDRAM2LDRAM:  {
      __mlvm_memcpy_stride_gdram_to_ldram(dst, src, size,
                                          dst_stride, src_stride, segnum);
    }
#endif  // __BANG_ARCH__ >= 200
  }
}
#if __BANG_ARCH__ >= 200
__DEVICE__ void __memcpy(void* dst,
                         void* src,
                         int size,
                         mluMemcpyDirection_t dir,
                         int id_dst_cluster) {
  if (dir != SRAM2SRAM) {
    __assert_fail("Unsupport stride memcpy direction",
                  __FILE__, __LINE__, __func__);
  }
  __mlvm_memcpy_sram_to_sram(dst, src, size, id_dst_cluster);
}
__DEVICE__ void __memcpy(void* dst,
                         void* src,
                         int size,
                         mluMemcpyDirection_t dir,
                         int dst_stride,
                         int src_stride,
                         int segnum,
                         int id_dst_cluster) {
  if (dir != SRAM2SRAM) {
    __assert_fail("Unsupport stride memcpy direction",
                  __FILE__, __LINE__, __func__);
  }
  __mlvm_memcpy_stride_sram_to_sram(dst, src, size,
                                    dst_stride, src_stride, segnum,
                                    id_dst_cluster);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: nram set operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ < 200
#define __nramset_float __mlvm_memset_nram_f32
#define __nramset_half __mlvm_memset_nram_f16
#define __nramset_int __mlvm_memset_nram_s32
#define __nramset_unsigned_int __mlvm_memset_nram_u32
#define __nramset_short __mlvm_memset_nram_s16
#define __nramset_unsigned_short __mlvm_memset_nram_u16
#else // __BANG_ARCH__ >= 200
#define __nramset_float __nramset
#define __nramset_half __nramset
#define __nramset_int __nramset
#define __nramset_unsigned_int __nramset
#define __nramset_short __nramset
#define __nramset_unsigned_short __nramset
// 8bit
__DEVICE__ void __nramset(char* dst,
                          int elem_count,
                          char value) {
  __mlvm_memset_nram_s8(dst, elem_count, value);
}
__DEVICE__ void __nramset(signed char* dst,
                          int elem_count,
                          signed char value) {
  __mlvm_memset_nram_s8(dst, elem_count, value);
}
__DEVICE__ void __nramset(unsigned char* dst,
                          int elem_count,
                          unsigned char value) {
  __mlvm_memset_nram_s8(dst, elem_count, value);
}
// 16bit
__DEVICE__ void __nramset(half* dst,
                          int elem_count,
                          half value) {
  __mlvm_memset_nram_f16(dst, elem_count, value);
}
__DEVICE__ void __nramset(short* dst,
                          int elem_count,
                          short value) {
  __mlvm_memset_nram_s16(dst, elem_count, value);
}
__DEVICE__ void __nramset(unsigned short* dst,
                          int elem_count,
                          unsigned short value) {
  __mlvm_memset_nram_u16(dst, elem_count, value);
}
// 32bit
__DEVICE__ void __nramset(float* dst,
                          int elem_count,
                          float value) {
  __mlvm_memset_nram_f32(dst, elem_count, value);
}
__DEVICE__ void __nramset(int* dst,
                          int elem_count,
                          int value) {
  __mlvm_memset_nram_s32(dst, elem_count, value);
}
__DEVICE__ void __nramset(unsigned int* dst,
                          int elem_count,
                          unsigned int value) {
  __mlvm_memset_nram_u32(dst, elem_count, value);
}
#endif  // __BANG_ARCH__ < 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: sram set operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
// 8bit
__DEVICE__ void __sramset(char* dst,
                          int elem_count,
                          char value) {
  __mlvm_memset_sram_s8(dst, elem_count, value);
}
__DEVICE__ void __sramset(signed char* dst,
                          int elem_count,
                          signed char value) {
  __mlvm_memset_sram_s8(dst, elem_count, value);
}
__DEVICE__ void __sramset(unsigned char* dst,
                          int elem_count,
                          unsigned char value) {
  __mlvm_memset_sram_s8(dst, elem_count, value);
}

// 16bit
__DEVICE__ void __sramset(half* dst,
                          int elem_count,
                          half value) {
  __mlvm_memset_sram_f16(dst, elem_count, value);
}
__DEVICE__ void __sramset(short* dst,
                          int elem_count,
                          short value) {
  __mlvm_memset_sram_s16(dst, elem_count, value);
}
__DEVICE__ void __sramset(unsigned short* dst,
                          int elem_count,
                          unsigned short value) {
  __mlvm_memset_sram_u16(dst, elem_count, value);
}

// 32bit
__DEVICE__ void __sramset(float* dst,
                          int elem_count,
                          float value) {
  __mlvm_memset_sram_f32(dst, elem_count, value);
}
__DEVICE__ void __sramset(int* dst,
                          int elem_count,
                          int value) {
  __mlvm_memset_sram_s32(dst, elem_count, value);
}
__DEVICE__ void __sramset(unsigned int* dst,
                          int elem_count,
                          unsigned int value) {
  __mlvm_memset_sram_u32(dst, elem_count, value);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: gdram set operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
// 8bit
__DEVICE__ void __gdramset(char* dst,
                           int elem_count,
                           char value) {
  __mlvm_memset_gdram_s8(dst, elem_count, value);
}
__DEVICE__ void __gdramset(signed char* dst,
                           int elem_count,
                           signed char value) {
  __mlvm_memset_gdram_s8(dst, elem_count, value);
}
__DEVICE__ void __gdramset(unsigned char* dst,
                           int elem_count,
                           unsigned char value) {
  __mlvm_memset_gdram_s8(dst, elem_count, value);
}

// 16bit
__DEVICE__ void __gdramset(half* dst,
                           int elem_count,
                           half value) {
  __mlvm_memset_gdram_f16(dst, elem_count, value);
}
__DEVICE__ void __gdramset(short* dst,
                           int elem_count,
                           short value) {
  __mlvm_memset_gdram_s16(dst, elem_count, value);
}
__DEVICE__ void __gdramset(unsigned short* dst,
                           int elem_count,
                           unsigned short value) {
  __mlvm_memset_gdram_u16(dst, elem_count, value);
}

// 32bit
__DEVICE__ void __gdramset(float* dst,
                           int elem_count,
                           float value) {
  __mlvm_memset_gdram_f32(dst, elem_count, value);
}
__DEVICE__ void __gdramset(int* dst,
                           int elem_count,
                           int value) {
  __mlvm_memset_gdram_s32(dst, elem_count, value);
}
__DEVICE__ void __gdramset(unsigned int* dst,
                           int elem_count,
                           unsigned int value) {
  __mlvm_memset_gdram_u32(dst, elem_count, value);
}
#endif  // __BANG_ARCH__ >= 200

// -----------------------------------------------------------------------------
// Bang C/C++ builtin function: ldram set operation
// -----------------------------------------------------------------------------
#if __BANG_ARCH__ >= 200
// 8bit
__DEVICE__ void __ldramset(char* dst,
                           int elem_count,
                           char value) {
  __mlvm_memset_ldram_s8(dst, elem_count, value);
}
__DEVICE__ void __ldramset(signed char* dst,
                           int elem_count,
                           signed char value) {
  __mlvm_memset_ldram_s8(dst, elem_count, value);
}
__DEVICE__ void __ldramset(unsigned char* dst,
                           int elem_count,
                           unsigned char value) {
  __mlvm_memset_ldram_s8(dst, elem_count, value);
}

// 16bit
__DEVICE__ void __ldramset(half* dst,
                           int elem_count,
                           half value) {
  __mlvm_memset_ldram_f16(dst, elem_count, value);
}
__DEVICE__ void __ldramset(short* dst,
                           int elem_count,
                           short value) {
  __mlvm_memset_ldram_s16(dst, elem_count, value);
}
__DEVICE__ void __ldramset(unsigned short* dst,
                           int elem_count,
                           unsigned short value) {
  __mlvm_memset_ldram_u16(dst, elem_count, value);
}

// 32bit
__DEVICE__ void __ldramset(float* dst,
                           int elem_count,
                           float value) {
  __mlvm_memset_ldram_f32(dst, elem_count, value);
}
__DEVICE__ void __ldramset(int* dst,
                           int elem_count,
                           int value) {
  __mlvm_memset_ldram_s32(dst, elem_count, value);
}
__DEVICE__ void __ldramset(unsigned int* dst,
                           int elem_count,
                           unsigned int value) {
  __mlvm_memset_ldram_u32(dst, elem_count, value);
}
#endif  // __BANG_ARCH__ >= 200

#endif  // __BANG_ARCH__

#endif  //__CLANG_BANG_INTRINSICS_H__
