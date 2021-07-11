#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../images/conversao.h"
#include "cnn.h"
#include "neuron.h"
#include "dendritic.h"
#include "pooling.h"

void layer_calc_pool(CNN_Neuron **n,int width,int height);
void layer_calc_relu(CNN_Neuron **n,int width,int height);
void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size);
void layer_calc_neuron(CNN_Layer **l,int type);
void layer_calc(CNN_Layer **l);