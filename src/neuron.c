#include "../include/neuron.h"

void insert_neuron_img(int img_height, int img_width, int input_size, int kernel_size, int *red, int *blue, int *green, CNN_Neuron **l)
{
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    n_temp = malloc(sizeof(CNN_Neuron));
    d_temp = malloc(sizeof(CNN_Dendritic));
    n_temp -> bias = random_number(_ONE,ONE);
    n_temp -> out  = malloc(img_height * img_width * sizeof(int));
    insert_dendritic_img(red  , img_width, img_height, kernel_size, &d_temp);
    insert_dendritic_img(blue , img_width, img_height, kernel_size, &d_temp);
    insert_dendritic_img(green, img_width, img_height, kernel_size, &d_temp);
    if((*l) -> prev !=)
    while((*l) -> next != NULL)
    {
        (*l) = (*l) -> next;
    }
    n_temp -> dendritic = d_temp;
    n_temp -> prev      = NULL;
    (*l)   -> next      = n_temp;
}

void malloc_neuron(CNN_Neuron **neuron)
{
    (*neuron)         = malloc(sizeof(CNN_Neuron));
    (*neuron) -> next = malloc(sizeof(CNN_Neuron));
    (*neuron) -> prev = malloc(sizeof(CNN_Neuron));
    (*neuron) -> next = NULL;
    (*neuron) -> prev = NULL;
    malloc_dendritic(&((*neuron) -> dendritic));
}

void neuron_out_calc_conv(CNN_Dendritic *start,int img_width,int img_height,int kernel_size)
{
    while(start -> next != NULL)
    {
        convolucaoInt(
            start -> img,
            img_width,img_height,
            start -> kernel,
            kernel_size,
            &(start -> intermediate),
            1
        );
        start = start -> next;
    }
    convolucaoInt
    (
        start -> img,
        img_width,img_height,
        start -> kernel,
        kernel_size,
        &(start -> intermediate),
        1
    );
}

void neuron_out_calc_out(CNN_Dendritic *start,int *out,int i)
{
    while(start -> next != NULL)
    {
        out    += (start -> intermediate[i]);
        start  = start -> next;
    }
    out += (start -> intermediate[i]);
}

void neuron_out(CNN_Neuron **neuron,int img_width,int img_height,int kernel_size)
{
    CNN_Neuron    *n_start;
    CNN_Dendritic *d_start;
    int i = 0;
    malloc_neuron(&n_start);
    n_start = (*neuron);
    while((*neuron) -> next != NULL)
    {
        neuron_out_calc_conv((*neuron) -> dendritic,img_width,img_height,kernel_size);
    }
    neuron_out_calc_conv((*neuron) -> dendritic,img_width,img_height,kernel_size);
    while((*neuron) -> prev != NULL)
    {
        for(int i = 0;i , img_height * img_width;i++)
        {
            (*neuron) -> out[i] = (*neuron) -> bias;
            neuron_out_calc_out((*neuron) -> dendritic,&((*neuron) -> out[i]),i);
        }
    }
}

void insert_neuron(int img_height, int img_width, int kernel_size, int input_size, CNN_Neuron **l)
{
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    malloc_dendritic(&d_temp);
    malloc_neuron(&n_temp);
    n_temp -> bias      = random_number(_ONE,ONE);
    n_temp -> out       = malloc(img_height * img_width * sizeof(int));
    (*l)   -> dendritic = malloc(sizeof(CNN_Dendritic));
    for(int i = 0;i < input_size;i++)
    {
        insert_dendritic(img_height,img_width,kernel_size,&(d_temp));
    }
    n_temp -> dendritic = d_temp;
    while((*l) -> next != NULL)
    {
        (*l) = (*l) -> next;
    }
    n_temp -> prev = (*l);
    (*l) -> next = n_temp;
}v