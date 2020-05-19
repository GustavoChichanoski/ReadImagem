#pragma once

#include <malloc.h>
#include <stdio.h>
#include "bmp.h"
#include "operacaoMatriz.h"

struct layer
{
    Matriz weight;
    Matriz input;
    Matriz output;
    int    height;
    int    width;
    struct layer *next;
};

typedef struct layer Layer;

int    random_number (int min_num,int max_num);
int    floorSqrt     (int erro);
int    floorSqrt     (int erro);
pixel  rootMeanSquare(pixel *error,int neurons);
Matriz calcErro      (Matriz real,int *setpoint);
Matriz setup_weight  (Matriz weigths);
int    removeLayer(Layer *l,int index);
pxMat  setupKernel(pxMat weigths);