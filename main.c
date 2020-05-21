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

int main(int argc,char *argv[])
{
    // reverse(10,2);
    long height, width;
    char *file_image;
    char *file_image2;
    int kernel_size = 3;
    bmpfileheader file_header;
    bitmapheader  bmp_header;
    CNN_Layer *l;
    layer_malloc(&l);
    file_image = ".\\img\\expresso_1.bmp";
    file_image2 = ".\\img\\gal_teste.bmp";
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
        layer_insert(3,10,CONV,&l);
        layer_insert(3,10,RELU,&l);
        layer_insert(3,10,CONV,&l);
        layer_insert(3,10,RELU,&l);
        layer_insert(3,10,POOL,&l);
    }
    layer_calc(&l);
    CNN_Layer *last;
    CNN_Neuron *n_last;
    last = l;
    do
    {
        n_last = last -> neuron;
        do
        {
            img_creat_red_to_blue(n_last -> out,(last -> out_height)*(last -> out_width),&red,&blue,&green);
            bmp_header.width = last -> out_width;
            bmp_header.height = last -> out_height;
            write_bmp_rgb(file_image2,&file_header,&bmp_header,&red,&blue,&green);
            n_last = n_last -> next;
        } while (n_last != last -> neuron);
        last = last -> next;
    } while (last != l);
    free(l);
}