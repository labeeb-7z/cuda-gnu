#include <stdio.h>
#include "test.h"

int main()
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int c[10] = {0};
    int n = 10;
    int device = 1;
    multiply(a, b, c, n, device);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");
}