#pragma once

#include <malloc.h>
#include <stdio.h>
#include "bmp.h"
#include "operacaoMatriz.h"
#include "cnn.h"

struct rnn_layer
{
    int  neuron_number;
    int  input_number;
    int *kernel;
    int *output;
    struct rnn_layer  *next;
    struct rnn_layer  *prev;
};

typedef struct rnn_layer  rnn_layer;
typedef struct rnn_neuron rnn_neuron;

int random_number (int min_num,int max_num);
void ann_layer_cnn(rnn_layer **l,int CNN_width,int CNN_height,int CNN_neuron ,int neuron_number);
void ann_layer_add(rnn_layer **l,int neuron_number);
void ann_layer_calc(rnn_layer **l,int *input,int cnn_size_output,int *target);
void ann_layer_first(rnn_layer **l, int neuron_number, int input_number);
int  ann_mse(int *labels,int *output,int **error,int o_size);