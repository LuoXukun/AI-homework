#include "layers.hpp"

CnmlCastLayer::CnmlCastLayer(vector<int> input_shape, cnmlCastType_t cast_type) {

    const int dimNum = 4;
    _output_count = input_shape[0] * input_shape[1] * input_shape[2] * input_shape[3];
    int output_shape[] = {input_shape[0], input_shape[1], input_shape[2], input_shape[3]};

    if (cast_type == CNML_CAST_FLOAT32_TO_FLOAT16) {
        // prepare input tensor
        _input_tensor = NULL;
        cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
        cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), NULL);
        cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT32);

        // prepare output tensor
        _output_tensor = nullptr;
        cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
        cnmlSetTensorShape_V2(_output_tensor, dimNum, output_shape, nullptr);
        cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT16);

        // mlu buffer ptr
        _output_mlu_ptr = NULL;

        // malloc cnml tensor
        cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
    } else if (cast_type == CNML_CAST_FLOAT16_TO_FLOAT32) {
        // prepare input tensor
        _input_tensor = NULL;
        cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
        cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), NULL);
        cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT16);

        // prepare output tensor
        _output_tensor = nullptr;
        cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
        cnmlSetTensorShape_V2(_output_tensor, dimNum, output_shape, nullptr);
        cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT32);

        // mlu buffer ptr
        _output_mlu_ptr = NULL;

        // malloc cnml tensor
        cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int32_t));
    } else {
        std::clog << "Error: Not support this cast type yet: "
                  << cast_type << std::endl;
        exit(1);
    }

    // prepare cast op and param
    _cast_op = NULL;

    // setup cast op
    cnmlCreateCastOp(&_cast_op, cast_type, _input_tensor, _output_tensor);

    // compile op
    cnmlSetBaseOpCoreVersion(_cast_op, mluConfig.getCoreVersion());
    cnmlSetBaseOpCorenum(_cast_op, mluConfig.getCoreNum());
    cnmlCompileBaseOp_V2(_cast_op);
}

void *CnmlCastLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    // compute cast op on MLU
    cnmlComputeCastOpForward_V4(_cast_op, NULL, input_mlu_ptr, NULL, _output_mlu_ptr, queue, NULL);

    return _output_mlu_ptr;
}

CnmlCastLayer::~CnmlCastLayer() {
    // delete cast op
    cnmlDestroyBaseOp(&_cast_op);

    // delete cnml buffer
    cnrtFree(_output_mlu_ptr);

    // delete cnml tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_output_tensor);
}
