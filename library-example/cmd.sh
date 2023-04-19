.
nvcc -o libmygpulib.so --compiler-options '-fPIC' -shared main.cpp  gpuadd.cu gpumul.cu cpuadd.cpp cpumul.cpp

gcc app.cpp -o sample -L ~/cuda/demolib/ -lmygpulib