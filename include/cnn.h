#pragma once

#ifdef CNN_EXPORTS
    #define CNN_API __declspec(dllexport)
#else
    #define CNN_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "conversao.h"
#include "dendritic.h"
#include "neuron.h"
#include "pooling.h"
#include "conversao.h"

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

void layer_malloc(CNN_Layer **layer);
void layer_calc_pool(CNN_Neuron **n,int width,int height);
void layer_calc_relu(CNN_Neuron **n,int width,int height);
void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size);
void layer_calc_neuron(CNN_Layer **l,int type);
void layer_insert(int kernel_size,int neuron_number,int type,CNN_Layer **l);
void layer_insert_img(int img_height, int img_width,int kernel_size,int neuron_number,int input_number,int *red,int *blue,int *green,CNN_Layer **l);
