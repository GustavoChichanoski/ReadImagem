#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../include/cnn.h"

void convolucaoInt(int *img,int img_width,int img_height,int *kernel,int kernel_degree,int **out,int stride);
void layer_calc_neuron(CNN_Layer **l,int type);

void convolucaoInt(int *img,int img_width,int img_height,int *kernel,int kernel_degree,int **out,int stride)
{
    int kernel_x, kernel_y, kernel_med = kernel_degree / 2, kernel_pos = 0;
    int img_x, img_y, img_x_new, img_y_new, img_pos_new;
    int out_pos = 0;
    for (img_y = 0;img_y < img_height;img_y += stride)
    {
        for (img_x = 0;img_x < img_width;img_x += stride)
        {
            (*out)[out_pos] = 0;
            kernel_pos = 0;
            for(int kernel_y = -kernel_med;kernel_y < kernel_med + 1;kernel_y++)
            {
                for(int kernel_x = -kernel_med;kernel_x < kernel_med + 1;kernel_x++)
                {
                    img_x_new = img_x + kernel_x;
                    img_y_new = img_y + kernel_y;
                    if(img_y_new > -1 && img_y_new < img_height && img_x_new > -1 && img_x_new < img_width)
                    {
                        img_pos_new = img_y_new * img_width + img_x_new;
                        (*out)[out_pos] += kernel[kernel_pos] * img[img_pos_new];
                    }
                    kernel_pos++;
                }
            }
            out_pos++;
        }
    }
}

void split_image(int **img, int **split_image, int width, int height, int kernel_size, int img_position_y, int img_position_x)
{
    int i, j, split_position = 0;
    int kernel_med = kernel_size / 2;
    for(i = -kernel_med;i < kernel_med + 1;i++)
    {
        for(j = -kernel_med;j < kernel_med + 1;j++)
        {
            if(img_position_y + kernel_med > -1 && img_position_y + kernel_med < height)
            {
                if(img_position_x + kernel_med > -1 && img_position_x + kernel_med < width)
                {
                    split_image[split_position] = img[(img_position_x + kernel_med) + (img_position_y + kernel_med)*width];
                }
            }
            split_position++;
        }
    }
}

void layer_insert_img(int img_height,int img_width,int kernel_size,int neuron_number,int input_number,int *red,int *blue,int *green,CNN_Layer **l)
{
    CNN_Layer     *l_temp;
    CNN_Layer     *l_last;
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    l_last = (*l);
    layer_malloc(&l_temp);
    neuron_malloc(&n_temp);
    dendritic_malloc(&d_temp);
    l_temp -> type          = CONV;
    l_temp -> img_height    = img_height;
    l_temp -> img_width     = img_width;
    l_temp -> out_height    = img_height;
    l_temp -> out_width     = img_width;
    l_temp -> input_number  = 3;
    l_temp -> kernel_size   = kernel_size;
    l_temp -> neuron_number = neuron_number;
    for(int i = 0;i < neuron_number;i++)
    {
        neuron_insert_img(img_height,img_width,input_number,kernel_size,red,blue,green,&n_temp);
    }
    l_temp -> neuron = n_temp;
    if((*l) -> prev == NULL)
    {
        (*l)         = l_temp;
        (*l) -> prev = l_temp;
        return;
    }
    while(l_last -> next != NULL)
    {
        l_last = l_last -> next;
    }
    l_temp -> prev = l_last;
    l_last -> next = l_temp;
}

void layer_malloc(CNN_Layer **layer)
{
    (*layer)         = malloc(sizeof(CNN_Layer));
    (*layer) -> next = malloc(sizeof(CNN_Layer));
    (*layer) -> prev = malloc(sizeof(CNN_Layer));
    (*layer) -> next = NULL;
    (*layer) -> prev = NULL;
    neuron_malloc(&((*layer) -> neuron));
}

void layer_insert(int kernel_size, int neuron_number, int type, CNN_Layer **l)
{
    CNN_Layer     *l_temp;
    CNN_Layer     *l_last;
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    layer_malloc(&l_temp);
    layer_malloc(&l_last);
    neuron_malloc(&n_temp);
    dendritic_malloc(&d_temp);
    l_last = (*l);
    while(l_last -> next != NULL)
    {
        l_last = l_last -> next;
    }
    l_temp -> type           = type;
    l_temp -> img_height     = l_last -> out_height;
    l_temp -> img_width      = l_last -> out_width;
    l_temp -> out_height     = (type == POOL) ? l_last -> out_height / 2 + 1 : l_last -> out_height;
    l_temp -> out_width      = (type == POOL) ? l_last -> out_width  / 2 + 1 : l_last -> out_width;
    l_temp -> input_number   = 3;
    l_temp -> kernel_size    = kernel_size;
    l_temp -> neuron_number  = neuron_number;
    neuron_insert(l_temp -> img_height,l_temp -> img_width,l_temp -> out_height,l_temp -> out_width,kernel_size,l_last -> neuron_number,type,&(l_temp -> neuron));
    l_temp -> prev = l_last;
    l_last -> next = l_temp;
}

void layer_calc_pool(CNN_Neuron **n,int width,int height)
{
    CNN_Neuron *n_last;
    n_last = (*n);
    int img_width, img_height;
    while(n_last -> next != NULL)
    {
        poolingInt(1,n_last -> dendritic -> img,width,height,&(n_last -> out),&img_width,&img_height);
        n_last = n_last -> next;
    }
    poolingInt(1,n_last -> dendritic -> img,width,height,&(n_last -> out),&img_width,&img_height);
}

void layer_calc_relu(CNN_Neuron **n,int width,int height)
{
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_last;
    n_last = (*n);
    while(n_last -> next != NULL)
    {
        for(int i = 0;i < width * height;i++)
        {
            n_last -> out[i] = (n_last -> dendritic -> img[i] > -1) ? n_last -> dendritic -> img[i] : 0;
        }
        n_last = n_last -> next;
    }
    for(int i = 0;i < width * height;i++)
    {
        n_last -> out[i] = (n_last -> dendritic -> img[i] > -1) ? n_last -> dendritic -> img[i] : 0;
    }
    n_last = n_last -> next;
}

void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size)
{
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_last;
    n_last = *n;
    while(n_last -> next != NULL)
    {
        d_last = n_last -> dendritic;
        while(d_last -> next != NULL)
        {
            convolucaoInt(d_last -> img,width,height,d_last -> kernel,kernel_size,&(d_last -> intermediate),1);
            d_last = d_last -> next;
        }
        convolucaoInt(d_last -> img,width,height,d_last -> kernel,kernel_size,&(d_last -> intermediate),1);
        for(int i = 0;i < width * height;i++)
        {
            d_last = n_last -> dendritic;
            n_last -> out[i] = n_last -> bias;
            while(d_last -> next != NULL)
            {
                n_last -> out[i] += d_last -> intermediate[i];
                d_last            = d_last -> next;
            }
            n_last -> out[i] += d_last -> intermediate[i];
        }
    }
}

void layer_calc_neuron(CNN_Layer **l,int type)
{
    CNN_Neuron *n;
    n = (*l) -> neuron;
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
}

void layer_calc(CNN_Layer **l)
{
    CNN_Layer *l_last;
    CNN_Neuron *n_last;
    l_last = *l;
    while(l_last -> next != NULL)
    {
        n_last = l_last -> neuron;
        layer_calc_neuron(&l_last, l_last -> type);
        l_last = l_last -> next;
    }
    layer_calc_neuron(&l_last, l_last -> type);
}
