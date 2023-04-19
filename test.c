#include <gnuastro/gpu.h>

int main()
{
    kernel_on_gpu();

    int arr_a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int arr_b[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    mat_add(arr_a, arr_b, 4);

    kernel_on_gpu();

    mat_mul(arr_a, arr_b, 4);

    return 0;
}
















/*
1. How to avoid -lcudart everytime?

2. How to add rules for each kernel?

3. Design of library - folder layout (kernles + headers) / user interface
*/