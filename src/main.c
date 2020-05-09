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
#include "../include/complex.h"

void   RELU(pxMat *img);
char  *sprite_name(int i);
pixel *sprite(pixel *imagem,int pos_x,int pos_y, int width,int height);

// void print_sine()
// {
//     printf("sine: \n");
//     int N    = 80;
//     int N2   = N / 2;
//     int grid = 65536 / N;
//     int i = 0, j = N - 1;
//     for(j = N;j > -1;j--)
//     {
//         for(i = 0;i < 4096;i += 2*(4096/360))
//         {
//             int valor = sine(i,0).red;
//             if(j > N2)
//             {
//                 if( valor > (j - N2) * grid )
//                 { printf("*"); }
//                 else
//                 { printf(" "); }
//             } else {
//                 if( valor * (-1) > (N2 - j) * grid )
//                 { printf("*"); }
//                 else
//                 { printf(" "); }
//             }
//         }
//         printf("\n");
//     }
// }

// int  main(int argc, char *argv[]){
//     srand(time(NULL));
//     reverse(10,2);
//     long height, width;
//     char *file_image;
//     bmpfileheader file_header;
//     bitmapheader  bmp_header;
//     file_image = ".\\img\\gal2.bmp";
//     // file_image = ".\\img\\grey_galgadot.bmp";
//     if(read_bmp_file_header(file_image,&file_header))
//     {
//         printf("Informações sobre o arquivo não lidos\n");
//         return 1;
//     }
//     if(read_bmp_header(file_image,&bmp_header))
//     {
//         printf("Informações sobre a imagem não lidos\n");
//         return 1;
//     }
//     width  = bmp_header.width;
//     height = bmp_header.height;
//     if(height < 0)
//     {
//         height = height*(-1);
//     }
//     pixel *imagem = allocate_image_array(width,height);
//     imagem = read_bmp_image(file_image,imagem,file_header,bmp_header);
//     // imagem = gray_scale(width,height,imagem);
//     pxMat img;
//     {
//         printf("Imagem rotacionada\n");
//         img.column = width;
//         img.row    = height;
//         img.image  = imagem;
//         // img        = cnn(img,3);
//         // img        = pooling(2,&img);
//         // for(int pos = 0;pos < img.column * img.row;pos++)
//         // {
//         //     img.image[pos] = reluPixel(img.image[pos]);
//         // }
//         // img        = cnn(img,3);
//         // img        = pooling(2,&img);
//         // for(int pos = 0;pos < img.column * img.row;pos++)
//         // {
//         //     img.image[pos] = reluPixel(img.image[pos]);
//         // }
//         // img        = cnn(img,3);
//         // RELU(&img);
//         // img        = cnn(img,3);
//         // RELU(&img);
//         // img        = pooling(2,&img);
//         img        = cnn(img,3);
//         RELU(&img);
//         img        = pooling(2,&img);
//         imagem     = img.image;
//         height     = img.row;
//         // width      = img.column;
//         printf("[%d][%d]\n",img.row,img.column);
//         // imagem = Conv2D(height,width,imagem,3);
//         printf("Imagem em Preto e branco\n");
//     }
//     // int pos_x  = 0, pos_y = 0, i = 0;
//     // img.column = 29;
//     // img.row    = 29;
//     // img.image = allocate_image_array(29,29);
//     bmp_header.height = img.row;
//     bmp_header.width  = img.column;
//     // int images = 0, number = 0;
//     if(write_bmp(".\\img\\bgray.bmp",&file_header,&bmp_header,img.image)){
//         printf("Imagem nao criada\n");
//         return 1;
//     }
//     /*
//     while(pos_y < height)
//     {
//         while(pos_x < width)
//         {
//             char name[40];
//             if(i < 10)
//             {
//                 snprintf(name,sizeof(name),".\\img\\number\\number_0%d.bmp",i);
//             } else {
//                 snprintf(name,sizeof(name),".\\img\\number\\number_%d.bmp",i);
//             }
//             printf("%s\n",name);
//             for(int i = 0;i < S_W;i++)
//             {
//                 for(int j = 0;j < S_W;j++)
//                 {
//                     img.image[i*29 + j] = imagem[(pos_y + i)*width + j + pos_x];
//                 }
//             }
//             if(write_bmp(name,&file_header,&bmp_header,img.image)){
//                 printf("Imagem nao criada\n");
//                 return 1;
//             }
//             pos_x += 29;
//             number++;
//             i++;
//         }
//         number = 0;
//         pos_x = 0;
//         pos_y += 29;
//     }
//     */
//     free(imagem);
//     // testeConvolucao();
//     // testeMatriz();
//     return 1;
// }

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
    write_bmp_rgb(file_image2,&file_header,&bmp_header,&out,&out,&out);
}

void RELU(pxMat *img)
{
    for(int pos = 0;pos < img -> column * img -> row;pos++)
    {
        img -> image[pos] = reluPixel(img -> image[pos]);
    }
}