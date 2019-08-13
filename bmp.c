#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "conversao.h"
#include "bmp.h"

#define GRAY_LEVELS 256

/* pixel **read_color_table(file_name,bmheader,rgb)
 * char *file_name
 * bitmapheader *bmheader
 * linha *rgb */
pixel **read_color_table(file_name,bmheader,rgb)
    char *file_name;
    bitmapheader *bmheader;
    pixel **rgb;
{

    FILE *fp;
    int position;
    char buffer[1];
    long height, width;
    int x, y, pad;

    fp = fopen(file_name,"rb");
    position = fseek(fp,54,SEEK_SET);
    height = bmheader->height;
    width = bmheader->width;
    pad = calculate_pad(width);
    printf("Lendo a imagem de [%ld][%ld]\n",height,width);
    int bytes = 54;

    rgb[20][223].blue = 0x00;

    if(ordem_de_leitura(width) == 1){
        for(y = height-1;y > -1;y--){
            for(x = 0;x < width+2;x++){
                if(x < width){

                    printf("%d [%d][%d][1]\n",bytes,y,x);
                    bytes = bytes + 1;
                    fread(buffer,1,1,fp);
                    rgb[y][x].blue  = buffer[0];

                    printf("%d [%d][%d][2]\n",bytes,y,x);
                    bytes = bytes + 1;
                    fread(buffer,1,1,fp);
                    rgb[y][x].green = buffer[1];

                    printf("%d [%d][%d][3]\n",bytes,y,x);
                    bytes = bytes + 1;
                    fread(buffer,1,1,fp);
                    rgb[y][x].red   = buffer[2];

                } else {
                    for(int a = 0;a < pad;a++){
                        printf("%d\n",bytes);
                        bytes = bytes + 1;
                        fread(buffer,1,1,fp);
                    }
                }
            }
        }
    } else {
        for(y = 0;y < height;y++){
            for(x = 0;x < width;x++){
                fread(buffer,1,3,fp);
                rgb[y][x].blue  = buffer[0];
                rgb[y][x].green = buffer[1];
                rgb[y][x].red   = buffer[2];
            }
            if(pad != 0){
                position = fseek(fp,pad,SEEK_CUR);
            }
        }
    }

    fclose(fp);
    return rgb;

}

int bytesperrow(long width,int bitCout){
    return (width*bitCout + 31)/32;
}

int read_bmp_file_header(char *file_name,bmpfileheader *file_header){

    char buffer[10];
    long ll;
    short ss;
    unsigned short uss;
    unsigned long ull;
    FILE *fp;

    if((fp = fopen(file_name,"rb")) == NULL){
        printf("Arquivo: %s não encontrado\n",file_name);
        return 1;
    }

    if(1 == 1){
        fread(buffer,1,2,fp);
        extract_ushort_from_buffer(buffer,1,0,&uss);
        file_header->filetype = uss;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        file_header->filesize = ull;

        fread(buffer,1,2,fp);
        extract_short_from_buffer(buffer,1,0,&ss);
        file_header->reserved1 = ss;

        fread(buffer,1,2,fp);
        extract_short_from_buffer(buffer,1,0,&ss);
        file_header->reserved2 = ss;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer, 1, 0, &ull);
        file_header->offset = ull;
    }

    if(ull != 54){
        printf("Arquivo corrompido");
        return 1;
    }

    fclose(fp);

    return 0;

}

int read_bmp_header(char *file_name,bitmapheader *bmp_header){

    char buffer[10];
    long ll;
    short ss;
    unsigned short uss;
    unsigned long ull;
    FILE *fp;

    if((fp = fopen(file_name,"rb")) == NULL){
        printf("Arquivo: %s não encontrado\n",file_name);
        return 1;
    }

    fseek(fp,14,SEEK_SET);

    if(1 == 1){

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->size = ull;

        fread(buffer,1,4,fp);
        extract_long_from_buffer(buffer,1,0,&ll);
        bmp_header->width = ll;

        fread(buffer,1,4,fp);
        extract_long_from_buffer(buffer,1,0,&ll);
        bmp_header->height = ll;

        fread(buffer,1,2,fp);
        extract_ushort_from_buffer(buffer,1,0,&uss);
        bmp_header->planes = uss;

        fread(buffer,1,2,fp);
        extract_ushort_from_buffer(buffer,1,0,&uss);
        bmp_header->bitsperpixel = uss;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->compression = ull;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->sizeofbitmap = ull;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->horzres = ull;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->vertres = ull;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->colorsused = ull;

        fread(buffer,1,4,fp);
        extract_ulong_from_buffer(buffer,1,0,&ull);
        bmp_header->colorsimp = ull;
    }

    fclose(fp);

    return 0;

}

/* read_bmp_image(file_name,array,file_header,bmheader)
 *  char *file_name;
 *  linha *array;
 *  bmpfileheader *file_header;
 *  bitmapheader *bmheader; */
pixel **read_bmp_image(file_name,array,file_header,bmheader)
    char *file_name;
    pixel **array;
    bmpfileheader *file_header;
    bitmapheader *bmheader;
{

    FILE *fp;
    int x, y, pad = 0, place = 0, i;
    long colors = 0, height = 0, width = 0, position = 0;
    char buffer[10];
    unsigned char uc;
    long ll;

    width = bmheader->width;
    height = bmheader->height;

    if(bmheader->height < 0){
        height *= (-1);
    }

    if(bmheader->compression != 0){
        exit(1);
    }

    array = read_color_table(file_name,bmheader,array);

    return array;

}

/* calculte_pad(...)
 * Verifica se a largura da imagem é um numero divisivel por
 * 4, se for não adiciona pads. Caso seja diferente, indica
 * o números de bytes adicionados para completar essa regra */
int calculate_pad(long width){

    int pad = 0;

    pad = ((width%4) == 0) ? 0 : (4 - (width%4));

    return pad;

}

/* is_a_bmp(...)
 * This function looks at a file to see if it is a bmp file.
 * First look at the file extension. Next look at the filetype 
 * to ensure it is 0x4d42 */
int is_a_bmp(char *file_name){

    char *cc;
    bmpfileheader file_header;

    cc = strstr(file_name,".bmp");
    if(cc == NULL){
        return 0;
    }

    read_bmp_file_header(file_name,&file_header);

    if(file_header.filetype != 0x4D42){
        return 0;
    } else {
        return 1;
    }

}

/* does_not_exist(...)
 * Verifica se o arquivo existe */
int does_not_exist(char file_name[]){

    FILE *image_file;

    image_file = fopen(file_name,"rb");
    if(image_file != NULL){
        fclose(image_file);
        return 0;
    }

    return 1;

}

pixel **allocate_image_array(long width,long height){
    pixel **rgb;
    int pad = calculate_pad(width);
    rgb = malloc(height*sizeof(pixel*));
    if(rgb == NULL){
        printf("Socorro o malloc devolveu NULL! \n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i < height;++i){
        rgb[i] = malloc((width+pad)*sizeof(pixel));
        if(rgb[i] == NULL){
            printf("Socorro o malloc devolveu NULL\n");
            exit(EXIT_FAILURE);
        }
    }
    return rgb;
}

int free_bmp(long width,long height,pixel **rgb){
    int x, y;
    for(y = 0;y < height;y++){
        free(rgb[y]);
    }
    printf("Memoria liberada\n");
    return 1;
}

int ordem_de_leitura(long height){
    if(height > 0){
        return 1;
    } else {
        return 0;
    }
}

int pixel_storage(int bitsperpixel,long width){
    long rowSize;
    rowSize = (bitsperpixel*width)/32;
    if((bitsperpixel*width)%32 != 0){
        rowSize = ((bitsperpixel*width)/32)*4;
    }
}

int write_bmp(file_name,file_header,bmp_header,rgb)
    char *file_name;
    bmpfileheader *file_header;
    bitmapheader *bmp_header;
    pixel **rgb;
{

    char buffer[10];
    long ll;
    short ss;
    unsigned short uss;
    unsigned long ull;
    FILE *fp;
    int x, y;
    long width = bmp_header->width;
    long height = bmp_header->height;
    int pad;

    fp = fopen(file_name,"wb");

    if(fp == NULL){
        printf("Arquivo: %s não encontrado\n",file_name);
        return 1;
    }

    if(1 == 1){

        insert_ushort_into_buffer(buffer,0,file_header->filetype);
        fwrite(buffer,1,2,fp);

        insert_ulong_into_buffer(buffer,0,file_header->filesize);
        fwrite(buffer,1,4,fp);

        insert_short_into_buffer(buffer,0,file_header->reserved1);
        fwrite(buffer,1,2,fp);

        insert_short_into_buffer(buffer,0,file_header->reserved2);
        fwrite(buffer,1,2,fp);

        insert_ulong_into_buffer(buffer,0,file_header->offset);
        fwrite(buffer,1,4,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->size);
        fwrite(buffer,1,4,fp);

        insert_long_into_buffer(buffer,0,bmp_header->width);
        fwrite(buffer,1,4,fp);

        insert_long_into_buffer(buffer,0,bmp_header->height);
        fwrite(buffer,1,4,fp);

        insert_short_into_buffer(buffer,0,bmp_header->planes);
        fwrite(buffer,1,2,fp);

        insert_short_into_buffer(buffer,0,bmp_header->bitsperpixel);
        fwrite(buffer,1,2,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->compression);
        fwrite(buffer,1,4,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->sizeofbitmap);
        fwrite(buffer,1,4,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->horzres);
        fwrite(buffer,1,4,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->vertres);
        fwrite(buffer,1,4,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->colorsused);
        fwrite(buffer,1,4,fp);

        insert_ulong_into_buffer(buffer,0,bmp_header->colorsimp);
        fwrite(buffer,1,4,fp);
    }

    pad = calculate_pad(width);

    for(y = height-1;y > -1;y--){
        for(x = 0;x < width;x++){
            buffer[0] = rgb[y][x].blue;
            buffer[1] = rgb[y][x].green;
            buffer[2] = rgb[y][x].red;
            fwrite(buffer,sizeof(char),3,fp);
        }
        if(pad > 0){
            buffer[0] = 0x00; buffer[1] = 0x00;
            buffer[2] = 0x00; buffer[3] = 0x00;
            fwrite(buffer,sizeof(char),pad,fp);
        }
    }

    fclose(fp);

    return 0;

}