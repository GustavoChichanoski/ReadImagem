#ifndef CNN_H_INCLUDED
    
    #define CNN_H_INCLUDED
    
    #ifdef CNN_EXPORTS
        #define CNN_API __declspec(dllexport)
    #else
        #define CNN_API __declspec(dllimport)
    #endif
    
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    #include "operacaoPixel.h"
    #include "pooling.h"
    #include "operacaoMatriz.h"
    #include "neuralNetwork.h"
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    struct cnnLayer
    {
        pxMat           *kernel;
        pxMat           *input;
        pxMat           *output;
        int              bias;
        struct cnnLayer *next;
        struct cnnLayer *prev;
    };
    
    typedef struct cnnLayer CNNLayer;
    
    typedef struct size
    {
        int row, column;
    } Size;
    
    void   convolucaoInt(int **img,int img_width,int img_height,int **kernel,int kernel_width,int kernel_height,int **out,int *out_width, int *out_heigth,int stride);
    void   imprimeMatriz(pxMat matriz);
    Size   createSize(int row,int column);
    void   testeConvolucao();
    int    sqr(int a);
    void   swap(int *x,int *y);
    pixel *setup_kernel(pxMat kernel);
    pxMat  cnn(pxMat img,int kernel_degree);
    pixel  reluPixel(pixel data);
    
    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif