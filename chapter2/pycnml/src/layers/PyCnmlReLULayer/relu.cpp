#include "layers.hpp"

CnmlReLuLayer::CnmlReLuLayer(vector<int> input_shape) {
    // prepare parameter for relu
    const int dimNum = 4;

    // count input, filter, bias, output nums
    _output_count = input_shape[0] * input_shape[1] * input_shape[2] * input_shape[3];

     // prepare input tensor
    _input_tensor = NULL;
    cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), NULL);
    cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT16);

    // prepare output tensor
    _output_tensor = NULL;
    cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_output_tensor, dimNum, input_shape.data(), NULL);
    cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT16);

    // prepare active op and customized active param
    _active_op = NULL;

    // setup costomized active op
    cnmlCreateActiveOp(&_active_op, CNML_ACTIVE_RELU, _input_tensor, _output_tensor);

    // if op hos no semantics, no need to set data-layout.
    cnmlSetOperationComputingDataType(_active_op, _input_tensor, CNML_DATA_FLOAT16, NULL);

    // compile op
    cnmlSetBaseOpCoreVersion(_active_op, mluConfig.getCoreVersion());
    cnmlSetBaseOpCorenum(_active_op, mluConfig.getCoreNum());
    cnmlCompileBaseOp_V2(_active_op);

    // mlu buffer ptr
    _output_mlu_ptr = NULL;

    // malloc cnml tensor
    cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
}

void *CnmlReLuLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    
    // compute relu op on MLU
    cnmlComputeActiveOpForward_V4(_active_op, NULL, input_mlu_ptr, NULL, _output_mlu_ptr, queue, NULL);

    return _output_mlu_ptr;
}

CnmlReLuLayer::~CnmlReLuLayer() {
    // delete active op
    cnmlDestroyBaseOp(&_active_op);

    // delete cnml buffer
    cnrtFree(_output_mlu_ptr);

    // delete cnml tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_output_tensor);
}