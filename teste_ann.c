#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/neuralNetwork.h"
#include <string.h>

int main(int argc,char *argv[])
{
    rnn_layer *rl;
    rl = NULL;
    ann_layer_first(&rl,1,1);
    ann_layer_add(&rl,3);
    ann_layer_add(&rl,3);
    ann_layer_add(&rl,1);
    int *x, *y, *error;
    x = malloc(sizeof(int));
    y = malloc(sizeof(int));
    *x = 4095;
    (*y) = (*x) + 4095;
    do
    {
        ann_layer_calc(&rl,x,1,y);
    }while((rl -> next -> next -> output[0] - (*y)) > 10 || (rl -> next -> next -> output[0] - (*y)) < -10);
    printf("fim");
}