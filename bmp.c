#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "conversao.h"
#include "bmp.h"

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

    fclose(fp);

    return 0;

}

int read_color_table(char *file_name,ctstruct *rgb, int size,int offset){
    int i;
    char buffer[10];
    FILE *fp;

    fp = fopen(file_name,"rb");
    fseek(fp,offset,SEEK_SET);

    for(i = 0;i < size;i++){
        fread(buffer,1,1,fp);
        rgb[i].blue = buffer[0];
        fread(buffer,1,1,fp);
        rgb[i].green = buffer[0];
        fread(buffer,1,1,fp);
        rgb[i].blue = buffer[0];
    }

    fclose(fp);

    return 1;

}

/* calculte_pad(...)
 * Calcula o pad necessário para cada linha de pixel no bitmap */
int calculate_pad(long width){

    int pad = 0;

    pad = ((width%4) == 0) ? 0 : (4 - (width%4));

    return pad;

}

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