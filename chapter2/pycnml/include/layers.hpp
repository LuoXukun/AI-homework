#ifndef PYTHON_CNML_LAYERS_H_
#define PYTHON_CNML_LAYERS_H_

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cnml.h"
#include "cnrt.h"
#include "config.hpp"

using std::vector;

class CnmlLayer{};

class CnmlConvLayer: public CnmlLayer {
    public:
    CnmlConvLayer() = delete;
    CnmlConvLayer(vector<int> input_shape, 
                  vector<int> output_shape, 
                  vector<int> kernel_shape,
                  vector<int> stride,
                  vector<int> dilation,
                  vector<int> pad,
                  int input_position, 
                  float input_scale);
    ~CnmlConvLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    void loadParam(vector<float> filter_data, 
                   vector<float> bias_data, 
                   int filter_position, 
                   float filter_scale);
    private:
    int _output_count;
    int16_t *_bias_cpu_ptr;
    int8_t *_filter_cpu_ptr;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _filter_tensor;
    cnmlTensor_t _bias_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _conv_op;
    cnmlConvOpParam_t _conv_param;
    void *_output_mlu_ptr;
    int _dimNum;
    int _kernel_h;
    int _kernel_w;
    int _stride_h;
    int _stride_w;
    int _dilation_h;
    int _dilation_w;
    int _pad_htop;
    int _pad_wleft;
    int _pad_hbottom;
    int _pad_wright;
};

class CnmlMlpLayer: public CnmlLayer {
    public:
    CnmlMlpLayer() = delete;
    CnmlMlpLayer(vector<int> input_shape, 
                 vector<int> output_shape,
                 int input_position, 
                 float input_scale);
    ~CnmlMlpLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    void loadParam(vector<float> filter_data,
                   vector<float> bias_data, 
                   int filter_position, 
                   float filter_scale);
    private:
    int _output_count;
    int16_t *_filter_cpu_ptr;
    int16_t *_bias_cpu_ptr;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _filter_tensor;
    cnmlTensor_t _bias_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _mlp_op;
    void *_output_mlu_ptr;
};

class CnmlReLuLayer: public CnmlLayer {
    public:
    CnmlReLuLayer() = delete;
    CnmlReLuLayer(vector<int> input_shape);
    ~CnmlReLuLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    
    private:
    int _output_count;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _active_op;
    void *_output_mlu_ptr;
};

class CnmlSoftmaxLayer: public CnmlLayer {
    public:
    CnmlSoftmaxLayer() = delete;
    CnmlSoftmaxLayer(vector<int> input_shape, int axis);
    ~CnmlSoftmaxLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    private:
    int _output_count;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _softmax_op;
    void *_output_mlu_ptr;
};

class CnmlPoolingLayer: public CnmlLayer {
    public:
    CnmlPoolingLayer() = delete;
    CnmlPoolingLayer(vector<int> input_shape, 
                     vector<int> kernel_shape, 
                     vector<int> stride);
    ~CnmlPoolingLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    private:
    int _output_count;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _pool_op;
    cnmlPoolOpParam_t _pool_param;
    void *_output_mlu_ptr;
};

class CnmlFlattenLayer: public CnmlLayer {
    public:
    CnmlFlattenLayer() = delete;
    CnmlFlattenLayer(vector<int> input_shape, 
                     vector<int> output_shape);
    ~CnmlFlattenLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    private:
    int _output_count;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _transpose_d2h_tensor;
    cnmlTensor_t _transpose_h2d_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _transpose_d2h_op;
    cnmlNdTransposeOpParam_t _transpose_d2h_param;
    cnmlBaseOp_t _reshape_op;
    cnmlReshapeOpParam_t _reshape_param;
    cnmlBaseOp_t _transpose_h2d_op;
    cnmlNdTransposeOpParam_t _transpose_h2d_param;
    void *_transpose_d2h_mlu_ptr;
    void *_transpose_h2d_mlu_ptr;
    void *_output_mlu_ptr;
};

class CnmlCastLayer: public CnmlLayer {
    public:
    CnmlCastLayer() = delete;
    CnmlCastLayer(vector<int> input_shape, cnmlCastType_t cast_type);
    ~CnmlCastLayer();
    void *forward(void *input_mlu_ptr, cnrtQueue_t queue);
    private:
    int _output_count;
    cnmlTensor_t _input_tensor;
    cnmlTensor_t _output_tensor;
    cnmlBaseOp_t _cast_op;
    void *_output_mlu_ptr;
};

#endif  // PYTHON_CNML_LAYERS_H_