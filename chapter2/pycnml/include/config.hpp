#ifndef PYTHON_CNML_CONFIG_H_
#define PYTHON_CNML_CONFIG_H_

#include "cnml.h"
class MluConfig {
    public:
    MluConfig() {
        _coreVersion = CNML_MLU270;
        _coreNum = 1;
    }
    inline cnmlCoreVersion_t getCoreVersion() const {
        return _coreVersion;
    }
    inline int getCoreNum() const {
        return _coreNum;
    }
    inline void setCoreVersion(cnmlCoreVersion_t coreVersion)  {
        _coreVersion = coreVersion;
    }
    inline void setCoreNum(int coreNum)  {
        _coreNum = coreNum;
    }
    private:
    cnmlCoreVersion_t _coreVersion;
    int _coreNum;
};

extern MluConfig mluConfig;

#endif  //PYTHON_CNML_CONFIG_H_