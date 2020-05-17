#include "../include/dendritic.h"

/* Insere um dentrito
    INPUTS :
    int           *img         - Imagem a ser gravada no dentrito
    int           *img_width   - Comprimento horizontal da imagem
    int           *img_height  - Comprimento vertical da imagem
    int           *kernel_size - ordem do nucleo de conversao da imagem
    CNN_Dendritic *head        - Dentrito
*/
void insert_dendritic_img(int *img,int img_width,int img_height,int kernel_size,CNN_Dendritic **head)
{
    CNN_Dendritic *d;
    d                 = malloc(sizeof(CNN_Dendritic));
    d -> prev         = malloc(sizeof(CNN_Dendritic));
    d -> next         = malloc(sizeof(CNN_Dendritic));
    d -> img          = malloc(img_width   * img_height  * sizeof(int));
    d -> intermediate = malloc(img_width   * img_height  * sizeof(int));
    d -> kernel       = malloc(kernel_size * kernel_size * sizeof(int));
    d -> next         = NULL;
    for(int i = 0;i < img_height * img_width;i++)
    {
        d -> img[i] = img[i];
    }
    if(head == NULL)
    {
        d -> prev = NULL;
        (*head) = d;
        return;
    } else {
        while((*head) -> next == NULL)
        {
            (*head) = (*head) -> next;
        }
        d -> prev = (*head);
        (*head) -> next = d;
        return;
    }
}

void insert_dendritic
(
    int img_height,
    int img_width,
    int kernel_size,
    CNN_Dendritic **l
)
{
    CNN_Dendritic *temp;
    temp                 = malloc(sizeof(CNN_Dendritic));
    temp -> next         = malloc(sizeof(CNN_Dendritic));
    temp -> prev         = malloc(sizeof(CNN_Dendritic));
    temp -> img          = malloc(img_height  * img_width   * sizeof(int));
    temp -> intermediate = malloc(img_height  * img_width   * sizeof(int));
    temp -> kernel       = malloc(kernel_size * kernel_size * sizeof(int));
    for (int i = 0;i < kernel_size*kernel_size;i++)
    {
        temp -> kernel[i] = random_number(_ONE,ONE);
    }
    while((*l) -> next != NULL)
    {
        (*l) = (*l) -> next;
    }
    temp -> next         = NULL;
    temp -> prev = (*l);
    (*l) -> next = temp;
}

void malloc_dendritic(CNN_Dendritic **dendritic)
{
    (*dendritic)         = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> next = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> prev = malloc(sizeof(CNN_Dendritic));
    (*dendritic) -> next = NULL;
    (*dendritic) -> prev = NULL;
}