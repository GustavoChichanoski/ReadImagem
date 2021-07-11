#pragma once

#ifdef CNN_EXPORTS
    #define CNN_API __declspec(dllexport)
#else
    #define CNN_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "neuralNetwork.h"
#include "..\images\conversao.h"

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
void convolucaoInt(int *img,int img_width,int img_height,int *kernel,int kernel_degree,int **out,int stride);