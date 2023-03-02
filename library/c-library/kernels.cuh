#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

    __global__ void multiply_kernel(int *, int *, int *, int);
    __global__ void add_kernel(int *, int *, int *, int);

#ifdef __cplusplus
}
#endif