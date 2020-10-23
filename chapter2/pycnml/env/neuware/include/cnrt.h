/*************************************************************************
 * Copyright (C) [2019] by Cambricon, Inc.
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *************************************************************************/

/************************************************************************
 *
 *  @file cnrt.h
 *
 *  @brief Runtime APIs provide programmable interfaces for users to develop
 *  their-owned programs, which includes device management, context
 *  management, memory management of both sides (devices and hosts), etc.
 *
 **************************************************************************/

#ifndef __CNRT_H
#define __CNRT_H

#define CNRT_MAJOR_VERSION 4
#define CNRT_MINOR_VERSION 3
#define CNRT_PATCH_VERSION 0

#define CNRT_VERSION (CNRT_MAJOR_VERSION * 10000 + CNRT_MINOR_VERSION * 100 + CNRT_PATCH_VERSION)

/************************************************************************
 *  Include files
 ************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus*/

/************************************************************************
 *  Definitions
 ************************************************************************/
/**< DLL exports controller. */
#if defined(WIN32) || defined(WINDOWS)
#ifdef USE_CNRT_DLL
#ifdef CNRT_DLL_EXPORTS
#define CNRT_DLL_API __declspec(dllexport)
#else /*CNRT_DLL_EXPORTS*/
#define CNRT_DLL_API __declspec(dllimport)
#endif /*CNRT_DLL_EXPORTS*/
#else
#define CNRT_DLL_API
#endif /*USE_CNRT_DLL*/
#else  /*WIN32 || WINDOWS*/
#define CNRT_DLL_API
#endif /*WIN32 || WINDOWS*/

/**< struct tailed */
#define CNRT_PARAM_END (void *)0xFFFFFFFF

/************************************************************************
 *  Data type declaration
 ************************************************************************/

#ifndef __CAMB_TYPES_H
#define __CAMB_TYPES_H
#if defined(WIN32) || defined(WINDOWS)
typedef unsigned __int64 u64_t;
typedef __int64 i64_t;
typedef unsigned __int32 u32_t;
typedef unsigned __int16 u16_t;
typedef unsigned __int8 u8_t;
typedef signed __int32 i32_t;
typedef signed __int16 i16_t;
typedef signed __int8 i8_t;

#else /*!WIN32 || WINDOWS*/

typedef uint64_t u64_t;
typedef int64_t i64_t;
typedef uint32_t u32_t;
typedef uint16_t u16_t;
typedef uint8_t u8_t;
typedef int32_t i32_t;
typedef int16_t i16_t;
typedef int8_t i8_t;

#endif /*WIN32||WINDOWS*/
#endif /*__CAMB_TYPES*/

/**< Return values for CNRT API calls. */
//! @brief An enum describes CNRT API return values.
/*! Function returns values of CNRT API interfaces. */
typedef enum {
  CNRT_RET_SUCCESS = 0,
  /*!< The operation was successful. */
  CNRT_RET_WARNING_FAKE_DEVICE = 1,
  /*!< That operations issued previously have not completed yet. */
  CNRT_RET_ERR_NOT_READY = 632006,
  /*!< Use fake device currently. */
  CNRT_RET_ERR_INVALID = 632007,
  /*!< The supplied argument was an invalid argument. */
  CNRT_RET_ERR_NOMEM = 632008,
  /*!< Insufficient memory for the operation. */
  CNRT_RET_ERR_NODEV = 632009,
  /*!< No such device. */
  CNRT_RET_ERR_IO = 632010,
  /*!< I/O error. */
  CNRT_RET_ERR_SYS = 632011,
  /*!< System error. */
  CNRT_RET_ERR_ACCES = 632012,
  /*!< Permission denied. */
  CNRT_RET_ERR_FAULT = 632013,
  /*!< Bad address. */
  CNRT_RET_ERR_BUSY = 632014,
  /*!< Device or resource busy. */
  CNRT_RET_ERR_TIMEOUT = 632015,
  /*!< Time expired. */
  CNRT_RET_ERR_EXIST = 632016,
  /*!< A resource or file already exists. */
  CNRT_RET_ERR_NOSYS = 632017,
  /*!< Function not implemented. */
  CNRT_RET_ERR_AGAIN = 632018,
  /*!< Try again later. */
  CNRT_RET_ERR_NORES = 632019,
  /*!< Out of resource. */
  CNRT_RET_ERR_UNSUPPORTED = 632020,
  /*!< Unsupported operation. */
  CNRT_RET_ERR_INVALID_POINTER = 632021,
  /*!< Invalid pointer. */
  CNRT_RET_ERR_NO_EXIST = 632022,
  /*!< A resource or file does not exist. */
  CNRT_RET_ERR_BROKEN = 632023,
  /*!< Data transmission is broken. */
  CNRT_RET_ERR_INIT = 632024,
  /*!< Uninitialized. */
  CNRT_RET_ERR_STREAM = 632025,
  /*!< Failure on Stream. */
  CNRT_RET_ERR_QUEUE = 632025,
  /*!< Failure on Queue. */
  CNRT_RET_ERR_OUT_RANGE = 632026,
  /*!< Number out of range. */
  CNRT_RET_ERR_MATH_OVERFLOW = 632027,
  /*!< Math results not representable. */
  CNRT_RET_ERR_FUNC_CALL = 632028,
  /*!< Failure to call runtime functions. */
  CNRT_RET_ERR_UNHANDLED = 632029,
  /*!< Unhandled error. */
  CNRT_RET_ERR_INVALID_TYPE = 632030,
  /*!< Invalid type. */
  CNRT_RET_ERR_INVALID_OP = 632031,
  /*!< Invalid operation. */
  CNRT_RET_ERR_MLU = 632032,
  /*!< MLU error. */
  CNRT_RET_ERR_ONCHIP_CORE = 632033,
  /*!< On-chip core error. */
  CNRT_RET_ERR_EVENT = 632034,
  /*!< Failure on event operation. */
  CNRT_RET_ERR_NOTIFIER = 632034,
  /*!< Failure on notifier operation. */
  CNRT_RET_ERR_RESHAPE = 632035,
  /*!< Failure on data reshape. */
  CNRT_RET_ERR_MEMCPY = 632036,
  /*!< Failure on memory copy. */
  CNRT_RET_ERR_ENCRYPT = 632037,
  /*!< Failure on encrypt. */
  CNRT_RET_ERR_INVALID_DATADESC = 632038,
  /*!< Invalid data descriptor. */
  CNRT_RET_ERR_MAP = 632039,
  /*!< Failure on mapping. */
  CNRT_RET_ERR_UNMAP = 632040,
  /*!< Failure on unmapping. */
  CNRT_RET_ERR_CACHE = 632041,
  /*!< Failure on the flush cache. */
  CNRT_RET_ERR_FIND_DEV_ADDR = 632042,
  /*!< Failure on find dev addr. */
  CNRT_RET_ERR_KERNEL_VERSION_TOO_HIGH = 632043,
  /*!< Kernel version too high, not supported. */
  CNRT_RET_ERR_UNKNOWN = 999991,
  /*!< Unknown error. */
  CNRT_RET_ERR_MAX
  /*!< The last one. */
} cnrtRet_t;

/**< Memory types available for allocator. */
//! @brief An enum describes memory types available for allocator.
/*! Enumeration types, used to represent the memory types. */
typedef enum {
  CNRT_MEMTYPE_DEFAULT = 0,
  /*!< Host user space pagable memory. */
  CNRT_MEMTYPE_LOCKED,
  /*!< Host user space pinned memory. */
  CNRT_MEMTYPE_DEV
  /*!< Device memory. */
} cnrtMemType_t;

/**< Malloc types available for cnrtMallocBufferEx. */
//! @brief An enum describes malloc types available for cnrtMallocBufferEx.
/*! Internal enum. */
typedef enum { CNRT_MALLOC_EX_PARALLEL_FRAMEBUFFER = 1 } cnrtMallocExType_t;

/**< Execution modes of tasks on MLU. */
//! @brief An enum execution modes of tasks on MLU.
/*! The number of cores running on the Function of a device. */
typedef enum {
  CNRT_FUNC_TYPE_BLOCK = 1,
  /*!< Use 1 core. */
  CNRT_FUNC_TYPE_BLOCK0 = CNRT_FUNC_TYPE_BLOCK,
  /*!< Use IP core 0. */
  CNRT_FUNC_TYPE_BLOCK1 = CNRT_FUNC_TYPE_BLOCK0 + 1,
  /*!< Use IP heterogeneous core 1. */
  CNRT_FUNC_TYPE_UNION1 = 4,
  /*!< Use 4 cores. */
  CNRT_FUNC_TYPE_UNION2 = 8,
  /*!< Use 8 cores. */
  CNRT_FUNC_TYPE_UNION4 = 16,
  /*!< Use 16 cores. */
  CNRT_FUNC_TYPE_UNION8 = 32,
  /*!< Use 32 cores. */
  CNRT_FUNC_TYPE_MUTABLE = -1,
  /*!< Flexible mode. */
  CNRT_JOB_TYPE_BLOCK = CNRT_FUNC_TYPE_BLOCK,
  /*!< Use 1 core. */
  CNRT_JOB_TYPE_UNION1 = CNRT_FUNC_TYPE_UNION1,
  /*!< Use 4 cores. */
  CNRT_JOB_TYPE_UNION2 = CNRT_FUNC_TYPE_UNION2,
  /*!< Use 8 cores. */
  CNRT_JOB_TYPE_UNION4 = CNRT_FUNC_TYPE_UNION4,
  /*!< Use 16 cores. */
} cnrtFunctionType_t,
    cnrtJobType_t;

/**< DDR Channel for tasks used on MLU. */
//! @brief An enum describe DDR Channel for tasks used on MLU.
/*! Used to represent Channel types. */
typedef enum {
  CNRT_CHANNEL_TYPE_DUPLICATE = -2,
  /*!< Duplicate data on DDR channels, used in runtime context. */
  CNRT_CHANNEL_TYPE_NONE = -1,
  /*!< Use random channel. */
  CNRT_CHANNEL_TYPE_0 = 0,
  /*!< Use DDR channel 0. */
  CNRT_CHANNEL_TYPE_1,
  /*!< Use DDR channel 1. */
  CNRT_CHANNEL_TYPE_2,
  /*!< Use DDR channel 2. */
  CNRT_CHANNEL_TYPE_3
  /*!< Use DDR channel 3. */
} cnrtChannelType_t;

/**< Direction of data transmission. */
//! @brief An enum describes direction of data transmission.
/*! The direction of data transmission. */
typedef enum {
  CNRT_MEM_TRANS_DIR_HOST2DEV = 0,
  /*!< From host to device. */
  CNRT_MEM_TRANS_DIR_DEV2DEV,
  /*!< From device to device, in one device internally. */
  CNRT_MEM_TRANS_DIR_DEV2HOST,
  /*!< From device to host. */
  CNRT_MEM_TRANS_DIR_HOST2HOST,
  /*!< From host to host, not supported yet. */
  CNRT_MEM_TRANS_DIR_PEER2PEER,
  /*!< Peer-to-peer devices, from device to device. */
  CNRT_MEM_TRANS_DIR_NODIR,
  /*!< No direction for initialization. */
} cnrtMemTransDir_t;

/**< Action about cache. */
//! @brief An enum describes Action about cache.
/*! Action about cache. */
typedef enum { CNRT_FLUSH_CACHE = 1, CNRT_INVALID_CACHE = 2 } cnrtCacheOps_t;

/**< Parameter for function call. */
/*!
 *  @struct cnrtDim3_t
 *  @brief A struct describes parameter for function call.
 *
 *  The dimension of task execution. */
typedef struct {
  unsigned int x; /*!< The x aixs. */
  unsigned int y; /*!< The y aixs. */
  unsigned int z; /*!< The z aixs. */
} cnrtDim3_t;

/**< Parameter for invoke function call. */
/*!
 *  @struct cnrtInvokeFuncParam_t
 *  @brief A struct.
 *
 *  Deprecated. Parameters which need to be invoked by the user. */
typedef struct {
  int *data_parallelism;  /*!< Data parallelism.*/
  unsigned int *affinity; /*!< Affinity.*/
  void *end;              /*!< End of struct.*/
} cnrtInvokeFuncParam_t;

/**< Type of cnrtInvokeParam. */
//! @brief An enum describes type of cnrtInvokeParam.
/*! Type of cnrtInvokeParam. */
typedef enum {
  CNRT_INVOKE_PARAM_TYPE_0 = 0,
  /*!< type 0 cnrtInvokeParam. */
} cnrtInvokeParamType_t;

/**< Parameter for function call. */
/*!
 *  @struct cnrtClusterAffinity_t
 *  @brief A struct describes parameter for function call.
 *
 *  Cluster of task execution. */
typedef struct { unsigned int *affinity; /*!< Affinity.*/ } cnrtClusterAffinity_t;

/**< Parameter for function call. */
/*!
 *  @struct cnrtInvokeParam_t
 *  @brief A struct describes parameter for function call.
 *
 * Parameters of the interface cnrtInvokeRuntimeContext_V2(), which need to be
 * invoked by the user. */
typedef struct {
  cnrtInvokeParamType_t invoke_param_type;
  /*!< Invoke param type. */
  cnrtClusterAffinity_t cluster_affinity;
  /*!< Invoke cluster affinity. */
} cnrtInvokeParam_t;

/**< Data type and data order.*/
//! @brief An enum.
/*! Data types. */
typedef enum cnrtDataType {
  CNRT_INVALID = 0x0,
  /*!< Invalid data. */
  CNRT_FLOAT16 = 0x12,
  /*!< 16-bit floating-point data. */
  CNRT_FLOAT32 = 0x13,
  /*!< 32-bit floating-point data. */
  CNRT_FLOAT64 = 0x14,
  /*!< 64-bit floating-point data. */

  CNRT_INT4 = 0x20, /* new element*/

  CNRT_INT8 = 0x21,
  /*!< 8-bit integer. */
  CNRT_INT16 = 0x22,
  /*!< 16-bit integer. */
  CNRT_INT32 = 0x23,
  /*!< 32-bit integer. */
  CNRT_INT64 = 0x24,
  /*!< 64-bit integer. */
  CNRT_AUTO = 0x25,
  /*!< Automatic bit-width integer, change between int8 int16 etc. */

  CNRT_UINT8 = 0x31,
  /*!< 8-bit unsigned integer. */
  CNRT_UINT16 = 0x32,
  /*!< 16-bit unsigned integer. */
  CNRT_UINT32 = 0x33,
  /*!< 32-bit unsigned integer. */
  CNRT_FIX8 = 0x41,
  /*!< 8-bit fixed-point data. */
  CNRT_QUANT8 = 0x51,
  /*!< 8-bit data. */
  CNRT_BOOL = 0x61,
  /*!< Boolean type. */
} cnrtDataType_t;

//! @brief An enum.
/*! Used to represent the format of data placement.
 * Data can be divided into at least four dimensions.
 * Take images as an example, the order of placement can be:
 * The number of images, the number of picture Channels.
 * The height of the images, and the width of images (NCHW).
 */
typedef enum cnrtDimOrder {
  CNRT_NCHW = 0x0123,
  /*!< Placed by the NCHW dimension orders. */
  CNRT_NHWC = 0x0231,
  /*!< Placed by the NHWC dimension orders. */
  CNRT_HWCN = 0x2310,
  /*!< Placed by the HWCN dimension orders. */
  CNRT_TNC = 0x401,
  /*!< Placed by the TNC dimension orders (RNN exclusive). */
  CNRT_NTC = 0x041,
  /*!< Placed by the NTC dimension orders (RNN exclusive). */
  CNRT_NCDHW = 0x01523,
  /*!< Placed by the NCHW dimension orders. */
  CNRT_NDHWC = 0x05231,
  /*!< Placed by the NHWC dimension orders. */
  CNRT_DHWCN = 0x52310,
  /*!< Placed by the HWCN dimension orders. */
} cnrtDimOrder_t;

//! @brief An enum.
/*! Context types. */
typedef enum cnrtRuntimeContextInfo {
  CNRT_RT_CTX_FUNCTION = 1,
  /*!< Computation unit. */
  CNRT_RT_CTX_DEV_ORDINAL = 2,
  /*!< Device ordinal. */
  CNRT_RT_CTX_CORE_NUMBER = 3,
  /*!< Core number set by compile time, has been deprecated. */
  CNRT_RT_CTX_MODEL_PARALLEL = 4,
  /*!< Degree of model parallelism. */
  CNRT_RT_CTX_CHANNEL = 5,
  /*!< Channel of device memory. */
  CNRT_RT_CTX_MAX_BATCH_NUM = 6,
  /*!< Maximum batch number, has been deprecated. */
} cnrtRuntimeContextInfo_t;

//! @brief An enum.
/*! Device types. */
typedef enum cnrtCoreVersion {
  CNRT_1H8 = 0,
  /*!< 1H8 hardware. */
  CNRT_1H16 = 1,
  /*!< 1H16 hardware. */
  CNRT_1H8MINI = 4,
  /*!< 1H8MINI hardware. */
  CNRT_MLU100 = 3,
  /*!< MLU100 hardware. */
  CNRT_MLU270 = 5,
  /*!< MLU270 hardware. */
  CNRT_MLU220 = 6,
  /*!< MLU220 hardware. */
} cnrtCoreVersion_t;

/**< Parameter for cnrtGetDeviceInfo function call.*/
/*!
 *  @struct cnrtDeviceInfo_t
 *  @brief A struct.
 *
 *  Parameters of the interface cnrtGetDeviceInfo(), for get the device info. */
typedef struct {
  char device_name[64];           /*!< Device name. */
  cnrtCoreVersion_t core_version; /*!< Device core version. */
  int core_num;                   /*!< Device core num. */
} cnrtDeviceInfo_t;

/**< Device affinity information. */
/*!
 *  @struct cnrtDeviceAffinity_t
 *  @brief A struct.
 *
 *  A struct describing the device affinity. */
typedef struct {
  uint32_t cpu_count; /*!< The number of CPUs having an affinity with the specified devices. */
  uint32_t cpu_affinity_bitmap[1024]; /*!< Obtain the affinity bitmask of the specified card. */
} cnrtDeviceAffinity_t;

/**< Topology relationship. */
//! @brief An enum.
/*! Topology struct. */
typedef enum {
  CNRT_TOPO_SELF = 0,
  CNRT_TOPO_INTERNAL = 1,
  /*!< Devices that are on the same board. */
  CNRT_TOPO_SINGLE = 2,
  /*!< All devices that only need traverse a single PCIe switch. */
  CNRT_TOPO_MULTIPLE = 3,
  /*!< All devices that need not traverse a host bridge. */
  CNRT_TOPO_HOST_BRIDGE = 4,
  /*!< All devices that are connected to the same host bridge. */
  CNRT_TOPO_CPU = 5,
  /*!< All devices that are connected to the same CPU. */
  CNRT_TOPO_SYSTEM = 6
  /*!< All device in the system. */
} cnrtTopologyRelationshipEnum_t;

/*!
 *  @struct cnrtQuantizedParam
 *  @brief A struct.
 *
 *  Semi-internal struct. A structure describes the parameters that are quantized. */
struct cnrtQuantizedParam;
/*! A pointer to the structure of the parameters that are quantized. */
typedef struct cnrtQuantizedParam *cnrtQuantizedParam_t;

/**< Model and function. */
/*!
 *  @struct cnrtModel
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing Model. */
struct cnrtModel;
/*! A pointer which points to the struct describing Model. */
typedef struct cnrtModel *cnrtModel_t;

/*!
 *  @struct cnrtFunction
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing Function. */
struct cnrtFunction;
/*! A pointer which points to the struct describing Function. */
typedef struct cnrtFunction *cnrtFunction_t;

/**< Parameter descriptor. */

/*!
 *  @struct cnrtParamDesc
 *  @brief A struct that describes the attribute (shape, order, datatype)
 *  of input or output parameter.
 *
 *  You can specify the attribute of input and output parameters by cnrtParamDesc,
 *  and pass them to cnrtInvokeRuntimeContext_V2. */
struct cnrtParamDesc;
/*! A pointer which points to cnrtParamDesc. */
typedef struct cnrtParamDesc *cnrtParamDesc_t;
/*! ``cnrtParamDesc_t`` is a second rank pointer to ``cnrtParamDesc`` which is a
     structure holding the description of IO param. */
typedef struct cnrtParamDesc **cnrtParamDescArray_t;

/*!
 *  @struct cnrtQueue
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing queue. */
struct cnrtQueue;
/*! A pointer which points to the struct describing queue. */
typedef struct cnrtQueue *cnrtQueue_t;

/*!
 *  @struct cnrtNotifier
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing notifier. */
struct cnrtNotifier;
/*! A pointer which points to the struct describing notifier. */
typedef struct cnrtNotifier *cnrtNotifier_t;

/*!
 *  @struct cnrtRuntimeContext
 *  @brief A struct.
 *
 *  A struct describing runtime context. */
struct cnrtRuntimeContext;
/*! A pointer which points to the struct describing runtime context. */
typedef struct cnrtRuntimeContext *cnrtRuntimeContext_t;

/*! The cnrtDev_t is unsigned int64 type. */
typedef u64_t cnrtDev_t;

/*!
 *  @struct cnrtPluginOpDimInfo
 *  @brief A struct.
 *
 *  Semi-internal struct. A structure describes the information about plugin operator dimension. */
struct cnrtPluginOpDimInfo;
/*! A pointer to the structure of the information about plugin operator dimension. */
typedef struct cnrtPluginOpDimInfo *cnrtPluginOpDimInfo_t;

/*!
 * @struct cnrtKernelParamsBuffer.
 * @brief A struct
 *
 * A structure describes the information about plugin operator parameters. */
typedef struct cnrtKernelParamsBuffer {
  void *host_ptr;
  /*!< A pointer to the current params. */
  unsigned int max_param;
  /*!< The max params num of param buffer can store. */
  unsigned int cur_param;
  /*!< The current params num of param buffer. */
  /*!< For plugin op, mark the position of kernel input, output, and static ptr in param. */
  int *input_index;
  int num_input;
  int *output_index;
  int num_output;
  int *static_index;
  int num_static;

  /*!< For plugin op,  mark the position of tensor dim info in param. */
  cnrtPluginOpDimInfo_t dim_info;
  int num_dim_info;
} * cnrtKernelParamsBuffer_t;

/**< Compiler. */
/*!
 * @struct cnrtKernelInitParam.
 * @brief A struct.
 *
 * A structure describes the kernel parameters. */
struct cnrtKernelInitParam;
/*! A pointer to the structure of the kernel parameters. */
typedef struct cnrtKernelInitParam *cnrtKernelInitParam_t;

/************************************************************************
 * Function prototype declaration
 ************************************************************************/

/************************************************************************
 * Error handling
 ************************************************************************/

/**
 * @brief Return string pointer that describes
 *     the error code passed in the argument errCode.
 *
 * The function returns a read only string that is corresponding
 * to the argument @p errcode.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  err_code[in] The error code was returned by previous function call.
 * @retval A pointer that points to a constant string.
 */
extern CNRT_DLL_API const char *cnrtGetErrorStr(cnrtRet_t err_code);

/**
 * @brief Gets the error code set by any runtime calls.
 *     Its value is meaningful only when the return value indicating an error.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @retval An error code of the last call of runtime functions.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetLastErr(void);

/**
 * @brief Check the cnrtRet_t value and print error info.
 *     This function is used for macro CNRT_CHECK().
 *
 *  **Supports all arch.**
 *
 * @param result: The CNRT return enum.
 * @param func: The name of cnrt function to be checked.
 * @param file: The __FILE__ macro.
 * @param line: The __LINE__ macro.
 * @retval: void.
 */
extern CNRT_DLL_API void cnrtCheck(cnrtRet_t result,
                                   const char *const func,
                                   const char *const file,
                                   int const line);

#define CNRT_CHECK(val) cnrtCheck((val), #val, __FILE__, __LINE__)

/*************************************************************************
 * Initialization and destroy
 *************************************************************************/

/**
 * @brief Initializes runtime environment in current process space.
 *
 * This API must be called before any other runtime API calls.
 *
 * To initialize a fake device:
 *
 * 1. Call the cnrtInit API and set the flags[in] to 1.
 *
 *    cnrtInit(1);
 *
 * 2. Declare cnrtDev_t
 *
 *    cnrtDev_t dev;
 *
 * 3. Call the cnrtGetDeviceHandle API and set ordinal[in] to -1.
 *
 *    cnrtGetDeviceHandle(&dev, -1);
 *
 * 4. Call the cnrtSetCurrentDevice API.
 *
 *    cnrtSetCurrentDevice(dev);
 *
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  flags[in] Reserved for further use, pass 0 as well. If you
           set the value of this parameter to 0, the real device is
                   initialized. If you set the value of this parameter to 1,
                   the fake device is initialized.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInit(unsigned int flags);

/**
 * @brief Destroy everything that allocated by runtime API calls.
 *
 * This API should be called after any other runtime API calls.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @retval void (None).
 */
extern CNRT_DLL_API void cnrtDestroy(void);

/******************************************************************************
 * Version and revision
 ******************************************************************************/

/**
 * @brief Returns the version of the CNRT software.
 *
 * Higher version usually offers more features provided by this library.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  ver[out] A pointer to retrieve the version.
 * @retval An unsigned int for version number.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetVersion(unsigned int *ver);

/******************************************************************************
 * Device management
 ******************************************************************************/

/**
 * @brief Gets the device handle by a given device ordinal.
 *
 *  The function returns the device handle given a specific device ordinal.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  pdev[out] A pointer to retrieve the device handle.
 * @param  ordinal[in] The device ordinal to get the device handle.
 * @note   The value of the ordinal parameter should be in the range
           [0~cnrtGetDeviceCount() - 1]. The value -1 represents a fake device.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */

extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceHandle(cnrtDev_t *pdev, int ordinal);

/**
 * @brief Sets the device handle for current thread execution context.
 *
 *  It implies that any subsequent runtime API calls are for this device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  dev[in] The device handle.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentDevice(cnrtDev_t dev);

/**
 * @brief Gets the cnrtDevice handle from current thread execution context.
 *
 * The handle has been set by calling cnrtSetCurrentDevice().
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  pdev[out] A pointer to retrieve the device handle.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetCurrentDevice(cnrtDev_t *pdev);

/**
 * @brief Gets the number of MLU devices in the system.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param  dev_num[out] A pointer to retrieve the number of devices.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceCount(unsigned int *dev_num);

/**
 * @brief Gets the information about the specified device
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param info[out] The information for the specified device.
 * @param device_ordinal[in] The device ordinal to get device information for.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceInfo(cnrtDeviceInfo_t *info, int device_ordinal);

/**
 * @brief  Wait for the current device in current process to complete precedent tasks.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSyncDevice(void);

/******************************************************************************
 * Queue management
 ******************************************************************************/

/**
 * @brief Creates a new queue after calling this function,
 *        it works in asynchronous mode by default.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pQueue[out] A pointer to retrieve the new created Queue handle.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 * @attention Queue numbers should be not greater than 4094 on MLU270.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateQueue(cnrtQueue_t *pQueue);

/**
 * @brief Destroy a queue created by calling cnrtCreateQueue.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param queue[in] A queue handle created by calling cnrtCreateQueue.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyQueue(cnrtQueue_t queue);

/**
 * @brief Function should be blocked until all precedent tasks in the queue are completed.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param queue[in] A queue handle created by calling cnrtCreateQueue.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSyncQueue(cnrtQueue_t queue);

/*********************************************************************************
 * Notifier. Supports both MLU220 and MLU270.
 *********************************************************************************/

/**
 * @brief Creates a notifier corresponding to the current device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param notifier[out] A point to an notifier handle to retrieve newly created notifier.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateNotifier(cnrtNotifier_t *notifier);

/**
 * @brief Destroy a notifier that was created by calling cnrtCreateNotifier.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param notifier[in] A notifier handle to be destroyed.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyNotifier(cnrtNotifier_t *notifier);

/**
 * @brief Waits notifier which has been placed to queue by calling cnrtPlaceNotifier
 *        until it is in the signaled state or exceeds the time-out interval.
 *        This function will block CPU thread.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param notifier[in] AN event handle created by calling cnrtCreateNotifier.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtWaitNotifier(cnrtNotifier_t notifier);

/**
 * @brief Query the status notifier which has been placed to queue by calling cnrtPlaceNotifier.
 *        This function will not block CPU thread.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param notifier[in] A notifier handle created by calling cnrtCreateNotifier.
 *
 * @retval CNRT_RET_SUCCESS If notification instruction has been executed,
 *         CNRT_RET_ERR_BUSY If the preceding tasks is still in progress,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryNotifier(cnrtNotifier_t notifier);

/**
 * @brief Places a notifier in specified queue. This function will not block the CPU thread.
 *        All computation tasks submitted to the queue will wait until event reports
 *        completion before starting execution.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param notifier[in] Signal handle created by calling cnrtCreateNotifier.
 * @param queue[in] A queue handle created by calling cnrtCreateQueue.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtPlaceNotifier(cnrtNotifier_t notifier, cnrtQueue_t queue);

/**
 * @brief Makes the specified queue wait for a notifier. This function is designed for
 *        cross queue synchronization.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param notifier[in] A signal handle created by calling cnrtCreateNotifier.
 * @param queue[in] A queue handle created by calling cnrtCreateQueue or cnrtCreateQueueEx.
 * @param flag[in] The flags control operation.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueueWaitNotifier(cnrtNotifier_t notifier,
                                                    cnrtQueue_t queue,
                                                    unsigned int flag);

/**
 * @brief Gets duration time of two makers.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param start[in] A notifier handle created by calling cnrtCreateNotifier.
 * @param end[in] A notifier handle created by calling cnrtCreateNotifier.
 * @param us[out] The duration time between start and end.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtNotifierDuration(cnrtNotifier_t start,
                                                   cnrtNotifier_t end,
                                                   float *us);

/*********************************************************************************
 * Execution control & BANG C Kernel
 *********************************************************************************/

/**
 * @brief Gets a parameter buffer for cnrtInvokeKernel_V2 or cnrtInvokeKernel_V3.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param params[in] A pointer to a param buffer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetKernelParamsBuffer(cnrtKernelParamsBuffer_t *params);

/**
 * @brief Copy Parambuffer from src_params_buf to dst_params_buf
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dst_params_buf[in] A pointer to an allocated param buffer.
 * @param src_params_buf[in] A pointer to an allocated param buffer.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCopyKernelParamsBuffer(cnrtKernelParamsBuffer_t dst_params_buf,
                                                         cnrtKernelParamsBuffer_t src_params_buf);

/**
 * @brief Adds a parameter to a specific parameter buffer.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param params[in] The destination parameter buffer.
 * @param data[in] A pointer to host memory.
 * @param bytes[in] The size in bytes.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferAddParam(cnrtKernelParamsBuffer_t params,
                                                             void *data,
                                                             size_t bytes);

/**
 * @brief Adds a InputPtr place holder to a specific parameter buffer.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param params[in] The destination parameter buffer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferMarkInput(cnrtKernelParamsBuffer_t params);

/**
 * @brief Adds a OutputPtr place holder to a specific parameter buffer.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param params[in] The destination parameter buffer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferMarkOutput(cnrtKernelParamsBuffer_t params);

/**
 * @brief Adds a StaticPtr place holder to a specific parameter buffer.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param params[in] The destination parameter buffer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferMarkStatic(cnrtKernelParamsBuffer_t params);

/**
 * @brief Destroy a parameter buffer returned by cnrtGetKernelParamsBuffer.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param params[in] A pointer to a param buffer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyKernelParamsBuffer(cnrtKernelParamsBuffer_t params);

/**
 * @brief Invokes a kernel written in Bang with given params on MLU.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param function[in] A point to the MLU function.
 * @param dim[in] The number of grid dimensions.
 * @param params[in] A point to arguments.
 * @param func_type[in] The function type. See cnrtFunctionType_t for details.
 * @param queue[in] A queue associated to the function call.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeKernel_V2(const void *function,
                                                  cnrtDim3_t dim,
                                                  cnrtKernelParamsBuffer_t params,
                                                  cnrtFunctionType_t func_type,
                                                  cnrtQueue_t queue);

/**
 * @brief Creates a kernel init param.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param init_param[in] A pointer to cnrtKernelInitParam_t.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateKernelInitParam(cnrtKernelInitParam_t *init_param);
/**
 * @brief Initializes a kernel memory, the kernel is written in Bang.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * Note: cnrtInitKernelMemory should be called before cnrtInvokeKernel_V3 and after
 * cnrtCreateKernelInitParam.
 *
 * @param function[in] A pointer to MLU function.
 * @param init_param[in] The kernel init param created by cnrtCreateKernelInitParam.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitKernelMemory(const void *function,
                                                   cnrtKernelInitParam_t init_param);
/**
 * @brief Invokes a kernel written by Bang with given params on MLU.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * Note: cnrtInvokeKernel_V3 should be called after cnrtInitKernelMemory. For a bang function, you
 * should call cnrtCreateKernelInitParam and cnrtInitKernelMemory only once, and call
 * cnrtInvokeKernel_V3 many times if you need invoke a bang function multi-times.
 *
 * @param function[in] A pointer to MLU function.
 * @param init_param[in] The kernel init param created by cnrtCreateKernelInitParam and used by
 * cnrtInitKernelMemory.
 * @param dim[in] The number of grid dimensions.
 * @param params[in] A point to arguments.
 * @param func_type[in] The function type. See cnrtFunctionType_t for details.
 * @param queue[in] A queue associated to the function call.
 * @param extra_param[in] A pointer to cnrtInvokeParam_t as extra param.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeKernel_V3(const void *function,
                                                  cnrtKernelInitParam_t init_param,
                                                  cnrtDim3_t dim,
                                                  cnrtKernelParamsBuffer_t params,
                                                  cnrtFunctionType_t func_type,
                                                  cnrtQueue_t queue,
                                                  void *extra_param);
/**
 * @brief Destroy Bang-kernel init param and memory.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param init_param[in] The kernel init param created by cnrtCreateKernelInitParam, used by
 * cnrtInitKernelMemory and cnrtInvokeKernel_V3.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyKernelInitParamAndMemory(cnrtKernelInitParam_t param);

/*********************************************************************************
 * Model load and Function call
 *********************************************************************************/

/**
 * @brief Loads a model from a given model file.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pmodel[out] A point to a cnrtModel_t.
 * @param fname[in]  The file name of a Cambricon model.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtLoadModel(cnrtModel_t *pmodel, const char *fname);

/**
 * @brief Loads a model from memory
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pmodel[out] A pointer to a cnrtModel_t.
 * @param ptr[in] The memory pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtLoadModelFromMem(cnrtModel_t *pmodel, char *ptr);

/**
 * @brief Unloads a model.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A point to a cnrtModel_t.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtUnloadModel(cnrtModel_t model);

/**
 * @brief  Gets actual size of model in offline file.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param fname[in] The file name of a Cambricon model.
 * @param size[out] A pointer to model's actual size.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetModelSize(const char *fname, int *size);

/**
 * @brief  Query model's core version, 1H8 or 1H16.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A pointer to a loaded model.
 * @param coreVersion[out] A pointer to model's core version.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryCoreVersion(cnrtModel_t model,
                                                   cnrtCoreVersion_t *coreVersion);

/**
 * @brief  Query model's parallelism, which means the core number
 * involved to compute this model.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A point to a loaded model.
 * @param modelParallelism[out] A pointer to model's parallelism.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryModelParallelism(cnrtModel_t model, int *modelParallelism);

/**
 * @brief  Query model's stack size, which is the biggest stack size(MB)
 * in all the kernels in the model.
 *
 * Deprecated. This interface will be deleted in the next version and
 * cnrtQueryModelLocalMemSize is recommended to use.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A point to a loaded model.
 * @param size[out] A pointer to the stack size.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryModelStackSize(cnrtModel_t model, uint64_t *stack_size);

/**
 * @brief  Query model's local memory size, which is the biggest local memory size(MB)
 * in all the kernels in the model.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A point to a loaded model.
 * @param local_mem_size[out] A pointer to the local memory size.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryModelLocalMemSize(cnrtModel_t model,
                                                         uint64_t *local_mem_size);

/**
 * @brief Gets function number of a given model.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A pointer of a Cambricon model.
 * @param func_num[out] A pointer to function number.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetFunctionNumber(cnrtModel_t model, int *func_num);

/**
 * @brief Extracts the symbol from the given model if symbol exists.
 *        Otherwise, error code will be returned.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param function[out] A point to a cnrtFunction_t.
 * @param model[in]  A point to a loaded model.
 * @param symbol[in] The symbol name.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtExtractFunction(cnrtFunction_t *pfunction,
                                                  cnrtModel_t model,
                                                  const char *symbol);

/**
 * @brief Creates a MLU function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param function[in] A pointer of cnrtFunction_t.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateFunction(cnrtFunction_t *pfunction);

/**
 * @brief Destroy a function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param function[in] A point to a function generated by cnrtExtractFunction.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyFunction(cnrtFunction_t function);

/**
 * @brief Gets index of paramdesc by name from a function.
 *
 *  **Supports only MLU270.**
 *
 * @param function[in] A point to a function generated by cnrtExtractFunction.
 * @param name[in] A point to a name that was set to a tensor before compiling.
 * @param index[out] A point to a index, will return right index of param_desc while name match.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetParamIndexByName(cnrtFunction_t func,
                                                      const char *name,
                                                      int *index);

/**
 * @brief Gets support shape dim_num by name from a function.
 *
 *  **Supports only MLU270.**
 *
 * @param function[in] A point to a function generated by cnrtExtractFunction.
 * @param name[in] A point to a name that was set to a tensor before compiling.
 * @param dim_num[out] A point to a int, will return right dim num of param_desc while name match.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetSupportedParamDimNumberByName(cnrtFunction_t func,
                                                                   const char *name,
                                                                   int *dim_num);

/**
 * @brief Gets support shape value by name from a function.
 *
 *  **Supports only MLU270.**
 *
 * @param function[in] A point to a function generated by cnrtExtractFunction.
 * @param name[in] A point to a name  that was set to a tensor before compiling.
 * @param dim_shape[out] A point to dim_num int values, will return right shape of param_desc while
 *        name match.
 *        The value will be -1 when dim is variable.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetSupportedParamShapeByName(cnrtFunction_t func,
                                                               const char *name,
                                                               int *dim_shape);

/**
 * @brief Gets support data type by name from a function.
 *
 *  **Supports only MLU270.**
 *
 * @param function[in] A point to a function generated by cnrtExtractFunction.
 * @param name[in] A point to a name  that was set to a tensor before compiling.
 * @param dtype[out] A point to a cnrt datatype, will return right data type of param_desc while
 *        name match.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetSupportedParamDataTypeByName(cnrtFunction_t func,
                                                                  const char *name,
                                                                  cnrtDataType_t *dtype);

/**
 * @brief Gets support dim_order by name from a function.
 *
 *  **Supports only MLU270.**
 *
 * @param function[in] A point to a function generated by cnrtExtractFunction.
 * @param name[in] A point to a name  that was set to a tensor before compiling.
 * @param dorder[out] A point to a cnrt order, will return right order of param_desc while name
 *        match.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetSupportedParamLayoutByName(cnrtFunction_t func,
                                                                const char *name,
                                                                cnrtDimOrder_t *dorder);

/**
 * @brief Generates a copy of source MLU function. The source and destination function share the
 *        same kernel on host, but they have different device space, so model
 *        data(include instruction) is doubled on device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param src[in] Pointer to a source MLU function.
 * @param dst[out] Pointer to a destination MLU function pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCopyFunction(cnrtFunction_t *dst, cnrtFunction_t src);

/*********************************************************************************
 * Memory management
 *********************************************************************************/

/**
 * @brief Allocates nByte bytes and place a pointer to pointer
 *        in pPtr to the allocated host memory. If bytes is 0, then
 *        cnrtMallocHost returns either NULL, or a unique pointer value
 *        that can later be passed to cnrtFreeHost.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pPtr[out]  A pointer to pointer for retrieving allocated host memory.
 * @param bytes[in] The number bytes of memory to be allocated.
 * @param type[in]  The memory type to be allocated.
 *                  See CNRT_HOST_MEMORY_TYPE_LOCK and CNRT_HOST_MEMORY_TYPE_MAPPED for details.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocHost(void **pPtr, size_t bytes, cnrtMemType_t type);

/**
 * @brief Frees the memory space pointed by ptr, which must be
 *        returned by a previous call of cnrtMallocHost.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param ptr[in]  A point to the address of memory to be free.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFreeHost(void *ptr);

/**
 * @brief Allocates memory on MLU device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pPtr[out] A pointer to pointer for retrieving allocated device memory.
 * @param bytes[in] Allocate size.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMalloc(void **pPtr, size_t bytes);

/**
 * @brief Allocates memory on MLU device. For P2P.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pPtr[out] A pointer to pointer for retrieving allocated device memory.
 * @param bytes[in] Allocate size.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocFrameBuffer(void **pPtr, size_t bytes);

/**
 * @brief Allocates memory on MLU device, for extension
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pPtr[out] A pointer to pointer for retrieving allocated device memory.
 * @param param[in] The parameter buffer allocated by cnrtAllocParam
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocBufferEx(void **pPtr, void *param);

/**
 * @brief Deallocates MLU device Memory.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param ptr[in] A point to the memory to be free.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFree(void *ptr);

/**
 * @brief Deallocates MLU multiple device memory addresses allocated
 *        by cnrtMalloc.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param ptr[in] A pointer array.
 * @param length[in] The array length.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFreeArray(void **ptr, int length);

/**
 * @brief Map device addr returned by a previous call to cnrtMalloc
 *        into host addr in user space.
 *
 *  **Supports only MLU220_ARM.**
 *
 * @param host_ptr[out] The mapped address of host.
 * @param dev_ptr[in]  The address of device.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMap(void **host_ptr, void *dev_ptr);

/**
 * @brief Map device addr in the range from a previous call to cnrtMalloc
 *        into host addr in user space.
 *
 * *  **Supports only MLU220_ARM.**
 *
 * @param host_ptr[out] mapped address of host.
 * @param dev_ptr[in]  address of device.
 * @param size[in]  map size
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMapRange(void **host_ptr, void *dev_ptr, size_t size);

/**
 * @brief Unmaps the memory space pointed by host_ptr, which must
 *        be returned by a previous call to cnrtMap.
 *
 *  **Supports only MLU220_ARM.**
 *
 * @param host_ptr[in] A point to the memory to be freed.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtUnmap(void *host_ptr);

/**
 * @brief Gets device address according to mappped_host_ptr
 *
 * @param dev_ptr[out] The address of device.
 * @param mappped_host_ptr[in] The mapped address of host.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFindDevAddrByMappedAddr(void *mappped_host_ptr, void **dev_ptr);

/**
 * @brief Takes an action in cache
 *
 *  **Supports only MLU220_ARM.**
 *
 * @param host_ptr[in] The mapped address of host.
 * @param opr[in] The action about in cache.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCacheOperation(void *host_ptr, cnrtCacheOps_t opr);

/**
 * @brief Take an action in cache with host addr in the range by cnrtMap or cnrtMapRange
 *
 *  **Supports only MLU220_ARM.**
 *
 * @param host_ptr[in] maped address of host.
 * @param size[in] operation size.
 * @param opr[in] action about in cache.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCacheOperationRange(void *host_ptr,
                                                      size_t size,
                                                      cnrtCacheOps_t opr);

/**
 * @brief Copy data from source address to destination address. The copy direction
 *        is specified by input parameter dir. The copy operation is
 *        always performed on current device which is set by cnrtSetCurrentDevice.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dst[in] The destination address.
 * @param src[in] The source address.
 * @param bytes[in] The number of bytes to be copied.
 * @param dir[in] The direction of transfer.
 *                See  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST, and
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST for details.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemcpy(void *dst, void *src, size_t bytes, cnrtMemTransDir_t dir);

/**
 * @brief Aysnchronous copy data from source address to destination address. The copy direction
 *        is specified by input parameter dir. The copy operation is
 *        always performed on current device which is set by cnrtSetCurrentDevice.
 *
 *  **Supports only MLU270.**
 *
 * @param dest[in] The destination address.
 * @param src[in] The source address.
 * @param bytes[in] The number of bytes to be copied.
 * @param queue[in] The queue handle created by calling cnrtCreateQueue.
 * @param dir[in] The direction of transfer.
 *                See  CNRT_MEM_TRANS_DIR_HOST2DEV and
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST for details.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtMemcpyAsync(void *dest, void *src, size_t bytes, cnrtQueue_t queue, cnrtMemTransDir_t dir);

/**
 * @brief Fills the bytes of the device memory space
 *        pointed by devPtr with the constant value c.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param ptr[in] The device memory address.
 * @param c[in] The value to be filled.
 * @param bytes[in] The number of bytes to be filled.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemset(void *ptr, int c, size_t bytes);

/**
 * @brief Sets MLU stack space memory to stack_size(MB).
 *
 * Deprecated. This interface will be deleted in the next version and
 * cnrtSetLocalMem is recommended to use.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param stacksize[in] The size of MLU stack space memory will be set.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetStackMem(unsigned int stacksize);

/**
 * @brief Gets MLU stack space memory to stack_size(MB).
 *
 * Deprecated. This interface will be deleted in the next version and
 * cnrtGetLocalMem is recommended to use.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pStacksize[out] The size of MLU stack space memory will be get.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, CNRT_RET_ERR_MLU is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetStackMem(unsigned int *pStacksize);

/**
 * @brief Sets MLU local memory space memory(MB).
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param local_mem_size[in] The size of MLU local memory space memory will be set.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, CNRT_RET_ERR_MLU is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetLocalMem(unsigned int local_mem_size);

/**
 * @brief Gets MLU local memory space(MB).
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pLocalsize[out] The size of MLU local memory space will be get.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, CNRT_RET_ERR_MLU is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetLocalMem(unsigned int *pLocalsize);

/**
 * @brief Gets max memory used of function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param function[in] A point to the MLU function.
 * @param pMemused[out] Return value.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetFunctionMemUsed(cnrtFunction_t function, int64_t *pMemused);

/**
 * @brief Gets max memory used of model.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param model[in] A point to the model.
 * @param pMemused[out] Return value.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetModelMemUsed(cnrtModel_t model, int64_t *pMemused);

/*********************************************************************************
 * Channel control, only MLU270 support.
 *********************************************************************************/

/**
 * @brief Sets memory and computation channel on current MLU device. Once
 *        a channel is configured, all memory allocation(eg. cnrtMalloc)
 *        will be performed on this channel. And all function invokation
 *        will be performed on this channel too.
 *
 *        Attention: The above policy only take effect when model parallelism
 *        is 1.
 *
 *        This function is base on CPU thread context. So it's action scope
 *        is within current CPU thread. This function should be called after
 *        cnrtSetCurrentDevice;
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param cnrtChannelType_t[in] The channel.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentChannel(cnrtChannelType_t channel);

/**
 * @brief Gets current channel of current CPU thread.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pChannel[out] Pointer to channel.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetCurrentChannel(cnrtChannelType_t *pChannel);

/*********************************************************************************
 * Parameter descriptor related API
 *********************************************************************************/

/**
 * @brief Creates parameter descriptor.
 *
 * @param param_desc[in] A pointer to parameter descriptor.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateParamDesc(cnrtParamDesc_t *param_desc);

/**
 * @brief Destroy parameter descriptor.
 *
 * @param param_desc[in] The parameter descriptor.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyParamDesc(cnrtParamDesc_t param_desc);

/**
 * @brief Creates cnrt param descriptor array.
 * @param param_descs[out] A pointer of parameters.
 * @param param_num[in] The length of parameters.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateParamDescArray(cnrtParamDescArray_t *param_descs,
                                                       int param_num);

/**
 * @brief Destroies cnrt param descriptor array.
 * @param param_descs[in] A pointer of parameters.
 * @param param_num[in] The length of parameters.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyParamDescArray(cnrtParamDescArray_t param_descs,
                                                        int param_num);

/**
 * @brief Sets shape to cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param dims[in] A pointer of dim values.
 * @param dim_num[in] The length of dims.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetShapeToParamDesc(cnrtParamDesc_t param_desc,
                                                      int *dims,
                                                      int dim_num);

/**
 * @brief Sets name to cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param name[in] A pointer of name.
 * @param name_size[in] The length of name.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetNameToParamDesc(cnrtParamDesc_t param_desc,
                                                     char *name,
                                                     int name_size);
/**
 * @brief Sets data type to cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param dtype[in] The data type of param.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetDataTypeToParamDesc(cnrtParamDesc_t param_desc,
                                                         cnrtDataType_t dtype);

/**
 * @brief Gets all dim product from cnrt param descriptor, can't contain dim less than 1.
 * @param param_desc[in] A pointer of a parameter.
 * @param num[out] A pointer of a num.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetParamElementNum(cnrtParamDesc_t param_desc, size_t *num);

/**
 * @brief Gets total size from cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param size[out] A pointer of size, is all shape multi data type size,
 * shape should be set positive integer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetParamDescSize(cnrtParamDesc_t param_desc, int64_t *size);

/**
 * @brief Gets shape from cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param dims[out] A pointer of dim values.
 * @param dim_num[out] The length of dims.
 * @return CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetShapeFromParamDesc(cnrtParamDesc_t param_desc,
                                                        int **dims,
                                                        int *dim_num);

/**
 * @brief Gets name from cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param name[out] A pointer of name.
 * @param name_size[out] The length of name.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetNameFromParamDesc(cnrtParamDesc_t param_desc,
                                                       char **name,
                                                       int *name_size);

/**
 * @brief Gets data type From cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param dtype[out] The data type of param.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDataTypeFromParamDesc(cnrtParamDesc_t param_desc,
                                                           cnrtDataType_t *dtype);

/**
 * @brief Gets dim order from cnrt param descriptor.
 * @param param_desc[in] A pointer of a parameter.
 * @param dim_order[out] The data type of param.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDimOrderFromParamDesc(cnrtParamDesc_t param_desc,
                                                           cnrtDimOrder_t *dim_order);

/**
 * @brief Gets cnrt param descriptor from paramdesc array via param name.
 * @param param_desc[out] A pointer of a parameter.
 * @param param_descs[in] A pointer of parameter desc array.
 * @param param_num[in] The number of parameter desc array.
 * @param name[in] A pointer of name.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtGetParamDescFromParamDescArrayByName(cnrtParamDesc_t *param_desc,
                                         cnrtParamDescArray_t param_descs,
                                         int param_num,
                                         const char *name);

/**
 * @brief Gets cnrt param index from paramdesc array via param name.
 * @param param_desc[out] A pointer of a parameter.
 * @param param_descs[in] A pointer of parameter desc array.
 * @param param_num[in] The number of parameter desc array.
 * @param name[in] A pointer of name.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetIndexFromParamDescArrayByName(int *index,
                                                                   cnrtParamDescArray_t param_descs,
                                                                   int param_num,
                                                                   const char *name);

/**
 * @brief Reshapes filter data from source address to destination address.
 *        The origin source data layout is src[N][H][W][C].
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dst[out] The destination address.
 * @param src[in] The source address.
 * @param n/h/w/c[in] The origin data layout.
 * @param type[in] The data type of dst[out] and src[in].
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtFilterReshape(void *dst, void *src, int n, int h, int w, int c, cnrtDataType_t type);

/**
 * @brief Reshapes data from source address to destination address.
 *        Only between NHWC and NCHW.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dst[out] The destination address.
 * @param src[in] The source address.
 * @param n/h/w/c[in] The origin data layout.
 * @param type[in] The data type of dst[out] and src[in].
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtReshapeNCHWToNHWC(void *dst, void *src, int n, int h, int w, int c, cnrtDataType_t type);

/**
 * @brief Reshapes data from source address to destination address.
 *        Only supports reshaping between NHWC and NCHW.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dst[out] The destination address.
 * @param src[in] The source address.
 * @param n/h/w/c[in] The origin data layout.
 * @param type[in] The data type of dst[out] and src[in].
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtReshapeNHWCToNCHW(void *dst, void *src, int n, int h, int w, int c, cnrtDataType_t type);

/**
 * @brief Gets model level from offline file.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param fname[in] The offline file name.
 * @param model_level[out] The model level.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetModelLevelFromFile(const char *fname, int *model_level);

/****************************************************************************
 * Generic parameters handling
 ***************************************************************************/

/**
 * @brief Allocates a CNRT parameter context buffer.
 *
 * @param pParam[out] A pointer to the parameter context buffer pointer.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtAllocParam(void **pParam);

/**
 * @brief Destroy a CNRT parameter context buffer.
 *
 * @param param[in] The parameter context buffer pointer.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestoryParam(void *param);

/**
 * @brief Adds one parameter to parameter context buffer.
 *
 * @param param[in] The parameter context buffer pointer.
 * @param name[in] The name of the parameter.
 * @param len[in] The length of the parameter.
 * @param data[in] A pointer to the parameter.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtAddParam(void *param, char *name, int len, void *data);

/**
 * @brief Gets one parameter from parameter context buffer.
 *
 * @param param[in] The parameter context buffer pointer.
 * @param name[in] The name of the parameter.
 * @param out[out] The result buffer.
 * @param outlen[in] The result buffer length.
 *
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 * @retval CNRT_RET_ERR_MEMCPY If parameter actual length is larger than result buffer length.
 * @retval CNRT_RET_ERR_NO_EXIST If "name" is not found in param context.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetParam(void *param, char *name, void *out, int outlen);

/**
 * @brief Converts a float or double to float16, store it at specific position (*f16 = (f16)d).
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param d[in] The number to convert.
 * @param f16[out] The place to store.
 * @retval The error code of the last call of runtime functions.
 */
extern CNRT_DLL_API cnrtRet_t cnrtConvertDoubleToHalf(uint16_t *f16, double x);

/**
 * @brief Converts a float to float16, store it at specific position (*f16 = (f16)d).
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param d[in] The number to convert.
 * @param f16[out] The place to store.
 * @retval The error code of the last call of runtime functions.
 */
extern CNRT_DLL_API cnrtRet_t cnrtConvertFloatToHalf(uint16_t *f16, float d);

/**
 * @brief Converts a float16 to float or double, store it at specific position (*d =
 * (float or double)(f16)).
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param f16[in] The number to convert.
 * @param d[out] The place to store.
 * @retval The error code of the last call of runtime functions.
 */

extern CNRT_DLL_API cnrtRet_t cnrtConvertHalfToDouble(double *d, uint16_t f16);

extern CNRT_DLL_API cnrtRet_t cnrtConvertHalfToFloat(float *d, uint16_t f16);

/**
 * @brief Gets datatype's size.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dt[in] The enum cnrtDataType variable.
 * @retval The size of DataType.
 */
extern CNRT_DLL_API int cnrtDataTypeSize(cnrtDataType_t dt);

/**
 * @brief Creates and deploy a runtime context on specified MLU device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[out] The receiver pointer of runtime context.
 * @param function[in] A point to the MLU function. Function must be initialized from a compiled OP
 *        or from an offline model(cnrtExtractFunction).
 * @param extra[in]  Reserved for future use.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateRuntimeContext(cnrtRuntimeContext_t *pctx,
                                                       cnrtFunction_t function,
                                                       void *extra);

/**
 * @brief Fork and deploy a runtime context on a specified MLU device. This API can only be used for
 * different queues or threads to avoid concurrent conflict on private spaces when invoking runtime
 * context. This API  creates dst_pctx inside, so you need to destroy dst_pctx when it is used up.
 *
 *  **Supports only MLU270**
 *
 * @param dst_pctx[out] receiver pointer of runtime context
 * @param src_pctx[in] point to the MLU runtime context. RuntimeContext must be initialized and
 *        called initRuntimeContextMemroy.
 * @param extra[in]  Reserved for future use, should set NULL now.
 * @retval CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtForkRuntimeContext(cnrtRuntimeContext_t *dst_pctx,
                                                     cnrtRuntimeContext_t src_pctx,
                                                     void *extra);

/**
 * This API is not recommended to use and will be deprecated in a next release.
 *
 * @brief Sets channel on the specified MLU device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] The receiver pointer of runtime context.
 * @param channel[in] Assign the DDR channel of the runtime context.
 *        CNRT_CHANNEL_TYPE_NONE: Let CNRT decide channel. It is recommended for most users.
 *        CNRT_CHANNEL_TYPE_DUPLICATE: Const memory will be duplicated on DDR channels.
 *        It could improve concurrency performance when you have multiple threads or
 *        streams associating with this runtime context with the cost of memory consumption.
 *        For advanced users, you could assign channel manually.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetRuntimeContextChannel(cnrtRuntimeContext_t pctx,
                                                           cnrtChannelType_t channel);

/**
 * @brief Sets device ID on the specified MLU device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] The receiver pointer of runtime context.
 * @param dev_ordinal[in] The device ordinal of which the runtime context is deployed.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetRuntimeContextDeviceId(cnrtRuntimeContext_t pctx,
                                                            int dev_ordinal);

/**
 * @brief Initializes runtime context on the specified MLU device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer of runtime context.
 * @param extra[in] For expand.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitRuntimeContext(cnrtRuntimeContext_t pctx, void *extra);

/**
 * @brief Creates a runtime context queue.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer of runtime context.
 * @param queue[out] Get a queue.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextCreateQueue(cnrtRuntimeContext_t pctx,
                                                            cnrtQueue_t *queue);

/**
 * @brief Creates an event corresponding to a specified runtime context.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer of runtime context.
 * @param pnotifier[out] A point to a notifier handle to retrieve newly created notifier.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextCreateNotifier(cnrtRuntimeContext_t pctx,
                                                               cnrtNotifier_t *pnotifier);

/**
 * @brief Allocates device memory by bytes array.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param ptr[out] A point to the allocated memory array.
 * @param bytesArray[in] Allocate memory size array.
 * @param num[in] Allocate memory array length.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextMallocBySizeArray(cnrtRuntimeContext_t pctx,
                                                                  void ***ptr,
                                                                  size_t *bytesArray,
                                                                  int length);

/**
 * @brief Frees the memory space pointed by ptr, which must
 *        be returned by a previous call to cnrtRuntimeContextMallocBySizeArray.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer to runtime context
 * @param ptr[in] A point to the memory to be free.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextFree(cnrtRuntimeContext_t pctx, void *ptr);

/**
 * @brief Frees the memory space array pointed by ptr, which must
 *        be returned by a previous call to cnrtRuntimeContextMallocBySizeArray.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer to runtime context
 * @param ptr[in] A pointer array.
 * @param length[in] The array length.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextFreeArray(cnrtRuntimeContext_t pctx,
                                                          void **ptr,
                                                          int length);

/**
 * @brief Destroy a runtime context.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer to runtime context.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyRuntimeContext(cnrtRuntimeContext_t pctx);

/**
 * We are going to support dynamic shape in the next release version(V4.1.0).
 * In order to avoid changing API, we expose dynamic shape API(
 * cnrtInvokeRuntimeContext_V2) in advance.
 * We strongly recommend you to use cnrtInvokeRuntimeContext_V2 rather than
 * cnrtInvokeRuntimeContext. See cnrtInvokeRuntimeContext_V2 for details.
 *
 * @brief Invokes a runtime context on MLU.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer to runtime context.
 * @param params[in]  A point to arguments.
 * @param queue[in] A queue associated to the function call.
 * @param extra[in]  Reserved for future use.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeRuntimeContext(cnrtRuntimeContext_t pctx,
                                                       void **params,
                                                       cnrtQueue_t queue,
                                                       void *extra);

/**
 * @brief Invokes a runtime context on MLU.
 *
 * We are going to support dynamic shape in the next release version(V4.1.0).
 * In order to avoid changing API, we expose dynamic shape API in advance.
 * In current release version(V4.0.0), you can pass NULL pointer to param_descs.
 * The behavior of cnrtInvokeRuntimeContext_V2 is the same as cnrtInvokeRuntimeContext.
 * We recommend you to use cnrtInvokeRuntimeContext_V2 rather than
 * cnrtInvokeRuntimeContext.
 *
 * @param pctx[in] A pointer to runtime context.
 * @param param_descs[in]  The parameter descriptor array.
 * @param param_buffers[in] The parameter buffer array.
 * @param queue[in] A queue associated to the function call.
 * @param extra[in] Reserved for future use.
 *
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeRuntimeContext_V2(cnrtRuntimeContext_t pctx,
                                                          cnrtParamDesc_t *param_descs,
                                                          void **param_buffers,
                                                          cnrtQueue_t queue,
                                                          void *extra);

/**
 * @brief Gets the runtime context info on the specified MLU device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer of runtime context.
 * @param key[in] The key of the runtime context.
 * @param out[out] The value of the key.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetRuntimeContextInfo(cnrtRuntimeContext_t pctx,
                                                        cnrtRuntimeContextInfo_t key,
                                                        void **out);

/**
 * @brief Sets current device to runtime context bounded device.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param pctx[in] A pointer of runtime context.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentContextDevice(cnrtRuntimeContext_t pctx);

/**
 * @brief Gets the specific CPU bitmap according to the device index write to
 *        the struct DeviceAffinity
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param affinity[out] The array reference in which to return a bitmask of CPUS, 64
 *        CPUS per unsigned long on 32 bit.
 * @param dev_ordinal[in] The device dev_ordinal.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceAffinity(cnrtDeviceAffinity_t *affinity,
                                                    int dev_ordinal);

/**
 * @brief Clears the current thread affinity binding.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dev_ordinal[in] The device ordinal.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtClearCurrentThreadAffinity(int dev_ordinal);

/**
 * @brief Sets the current thread to the specific CPU according to the device affinity.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dev_ordinal[in] The device ordinal.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentThreadAffinity(int dev_ordinal);

/**
 * @brief Gets the ordinal1 topology relationship with the ordinal2.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param relationship[out] The relationship of two device'topology.
 * @param dev_ordinal1[in] The first device ordinal.
 * @param dev_ordinal2[in] The second device ordinal.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtTopologyGetRelationship(cnrtTopologyRelationshipEnum_t *relationship,
                            int dev_ordinal1,
                            int dev_ordinal2);

/**
 * @brief Retrieves the set of devices that nearest to a given device at a specific
 *        interconnectivity level for all products.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param relationship[in] The specified relationship.
 * @param count[out] The ordinalArray' size.
 * @param ordinalArray[out] The ID of related devices.
 * @param dev_ordinal[in] The device ordinal.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtTopologyGetNearestDevices(cnrtTopologyRelationshipEnum_t relationship,
                              uint64_t *count,
                              uint64_t *ordinal_array,
                              int dev_ordinal);

/**
 * @brieif Retrieves the set of devices that have a CPU affinity with the given CPU number
 *         for all products.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param cpuid[in] The specified CPU ID.
 * @param count[out] The ordinalArray's size.
 * @param ordinalArray[out] The ID of related devices.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtTopologyGetCpuRelatedDevices(int cpuid,
                                                               uint64_t *count,
                                                               uint64_t *ordinal_array);

/**
 * @brief Queries if a device(Dev) is capable of directly accessing memories on another(PeerDev).
 * @param CanPeer[out] Value to be returned. CanPeer is 1 represents Dev is of capable of directly
 *        accessing memories on PeerDev and 0 otherwise.
 * @param Dev[in] Device that directly accessing memories on another(PeerDev).
 * @param PeerDev[in] Deivce on which memories to be directly accessed by Dev.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetPeerAccessibility(unsigned int *CanPeer, int Dev, int PeerDev);

/**
 * @brief Copy memories from one device to another. The two devices should be peerable.
 *        You should set current device to srcDevice by calling cnrtSetCurrentDevice()
 *        before using this interface.
 * @param dst[in] Destination device memory pointer.
 * @param dstDevice[in] Destination device.
 * @param src[in] Source device memory pointer.
 * @param srcDevice[in] Source device.
 * @param count[in] Size of memory to be copied in bytes.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtMemcpyPeer(void *dst, int dstDevice, void *src, int srcDevice, size_t count);

/**
 * @brief Creates the quantized param for cast data type.
 * @param param[out] A pointer to cnrtQuantizedParam_t.
 * @param pos[in] The quantized value of position.
 * @param scale[in] The quantized value of scale.
 * @param offset[in] The quantized value of offset.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateQuantizedParam(cnrtQuantizedParam_t *param,
                                                       int pos,
                                                       float scale,
                                                       int offset);

/**
 * @brief Creates the quantized param for cast data type.
 * @param param[out] A pointer to cnrtQuantizedParam_t.
 * @param poses[in] The quantized values of position.
 * @param scales[in] The quantized values of scale.
 * @param offsets[in] The quantized values of offset.
 * @param dimNum[in] The length of dimValues.
 * @param dimValues[in] The dim values of data to quant.
 * @param channelDim[in] The dim of channel in dim values.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateQuantizedParamByChannel(cnrtQuantizedParam_t *param,
                                                                int *poses,
                                                                float *scales,
                                                                float *offsets,
                                                                int dimNum,
                                                                int *dimValues,
                                                                int channelDim);

/**
 * @brief Destroy the quantized param.
 * @param param[in] A pointer to cnrtQuantizedParam_t.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyQuantizedParam(cnrtQuantizedParam_t param);

/**
 * @brief Casts the data type from source address to destination address depend on param.
 *
 *        If the param is null, no need quantized, support the cast data type:
 *        float32->float16, float32->uint8, int64->float16, float16->float32, float16->uint8,
 *        uint8->float32, uint8->float16, float32->float32
 *
 *        If the parm is not null, need quantized, support the case data type:
 *        float32->float16, float32->int16, float32->int8, float32->int32, int32->float32,
 *        float16->int16, int16->float32, int8->float32, float32->float32
 * @param src_addr[in] A pointer to source address.
 * @param src_data_type[in] The type of source data.
 * @param dst_addr[out] A pointer to destination address.
 * @param dst_data_type[in] The type of destination data.
 * @param data_num[in] The number of need cast data.
 * @param param[in] A pointer to cnrtQuantizedParam_t.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCastDataType(void *src_addr,
                                               cnrtDataType_t src_data_type,
                                               void *dst_addr,
                                               cnrtDataType_t dst_data_type,
                                               int data_num,
                                               cnrtQuantizedParam_t param);

/**
 * @brief Adds data stride when destination shape greater than source shape.
 * @param src_addr[in] A pointer to source address.
 * @param data_type[in] A pointer to cnrtDataType_t.
 * @param dst_addr[out] A pointer to destination address.
 * @param dimNum[in] The number of dim.
 * @param dimValues[in] The values of dim array.
 * @param dimStride[in] The values of stride array, which the specified dimension need to add
 *        specified stride size data.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtAddDataStride(void *src_addr,
                                                cnrtDataType_t data_type,
                                                void *dst_addr,
                                                int dimNum,
                                                int *dimValues,
                                                int *dimStride);

/**
 * @brief Transforms the data order to the op need by transform the order of the dim.
 * @param src_addr[in] A pointer to source address.
 * @param data_type[in] A pinter to cnrtDataType_t.
 * @param dst_addr[out] A pointer to destination address.
 * @param dimNum[in] The number of dim.
 * @param dimValues[in] The values of dim array.
 * @param dimOrder[in] The values of dim array which dim order you want to transform.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtTransDataOrder(void *src_addr,
                                    cnrtDataType_t data_type,
                                    void *dst_addr,
                                    int dimNum,
                                    int dimValues[],
                                    int dimOrder[]);

/**
 * @brief Transforms the data order and cast the data type.
 * @param src_addr[in] A pointer to source address.
 * @param src_type[in] A pinter to cnrtDataType_t of source.
 * @param dst_addr[out]  pointer to destination address.
 * @param dst_type[in] A pinter to cnrtDataType_t of destination.
 * @param param[in] A pointer to cnrtQuantizedParam_t.
 * @param dimNum[in] The num of dim.
 * @param dimValues[in] The values of dim array.
 * @param dimOrder[in] The values of dim array which dim order you want to transform.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtTransOrderAndCast(void *src_addr,
                                       cnrtDataType_t src_type,
                                       void *dst_addr,
                                       cnrtDataType_t dst_type,
                                       cnrtQuantizedParam_t param,
                                       int dimNum,
                                       int dimValues[],
                                       int dimOrder[]);
/**
 * @brief Transforms the data channel order. This API is used to change the channel order of the
 * image data to other channel orders, such as changing from ARGB to RGBA, or from RGB to BGR. Only
 * three or four channels of image data are supported.
 * @param src_addr[in] A pointer to the source data address.
 * @param dst_addr[out] A pointer to the destination data address.
 * @param data_type[in] The data type of the source and destination data.
 * @param dim_order[in] The data order of the source and destination data. The CNRT_TNC and CNRT_NTC
 * values are not supported in this parameter.
 * @param dimValues[in] An array represents the source data dimension. This should be consistent
 * with the data order you set in dim_order parameter.
 * @param colorOrder[in] An array represents the image channel order you want to transform.
 * @retval CNRT_RET_SUCCESS The function ends normally. Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtTransDataColorOrder(void *src_addr,
                                         void *dst_addr,
                                         cnrtDataType_t data_type,
                                         cnrtDimOrder_t dim_order,
                                         int dimValues[],
                                         int colorOrder[]);
/**
 * @brief Get a series of input data sizes from a given function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param sizeArray[out] A point to the data size array.
 * @param num[out] The length of the datasize array.
 * @param function[in] The MLU function pointer.
 * @retval CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetInputDataSize(int64_t **sizeArray,
                                                   int *num,
                                                   cnrtFunction_t function);

/**
 * @brief Gets a series of output data sizes from a given function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param sizeArray[out] A point to the data size array.
 * @param num[out] The length of the datasize array.
 * @param function[in] The MLU function pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetOutputDataSize(int64_t **sizeArray,
                                                    int *num,
                                                    cnrtFunction_t function);

/**
 * @brief Gets a series of input data type from a given function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dtype[out] A point to the input data type array.
 * @param num[out] The length of the input data array.
 * @param function[in] The MLU function pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetInputDataType(cnrtDataType_t **dtype,
                                                   int *num,
                                                   cnrtFunction_t function);

/**
 * @brief Gets a series of output data type from a given function.
 *
 *  **Supports both MLU220 and MLU270.**
 *
 * @param dtype[out] A point to the output data type array.
 * @param num[out] The length of the output array.
 * @param function[in] The MLU function pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetOutputDataType(cnrtDataType_t **dtype,
                                                    int *num,
                                                    cnrtFunction_t function);

/**
 * @brief Gets the index input data shape from a given function.
 *
 *  **Supports MLU270.**
 *
 * @param dimValues[out] A point to the input data dimValues array, need free by user.
 * @param dimNum[out] The length of the input data dimValues.
 * @param index[in] The index of input data.
 * @param function[in] The MLU function pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetInputDataShape(int **dimValues,
                                                    int *dimNum,
                                                    int index,
                                                    cnrtFunction_t function);

/**
 * @brief Gets the index output data shape from a given function.
 *
 *  **Supports MLU270.**
 *
 * @param dimValues[out] A point to the output data dimValues array, need free by user.
 * @param dimNum[out] The length of the output dimValues.
 * @param index[in] The index of output data.
 * @param function[in] The MLU function pointer.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetOutputDataShape(int **dimValues,
                                                     int *dimNum,
                                                     int index,
                                                     cnrtFunction_t function);
/**
 * @brief Inferences output shape by input_param, func should be inited from model or fusion_op,
 * inputshape should set to input_params. This func will fill data type and dim_order to params if
 * get right shape.
 *
 *  **Supports MLU270.**
 *
 * @param func[in] A pointer of cnrt function.
 * @param input_num[in] The num of input paramdescs.
 * @param input_params[in] A pointer of input paramdescs.
 * @param output_num[in] The num of output paramdescs.
 * @param output_params[in] A pointer of output paramdescs.
 * @retval CNRT_RET_SUCCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInferFunctionOutputShape(cnrtFunction_t func,
                                                           int input_num,
                                                           cnrtParamDescArray_t input_params,
                                                           int output_num,
                                                           cnrtParamDescArray_t output_params);

/*! A pointer which points to void. */
typedef void *cnrtIpcMemHandle;

/**
 * @brief Acquires an inter-process memory handle for an existing device memory allocation.
 *        cnrtSetCurrentDevicie() should be called before using this interface.
 *
 *        To release the memory resource that the `devPtr` is pointing to, you must use the process
 *        in which cnrtMalloc() API was called. Otherwise, the unexpected errors occurred when you
 *        use other peocesses to release memory resources.
 *
 * @param handle[out] The unique handle for device memory share.
 * @param devPtr[in] Base pointer to previously allocated device memory.
 * @retval CNRT_RET_SUCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtAcquireMemHandle(cnrtIpcMemHandle *handle, void *devPtr);

/**
 * @brief Maps an inter-process memory handle exported from another process and returns the device
 *        memory pointer usable in the local process. cnrtSetCurrentDevicie() should be called
 *        before using this interface.
 *
 *        Note that `devPtr` should be unmapped only with cnrtUnMapMemHandle() in the same process.
 *        Otherwise, the unexpected errors occurred when you use other processes to release
 *        `devPtr`.
 *
 * @param devPtr[out] Returns device memory pointer.
 * @param handle[in] The unique handle for device memory to map.
 * @param flag[in] Flag for this operation. 0 is reserved.
 * @retval CNRT_RET_SUCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtMapMemHandle(void **devPtr, cnrtIpcMemHandle handle, int flag);

/**
 * @brief Unmaps the memory that is mapped with cnrtMapMemHandle(). This interface should be called
 *        in the same process to unmap `devPtr`. cnrtSetCurrentDevicie() should be called before
 *        using this interface.
 *
 * @param devPtr[in] Device memory pointer.
 * @retval CNRT_RET_SUCESS The function ends normally.
 *         Otherwise, the error code is returned.
 */
extern cnrtRet_t cnrtUnMapMemHandle(void *devPtr);

#if defined(__cplusplus)
}
#endif /*__cplusplus*/
#endif /*__CNRT_H*/
