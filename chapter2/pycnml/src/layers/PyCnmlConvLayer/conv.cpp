#include "layers.hpp"

CnmlConvLayer::CnmlConvLayer(vector<int> input_shape, 
                  vector<int> output_shape, 
                  vector<int> kernel_shape,
                  vector<int> stride,
                  vector<int> dilation,
                  vector<int> pad,
                  int input_position, 
                  float input_scale) {

    const int dimNum = 4;
    const int kernel_h = kernel_shape[0];
    const int kernel_w = kernel_shape[1];
    const int stride_h = stride[0];
    const int stride_w = stride[1];
    const int dilation_h = dilation[0];
    const int dilation_w = dilation[1];
    const int pad_htop = pad[0];
    const int pad_wleft = pad[1];
    const int pad_hbottom = pad[2];
    const int pad_wright = pad[3];

    // count tensor nums
    int filter_count = output_shape[1] * input_shape[1] * kernel_h * kernel_w;
    int bias_count = 1 * 1 * 1 * output_shape[1];
    _output_count = output_shape[0] * output_shape[1] * output_shape[2] * output_shape[3];

    // prepare buffer to store the converted data after calling cnrt-cast function
    // be careful to set buffer size
    _bias_cpu_ptr = (int16_t *)malloc(bias_count * sizeof(int16_t));
    _filter_cpu_ptr = (int8_t *)malloc(filter_count * sizeof(int8_t));

    // set tensor shapes
    int filter_shape[] = {output_shape[1], input_shape[1], kernel_shape[0], kernel_shape[1]};
    int bias_shape[] = {1, output_shape[1], 1, 1};

    // prepare input tensor
    _input_tensor = NULL;
    cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), NULL);
    cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT16);

    // prepare filter tensor
    _filter_tensor = NULL;
    cnmlCreateTensor_V2(&_filter_tensor, CNML_FILTER);
    cnmlSetTensorShape_V2(_filter_tensor, dimNum, filter_shape, NULL);
    cnmlSetTensorDataType(_filter_tensor, CNML_DATA_INT8);

    // prepare bias tensor
    _bias_tensor = NULL;
    cnmlCreateTensor_V2(&_bias_tensor, CNML_CONST);
    cnmlSetTensorShape_V2(_bias_tensor, dimNum, bias_shape, NULL);
    cnmlSetTensorDataType(_bias_tensor, CNML_DATA_FLOAT16);

    // prepare output tensor
    _output_tensor = NULL;
    cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_output_tensor, dimNum, output_shape.data(), NULL);
    cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT16);

    // create conv op ptr and _conv_param
    _conv_op = NULL;
    _conv_param = NULL;

    // set conv op
    // prepare conv param
    cnmlCreateConvOpParam(&_conv_param, stride_h, stride_w, dilation_h, dilation_w, pad_htop + pad_hbottom, pad_wleft + pad_wright);
    // setup conv operator
    cnmlCreateConvOp(&_conv_op, _conv_param, _input_tensor, _output_tensor, _filter_tensor, _bias_tensor);

    float input_offset = 0;
    // prepare input tensor quant param for conv op
    cnmlQuantizedParam_t input_quant_param;

    // create quant-param when setting computing datatype for conv op, please set offset 0 here
    cnmlCreateQuantizedParam(&input_quant_param, input_position, input_scale, input_offset);

    // setup conv op computing datatype
    cnmlSetOperationComputingDataType(_conv_op, _input_tensor, CNML_DATA_INT8, input_quant_param);

    cnmlDestroyQuantizedParam(&input_quant_param);

    // mlu buffer ptr
    _output_mlu_ptr = NULL;

    // malloc cnml tensor
    cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
}

void CnmlConvLayer::loadParam(vector<float> filter_cpu_data, 
                               vector<float> bias_cpu_data, 
                               int filter_position, 
                               float filter_scale) {

    // converts data type for mlu computing
    cnrtCastDataType(bias_cpu_data.data(), CNRT_FLOAT32, _bias_cpu_ptr, CNRT_FLOAT16, bias_cpu_data.size(), NULL);

    float filter_offset = 0;
    // prepare filter tensor quant param for filter data
    cnrtQuantizedParam_t filter_quant_param;
    cnrtCreateQuantizedParam(&filter_quant_param, filter_position, filter_scale, filter_offset);
    cnrtCastDataType(filter_cpu_data.data(), CNRT_FLOAT32, _filter_cpu_ptr, CNRT_INT8, filter_cpu_data.size(), filter_quant_param);
    cnrtDestroyQuantizedParam(filter_quant_param);

    // set filter tensor quant scale and position
    cnmlSetQuantizedPosition(_filter_tensor, filter_position);
    cnmlSetQuantizedScale(_filter_tensor, filter_scale);

    // bind cpu filter, bias to cnml const tensor
    cnmlBindConstData_V2(_filter_tensor, _filter_cpu_ptr, false);
    cnmlBindConstData_V2(_bias_tensor, _bias_cpu_ptr, false);

    // setup conv op computing layout
    cnmlSetOperationComputingLayout(_conv_op, CNML_NCHW);

     // compile op
    cnmlSetBaseOpCoreVersion(_conv_op, mluConfig.getCoreVersion());
    cnmlSetBaseOpCorenum(_conv_op, mluConfig.getCoreNum());
    cnmlCompileBaseOp_V2(_conv_op);
}

void *CnmlConvLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    
    // compute conv op on MLU
    cnmlComputeConvOpForward_V4(_conv_op, NULL, input_mlu_ptr, NULL, _output_mlu_ptr, queue, NULL);

    return _output_mlu_ptr;
}

CnmlConvLayer::~CnmlConvLayer() {
    // delete conv param, op
    cnmlDestroyConvOpParam(&_conv_param);
    cnmlDestroyBaseOp(&_conv_op);

    // delete cnml buffer
    cnrtFree(_output_mlu_ptr);

    // delete cnml tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_filter_tensor);
    cnmlDestroyTensor(&_bias_tensor);
    cnmlDestroyTensor(&_output_tensor);

    // delete pointers (including data pointers)
    free(_filter_cpu_ptr);
    free(_bias_cpu_ptr);
}
