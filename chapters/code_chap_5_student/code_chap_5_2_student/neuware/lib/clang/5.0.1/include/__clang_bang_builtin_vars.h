/*===---------- bang_builtin_vars.h - BANG built-in variables --------------===
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
#ifndef __BANG_BUILTIN_VARS_H
#define __BANG_BUILTIN_VARS_H

// The file implements built-in BANG variables using __declspec(property).
// All read accesses of built-in variable fields get converted into calls to a
// getter function which in turn calls the appropriate builtin to fetch the
// value.
//
// Example:
//    int x = taskIdX;
// IR output:
//  %0 = call i32 @llvm.mlvm.read.mlu.sreg.taskidx() #3
// MLISA output:
//  mv.gpr.sreg %r0, %taskidx;

#define taskIdX __mlvm_read_mlu_sreg_taskidx()
#define taskIdY __mlvm_read_mlu_sreg_taskidy()
#define taskIdZ __mlvm_read_mlu_sreg_taskidz()
#define taskId __mlvm_read_mlu_sreg_taskid()
#define taskDimX __mlvm_read_mlu_sreg_taskdimx()
#define taskDimY __mlvm_read_mlu_sreg_taskdimy()
#define taskDimZ __mlvm_read_mlu_sreg_taskdimz()
#define taskDim __mlvm_read_mlu_sreg_taskdim()
#define clusterDim __mlvm_read_mlu_sreg_clusterdim()
#define clusterId __mlvm_read_mlu_sreg_clusterid()
#define coreDim __mlvm_read_mlu_sreg_coredim()
#define coreId __mlvm_read_mlu_sreg_coreid()

#endif  // __BANG_BUILTIN_VARS_H
