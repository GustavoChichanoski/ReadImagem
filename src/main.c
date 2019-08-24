#include <stdio.h>
#include <stdlib.h>
#include "conversao.h"
#include "bmp.h"
#include "detectores.h"

int main(){

    long height, width;
    char *file_image;

    bmpfileheader file_header;
    bitmapheader bmp_header;
    file_image = "lena.bmp";

    if(read_bmp_file_header(file_image,&file_header) == 1){
        printf("Informações sobre o arquivo não lidos\n");
        return 1;
    }

    if(read_bmp_header(file_image,&bmp_header) == 1)
    {
        printf("Informações sobre a imagem não lidos\n");
        return 1;
    }

    width = bmp_header.width;
    height = bmp_header.height;

    if(height < 0)
    {
        height = height*(-1);
    }

    pixel **rgb = allocate_image_array(width+1,height+1);
    rgb = read_bmp_image(file_image,rgb,&file_header,&bmp_header);
    rgb = gray_scale(width,height,rgb);
    rgb = detectorBorda(width,height,rgb);
    write_bmp("eanl.bmp",&file_header,&bmp_header,rgb);

    return 0;

}
