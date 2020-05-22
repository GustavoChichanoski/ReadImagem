#include "../include/neuron.h"

void neuron_insert_img(int img_height, int img_width, int input_size, int kernel_size, int *red, int *blue, int *green, CNN_Neuron **l)
{
    CNN_Neuron    *n_temp;
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_temp;
    n_last = (*l);
    neuron_malloc(&n_temp);
    dendritic_malloc(&d_temp);
    n_temp -> bias = random_number(_ONE,ONE);
    n_temp -> out  = malloc(img_height * img_width * sizeof(int));
    dendritic_insert_img(red  , img_width, img_height, kernel_size,&d_temp);
    dendritic_insert_img(blue , img_width, img_height, kernel_size,&d_temp);
    dendritic_insert_img(green, img_width, img_height, kernel_size,&d_temp);
    n_temp -> dendritic = d_temp;
    if((*l) -> prev == NULL)
    {
        (*l)         = n_temp;
        (*l) -> prev = n_temp;
        (*l) -> next = n_temp;
        return;
    }
    while(n_last -> next != (*l))
    {
        n_last = n_last -> next;
    }
    n_last -> next = n_temp;
    n_temp -> prev = n_last;
    n_temp -> next = (*l);
    (*l)   -> prev = n_temp;
}

void neuron_malloc(CNN_Neuron **neuron)
{
    (*neuron)         = malloc(sizeof(CNN_Neuron));
    (*neuron) -> next = malloc(sizeof(CNN_Neuron));
    (*neuron) -> prev = malloc(sizeof(CNN_Neuron));
    (*neuron) -> next = NULL;
    (*neuron) -> prev = NULL;
    dendritic_malloc(&((*neuron) -> dendritic));
}

void neuron_out_calc_conv(CNN_Dendritic **d,int img_width,int img_height,int kernel_size)
{
    while((*d) -> next != NULL)
    {
        convolucaoInt((*d) -> img,img_width,img_height,(*d) -> kernel,kernel_size,&((*d) -> intermediate),1);
        (*d) = (*d) -> next;
    }
    convolucaoInt((*d) -> img,img_width,img_height,(*d) -> kernel,kernel_size,&((*d) -> intermediate),1);
}

void neuron_out_calc_out(CNN_Dendritic **start,int *out,int i)
{
    while((*start) -> next != NULL)
    {
        out      += ((*start) -> intermediate[i]);
        (*start)  = (*start) -> next;
    }
    out += ((*start) -> intermediate[i]);
}

void neuron_out(CNN_Neuron **neuron,int img_width,int img_height,int kernel_size)
{
    CNN_Neuron    *n_start;
    CNN_Dendritic *d_start;
    neuron_malloc(&n_start);
    dendritic_malloc(&d_start);
    n_start = (*neuron);
    while(n_start -> next != NULL)
    {
        neuron_out_calc_conv(&(n_start -> dendritic),img_width,img_height,kernel_size);
    }
    neuron_out_calc_conv(&(n_start -> dendritic),img_width,img_height,kernel_size);
    while(n_start -> prev != NULL)
    {
        for(int i = 0;i < img_height * img_width;i++)
        {
            n_start -> out[i] = n_start -> bias;
            neuron_out_calc_out(&(n_start -> dendritic),&(n_start -> out[i]),i);
        }
    }
}

void neuron_insert(int img_height, int img_width,int out_height, int out_width, int kernel_size, int input_size, int type, CNN_Neuron **n)
{
    CNN_Neuron    *n_temp;
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_temp;
    dendritic_malloc(&d_temp);
    neuron_malloc(&n_temp);
    n_last         = (*n);
    n_temp -> bias = random_number(_ONE,ONE);
    n_temp -> out  = malloc(out_width * out_height * sizeof(int));
    if(type == CONV)
    {
        for(int i = 0;i < input_size;i++)
        {
            dendritic_insert(img_height,img_width,img_height,img_width,kernel_size,type,&(d_temp));
        }
    } else {
        dendritic_insert(img_height,img_width,out_height,out_width,kernel_size,type,&(d_temp));
    }
    n_temp -> dendritic = d_temp;
    if((*n) -> prev == NULL)
    {
        (*n)         = n_temp;
        (*n) -> next = n_temp;
        (*n) -> prev = n_temp;
        return;
    }
    while(n_last -> next != (*n))
    {
        n_last = n_last -> next;
    }
    n_last -> next = n_temp;
    n_temp -> prev = n_last;
    n_temp -> next = (*n);
    (*n)   -> prev = n_temp;
}