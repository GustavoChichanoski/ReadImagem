#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/detectores.h"
#include "../include/cnn.h"
#include "../include/matriz.h"
#include "../include/processamento.h"

int main(int argc, char *argv[ ]){
    
    // srand(time(NULL));
    // long height, width;
    // char *file_image;
    
    // bmpfileheader file_header;
    // bitmapheader  bmp_header;
    // file_image = ".\\img\\carro.bmp";
    
    // if(read_bmp_file_header(file_image,&file_header))
    // {
    //     printf("Informações sobre o arquivo não lidos\n");
    //     return 1;
    // }
    
    // if(read_bmp_header(file_image,&bmp_header))
    // {
    //     printf("Informações sobre a imagem não lidos\n");
    //     return 1;
    // }

    // width  = bmp_header.width;
    // height = bmp_header.height;

    // {
    //     printf("Tamanho do arquivo : %lu\n",file_header.filesize);
    //     printf("Tamanho do arquivo : %ld\n",file_header.offset);
    //     printf("Altura : %ld\n",bmp_header.height);
    //     printf("Comprimento : %ld\n",bmp_header.width);
    //     printf("BitsPerPixel : %d\n",bmp_header.bitsperpixel);
    // }

    // if(height < 0)
    // {
    //     height = height*(-1);
    // }
    
    // int *matA, *matB;
    // create_matriz(3,2,matA);
    // create_matriz(3,2,matB);
    
    // pixel *imagem = allocate_image_array(width,height);
    // printf("Imagem alocada\n");
    // imagem = read_bmp_image(file_image,imagem,file_header,bmp_header);
    // printf("Imagem lida\n");
    // imagem = gray_scale(width,height,imagem);
    // // imagem = Conv2D(height,width,imagem,3);
    // printf("Imagem em Preto e branco\n");
    // if(write_bmp(".\\img\\grey_galgadot.bmp",file_header,bmp_header,imagem)){
    //     printf("Imagem nao criada\n");
    //     return 1;
    // }
    // printf("Imagem criada\n");
    // free(imagem);
    
    // testeConvolucao();
    testeMatriz();
    
    return 0;

}