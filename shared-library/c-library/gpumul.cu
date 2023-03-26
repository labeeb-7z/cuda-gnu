#include "gpu.h"
__global__ void multiply_kernel(int *a, int *b, int *c, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
        c[i] = a[i] * b[i];
}

__global__ void mulby2_kernel(int *a, int *b, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
        b[i] = a[i] * 2;
}

void gpumul(int *a, int *b, int *c, int n)
{
    int *dev_a, *dev_b, *dev_c;

    cudaMalloc((void **)&dev_a, n * sizeof(int));
    cudaMalloc((void **)&dev_b, n * sizeof(int));
    cudaMalloc((void **)&dev_c, n * sizeof(int));

    cudaMemcpy(dev_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, n * sizeof(int), cudaMemcpyHostToDevice);

    dim3 dimBlock(1000, 1);
    dim3 dimGrid(1, 1);
    multiply_kernel<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c, n);

    cudaMemcpy(c, dev_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}
