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
    ann_layer_add(&rl,2);
    ann_layer_add(&rl,1);
    int *x, *y;
    x = malloc(sizeof(int));
    y = malloc(sizeof(int));
    *x = 4095;
    do
    {
        for((*x) = 4095;(*x) < 4095*2;(*x) = (*x) + 10)
        {
            (*y) = (*x) + ONE/45;
            ann_layer_calc(&rl,x,1,y);
        }
    } while((rl -> next -> next -> output[0] - (*y)) > 100 || (rl -> next -> next -> output[0] - (*y)) < -100);
    printf("%d - %d = %d",rl -> next -> next -> output[0],(*y),rl -> next -> next -> output[0] - (*y));
}