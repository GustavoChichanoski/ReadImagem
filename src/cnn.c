#include "../include/cnn.h"

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
    l_temp -> input_number  = input_number;
    l_temp -> kernel_size   = kernel_size;
    l_temp -> neuron_number = neuron_number;
    for(int i = 0;i < l_temp -> neuron_number;i++)
    {
        neuron_insert_img(img_height,img_width,input_number,kernel_size,red,blue,green,&n_temp);
    }
    l_temp -> neuron = n_temp;
    if((*l) -> prev == NULL)
    {
        (*l)         = l_temp;
        (*l) -> prev = l_temp;
        (*l) -> next = l_temp;
        return;
    }
    while(l_last -> next != (*l))
    {
        l_last = l_last -> next;
    }
    l_temp -> prev = l_last;
    l_temp -> next = (*l);
    l_last -> next = l_temp;
    (*l)   -> prev   = l_temp;
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
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_temp;
    layer_malloc(&l_temp);
    l_last = (*l);
    while(l_last -> next != (*l))
    {
        l_last = l_last -> next;
    }
    l_temp -> type           = type;
    l_temp -> img_height     = l_last -> out_height;
    l_temp -> img_width      = l_last -> out_width;
    l_temp -> input_number   = l_last -> neuron_number;
    l_temp -> kernel_size    = kernel_size;
    l_temp -> neuron_number  = (type == CONV) ? neuron_number : l_last -> neuron_number;
    if(type == POOL)
    {
        if(l_last -> out_height % 2 == 0)
        {
            l_temp -> out_height = l_last -> out_height/2;
            l_temp -> out_width  = l_last -> out_width /2;
        } else {
            l_temp -> out_height = (l_last -> out_height/2) + 1;
            l_temp -> out_width  = (l_last -> out_width /2) + 1;
        }
    } else {
        l_temp -> out_height = l_last -> out_height;
        l_temp -> out_width  = l_last -> out_width ;
    }
    for(int i = 0;i < l_temp -> neuron_number;i++)
    {
        neuron_insert(l_temp -> img_height,l_temp -> img_width,l_temp -> out_height,l_temp -> out_width,kernel_size,l_last -> neuron_number,type,&(l_temp -> neuron));
    }
    if(type == CONV)
    {
        /* Apontando para a anterior */
        n_temp = l_temp -> neuron; /* Neuronio atual */
        do
        {
            d_temp = n_temp -> dendritic; /* Dentrito atual*/
            n_last = l_last -> neuron;    /* Neuronio da camada anterior */
            do
            {
                d_temp -> img = n_last -> out;        /* Imagem do dentrito atual recebe a saida do neuronio da camada anterior */
                d_temp        = d_temp -> next;       /* Proximo dentrito */
                n_last        = n_last -> next;       /* Proximo neuronio da camada anterior */
            } while (n_last  != l_last -> neuron); /* Verifica se voltou para o começo */
            n_temp = n_temp -> next;
        } while (n_temp != l_temp -> neuron);
    } else {
        n_temp = l_temp -> neuron;
        do
        {
            d_temp = n_temp -> dendritic;
            n_last = l_last -> neuron;
            do
            {
                d_temp -> img = n_last -> out;
                d_temp = d_temp -> next;
                n_last = n_last -> next;
            } while (d_temp != n_temp -> dendritic);
            n_temp = n_temp -> next;
        } while (n_temp != l_temp -> neuron);
    }
    l_last -> next = l_temp;
    l_temp -> prev = l_last;
    l_temp -> next = (*l);
    (*l)   -> prev = l_temp;
}