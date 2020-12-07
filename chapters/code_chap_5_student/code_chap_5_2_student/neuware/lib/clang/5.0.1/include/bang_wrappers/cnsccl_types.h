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
#ifndef CNSCCL_TYPES_H_
#define CNSCCL_TYPES_H_

// Error type
typedef enum { cnscclSuccess                 =  0,
               cnscclUnhandledMLUError       =  1,
               cnscclSystemError             =  2,
               cnscclInternalError           =  3,
               cnscclInvalidSharedPointer    =  4,
               cnscclUnsupportedClusterCount =  5,
               cnscclClusterNotFound         =  6,
               cnscclInvalidClusterIndex     =  7,
               cnscclShmMallocFailed         =  8,
               cnscclInvalidArgument         =  9,
               cnscclInvalidType             = 10,
               cnscclInvalidOperation        = 11,
               cnsccl_NUM_RESULTS            = 12 } cnscclResult_t;

// Reduction opperation selector
typedef enum { cnscclSum        = 0,
               cnscclProd       = 1,
               cnscclMax        = 2,
               cnscclMin        = 3,
               cnscclAnd        = 4,
               cnscclOr         = 5,
               cnscclXor        = 6,
               cnscclFuncNull   = 7,
               cnsccl_NUM_OPS   = 8 } cnscclRedOp_t;

// Data types
typedef enum { cnscclChar       = 0,
               cnscclShort      = 1,
               cnscclHalf       = 2,
               cnscclInt        = 3,
               cnscclFloat      = 4,
               cnsccl_NUM_TYPES = 5 } cnscclDataType_t;

#endif  // CNSCCL_TYPES_H_
