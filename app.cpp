#include <stdio.h>
#include "demolib.h"
//void add(int *a, int *b, int *c, int n, int device);




int main()
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int c[10] = {0};
    int n = 10;
    int device = 0;
    multiply(a, b, c, n, device);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");
}