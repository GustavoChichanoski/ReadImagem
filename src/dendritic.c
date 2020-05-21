#include "../include/dendritic.h"

void convolucaoInt(int *img,int img_width,int img_height,int *kernel,int kernel_degree,int **out,int stride);

/* Insere um dentrito
    INPUTS :
    int           *img         - Imagem a ser gravada no dentrito
    int           *img_width   - Comprimento horizontal da imagem
    int           *img_height  - Comprimento vertical da imagem
    int           *kernel_size - ordem do nucleo de conversao da imagem
    CNN_Dendritic *head        - Dentrito
*/
void dendritic_insert_img(int *img,int img_width,int img_height,int kernel_size,CNN_Dendritic **head)
{
    CNN_Dendritic *d;
    CNN_Dendritic *last;
    dendritic_malloc(&d);
    last = (*head);
    d -> img          = malloc(img_width   * img_height  * sizeof(int));
    d -> intermediate = malloc(img_width   * img_height  * sizeof(int));
    d -> kernel       = malloc(kernel_size * kernel_size * sizeof(int));
    for(int i = 0;i < img_height * img_width;i++)
    {
        if(i < kernel_size * kernel_size)
        {
            d -> kernel[i] = random_number(_ONE,ONE);
        }
        d -> img[i] = img[i];
    }
    if((*head) -> prev == NULL)
    {
        (*head)         = d;
        (*head) -> prev = d;
        (*head) -> next = d;
        return;
    }
    while(last -> next != (*head))
    {
        last = last -> next;
    }
    last    -> next = d;
    d       -> prev = last;
    d       -> next = (*head);
    (*head) -> prev = d;
}

void dendritic_insert(int img_height,int img_width,int out_height,int out_width,int kernel_size,int type,CNN_Dendritic **l)
{
    CNN_Dendritic *start;
    CNN_Dendritic *temp;
    dendritic_malloc(&temp);
    dendritic_malloc(&start);
    int max     = img_height  * img_width, core = kernel_size * kernel_size;
    start       = (*l);
    if(type == CONV)
    {
        temp -> intermediate = malloc(max  * sizeof(int));
        temp -> kernel       = malloc(core * sizeof(int));
        for (int i = 0;i < core;i++)
        {
            temp -> kernel[i] = random_number(_ONE,ONE);
        }
    }
    if((*l) -> prev == NULL)
    {
        (*l)         = temp;
        (*l) -> prev = temp;
        (*l) -> next = temp;
        return;
    }
    while(start -> next != (*l))
    {
        start = start -> next;
    }
    start -> next = temp;
    temp  -> prev = start;
    temp  -> next = (*l);
    (*l)  -> prev = temp;
}

void dendritic_malloc(CNN_Dendritic **dendritic)
{
    (*dendritic)         = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> next = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> prev = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> next = NULL;
    (*dendritic) -> prev = NULL;
}

void convolucaoInt(int *img,int img_width,int img_height,int *kernel,int kernel_degree,int **out,int stride)
{
    int kernel_x, kernel_y, kernel_med = kernel_degree / 2, kernel_pos = 0;
    int img_x, img_y, img_x_new, img_y_new, img_pos_new;
    int out_pos = 0;
    int soma = 0;
    int v_k = 0;
    int v_i = 0;
    for (img_y = 0;img_y < img_height;img_y += stride)
    {
        for (img_x = 0;img_x < img_width;img_x += stride)
        {
            (*out)[out_pos] = 0;
            soma = 0;
            kernel_pos = 0;
            for(kernel_y = -kernel_med;kernel_y < kernel_med + 1;kernel_y++)
            {
                for(kernel_x = -kernel_med;kernel_x < kernel_med + 1;kernel_x++)
                {
                    img_x_new = img_x + kernel_x;
                    img_y_new = img_y + kernel_y;
                    if(img_y_new > -1 && img_y_new < img_height && img_x_new > -1 && img_x_new < img_width)
                    {
                        img_pos_new      = img_y_new * img_width + img_x_new;
                        v_k = kernel[kernel_pos];
                        v_i = img[img_pos_new];
                        soma            += kernel[kernel_pos] * img[img_pos_new] / ONE;
                        (*out)[out_pos] += kernel[kernel_pos] * img[img_pos_new] / ONE;
                    }
                    kernel_pos++;
                }
            }
            out_pos++;
        }
    }
}