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

void insert_neuron(int img_height, int img_width, int kernel_size, int input_size, CNN_Neuron **l )
{
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    d_temp              = malloc(sizeof(CNN_Dendritic));
    d_temp -> prev      = malloc(sizeof(CNN_Dendritic));
    d_temp -> next      = malloc(sizeof(CNN_Dendritic));
    d_temp -> prev      = NULL;
    d_temp -> next      = NULL;
    n_temp              = malloc(sizeof(CNN_Neuron));
    n_temp -> prev      = malloc(sizeof(CNN_Neuron));
    n_temp -> next      = malloc(sizeof(CNN_Neuron));
    n_temp -> prev      = NULL;
    n_temp -> next      = NULL;
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
}