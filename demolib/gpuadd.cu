#include "gpu.h"
#include <iostream>
using namespace std;
__global__ void add(int *a, int *b, int *c, int n)
{
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < n)
        c[index] = a[index] + b[index];
    //cout<<index<<endl;
}

void gpuadd(int *a, int *b, int *c, int n)
{
    //cout<<"gpuadd"<<endl;
    int *dev_a, *dev_b, *dev_c;
    cudaMalloc((void **)&dev_a, n * sizeof(int));
    cudaMalloc((void **)&dev_b, n * sizeof(int));
    cudaMalloc((void **)&dev_c, n * sizeof(int));

    cudaMemcpy(dev_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, n * sizeof(int), cudaMemcpyHostToDevice);

    dim3 dimBlock(10, 1,1);
    dim3 dimGrid(1, 1);

    add<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c, n);

    cudaMemcpy(c, dev_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}