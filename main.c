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

    extract_ushort_from_buffer(buffer,1,0,number);
    uss = *number;
    printf("String: %c%c, short: %i\n",buffer[0],buffer[1],uss);

    if(read_bmp_file_header(file_image,&file_header) == 1){
        printf("Could not read a file\n");
        return 1;
    }

    uss = file_header.filetype;
    printf("Assinatura: %i\n",uss);

    ull = file_header.filesize;
    printf("Tamanho do arquivo: %lu\n",ull);

    ull = file_header.offset;
    printf("Offset: %lu \n",ull);

    read_bmp_header(file_image,&bmp_header);
    uss = bmp_header.bitsperpixel;
    printf("Bit per pixel: %u\n",uss);

    ull = bmp_header.compression;
    printf("compression: %lu\n",ull);

    return 0;

}