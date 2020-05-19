#pragma once
#include <malloc.h>

int *matriz_mul_const(int *matriz,int m,int n,int constant);
int *matriz_transpose(int *matriz,int width,int height);
int *matriz_mul(int *a,int *b,int a_w,int a_h);
int *matriz_sub(int *a,int *b,int m,int n);
int *matriz_sum(int *a,int *b,int m,int n);