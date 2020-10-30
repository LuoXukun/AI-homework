"""
setup.py
"""
 
from distutils.core import setup, Extension
import os

neuware_home = os.environ.get('NEUWARE_HOME')
 
example_module = Extension('_pycnml',
                            sources=['./swig/pycnml_wrap.cxx', 
                            './src/net.cpp', 
                            './src/layers/PyCnmlConvLayer/conv.cpp', 
                            './src/layers/PyCnmlMlpLayer/mlp.cpp', 
                            './src/layers/PyCnmlReLULayer/relu.cpp', 
                            './src/layers/PyCnmlSoftmaxLayer/softmax.cpp', 
                            './src/layers/PyCnmlPoolLayer/pool.cpp',
                            './src/layers/PyCnmlFlattenLayer/flatten.cpp',
                            './src/layers/PyCnmlCastLayer/cast.cpp', 
                            './src/tools/get_quantized_position_scale.cpp'],
                            include_dirs=[neuware_home + '/include', './include'],
                            libraries=['cnml', 'cnrt'],
                            library_dirs=[neuware_home + '/lib64'],
                            swig_opts=['c++'],
                            extra_compile_args=['-std=c++11'],
                            extra_link_args=['-std=c++11'],
                           )
 
setup (name = 'pycnml',
       version = '0.3',
       author      = "ict-tzh",
       description = """cnml op for python""",
       ext_modules = [example_module],
       py_modules = ["pycnml"],
       )