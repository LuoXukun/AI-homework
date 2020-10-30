%module pycnml
%{
    #define SWIG_FILE_WITH_INIT
    #include "net.hpp"
    #include "tools.hpp"
%}

%include "std_vector.i"

%include "std_string.i"

%include "numpy.i"

%init %{
    import_array();
%}

typedef enum {
    CNML_1H8 = 1,
    /*!< 1H8 hardware. */
    CNML_1H16 = 2,
    /*!< 1H16 hardware. */
    CNML_C10 = 3,
    /*!< MLU100 hardware, deprecated, use CNML_MLU100 instead. */
    CNML_1H8MINI = 4,
    /*!< 1H8MINI hardware. */
    CNML_MLU100 = 3,
    /*!< MLU100 hardware, instead name of CNML_C10.*/
    CNML_MLU270 = 5,
    /*!< MLU270 hardware. */
    CNML_MLU220 = 6,
    /*!< MLU220 hardware. */
} cnmlCoreVersion_t;

namespace std {
    %template(FloatVector) vector<float>;
    %template(IntVector) vector<int>;
    %template(DoubleVector) vector<double>;
    %template(FloatVector2) vector<vector<float>>;
    %template(IntVector2) vector<vector<int>>;
    %template(DoubleVector2) vector<vector<double>>;
}

%include "net.hpp"
%include "tools.hpp"
