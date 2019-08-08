#include <stdio.h>
#include <stdlib.h>
#include "conversao.h"
#include "bmp.h"

int main(){

    printf("Hello world!\n");

    char buffer[2] = {'B','M'};
    unsigned short *number;
    unsigned short uss;
    unsigned long ull;
    long ll;
    short ss;
    char *file_image = "lena.bmp";
    bmpfileheader file_header;
    bitmapheader bmp_header;

    if(!is_a_bmp(file_image)){
        printf("O arquivo %s não é um .bmp",file_image);
    }

    extract_ushort_from_buffer(buffer,1,0,number);
    uss = *number;
    printf("String: %c%c, short: %i\n",buffer[0],buffer[1],uss);

    if(read_bmp_file_header(file_image,&file_header) == 1){
        printf("Informações sobre o arquivo não lidos\n");
        return 1;
    }

    printf("Assinatura: %i\n",file_header.filetype);
    printf("Tamanho do arquivo: %ld\n",file_header.filesize);
    printf("Offset: %lu \n\n",file_header.offset);

    if(read_bmp_header(file_image,&bmp_header) == 1){
        printf("Informações sobre a imagem não lidos\n");
        return 1;
    }

    printf("Tamanho do header da imagem: %lu \n",bmp_header.size);
    printf("width: %ld\n",bmp_header.width);
    printf("height: %ld\n",bmp_header.height);
    printf("planes: %i\n",bmp_header.planes);
    printf("size of bitmap: %lu\n",bmp_header.sizeofbitmap);
    printf("Bit per pixel: %u\n",bmp_header.bitsperpixel);
    printf("compression: %lu\n",bmp_header.compression);
    printf("cor importante: %lu\n",bmp_header.colorsimp);
    printf("cor usadas: %lu\n",bmp_header.colorsused);
    int pad = calculate_pad(bmp_header.width);
    printf("pad: %i\n",pad);

    return 0;

}