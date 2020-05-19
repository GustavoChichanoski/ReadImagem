#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "cnn.h"
#include "neuralNetwork.h"
#include "neuron.h"

struct cnnDendritic
{
    int *img;
    int *kernel;
    int *intermediate;
    struct cnnDendritic *next;
    struct cnnDendritic *prev;
};
typedef struct cnnDendritic CNN_Dendritic;

void dendritic_malloc(CNN_Dendritic **dendritic);
void dendritic_insert(int img_height,int img_width,int out_height,int out_width,int kernel_size,int type,CNN_Dendritic **l);
void dendritic_insert_img(int *img,int img_width,int img_height,int kernel_size,CNN_Dendritic **head);