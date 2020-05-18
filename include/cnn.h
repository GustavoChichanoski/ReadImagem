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
    #include "pooling.h"
    #include "neuron.h"
    #include "dendritic.h"
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    #define  POOL    0
    #define  CONV    1
    #define  RELU    2
    #define  ONE   255
    #define _ONE  -256 
    struct cnnLayer
    {
        int    img_width;
        int    img_height;
        int    out_width;
        int    out_height;
        int    input_number;
        int    type;
        int    kernel_size;
        int    neuron_number;
        struct cnnNeuron *neuron;
        struct cnnLayer  *next;
        struct cnnLayer  *prev;
    };
    typedef struct cnnLayer CNN_Layer;
    void malloc_layer(CNN_Layer **layer);
    void convolucaoInt(int *img,int img_width,int img_height,int *kernel,int kernel_degree,int **out,int stride);
    void insert_layer_img(int img_height, int img_width, int kernel_size, int neuron_number, int input_number, int *red, int *blue, int *green, CNN_Layer **l);
    void insert_layer(int img_height, int img_width, int type, int kernel_size, int neuron_number, CNN_Layer **l);
    // void   imprimeMatriz(pxMat matriz);
    // Size   createSize(int row,int column);
    // void   testeConvolucao();
    // int    sqr(int a);
    // void   swap(int *x,int *y);
    // pixel *setup_kernel(pxMat kernel);
    // pxMat  cnn(pxMat img,int kernel_degree);
    // pixel  reluPixel(pixel data);
    
    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif