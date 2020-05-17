#ifndef DENTRITIC_H_INCLUDED
    #define DENTRITIC_H_INCLUDED
    #ifdef DENTRITIC_EXPORTS
        #define DENTRITIC_API __declspec(dllexport)
    #else
        #define DENTRITIC_API __declspec(dllimport)
    #endif
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    #include "cnn.h"
    #include "neuralNetwork.h"
    #include "neuron.h"
    #ifdef __cplusplus
        extern "C" {
    #endif
    struct cnnDendritic
    {
        int *img;
        int *kernel;
        int *intermediate;
        struct cnnDendritic *next;
        struct cnnDendritic *prev;
    };
    typedef struct cnnDendritic CNN_Dendritic;
    void malloc_dendritic(CNN_Dendritic **dendritic);
    void insert_dendritic(int img_height,int img_width,int kernel_size,CNN_Dendritic **l);
    void insert_dendritic_img(int *img,int img_width,int img_height,int kernel_size,CNN_Dendritic **head);
    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif