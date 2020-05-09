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
    
    struct neuron
    {
        int *img;
        int *kernel;
        int *out;
        struct neuron *next;
    };
    
    typedef struct neuron Neuron;
    
    struct camada
    {
        Neuron n;
        struct camada *next;
    };
    
    typedef struct camda Camada;
    void printf_kernel(Neuron *n,int kernel_size);

    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif