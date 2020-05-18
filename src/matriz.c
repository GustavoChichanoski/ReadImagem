#include "../include/matriz.h"

int *matriz_sum(int *a,int *b,int m,int n)
{
    int i, max = m * n;
    int *c = malloc(max * sizeof(int));
    for(i = 0;i < max;i++)
    {
        c[i] = a[i] + b[i];
    }
    return c;
}

int *matriz_sub(int *a,int *b,int m,int n)
{
    int i, max = m * n;
    int *c = malloc(max * sizeof(int));
    for(i = 0;i < max;i++)
    {
        c[i] = c[i] + b[i];
    }
    return c;
}

int *matriz_mul(int *a,int *b,int a_w,int a_h)
{
    int i, j, max = a_w * a_h, soma = 0;
    int *c;
    c = malloc(max * sizeof(int));
    for(i = 0;i < a_h;i++)
    {
        soma = 0;
        for(j = 0;j < a_w;j++)
        {
            soma += a[i*a_w + j]*b[j*a_w + i];
        }
        c[i*a_w + j] = soma;
    }
    return c;
}

int *matriz_transpose(int *matriz,int width,int height)
{
    int *c = malloc(width * height * sizeof(int));
    for (int row = 0;row < height;row++)
    {
        for(int column = 0;column < width;column++)
        {
            c[row*width + column] = matriz[column*width + row];
        }
    }
    return c;
}

int *matriz_mul_const(int *matriz,int m,int n,int constant)
{
    int *c = malloc(m * n * sizeof(int));
    for (int i = 0;i < m* n;i++)
    {
        c[i] = matriz[i] * constant;
    }
    return c;
}