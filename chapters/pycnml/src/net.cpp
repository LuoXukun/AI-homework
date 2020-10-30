#include "net.hpp"
#include<sys/time.h>

MluConfig mluConfig = MluConfig();

CnmlNet::CnmlNet(int core_num, cnmlCoreVersion_t core_version) {
    cnmlInit(0);
    cnrtDev_t dev;
    cnrtGetDeviceHandle(&dev, 0);
    cnrtSetCurrentDevice(dev);
    _isFirstLayer = true;
    mluConfig.setCoreNum(core_num);
    mluConfig.setCoreVersion(core_version);
    std::cout << "CORE NUM: " << mluConfig.getCoreNum() << std::endl;
    std::cout << "CORE VERSION: " << mluConfig.getCoreVersion() << std::endl;

    cnrtCreateQueue(&_queue);
}

CnmlNet::~CnmlNet() {
    for (uint i = 0; i < _layerList.size(); i++) {
        delete _layerList[i];
    }
    cnrtFree(_input_mlu_ptr);
    cnrtDestroyQueue(_queue);
}

void CnmlNet::setInputShape(int dim_1, int dim_2, int dim_3, int dim_4) {
    _inputShape.resize(4);
    _inputShape[0] = dim_1;
    _inputShape[1] = dim_2;
    _inputShape[2] = dim_3;
    _inputShape[3] = dim_4;

    _outputShape.resize(4);
    _outputShape = _inputShape;

    _inputData.resize(dim_1 * dim_2 * dim_3 * dim_4);
    
    // cast layer is used to casting data type from float32 to float16 or float16 to float32
    insertCastLayer(CNML_CAST_FLOAT32_TO_FLOAT16);
}

void CnmlNet::createConvLayer(string layer_name,
                              int out_channel, 
                              int kernel_size,
                              int stride,
                              int dilation,
                              int pad,
                              QuantParam quant_param) {
    vector<int>* input_shape;

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " " 
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = new vector<int>(_outputShape);
    }

    std::cout << "creating conv layer ..." << std::endl;

    int out_height=((*input_shape)[2] + 2 * pad - kernel_size)/stride + 1;
    int out_width=((*input_shape)[3] + 2 * pad - kernel_size)/stride + 1;

    _outputShape[0] = (*input_shape)[0];
    _outputShape[1] = out_channel;
    _outputShape[2] = out_height;
    _outputShape[3] = out_width;

    std::cout << "output_shape: [" << _outputShape[0] << " " 
                                   << _outputShape[1] << " "
                                   << _outputShape[2] << " "
                                   << _outputShape[3] << "]\n";
    vector<int> kernel_vector= {kernel_size, kernel_size};
    vector<int> stride_vector = {stride, stride};
    vector<int> dilation_vector = {dilation, dilation};
    vector<int> pad_vector = {pad, pad, pad, pad};
    int input_position = quant_param.position;
    float input_scale = quant_param.scale;

    CnmlConvLayer * convlayer = new CnmlConvLayer(*input_shape, 
                                                  _outputShape, 
                                                  kernel_vector,
                                                  stride_vector,
                                                  dilation_vector,
                                                  pad_vector,
                                                  input_position, 
                                                  input_scale);
    _layerList.push_back(new Layer(convlayer, layer_name, CONVOLUTION, false));
}

void CnmlNet::createMlpLayer(string layer_name,
                             int output_num,
                             QuantParam quant_param){
    vector<int>* input_shape;

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " " 
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = new vector<int>(_outputShape);
    }

    std::cout << "creating mlp layer ..." << std::endl;

    _outputShape[0] = (*input_shape)[0];
    _outputShape[1] = output_num;
    _outputShape[2] = 1;
    _outputShape[3] = 1;

    std::cout << "output_shape: [" << _outputShape[0] << " " 
                                   << _outputShape[1] << " "
                                   << _outputShape[2] << " "
                                   << _outputShape[3] << "]\n";
    int input_position = quant_param.position;
    float input_scale = quant_param.scale;
    
    CnmlMlpLayer * mlplayer = new CnmlMlpLayer(*input_shape, 
                                               _outputShape,
                                               input_position, 
                                               input_scale);
    _layerList.push_back(new Layer(mlplayer, layer_name, MLP, false));
}

void CnmlNet::createReLuLayer(string layer_name) {
    vector<int>* input_shape;

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " " 
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = &_outputShape;
    }

    std::cout << "creating relu layer ..." << std::endl;

    _outputShape[0] = (*input_shape)[0];
    _outputShape[1] = (*input_shape)[1];
    _outputShape[2] = (*input_shape)[2];
    _outputShape[3] = (*input_shape)[3];

    std::cout << "output_shape: [" << _outputShape[0] << " " 
                                   << _outputShape[1] << " "
                                   << _outputShape[2] << " "
                                   << _outputShape[3] << "]\n";

    CnmlReLuLayer * relulayer = new CnmlReLuLayer(*input_shape);
    _layerList.push_back(new Layer(relulayer, layer_name, RELU, false));
}

void CnmlNet::createSoftmaxLayer(string layer_name, int axis) {
    vector<int>* input_shape;

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " " 
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = &_outputShape;
    }

    std::cout << "creating softmax layer ..." << std::endl;

    _outputShape[0] = (*input_shape)[0];
    _outputShape[1] = (*input_shape)[1];
    _outputShape[2] = (*input_shape)[2];
    _outputShape[3] = (*input_shape)[3];

    std::cout << "output_shape: [" << _outputShape[0] << " " 
                                   << _outputShape[1] << " "
                                   << _outputShape[2] << " "
                                   << _outputShape[3] << "]\n";

    CnmlSoftmaxLayer * softmaxlayer = new CnmlSoftmaxLayer(*input_shape, axis);
    _layerList.push_back(new Layer(softmaxlayer, layer_name, SOFTMAX, false));
}

void CnmlNet::createPoolingLayer(string layer_name,
                                 int kernel_size, 
                                 int stride) {
    vector<int>* input_shape;

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " " 
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = new vector<int>(_outputShape);
    }

    std::cout << "creating pooling layer ..." << std::endl;

    const int pooled_height = static_cast<int>(floor(static_cast<float>(
            (*input_shape)[2] - kernel_size) /
          stride)) + 1;
    const int pooled_width = static_cast<int>(floor(static_cast<float>(
            (*input_shape)[3] - kernel_size) /
          stride)) + 1;

    _outputShape[0] = (*input_shape)[0];
    _outputShape[1] = (*input_shape)[1];
    _outputShape[2] = pooled_height;
    _outputShape[3] = pooled_width;

    std::cout << "output_shape: [" << (*input_shape)[0] << " " 
                                   << (*input_shape)[1] << " "
                                   << pooled_height << " "
                                   << pooled_width << "]\n";

    vector<int> kernel_vector = {kernel_size, kernel_size};
    vector<int> stride_vector = {stride, stride};

    CnmlPoolingLayer * poolinglayer = new CnmlPoolingLayer(*input_shape,
                                                           kernel_vector,
                                                           stride_vector);
    _layerList.push_back(new Layer(poolinglayer, layer_name, POOL, false));
}

void CnmlNet::createFlattenLayer(string layer_name,
                                 vector<int> output_shape) {
    vector<int>* input_shape;

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " " 
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = new vector<int>(_outputShape);
    }

    std::cout << "creating flatten layer ..." << std::endl;

    _outputShape[0] = output_shape[0];
    _outputShape[1] = output_shape[1];
    _outputShape[2] = output_shape[2];
    _outputShape[3] = output_shape[3];

    std::cout << "output_shape: [" << output_shape[0] << " " 
                                   << output_shape[1] << " "
                                   << output_shape[2] << " "
                                   << output_shape[3] << "]\n";
    
    CnmlFlattenLayer * flattenlayer = new CnmlFlattenLayer(*input_shape,
                                                           _outputShape);
    _layerList.push_back(new Layer(flattenlayer, layer_name, FLATTEN, false));
}

void CnmlNet::insertCastLayer(cnmlCastType_t cast_type) {
    // insert the cast out layer
    CnmlCastLayer *castlayer = new CnmlCastLayer(_outputShape, cast_type);
    string layer_name;
    if (cast_type == CNML_CAST_FLOAT32_TO_FLOAT16) {
        layer_name = "cast_in";
    } else if (cast_type == CNML_CAST_FLOAT16_TO_FLOAT32) {
        layer_name = "cast_out";
    } else {
        std::clog << "Error: Not support this cast type yet: "
                  << cast_type << std::endl;
        exit(1);
    }
    _layerList.push_back(new Layer(castlayer, layer_name, CAST, false));
}

void CnmlNet::setInputData(vector<float> data) {
    _inputData = data;
    // malloc cnml tensor
    cnrtMalloc(&_input_mlu_ptr, _inputData.size() * sizeof(int32_t));
    // copy input to cnml buffer
    cnrtMemcpy(_input_mlu_ptr, _inputData.data(), _inputData.size() * sizeof(int32_t), CNRT_MEM_TRANS_DIR_HOST2DEV);
}

void CnmlNet::forward() {
    void *output_mlu_ptr = _input_mlu_ptr;
    for (unsigned int i = 0; i < _layerList.size(); i++) {
        switch (_layerList[i]->type) {
            case CONVOLUTION:
            {
                if (_layerList[i]->isParamLoaded == false) {
                    std::clog << "ERROR: param of layer " << _layerList[i]->name << " is not loaded !\n";
                    exit(1);
                }
                CnmlConvLayer* convlayer = static_cast<CnmlConvLayer*>(_layerList[i]->layer);
                output_mlu_ptr = convlayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case MLP:
            {
                if (_layerList[i]->isParamLoaded == false) {
                    std::clog << "ERROR: param of layer " << _layerList[i]->layer << " is not loaded !\n";
                    exit(1);
                }
                CnmlMlpLayer* mlplayer = static_cast<CnmlMlpLayer*>(_layerList[i]->layer);
                output_mlu_ptr = mlplayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case RELU:
            {
                CnmlReLuLayer* relulayer = static_cast<CnmlReLuLayer*>(_layerList[i]->layer);
                output_mlu_ptr = relulayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case SOFTMAX:
            {
                CnmlSoftmaxLayer* softmaxlayer = static_cast<CnmlSoftmaxLayer*>(_layerList[i]->layer);
                output_mlu_ptr = softmaxlayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case POOL:
            {
                CnmlPoolingLayer* poolinglayer = static_cast<CnmlPoolingLayer*>(_layerList[i]->layer);
                output_mlu_ptr = poolinglayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case FLATTEN:
            {
                CnmlFlattenLayer* flattenlayer = static_cast<CnmlFlattenLayer*>(_layerList[i]->layer);
                output_mlu_ptr = flattenlayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case CAST:
            {
                CnmlCastLayer* castlayer = static_cast<CnmlCastLayer*>(_layerList[i]->layer);
                output_mlu_ptr = castlayer->forward(output_mlu_ptr, _queue);
                break;
            }
            default:
            {
                std::clog << "Error: Not support this layer type: " << _layerList[i]->type << std::endl;
                exit(1);
            }
        }
    }

    cnrtSyncQueue(_queue);
    
    int output_size = _outputShape[0] * _outputShape[1] * _outputShape[2] * _outputShape[3];

    _outputData.resize(output_size);
    // copy output to cpu
    cnrtMemcpy(_outputData.data(), output_mlu_ptr, output_size * sizeof(int32_t),
                CNRT_MEM_TRANS_DIR_DEV2HOST);

}

vector<float> CnmlNet::getOutputData() {
    return _outputData;
}

void CnmlNet::loadParams(int layer_id,
                         vector<float> filter_data, 
                         vector<float> bias_data, 
                         QuantParam quant_param) {
    // starting to load params means that the construction of the net has finished.
    // insert the output data cast layer.
    if (_layerList.back()->type != CAST) {
        insertCastLayer(CNML_CAST_FLOAT16_TO_FLOAT32);
    }
    // the first layer is cast layer. skip it
    layer_id += 1;
    
    std::cout << "loading params for layer " << _layerList[layer_id]->name << " ..." << std::endl;
    std::cout << "weight size: " << filter_data.size() << std::endl;
    int filter_position = quant_param.position;
    float filter_scale = quant_param.scale;

    if (_layerList[layer_id]->type == CONVOLUTION) {
        CnmlConvLayer* convlayer = static_cast<CnmlConvLayer*>(_layerList[layer_id]->layer);
        convlayer->loadParam(filter_data, bias_data, filter_position, filter_scale);
    } else if (_layerList[layer_id]->type == MLP) {
        CnmlMlpLayer* mlplayer = static_cast<CnmlMlpLayer*>(_layerList[layer_id]->layer);
        mlplayer->loadParam(filter_data, bias_data, filter_position, filter_scale);
    } else {
        std::clog << "ERROR : This layer is not conv or mlp !\n";
        std::clog << "\tlayer name is : " << _layerList[layer_id]->name << std::endl;
        exit(1);
    }
    _layerList[layer_id]->isParamLoaded = true;
}

string CnmlNet::getLayerName(int layer_id) {
    // layer_id + 1 to skip the cast layer
    return _layerList[layer_id + 1]->name;
}

int CnmlNet::size() {
    // the first and the last layer are cast layers.
    return _layerList.size() - 2;
}

bool CnmlNet::needToBeQuantized(int layer_id) {
    // layer_id + 1 to skip the cast layer
    return _layerList[layer_id + 1]->type == CONVOLUTION || _layerList[layer_id + 1]->type == MLP;
}

