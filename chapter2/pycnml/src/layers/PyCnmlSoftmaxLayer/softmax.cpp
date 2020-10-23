#include "layers.hpp"

CnmlSoftmaxLayer::CnmlSoftmaxLayer(vector<int> input_shape, int axis) {
    // prepare parameter for softmax
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

    // prepare softmax op
    _softmax_op = NULL;

    // setup softmax op
    cnmlCreateNdSoftmaxOpForward(&_softmax_op, axis, _input_tensor, _output_tensor);

    // if op hos no semantics, no need to set data-layout.
    cnmlSetOperationComputingDataType(_softmax_op, _input_tensor, CNML_DATA_FLOAT16, NULL);

    // compile op
    cnmlSetBaseOpCoreVersion(_softmax_op, mluConfig.getCoreVersion());
    cnmlSetBaseOpCorenum(_softmax_op, mluConfig.getCoreNum());
    cnmlCompileBaseOp_V2(_softmax_op);

    // mlu buffer ptr
    _output_mlu_ptr = NULL;

    // malloc cnml tensor
    cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
}

void *CnmlSoftmaxLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    
    // compute softmax op on mlu
    cnmlComputeNdSoftmaxOpForward_V2(_softmax_op, _input_tensor, input_mlu_ptr, _output_tensor, _output_mlu_ptr, queue, nullptr);

    return _output_mlu_ptr;
}

CnmlSoftmaxLayer::~CnmlSoftmaxLayer() {
    // delete active op
    cnmlDestroyBaseOp(&_softmax_op);

    // delete cnml buffer
    cnrtFree(_output_mlu_ptr);

    // delete cnml tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_output_tensor);

}