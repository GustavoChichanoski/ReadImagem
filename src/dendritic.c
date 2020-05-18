#include "../include/dendritic.h"

/* Insere um dentrito
    INPUTS :
    int           *img         - Imagem a ser gravada no dentrito
    int           *img_width   - Comprimento horizontal da imagem
    int           *img_height  - Comprimento vertical da imagem
    int           *kernel_size - ordem do nucleo de conversao da imagem
    CNN_Dendritic *head        - Dentrito
*/
void insert_dendritic_img
(
    int *img,
    int img_width,
    int img_height,
    int kernel_size,
    CNN_Dendritic **head
)
{
    CNN_Dendritic *d;
    malloc_dendritic(&d);
    malloc_dendritic(&last);
    d -> img          = malloc(img_width   * img_height  * sizeof(int));
    d -> intermediate = malloc(img_width   * img_height  * sizeof(int));
    d -> kernel       = malloc(kernel_size * kernel_size * sizeof(int));
    for(int i = 0;i < img_height * img_width;i++)
    {
        d -> img[i] = img[i];
    }
    if((*head))
    while((*head) -> next != NULL)
    {
        (*l) = (*l) -> next;
    }
    d -> prev = 
    (*l) -> next = 
}

void insert_dendritic
(
    int img_height,
    int img_width,
    int kernel_size,
    CNN_Dendritic **l
)
{
    CNN_Dendritic *start;
    CNN_Dendritic *temp;
    malloc_dendritic(&temp);
    malloc_dendritic(&start);
    int max  = img_height  * img_width, core = kernel_size * kernel_size;
    start                = (*l);
    temp -> img          = malloc(max  * sizeof(int));
    temp -> intermediate = malloc(max  * sizeof(int));
    temp -> kernel       = malloc(core * sizeof(int));
    for (int i = 0;i < core;i++)
    {
        temp -> kernel[i] = random_number(_ONE,ONE);
    }
    for (int i = 0;i < max;i++)
    {
        temp -> intermediate[i] = 0;
        temp -> img[i]          = 0;
    }
    while(start -> next != NULL)
    {
        start = start -> next;
    }
    temp  -> next = NULL;
    temp  -> prev = start;
    start -> next = temp;
}

void malloc_dendritic(CNN_Dendritic **dendritic)
{
    (*dendritic)         = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> next = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> prev = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> next = NULL;
    (*dendritic) -> prev = NULL;
}

void dendrintic_conv(CNN_Neuron *n_head,int img_width,int img_height,int kernel_size)
{
    CNN_Neuron    *n_temp;
    CNN_Dendritic *d_temp;
    malloc_neuron(&n_temp);
    malloc_dendritic(&d_temp);
    n_temp = n_head;
    while(n_temp -> next != NULL)
    {
        d_temp = n_temp -> dendritic;
        while(d_temp != NULL)
        {
            convolucaoInt(d_temp -> img,img_width,img_height,d_temp -> kernel,kernel_size,d_temp -> intermediate,1);
            d_temp = d_temp -> next;
        }
        d_temp = n_temp -> dendritic;
        for (int i = 0;i < img_height * img_width;i++)
        {
            n_temp -> out[i]  = n_temp -> bias;
            while(d_temp -> next != NULL)
            {
                n_temp -> out[i] += d_temp -> intermediate[i];
            }
            n_temp -> out[i] += d_temp -> intermediate[i];
        }
        n_temp = n_temp -> next;
    }
}