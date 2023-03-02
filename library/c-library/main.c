#include <stdio.h>
#include "main.h"
#include "cpu.h"
#include "gpu.h"


void add(int *a, int *b, int *c, int n, int device)
{
    if (device == 0)
    {
        cpuadd(a, b, c, n);
    }
    else{
        gpuadd(a, b, c, n);
    }
}

void multiply(int *a, int *b, int *c, int n, int device)
{
    if (device == 0)
    {
        cpumul(a, b, c, n);
    }
    else{
        gpumul(a, b, c, n);
    }
}