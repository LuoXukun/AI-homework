#ifndef PYTHON_CNML_TEST_H_
#define PYTHON_CNML_TEST_H_

#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <memory>
#include <math.h>
#include <utility>
#include "layers.hpp"
#include "tools.hpp"

using std::vector;
using std::pair;
using std::make_pair;
using std::string;

struct Layer {
    CnmlLayer *layer;
    string name;
    LayerType type;
    bool isParamLoaded;
    Layer() = delete;
    Layer(CnmlLayer *layer, 
          string name, 
          LayerType type, 
          bool is_param_loaded): layer(layer), name(name), type(type), isParamLoaded(is_param_loaded) {}
    ~Layer() {
        if (layer != NULL) {
            delete layer;
        }
    }
};

class CnmlNet {
    public:
    CnmlNet(int core_num = 1, cnmlCoreVersion_t core_version = CNML_MLU270);
    ~CnmlNet();
    void setInputShape(int dim_1, int dim_2, int dim_3, int dim_4);
    void createConvLayer(string layer_name,
                         int out_channel, 
                         int kernel_size,
                         int stride,
                         int dilation,
                         int pad,
                         QuantParam quant_param);
    void createMlpLayer(string layer_name,
                        int output_num,
                        QuantParam quant_param);
    void createReLuLayer(string layer_name);
    void createSoftmaxLayer(string layer_name,
                            int axis);
    void createPoolingLayer(string layer_name,
                            int kernel_size, 
                            int stride);
    void createFlattenLayer(string layer_name,
                            vector<int> output_shape);
    // vector<float> forward(vector<float> input_data);
    void setInputData(vector<float> data);
    void forward();
    vector<float> getOutputData();
    void loadParams(int layer_id,
                    vector<float> filter_data, 
                    vector<float> bias_data, 
                    QuantParam quant_param);
    int size();
    string getLayerName(int layer_id);
    bool needToBeQuantized(int layer_id);
    private:
    void insertCastLayer(cnmlCastType_t cast_type);
    bool _isFirstLayer;
    cnrtQueue_t _queue;
    vector<Layer*> _layerList;
    vector<int> _inputShape;
    vector<int> _outputShape;
    void* _input_mlu_ptr;
    vector<float> _inputData;
    vector<float> _outputData;
};

#endif  // PYTHON_CNML_TEST_MLP_H_