### This is a demonstration of combining Cuda and C code into a single library.

The procedure is 

- compile C source code independently into .o files with gcc
- compile Cuda source code independtly into .o files with nvcc
- combine all the object files into a single .a (archive) file
- This arhcive file can than be used as a library by users (in new, independent programs).

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

compile all the cuda source with the following command

`nvcc -c gpuadd.cu gpumul.cu`

generate an archive file (resulting library - libtest) from all the object files

`ar cr libtest.a *o`

`ranlib libtest.a`

The library is ready now! it can be used like any other C library

### Example

cd back into the current directory which contains app.c - an independent file which will be written by the user.

`cd ..`

now compile the app.c with the following command 

`gcc app.c -o app -L /path/to/c-library/folder -ltest -L /path/to/cuda/library -lcudart`

example : 

`gcc app.c -o app -L ~/github/cuda-gnu/library/c-library/ -ltest -L /usr/local/cuda/targets/x86_64-linux/lib -lcudart`

your path to cuda library will most likely be the same (if you've installed it like a normal package) as in the example command, unless its installed in a conda virtual environment or similar in which case you can search for `libcudart.so` in your file system and use that path.

Now you can run the app with the following command

`./app`



 nvcc -Xcompiler -fPIC -c gpuadd.cu gpumul.cu


 gcc -shared -o libmylibrary.so main.o cpumul.o cpuadd.o gpuadd.o gpumul.o /usr/local/cuda/lib64/libcudart.so

 

 gcc app.c -o app -L ~/github/cuda-gnu/library/c-library/ -lmylibrary -L/usr/local/cuda/targets/x86_64-linux/lib -lcudart













 To build a shared library with both C and CUDA code, you can follow these general steps:

Write your C code and CUDA code in separate files with .c and .cu extensions, respectively.

Compile your CUDA code with the nvcc compiler. This will generate an object file (.o) for each CUDA source file.

r
Copy code
nvcc -c file.cu -o file.o
Compile your C code with the standard C compiler, but link against the CUDA libraries and include the CUDA object files.
bash
Copy code
gcc -c file.c -o file.o -I/path/to/cuda/include
gcc -shared -o libmylibrary.so file.o file2.o /path/to/cuda/lib64/libcudart.so
Note that the order of the object files and libraries matters, and the -shared option is used to create a shared library.

Use the resulting shared library in your C or CUDA program as usual.
Here's an example with two files, foo.c and bar.cu, where foo.c calls a CUDA function defined in bar.cu:

foo.c:

c
Copy code
#include <stdio.h>

extern void cuda_function();

int main() {
    printf("Calling CUDA function...\n");
    cuda_function();
    printf("Done.\n");
    return 0;
}
bar.cu:

cuda
Copy code
#include <stdio.h>

__global__ void kernel() {
    printf("Hello from CUDA!\n");
}

void cuda_function() {
    kernel<<<1, 1>>>();
    cudaDeviceSynchronize();
}
To compile and link these files into a shared library, you can use:

bash
Copy code
nvcc -c bar.cu -o bar.o
gcc -c foo.c -o foo.o
gcc -shared -o libmylibrary.so foo.o bar.o /usr/local/cuda/lib64/libcudart.so
And then to compile and run a program that uses this library:

vbnet
Copy code
gcc -o myprogram main.c -L/path/to/lib -lmylibrary -Wl,-rpath,/path/to/lib
./myprogram
