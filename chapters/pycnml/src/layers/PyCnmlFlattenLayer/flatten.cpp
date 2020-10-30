#include "layers.hpp"

vector<int> reshape(vector<int> data_order, vector<int> dim_order) {
    vector<int> new_order;
    for (unsigned int i = 0; i < dim_order.size(); i++) {
        new_order.push_back(data_order[dim_order[i]]);
    }
    return new_order;
}

CnmlFlattenLayer::CnmlFlattenLayer(vector<int> input_shape, 
                                   vector<int> output_shape) {
    const int dimNum = 4;
    
    // count tensor nums
    int input_count = input_shape[0] * input_shape[1] * input_shape[2] * input_shape[3];
    _output_count = output_shape[0] * output_shape[1] * output_shape[2] * output_shape[3];

    // NCHW ==> NHWC
    int input_axes = input_shape.size();
    vector<int> trans_dim_order_d2h(input_axes, 0);
    trans_dim_order_d2h[input_axes - 1] = 1;
    for (int i = 1; i < input_axes - 1; i++) {
        trans_dim_order_d2h[i] = i + 1;
    }
    // NCHW => NHWC
    int output_axes = output_shape.size();
    vector<int> trans_dim_order_h2d(output_axes, 0);
    trans_dim_order_h2d[1] = output_axes - 1;
    for (int i = 2; i < output_axes; i++) {
        trans_dim_order_h2d[i] = i-1;
    }

    /* Tranpose d2h */
    // std::cout << "Tranpose d2h\n";
    // prepare input tensor
    _input_tensor = nullptr;
    cnmlCreateTensor_V2(&_input_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_input_tensor, dimNum, input_shape.data(), nullptr);
    cnmlSetTensorDataType(_input_tensor, CNML_DATA_FLOAT16);

    // prepare output tensor
    _transpose_d2h_tensor = nullptr;
    cnmlCreateTensor_V2(&_transpose_d2h_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_transpose_d2h_tensor, dimNum, reshape(input_shape, trans_dim_order_d2h).data(), nullptr);
    cnmlSetTensorDataType(_transpose_d2h_tensor, CNML_DATA_FLOAT16);

    // prepare transpose op and param
    _transpose_d2h_op = NULL;
    _transpose_d2h_param = NULL;

    // setup transpose param
    cnmlCreateNdTransposeOpParam(&_transpose_d2h_param, trans_dim_order_d2h.data(), input_axes);

    // setup transpose op
    cnmlCreateNdTransposeProOp(&_transpose_d2h_op,
                                     _input_tensor,
                                     _transpose_d2h_tensor,
                                     _transpose_d2h_param);
    
    /* reshape */
    // std::cout << "reshape\n";
    vector<int> transpose_h2d_shape = reshape(output_shape, trans_dim_order_d2h);
    // prepare output tensor
    _transpose_h2d_tensor = nullptr;
    cnmlCreateTensor_V2(&_transpose_h2d_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_transpose_h2d_tensor, dimNum, transpose_h2d_shape.data(), nullptr);
    cnmlSetTensorDataType(_transpose_h2d_tensor, CNML_DATA_FLOAT16);

    // prepare transpose op and param
    _reshape_op = NULL;
    _reshape_param = NULL;

    // setup transpose param
    cnmlCreateNdReshapeOpParam(&_reshape_param, transpose_h2d_shape.data(), output_axes);
    
    // setup transpose op
    cnmlCreateReshapeOp(&_reshape_op,
                              _reshape_param,
                              _transpose_d2h_tensor,
                              _transpose_h2d_tensor);
    
    /* Tranpose h2d */
    // std::cout << "Tranpose h2d\n";
    // prepare output tensor
    _output_tensor = nullptr;
    cnmlCreateTensor_V2(&_output_tensor, CNML_TENSOR);
    cnmlSetTensorShape_V2(_output_tensor, dimNum, output_shape.data(), nullptr);
    cnmlSetTensorDataType(_output_tensor, CNML_DATA_FLOAT16);

    // prepare transpose op and param
    _transpose_h2d_op = NULL;
    _transpose_h2d_param = NULL;

    // set up transpose param
    cnmlCreateNdTransposeOpParam(&_transpose_h2d_param, trans_dim_order_h2d.data(), output_axes);

    // set up transpose op
    cnmlCreateNdTransposeProOp(&_transpose_h2d_op,
                               _transpose_h2d_tensor,
                               _output_tensor,
                               _transpose_h2d_param);
    
    // compile op
    cnmlCompileBaseOp(_transpose_d2h_op,
                              mluConfig.getCoreVersion(),
                              mluConfig.getCoreNum());
    cnmlCompileBaseOp(_reshape_op,
                              mluConfig.getCoreVersion(),
                              mluConfig.getCoreNum());
    cnmlCompileBaseOp(_transpose_h2d_op,
                              mluConfig.getCoreVersion(),
                              mluConfig.getCoreNum());
    
    // mlu buffer ptr
    _transpose_d2h_mlu_ptr = NULL;
    _transpose_h2d_mlu_ptr = NULL;
    _output_mlu_ptr = NULL;

    // malloc cnml tensor
    cnrtMalloc(&_transpose_d2h_mlu_ptr, input_count * sizeof(int16_t));
    cnrtMalloc(&_transpose_h2d_mlu_ptr, _output_count * sizeof(int16_t));
    cnrtMalloc(&_output_mlu_ptr, _output_count * sizeof(int16_t));
}

void *CnmlFlattenLayer::forward(void *input_mlu_ptr, cnrtQueue_t queue) {
    
    // compute on mlu
    cnmlComputeTransposeProOpForward_V4(_transpose_d2h_op,
                              NULL,
                              input_mlu_ptr,
                              NULL,
                              _transpose_d2h_mlu_ptr,
                              queue, NULL);
    cnmlComputeReshapeOpForward_V4(_reshape_op, 
                              NULL,
                              _transpose_d2h_mlu_ptr,
                              NULL,
                              _transpose_h2d_mlu_ptr,
                              queue, NULL);
    cnmlComputeTransposeProOpForward_V4(_transpose_h2d_op,
                              NULL,
                              _transpose_h2d_mlu_ptr,
                              NULL,
                              _output_mlu_ptr,
                              queue, NULL);
    
    
    return _output_mlu_ptr;
}

CnmlFlattenLayer::~CnmlFlattenLayer() {
    // delete op
    cnmlDestroyBaseOp(&_transpose_d2h_op);
    cnmlDestroyBaseOp(&_reshape_op);
    cnmlDestroyBaseOp(&_transpose_h2d_op);

    // delete cnml buffer
    cnrtFree(_transpose_d2h_mlu_ptr);
    cnrtFree(_transpose_h2d_mlu_ptr);
    cnrtFree(_output_mlu_ptr);

    // delete op param
    cnmlDestroyNdTransposeOpParam(&_transpose_d2h_param);
    cnmlDestroyReshapeOpParam(&_reshape_param);
    cnmlDestroyNdTransposeOpParam(&_transpose_h2d_param);

    // delete cnml tensors
    cnmlDestroyTensor(&_input_tensor);
    cnmlDestroyTensor(&_transpose_d2h_tensor);
    cnmlDestroyTensor(&_transpose_h2d_tensor);
    cnmlDestroyTensor(&_output_tensor);
}