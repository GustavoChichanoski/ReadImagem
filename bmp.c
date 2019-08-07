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

    printf("Arquivo: '%s' encontrado\n",file_name);
    printf("filetype: %i\n",file_header->filetype);

    fread(buffer,1,2,fp);
    printf("Assinatura lida\n");
    extract_ushort_from_buffer(buffer,1,0,&uss);
    printf("Assinatura: %u\n",uss);
    (*file_header).filetype = uss;
    printf("Assinatura armazenada: %u\n",file_header->filetype);

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
    extract_ulong_from_buffer(buffer,1,0,&ull);
    file_header->offset = ull;

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

    printf("Abrindo o arquivo\n");

    fp = fopen(file_name,"rb");
    fseek(fp,14,SEEK_SET);

    printf("Mudando o cursor para 14\n");

    fread(buffer,1,4,fp);
    printf("Tamanho da imagem lida\n");
    extract_ulong_from_buffer(buffer,1,0,&ull);
    printf("Valor convertido\n");
    bmp_header->size = ull;
    printf("Valor recebido\n");

    fread(buffer,1,4,fp);
    printf("Comprimento da imagem lida\n");
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
    bmp_header->sizeofbitmap = ull;

    fclose(fp);

    return 1;

}