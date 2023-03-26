### This is a demonstration of combining Cuda and C code into a single library.

The procedure is 

- compile C source code independently into .o files with gcc
- compile Cuda source code independtly into .o files with nvcc
- use gcc create a shared library from all the object files

### Requirements

System should have 

- gcc AND g++ (latter is used to compile the host code in cuda files).
- nvcc (delivered with cuda-toolkit)


To install cuda-toolkit, refer to the [Nvidia installation docs](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html) or the [quickstart-guide](https://docs.nvidia.com/cuda/cuda-quick-start-guide/index.html#linux) or get [terminal commands](https://developer.nvidia.com/cuda-downloads) for your specs.


### Setup

once the repo is setup locally, cd into the c-liibrary directory

`cd c-library`

compile all the c source code with the following command

`gcc -c main.c cpuadd.c cpumul.c`

compile all the cuda source with the following command. 
since we want to create a shared library, we should pass the `-fPIC` flag to create position independent code.
`-fPIC` is a compiler flag, so we must specify that by using `-Xcompiler`

`nvcc -Xcompiler -fPIC -c gpuadd.cu gpumul.cu`

create a shared object file (library) (resulting library - libmylibrary) from all the object files

`gcc -shared -o libmylibrary.so main.o cpumul.o cpuadd.o gpuadd.o gpumul.o /usr/local/cuda/lib64/libcudart.so`

add the current path to `LD_LIBRARY_PATH`

`export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH`


The library is ready now! it can be used like any other C library

### Example

cd back into the current directory which contains app.c - an independent file which will be written by the user.

`cd ..`

now compile the app.c with the following command 

`gcc app.c -o app -L /path/to/c-library/folder -lmylibrary`

example : 

`gcc app.c -o app -L ~/github/cuda-gnu/shared-library/c-library/ -lmylibrary`

your path to cuda library will most likely be the same (if you've installed it like a normal package) as in the example command, unless its installed in a conda virtual environment or similar in which case you can search for `libcudart.so` in your file system and use that path.

Now you can run the app with the following command

`./app`
