#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/detectores.h"
#include "../include/cnn.h"
#include "../include/operacaoMatriz.h"
#include "../include/neuralNetwork.h"
#include "../include/fft.h"

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
    CNN_Layer *last;
    malloc_layer(&l);
    file_image = ".\\img\\gal.bmp";
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
    int *out, out_width, out_height;
    int *kernel;
    red    = (int *) malloc(width * height * sizeof(int));
    blue   = (int *) malloc(width * height * sizeof(int));
    green  = (int *) malloc(width * height * sizeof(int));
    out    = (int *) malloc(width * height * sizeof(int));
    kernel = (int *) malloc(kernel_size * kernel_size * sizeof(int));
    read_bmp_image_rgb(file_image,file_header,bmp_header,&red,&blue,&green);
    layer_insert_img(height,width,kernel_size,10,3,red,blue,green,&l);
    {   /* CNN of https://poloclub.github.io/cnn-explainer/#article-pooling*/
        layer_insert(RELU,3,10,&l);
        layer_insert(CONV,3,10,&l);
        layer_insert(RELU,3,10,&l);
        layer_insert(POOL,3,10,&l);
        layer_insert(CONV,3,10,&l);
        layer_insert(RELU,3,10,&l);
        layer_insert(CONV,3,10,&l);
        layer_insert(RELU,3,10,&l);
        layer_insert(POOL,3,10,&l);
    }
    neuron_out(&(l -> neuron),l -> img_width,l -> img_height,l -> kernel_size);
    while(last -> prev == last)
    {
        last = l;
        while(last -> prev == NULL)
        {
            last = last -> next;
        }
        free(last);
    }
    free(l);
    write_bmp_rgb(file_image2,&file_header,&bmp_header,&red,&blue,&green);
}