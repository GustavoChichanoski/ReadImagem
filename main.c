#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/detectores.h"
#include "../include/cnn.h"
#include "../include/operacaoMatriz.h"
#include "../include/processamento.h"
#include "../include/neuralNetwork.h"

int main(int argc,char *argv[])
{
    srand(time(NULL));
    // reverse(10,2);
    long height, width;
    char *file_image;
    char *file_image2;
    bmpfileheader file_header;
    bitmapheader  bmp_header;
    file_image = ".\\img\\8k.bmp";
    file_image2 = ".\\img\\gal_teste.bmp";
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
    kernel = (int *) malloc(3 * 3 * sizeof(int));
    for (int i = 0;i < width * height;i++)
    {
        red  [i] = 0;
        blue [i] = 0;
        green[i] = 0;
    }
    kernel[0] = 76; kernel[1] = 53; kernel[2] = 18;
    kernel[3] = 48; kernel[4] = 25; kernel[5] = 2;
    kernel[6] = 10; kernel[7] = 5;  kernel[8] = 20;
    read_bmp_rgb(file_image,file_header,bmp_header,&red,&blue,&green);
    write_bmp_rgb(file_image2,&file_header,&bmp_header,&red,&blue,&green);
}

// void RELU(pxMat *img)
// {
//     for(int pos = 0;pos < img -> column * img -> row;pos++)
//     {
//         img -> image[pos] = reluPixel(img -> image[pos]);
//     }
// }