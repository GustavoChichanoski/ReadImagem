#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "operacaoPixel.h"
#include "pooling.h"

void  multiplyMatriz(int *first,int *second,int *result,int *size_f,int *size_s);
int   positionMatrizVector(int *size,int *pos);
int  *positionVectorMatriz(int position,int *size);
void  create_matriz(int height,int width,int *matrix);
void  testeMatriz();