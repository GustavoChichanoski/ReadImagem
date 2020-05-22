#pragma once

#include <malloc.h>
#include <stdio.h>
#include "bmp.h"
#include "operacaoMatriz.h"
#include "cnn.h"

struct rnn_layer
{
    int neuron_number;
    int *kernel;
    int *output;
    struct rnn_layer  *next;
    struct rnn_layer  *prev;
};

typedef struct rnn_layer  rnn_layer;
typedef struct rnn_neuron rnn_neuron;

int random_number (int min_num,int max_num);