#pragma once
    
    #ifdef NEURALNETWORK_EXPORTS
        #define NEURALNETWORK_API __declspec(dllexport)
    #else
        #define NEURALNETWORK_API __declspec(dllimport)
    #endif
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    #include "operacaoPixel.h"
    #include "pooling.h"

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

#ifdef __cplusplus
    extern "C" {
#endif