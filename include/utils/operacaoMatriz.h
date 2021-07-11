#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "..\images\operacaoPixel.h"
#include "..\nn\pooling.h"

typedef struct matriz
{
    int row, column;
    int *mat;
} Matriz;

int     positionMatrizVector(int *size,int *pos);
int    *positionVectorMatriz(int position,int *size);
Matriz  create_matriz(int row,int column);
void    printMatriz(Matriz mat);
Matriz  multiplyMatriz(Matriz first,Matriz second);
Matriz  hadamart(Matriz erro,Matriz dS);
Matriz  multConst(Matriz mat,int constant);
Matriz  divConst(Matriz mat,int constant);
Matriz  transposed(Matriz mat);
Matriz  somaMatrizes(Matriz a,Matriz b);
void    testeMatriz();