#include "tools.hpp"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <utility>

using std::map;
using std::string;
using std::pair;

QuantParam getInt8Info(const vector<float> input_data,
                       string layer_name,
                       LayerType layer_type,
                       const string& mode,
                       // only weights should get channel quantimizaed
                       bool channel_quantimize = false,
                       // this is for multi-batch images in generate_int8_pt
                       // for bottoms only
                       map<string, float>* const max_value = nullptr,
                       // absmax should be squared for normalize bottom 0
                       // not normalize bottom 1
                       bool is_first_normalize = false) {
    vector<float> max(1, 0), min(1, 0), abs_max(1, 0),
    position(1, 0), scale(1, 0);
    int length = input_data.size();
    bool lrn = layer_type == LRN;
    string key = layer_name;

    const float* data = input_data.data();
    min[0] = max[0] = data[0];
    for (int j = 0; j < length; ++j) {
        max[0] = std::max(data[j], max[0]);
        min[0] = std::min(data[j], min[0]);
    }
    abs_max[0] = std::max(std::abs(min[0]), std::abs(max[0]));
    
    if (max_value != nullptr) {
        for (unsigned int i = 0; i < abs_max.size(); i++) {
        auto iter = max_value->find(key);
        if (iter != max_value->end()) {
            if (abs_max[i] > iter->second) {
            (*max_value)[key] = abs_max[i];
            } else {
            abs_max[i] = (*max_value)[key];
            }
        } else {
            max_value->insert(pair<string, float>(key, abs_max[i]));
        }
        }
    }
    if (lrn) {
        // abs_max[0] = abs_max[0] * abs_max[0] * layer_param.lrn_param().alpha();
        std::cout << "ERROR: NOT SUPPORT LRN YET!\n";
        exit(1);
    } else if (is_first_normalize) {
        // abs_max[0] *= abs_max[0];
        std::cout << "ERROR: NOT SUPPORT NORMALIZE YET!\n";
        exit(1);
    }

    int critical_value = std::pow(2, 7) - 1;
    // if (data_type == DT_INT8) {
    //     critical_value = std::pow(2, 7) - 1;
    // } else if (data_type == DT_INT16) {
    //     critical_value = std::pow(2, 15) - 1;
    // }

    QuantParam quant_param;
    for (unsigned int i = 0; i < abs_max.size(); i++) {
        if (abs_max[i] == 0) {
            position[i] = 0;
            scale[i] = 1;
        } else {
            position[i] = log2(abs_max[i] / critical_value);
            position[i] += position[i] > 0 ? 1 : 0;
            scale[i] = critical_value * pow(2, static_cast<int>(position[i])) / abs_max[i];
        }
        if (position[i] > 32) position[i] = 32;
        if (position[i] < -32) position[i] = -32;
        if (mode == "common" || mode == "int8_channel" || lrn) {
            // blob_dtype.set_type(data_type);
            // blob_dtype.add_position(position[i]);
            quant_param.position = position[i];
            // blob_dtype.add_scale(scale[i]);
            quant_param.scale = scale[i];
        } else if (mode == "scale") {
            float new_scale =  pow(2, static_cast<int>(-position[i])) * scale[i];
            // blob_dtype.set_type(data_type);
            // blob_dtype.add_scale(new_scale);
            quant_param.position = -999999;
            quant_param.scale = new_scale;
        }
    }
    return quant_param;
}

QuantParam QuantTool::getQuantParam(const vector<float> input_data,
                                    string layer_name) {
    LayerType layer_type = CONVOLUTION;
    int iteration = input_data.size();
    return getInt8Info(input_data, layer_name, layer_type, "common", false, &_max_value, false);
}