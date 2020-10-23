#include "layers.hpp"

CnmlPoolingLayer::CnmlPoolingLayer(vector<int> input_shape, 
                     vector<int> kernel_shape, 
                     vector<int> stride) {
    const int dimNum = 4;
    const int height = input_shape[2];
    const int width = input_shape[3];
    const int kernel_h = kernel_shape[0];
    const int kernel_w = kernel_shape[1];
    const int stride_h = stride[0];
    const int stride_w = stride[1];
    const int pad_h = 0, pad_w = 0;

    const int pooled_height = static_cast<int>(floor(static_cast<float>(
            height + 2 * pad_h - kernel_h) /
          stride_h)) + 1;
    const int pooled_width = static_cast<int>(floor(static_cast<float>(
            width + 2 * pad_w - kernel_w) /
          stride_w)) + 1;

    // count tensor nums
    _output_count = input_shape[0] * input_shape[1] * pooled_height * pooled_width;

    // set tensor shapes
    int output_shape[] = {input_shape[0], input_shape[1], pooled_height, pooled_width};

    // prepare input tensor
    _input_tensor = nullptr;
    cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), nullptr);
    cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT16);

    // prepare output tensor
    _output_tensor = nullptr;
    cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_output_tensor, dimNum, output_shape, nullptr);
    cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT16);

    // prepare pool op and param
    _pool_op = NULL;
    _pool_param = NULL;

    // setup pool op param
    cnmlCreatePoolOpParam(&_pool_param,
                            kernel_h,
                            kernel_w,
                            stride_h,
                            stride_w,
                            0, /* origin pad_h ignored */
                            0, /* origin pad_w ignored */
                            0, /* dilation_h not set */
                            0, /* dilation_w not set */
                            CNML_POOL_MAX,
                            CNML_POOL_KVALID,
                            false);
    // setup pool op
    cnmlCreatePoolOp(&_pool_op, _pool_param, _input_tensor, _output_tensor);

    // if op hos no semantics, no need to set data-layout.
    cnmlSetOperationComputingDataType(_pool_op, _input_tensor, CNML_DATA_FLOAT16, NULL);
    // setup pool op computing layout
    cnmlSetOperationComputingLayout(_pool_op, CNML_NCHW);

    // compile op
    cnmlSetBaseOpCoreVersion(_pool_op, mluConfig.getCoreVersion());
    cnmlSetBaseOpCorenum(_pool_op, mluConfig.getCoreNum());
    cnmlCompileBaseOp_V2(_pool_op);

    // mlu buffer ptr
    _output_mlu_ptr = NULL;

    // malloc cnml tensor
    cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
}

void *CnmlPoolingLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    
    // compute pool op on MLU
    cnmlComputePoolOpForward_V4(_pool_op, NULL, input_mlu_ptr, NULL, _output_mlu_ptr, queue, NULL);

    return _output_mlu_ptr;
}

CnmlPoolingLayer::~CnmlPoolingLayer() {
    // delete pool op
    cnmlDestroyBaseOp(&_pool_op);

    // delete cnml buffer
    cnrtFree(_output_mlu_ptr);

    // delete pool op param
    cnmlDestroyPoolOpParam(&_pool_param);

    // delete cnml tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_output_tensor);
}
