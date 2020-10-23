#ifndef PYTHON_CNML_TOOLS_H_
#define PYTHON_CNML_TOOLS_H_
#include <vector>
#include <map>
#include <string>
#include "config.hpp"

using std::vector;
using std::map;
using std::string;

typedef enum {
    CAST = 0,
    CONVOLUTION = 1,
    LRN = 2,
    MLP = 3,
    NORMALIZE = 4,
    RELU = 5,
    SOFTMAX =6,
    POOL = 7,
    FLATTEN = 8
} LayerType;

struct QuantParam {
    int position = 0;
    float scale = 0;
    QuantParam(): position(1), scale(1) {};
    QuantParam(int p, float s): position(p), scale(s) {};
};

class QuantTool {
    public:
    QuantParam getQuantParam(const vector<float> input_data,
                             string layer_name);
    private:
    std::map<string, float> _max_value;
};

#endif  // PYTHON_CNML_TOOLS_H_