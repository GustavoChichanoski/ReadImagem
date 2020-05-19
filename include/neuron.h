#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "cnn.h"
#include "dendritic.h"
#include "neuralNetwork.h"

#define A_360            4095
#define SQRT_2           5793
#define A_180            2047
#define A_90             1023
#define FORWARD          0
#define INVERSE          1
#define MINIMUM_FFT_SIZE 8
#define MAXIMUM_FFT_SIZE 1048576

struct cnnNeuron
{
    int                  bias;
    int                 *out;
    struct cnnDendritic *dendritic;
    struct cnnNeuron    *next;
    struct cnnNeuron    *prev;
};
typedef struct cnnNeuron CNN_Neuron;

void neuron_malloc(CNN_Neuron **neuron);
void neuron_out(CNN_Neuron **neuron,int img_width,int img_height,int kernel_size);
void neuron_insert(int img_height, int img_width,int out_height, int out_width, int kernel_size, int input_size, int type, CNN_Neuron **l);
void neuron_insert_img(int img_height,int img_width,int input_size,int kernel_size,int *red,int *blue,int *green, CNN_Neuron **l);