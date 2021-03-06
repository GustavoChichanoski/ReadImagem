#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/detectores.h"
#include "../include/cnn.h"
#include "../include/cnn_exec.h"
#include "../include/operacaoMatriz.h"
#include "../include/neuralNetwork.h"
#include "../include/fft.h"
#include "../include/processamento.h"
#include <string.h>

int main(int argc,char *argv[])
{
    // reverse(10,2);
    long height, width;
    char *file_image;
    int kernel_size = 3;
    bmpfileheader file_header;
    bitmapheader  bmp_header;
    CNN_Layer *l;
    layer_malloc(&l);
    file_image  = ".\\img\\expresso_1.bmp";
    srand(time(NULL));
    if(read_bmp_file_header(file_image,&file_header))
    {
        printf("Informações sobre o arquivo não lidos\n");
        return 1;
    }
    if(read_bmp_header(file_image,&bmp_header))
    {
        printf("Informações sobre a imagem não lidos\n");
        return 1;
    }
    width  = bmp_header.width;
    height = bmp_header.height;
    if(height < 0)
    {
        height = height*(-1);
    }
    int *red, *blue, *green;
    red    = (int *) malloc(width * height * sizeof(int));
    blue   = (int *) malloc(width * height * sizeof(int));
    green  = (int *) malloc(width * height * sizeof(int));
    read_bmp_image_rgb(file_image,file_header,bmp_header,&red,&blue,&green);
    layer_insert_img(height,width,kernel_size,10,3,red,blue,green,&l);
    {   /* CNN of https://poloclub.github.io/cnn-explainer/#article-pooling*/
        layer_insert(3,10,RELU,&l);
        layer_insert(3,10,CONV,&l);
        layer_insert(3,10,RELU,&l);
        layer_insert(3,10,POOL,&l);
    }
    layer_calc(&l);
    CNN_Layer  *last;
    CNN_Neuron *n_last;
    last = l;
    int num_layer = 0;
    int num_neuron = 0;
    char str[30] = ".\\img\\cnn\\CNN_0_0_0.bmp\0";
    do
    {
        n_last = last -> neuron;
        num_neuron = 0;
        do
        {
            str[14] = (char) (num_layer    + 48);
            str[16] = (char) (num_neuron   + 48);
            str[18] = (char) (last -> type + 48);
            img_creat_red_to_blue(n_last -> out,(last -> out_height)*(last -> out_width),&red,&blue,&green);
            bmp_header.width  = last -> out_width;
            bmp_header.height = last -> out_height;
            write_bmp_rgb(str,&file_header,&bmp_header,&red,&blue,&green);
            n_last = n_last -> next;
            num_neuron++;
        } while (n_last != last -> neuron);
        num_layer++;
        last = last -> next;
    } while (last != l);
    rnn_layer *rl;
    last    = l    -> prev;
    n_last  = last -> neuron;
    int tam = last -> out_height * last -> out_width ;
    int *input;
    input = malloc(tam * last -> neuron_number * sizeof(int));
    for(int j = 0;j < last -> neuron_number;j++)
    {
        for (int i = 0;i < last -> out_height * last -> out_width;i++)
        {
            input[j*tam + i] = last -> neuron -> out[i];
        }
        n_last = n_last -> next;
    }
    ann_layer_cnn(&rl,last -> out_width,last -> out_height,last -> neuron_number,10);
    ann_layer_add(&rl,10);
    ann_layer_add(&rl,10);
    ann_layer_add(&rl,10);
    ann_layer_add(&rl,10);
    ann_layer_add(&rl,64*64);
    for (int i = 0;i < 1000;i++)
    {
        ann_layer_calc(&rl,input,tam * last -> neuron_number,red);
    }
    rnn_layer *rl_last;
    rl_last = rl;
    while(rl_last -> next != NULL)
    {
        rl_last = rl_last -> next;
    }
    write_bmp_rgb(str,&file_header,&bmp_header,&(rl_last -> output),&blue,&green);
    free(l);
}