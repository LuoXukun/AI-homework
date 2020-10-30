#include "layers.hpp"

CnmlMlpLayer::CnmlMlpLayer(vector<int> input_shape, 
                           vector<int> output_shape,
                           int input_position, 
                           float input_scale) {

    // prepare data for mlp
    const int dimNum = 4;

    // count input, filter, bias, output nums
    int filter_count = output_shape[1] * input_shape[1] * input_shape[2] * input_shape[3];
    int bias_count = 1 * output_shape[1] * 1 * 1;
    _output_count = output_shape[0] * output_shape[1] * output_shape[2] * output_shape[3];

    // prepare data to converts to mlu memory
    _filter_cpu_ptr = (int16_t *)malloc(filter_count * sizeof(int16_t));
    _bias_cpu_ptr = (int16_t *)malloc(bias_count * sizeof(int16_t));

    // set tensor shapes
    int filter_shape[] = {output_shape[1], input_shape[1], input_shape[2], input_shape[3]};
    int bias_shape[] = {1, output_shape[1], 1, 1};

    // prepare input tensor
    _input_tensor = nullptr;
    cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), nullptr);
    cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT16);

    // prepare filter tensor
    _filter_tensor = nullptr;
    cnmlCreateTensor_V2(&_filter_tensor, CNML_FILTER);
    cnmlSetTensorShape_V2(_filter_tensor, dimNum, filter_shape, nullptr);
    cnmlSetTensorDataType(_filter_tensor, CNML_DATA_FLOAT16);

    // prepare bias tensor
    _bias_tensor = nullptr;
    cnmlCreateTensor_V2(&_bias_tensor, CNML_CONST);
    cnmlSetTensorShape_V2(_bias_tensor, dimNum, bias_shape, nullptr);
    cnmlSetTensorDataType(_bias_tensor, CNML_DATA_FLOAT16);

    // prepare output tensor
    _output_tensor = nullptr;
    cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_output_tensor, dimNum, output_shape.data(), nullptr);
    cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT16);

    // setup mlp op
    _mlp_op = nullptr;
    cnmlCreateMlpOp(&_mlp_op, _input_tensor, _output_tensor, _filter_tensor, _bias_tensor);

    float input_offset = 0;
    // set mlp op computing datatype
    cnmlQuantizedParam_t input_compute_quant;
    cnmlCreateQuantizedParam(&input_compute_quant, input_position, input_scale, input_offset);
    cnmlSetOperationComputingDataType(_mlp_op, _input_tensor, CNML_DATA_INT8, input_compute_quant);

    // set mlp op computing layout
    cnmlSetOperationComputingLayout(_mlp_op, CNML_NCHW);

    // mlu buffer ptr
    _output_mlu_ptr = nullptr;

    // malloc cnml tensor
    cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
}

void CnmlMlpLayer::loadParam(vector<float> filter_data, 
                             vector<float> bias_data, 
                             int filter_position, 
                             float filter_scale) {
    // converts input cpu data
    cnrtCastDataType(filter_data.data(), CNRT_FLOAT32, _filter_cpu_ptr, CNRT_FLOAT16, filter_data.size(), NULL);
    cnrtCastDataType(bias_data.data(), CNRT_FLOAT32, _bias_cpu_ptr, CNRT_FLOAT16, bias_data.size(), NULL);

    // set mlp op computing datatype
    float filter_offset = 0;
    cnmlQuantizedParam_t filter_compute_quant;
    cnmlCreateQuantizedParam(&filter_compute_quant, filter_position, filter_scale, filter_offset);
    cnmlSetOperationComputingDataType(_mlp_op, _filter_tensor, CNML_DATA_INT8, filter_compute_quant);
    cnmlDestroyQuantizedParam(&filter_compute_quant);

    // bind cpu filter, bias to cnml const tensor
    cnmlBindConstData_V2(_filter_tensor, _filter_cpu_ptr, false);
    cnmlBindConstData_V2(_bias_tensor, _bias_cpu_ptr, false);

    // set op core version
    cnmlSetBaseOpCoreVersion(_mlp_op, mluConfig.getCoreVersion());
    // set op core num
    cnmlSetBaseOpCorenum(_mlp_op, mluConfig.getCoreNum());
    // compile op
    cnmlCompileBaseOp_V2(_mlp_op);
}

void *CnmlMlpLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    
    // mlp compute online
    cnmlComputeMlpOpForward_V4(_mlp_op, NULL, input_mlu_ptr, NULL, _output_mlu_ptr, queue, NULL);

    return _output_mlu_ptr;
}

CnmlMlpLayer::~CnmlMlpLayer() {
    // destroy mlp op
    cnmlDestroyBaseOp(&_mlp_op);

    // delete mlu buffer
    cnrtFree(_output_mlu_ptr);

    // delete tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_filter_tensor);
    cnmlDestroyTensor(&_bias_tensor);
    cnmlDestroyTensor(&_output_tensor);

    // delete all pointers
    free(_filter_cpu_ptr);
    free(_bias_cpu_ptr);
}