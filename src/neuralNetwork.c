#include "../include/neuralNetwork.h"

int  random_number(int min_num,int max_num);
void ann_layer_calc(rnn_layer **l,CNN_Layer **CNN);
void ann_layer_cnn(rnn_layer **l,CNN_Layer **CNN,int neuron_number);
void ann_layer_add(rnn_layer **l,int neuron_number);
void ann_layer_malloc(rnn_layer **layer);
void ann_layer_calc(rnn_layer **l,CNN_Layer **CNN);
void matriz_calc(int *a,int *b,int **c,int a_r,int a_c,int b_r,int b_c);

// example of use: int x = random_number(0,255);
int random_number(int min_num,int max_num)
{
    int result = 0, low_num = 0, high_num = 0;
    low_num    = (min_num < max_num) ? min_num : max_num + 1;
    high_num   = (min_num > max_num) ? min_num : max_num + 1;
    result     = (rand() % (high_num - low_num)) + low_num;
    return result;
}

void ann_layer_cnn(rnn_layer **l,CNN_Layer **CNN,int neuron_number)
{
    rnn_layer *l_temp;
    CNN_Layer *CNN_last;
    CNN_last = (*CNN);
    while(CNN_last -> next != (*CNN))
    {
        CNN_last = CNN_last -> next;
    }
    ann_layer_malloc(&l_temp);
    l_temp -> kernel = malloc(neuron_number * CNN_last -> img_height * CNN_last -> img_height * CNN_last -> neuron_number * sizeof(int));
    l_temp -> output = malloc(neuron_number * sizeof(int));
    (*l) = l_temp;
}

void ann_layer_add(rnn_layer **l,int neuron_number)
{
    rnn_layer *l_temp;
    rnn_layer *l_last;
    l_last = (*l);
    while(l_last -> next != NULL)
    {
        l_last = l_last -> next;
    }
    ann_layer_malloc(&l_temp);
    l_temp -> neuron_number = neuron_number;
    l_temp -> kernel        = malloc(l_last -> neuron_number * l_temp -> neuron_number * sizeof(int));
    l_temp -> output        = malloc(l_temp -> neuron_number * sizeof(int));
    l_last -> next = l_temp;
    l_temp -> prev = l_last;
}

void ann_layer_malloc(rnn_layer **layer)
{
    (*layer)           = malloc(sizeof(rnn_layer));
    (*layer) -> next   = malloc(sizeof(rnn_layer));
    (*layer) -> prev   = malloc(sizeof(rnn_layer));
    (*layer) -> next   = NULL;
    (*layer) -> prev   = NULL;
}

void ann_layer_calc(rnn_layer **l,CNN_Layer **CNN)
{
    rnn_layer  *l_last;
    CNN_Layer  *C_last;
    CNN_Neuron *N_last;
    int pos  = 0, width  = 0, height = 0, out_pos;
    int *img;
    l_last = (*l);
    C_last = (*CNN);
    while(C_last -> next != (*CNN))
    {
        C_last = C_last -> next;
    }
    height = C_last -> out_height;
    width  = C_last -> out_width;
    N_last = C_last -> neuron;
    img    = malloc(width * height * C_last -> neuron_number * sizeof(int));
    while(N_last -> next)
    {
        out_pos = 0;
        while(pos < height * width)
        {
            img[pos] = N_last -> out[out_pos];
            out_pos++;
            pos++;
        }
        N_last = N_last -> next;
    }
    matriz_calc(img,l_last -> kernel,&(l_last -> output),l_last -> neuron_number,width*height,width,height);
    l_last = l_last -> next;
    while(l_last -> next != NULL)
    {
        matriz_calc(l_last -> kernel,l_last -> prev -> output,&(l_last -> output),l_last -> neuron_number,1,l_last -> prev -> neuron_number,1);
        l_last = l_last -> next;
    }
    matriz_calc(l_last -> kernel,l_last -> prev -> output,&(l_last -> output),l_last -> neuron_number,1,l_last -> prev -> neuron_number,1);
}

void matriz_calc(int *a,int *b,int **c,int a_r,int a_c,int b_r,int b_c)
{
    if(a_c != b_r)
    {
        printf("Multiplicação de matrizes com colunas diferentes");
        exit(EXIT_FAILURE);
    }
    int pos = 0;
    for (int i = 0;i < a_r;i++)
    {
        for (int j = 0;j < b_c;j++)
        {
            (*c)[pos] = 0;
            for(int k = 0;k < a_c;k++)
            {
                (*c)[pos] += a[i*a_c + k] * b[k*b_r + j];
            }
            pos++;
        }
    }
}