#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../include/cnn.h"

void convolucaoInt(int **img,int img_width,int img_height,int **kernel,int kernel_degree,int **out,int stride);

void convolucaoInt(int **img,int img_width,int img_height,int **kernel,int kernel_degree,int **out,int stride)
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
                        (*out)[out_pos] += (*kernel)[kernel_pos]*(*img)[img_pos_new];
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

void fpga_cnn(CNN_Layer *cnn)
{
    int dendritic = 0;
    while(cnn != NULL)
    {
        while(cnn -> neuron != NULL)
        {
            while(cnn -> neuron -> dendritic != NULL)
            {
                if(cnn -> type == CONV)
                {
                    convolucaoInt
                    (
                        &(cnn -> neuron -> dendritic -> img),
                        cnn   -> img_width,
                        cnn   -> img_height,
                        &(cnn -> neuron -> dendritic -> kernel),
                        cnn   -> kernel_size,
                        &(cnn -> neuron -> dendritic -> intermediate),
                        1
                    );
                }
                if(cnn -> type == POOL)
                {
                    poolingInt
                    (
                        1,
                        &(cnn -> neuron -> dendritic -> img),
                        cnn -> img_width,
                        cnn -> img_height,
                        &(cnn -> neuron -> out),
                        &(cnn -> next -> img_width),
                        &(cnn -> next -> img_height)
                    );
                }
                cnn -> neuron -> dendritic = cnn -> neuron -> dendritic -> next;
            }
            for(int i = 0;i < cnn -> img_height * cnn -> img_width;i++)
            {
                cnn -> neuron -> out[i] = 0;
                while(cnn -> neuron -> dendritic != NULL)
                {
                    cnn -> neuron -> out[i]    += cnn -> neuron -> dendritic -> intermediate[i];
                    cnn -> neuron -> dendritic  = cnn -> neuron -> dendritic -> next;
                }
                cnn -> neuron -> out[i] += cnn -> neuron -> bias;
            }
            cnn -> neuron = cnn -> neuron -> next;
        }
        cnn = cnn -> next;
    }
}

void insert_layer_img(int img_height, int img_width, int kernel_size, int neuron_number, int input_number, int *red, int *blue, int *green, CNN_Layer **l)
{
    CNN_Layer     *l_temp;
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    l_temp                  = malloc(sizeof(CNN_Layer));
    n_temp                  = malloc(sizeof(CNN_Neuron));
    d_temp                  = malloc(sizeof(CNN_Dendritic));
    l_temp -> next          = malloc(sizeof(CNN_Layer));
    n_temp -> next          = malloc(sizeof(CNN_Neuron));
    d_temp -> next          = malloc(sizeof(CNN_Dendritic));
    d_temp                  = malloc(sizeof(CNN_Dendritic));
    l_temp -> next          = NULL;
    n_temp -> next          = NULL;
    d_temp -> next          = NULL;
    l_temp -> type          = CONV;
    l_temp -> img_height    = img_height;
    l_temp -> img_width     = img_width;
    l_temp -> input_number  = 3;
    l_temp -> kernel_size   = kernel_size;
    l_temp -> neuron_number = neuron_number;
    l_temp -> neuron = malloc(sizeof(CNN_Neuron));
    insert_neuron_img(img_height,img_width,input_number,kernel_size,red,blue,green,&n_temp);
    (*l)         = l_temp;
    (*l) -> next = malloc(sizeof(CNN_Layer));
    (*l) -> prev = malloc(sizeof(CNN_Layer));
    (*l) -> next = NULL;
    (*l) -> prev = NULL;
}

void malloc_layer(CNN_Layer **layer)
{
    (*layer)         = malloc(sizeof(CNN_Layer));
    (*layer) -> next = malloc(sizeof(CNN_Layer));
    (*layer) -> prev = malloc(sizeof(CNN_Layer));
    (*layer) -> next = NULL;
    (*layer) -> prev = NULL;
    malloc_neuron(&((*layer) -> neuron));
}

void insert_layer(int img_height, int img_width, int type, int kernel_size, int neuron_number, CNN_Layer **l)
{
    CNN_Layer     *l_temp;
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    malloc_layer(&l_temp);
    malloc_neuron(&n_temp);
    malloc_dendritic(&d_temp);
    l_temp -> type           = type;
    l_temp -> img_height     = img_height;
    l_temp -> img_width      = img_width;
    l_temp -> input_number   = 3;
    l_temp -> kernel_size    = kernel_size;
    l_temp -> neuron_number  = neuron_number;
    while((*l) -> next != NULL)
    {
        (*l) = (*l) -> next;
    }
    insert_neuron(img_height,img_width,kernel_size,(*l) -> neuron_number,&(l_temp -> neuron));
    (*l) = l_temp;
    (*l) -> next = malloc(sizeof(CNN_Layer));
    (*l) -> prev = malloc(sizeof(CNN_Layer));
    (*l) -> next = NULL;
    (*l) -> prev = &l;
}
