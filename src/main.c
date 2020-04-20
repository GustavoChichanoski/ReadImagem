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

int main(int argc, char *argv[]){
    srand(time(NULL));
    long height, width;
    char *file_image;
    bmpfileheader file_header;
    bitmapheader  bmp_header;
    file_image = ".\\img\\carro.bmp";
    // file_image = ".\\img\\grey_galgadot.bmp";
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
    {
        printf("Tamanho do arquivo : %lu\n",file_header.filesize);
        printf("Tamanho do arquivo : %ld\n",file_header.offset);
        printf("Altura : %ld\n",bmp_header.height);
        printf("Comprimento : %ld\n",bmp_header.width);
        printf("BitsPerPixel : %d\n",bmp_header.bitsperpixel);
    }
    if(height < 0)
    {
        height = height*(-1);
    }
    pixel *imagem = allocate_image_array(width,height);
    printf("Imagem alocada\n");
    imagem = read_bmp_image(file_image,imagem,file_header,bmp_header);
    printf("Imagem lida\n");
    imagem = gray_scale(width,height,imagem);
    {
        printf("Imagem rotacionada\n");
        pxMat img;
        img.column = width;
        img.row    = height;
        img.image  = imagem;
        img        = pooling(5,img);
        imagem     = img.image;
        height     = img.row;
        width      = img.column;
        printf("[%d][%d]\n",img.row,img.column);
        // imagem = Conv2D(height,width,imagem,3);
        printf("Imagem em Preto e branco\n");
        bmp_header.height = img.row;
        bmp_header.width  = img.column;
    }
    if(write_bmp(".\\img\\grey_galgadot.bmp",file_header,bmp_header,imagem)){
        printf("Imagem nao criada\n");
        return 1;
    }
    printf("Imagem criada\n");
    free(imagem);
    testeConvolucao();
    testeMatriz();
    return 0;
}