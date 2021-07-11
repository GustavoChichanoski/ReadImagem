#include "../include/nn/cnn_exec.h"

void layer_calc_pool(CNN_Neuron **n,int width,int height);
void layer_calc_relu(CNN_Neuron **n,int width,int height);
void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size);
void layer_calc_neuron(CNN_Layer **l,int type);
void layer_calc(CNN_Layer **l);

void layer_calc_pool(CNN_Neuron **n,int width,int height)
{
    CNN_Neuron *n_last;
    n_last = (*n);
    int img_width, img_height;
    do
    {
        poolingInt(1,n_last -> dendritic -> img,width,height,&(n_last -> out),&img_width,&img_height);
        n_last = n_last -> next;
    }
    while(n_last -> next != (*n));
}

void layer_calc_relu(CNN_Neuron **n,int width,int height)
{
    CNN_Neuron *n_last;
    n_last = (*n);
    do
    {
        for(int i = 0;i < width * height;i++)
        {
            int valor = n_last -> dendritic -> img[i];
            n_last -> out[i] = (valor > -1) ? valor : 0;
        }
        n_last = n_last -> next;
    }
    while(n_last -> next != (*n));
}

void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size)
{
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_last;
    n_last = (*n);
    do
    {
        d_last = n_last -> dendritic;
        do
        {
            convolucaoInt(d_last -> img,width,height,d_last -> kernel,kernel_size,&(d_last -> intermediate),1);
            d_last = d_last -> next;
        }
        while(d_last != n_last -> dendritic);
        for(int i = 0;i < width * height;i++)
        {
            d_last = n_last -> dendritic;
            n_last -> out[i] = n_last -> bias;
            do
            {
                n_last -> out[i] += d_last -> intermediate[i];
                d_last            = d_last -> next;
            }
            while(d_last != n_last -> dendritic);
        }
    } while(n_last != (*n));
}

void layer_calc_neuron(CNN_Layer **l,int type)
{
    CNN_Neuron *n;
    n = (*l) -> neuron;
    do{
        if(type == CONV)
        {
            layer_calc_conv(&n,(*l) -> img_width,(*l) -> img_height,(*l) -> kernel_size);
        } 
        if(type == RELU)
        {
            layer_calc_relu(&n,(*l) -> img_width,(*l) -> img_height);
        }
        if(type == POOL)
        {
            layer_calc_pool(&n,(*l) -> img_width,(*l) -> img_height);
        }
        n = n -> next;
    } while(n != (*l) -> neuron);
}

void layer_calc(CNN_Layer **l)
{
    CNN_Layer *l_last;
    l_last = (*l);
    do
    {
        layer_calc_neuron(&l_last, l_last -> type);
        l_last = l_last -> next;
    }
    while(l_last != (*l));
}
