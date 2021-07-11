#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../include/images/bmp.h"

#define GRAY_LEVELS 256

int    read_bmp_header(char *file_name,bitmapheader *bmp_header);
int    read_bmp_file_header(char *file_name,bmpfileheader *file_header);
pixel *read_bmp_image(char *file_name,pixel *array,bmpfileheader file_header,bitmapheader bmheader);
void   read_bmp_rgb(char *file_name,bmpfileheader file_header,bitmapheader bmheader,int **red,int **blue,int **green);
int    read_bmp_image_rgb(char *file_name,bmpfileheader file_header,bitmapheader bmheader,int **red,int **blue,int **green);

int    is_a_bmp(char *file_name);
int    calculate_pad(long width);
int    does_not_exist(char file_name[]);
int    write_bmp(char *file_name,bmpfileheader *file_header,bitmapheader *bmp_header,pixel *imagem);
int    free_image_array(pixel *the_array,long width,long height);
int    calculate_pad(long width);
int    ordem_de_leitura(long height);

/* Define a ordem de leitura da imagme */
int ordem_de_leitura(long height)
{
    return (height > 0) ? 1 : 0;
}

/* pixel **read_color_table(file_name,bmheader,rgb) *
 * Entrada :                                        *
 * char *file_name - Nome do arquivo da imagem      *
 * bitmapheader *bmheader - Cabecalho da imagem     *
 * pixel **imagem - mapa de pixel da imagem         *
 * Saida :                                          *
 * pixel **imagem - mapa de saida                   */
pixel *read_color_table(char *file_name,int height,int width,pixel *imagem)
{
    FILE *fp;
    char buffer[10];
    long position = 0;
    int column, row, pad;
    fp       = fopen(file_name,"rb");
    position = fseek(fp,54,SEEK_SET);
    pad      = calculate_pad(width);
    for(row  = height-1; row > -1; row--)
    {
        for(column = 0;column < width;column++)
        {
            position = row*width + column;
            fread(buffer,sizeof(char),3,fp);
            igualarCorPixel(0, &imagem[position]);
            imagem[position].blue  = buffer[0];
            imagem[position].green = buffer[1];
            imagem[position].red   = buffer[2];
        }
        if(pad > 0)
        {
            fread(buffer,sizeof(char),pad,fp);
        }
    }
    fclose(fp);
    return imagem;
}

void read_bmp_rgb(char *file_name,bmpfileheader file_header,bitmapheader bmheader,int **red,int **blue,int **green)
{
    FILE *fp;
    char buffer[10];
    long position = 0;
    int  column, row, pad, width = bmheader.width, height = bmheader.height;
    fp       = fopen(file_name,"rb");
    position = fseek(fp,54,SEEK_SET);
    pad      = calculate_pad(width);
    for(row  = height-1; row > -1; row--)
    {
        for(column = 0;column < width;column++)
        {
            position = row*width + column;
            fread(buffer,sizeof(char),3,fp);
            (*blue)[position]  = (int) buffer[0];
            (*green)[position] = (int) buffer[1];
            (*red)[position]   = (int) buffer[2];
        }
        if(pad > 0)
        {
            fread(buffer,sizeof(char),pad,fp);
        }
    }
    fclose(fp);
}

/* Funcao que retorna o cabecalho do arquivo             *
 * Entradas :                                            *
 * char *file_name - nome do arquivo que contem a imagem *
 * bmpfileheader - cabecalho do arquivo                  */
int read_bmp_file_header(char *file_name,bmpfileheader *file_header)
{

    char buffer[10];
    short ss;
    unsigned short uss;
    unsigned long ull;
    FILE *fp;

    fp = fopen(file_name,"rb");

    if( fp == NULL){
        printf("Arquivo: %s não encontrado\n",file_name);
        return 1;
    }

    {
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

/* Funcao que retorna o cabecalho da imagem       *
 * Entrada :                                      *
 * char *file_name - nome do arquivo da imagem    *
 * bitmapheader *bmp_header - cabecalho da imagem */
int read_bmp_header(
    char *file_name,
    bitmapheader *bmp_header
)
{
    char buffer[10]; long ll;
    unsigned short uss; unsigned long ull;
    
    FILE *fp;
    fp = fopen(file_name, "rb"); // Abre o arquivo da imagem 
    if((fp = fopen(file_name,"rb")) == NULL) // Abre o arquivo 
    {
        printf("Arquivo: %s não encontrado\n", file_name);
        return 1;
    }

    fseek(fp,14,SEEK_SET); // Redirecionar o cursor da imagem para a posição 14 da imagem
    {
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

/* read_bmp_image(file_name,array,file_header,bmheader) *
 * Entrada :                                            *
 *  char *file_name - nome do arquivo da imagem         *
 *  pixel *array - matriz de pixel                      *
 *  bmpfileheader *file_header - cabecalho da arquivo   *
 *  bitmapheader *bmheader - cabecalho da imagem        *
 * Saida :                                              *
 *  pixel **imagem - matriz de pixel da imagem          */
pixel *read_bmp_image(char *file_name,pixel *array,bmpfileheader file_header,bitmapheader bmheader)
{
    long height = 0, width = 0;
    width = bmheader.width;
    height = bmheader.height;
    if(height < 0){height *= (-1);}
    if(bmheader.compression){exit(1);}
    array = read_color_table(file_name,height,width,array);
    return array;
}

/* read_bmp_image(file_name,array,file_header,bmheader) *
 * Entrada :                                            *
 *  char *file_name - nome do arquivo da imagem         *
 *  pixel *array - matriz de pixel                      *
 *  bmpfileheader *file_header - cabecalho da arquivo   *
 *  bitmapheader *bmheader - cabecalho da imagem        *
 * Saida :                                              *
 *  pixel **imagem - matriz de pixel da imagem          */
int read_bmp_image_rgb(char *file_name,bmpfileheader file_header,bitmapheader bmheader,int **red,int **blue,int **green)
{
    if(bmheader.compression){exit(1);}
    read_bmp_rgb(file_name,file_header,bmheader,&(*red),&(*blue),&(*green));
    return 1;
}

/* calculte_pad(...)                                         *
 * Verifica se a largura da imagem é um numero divisivel por *
 * 4, se for não adiciona pads. Caso seja diferente, indica  *
 * o números de bytes adicionados para completar essa regra  */
int calculate_pad(long width)
{
    return ((width % 4) == 0) ? 0 : (width % 4);
}

/* is_a_bmp(...)                                                *
 * This function looks at a file to see if it is a bmp file.    *
 * First look at the file extension. Next look at the filetype  *
 * to ensure it is 0x4d42                                       */
int is_a_bmp(char *file_name)
{
    char *cc;
    bmpfileheader file_header;
    cc = strstr(file_name,".bmp");
    if(cc == NULL)
    {
        return 0;
    }
    read_bmp_file_header(file_name,&file_header);
    return (file_header.filetype != 0x4D42) ? 0 : 1;
}

/* does_not_exist(...)
 * Verifica se o arquivo existe */
int does_not_exist(char file_name[])
{
    FILE *image_file;
    image_file = fopen(file_name,"rb");
    if(image_file != NULL){
        fclose(image_file);
        return 0;
    }
    return 1;
}

/* Funcao que libera a memoria utilizada no armazenamento *
 * dos pixel da imagem                                    *
 * Entradas :                                             *
 * long maxLinhas - Tamanho maximo vertical da imagem     *
 * pixel imagem - Imagem a ser liberada                   */
int free_bmp(long lenght,pixel *imagem)
{
    free(imagem);
    printf("Memoria liberada\n");
    return 1;
}

pxMat createPixelMatriz(int row,int column)
{
    pxMat matriz;
    matriz.column = column;
    matriz.row    = row;
    matriz.image  = allocate_image_array(row,column);
    return matriz;
}

unsigned long calcSize(int width,int height,int offset,int pad)
{
    return offset + height * (width * 3 + pad);
}

unsigned long sizebmp(int width,int height)
{
    return 3*width*height;
}

int write_bmp(char *file_name,bmpfileheader *file_header,bitmapheader *bmp_header,pixel *imagem)
{
    char buffer[10];
    FILE *fp;
    int x, y, pad, position;
    long width  = (*bmp_header).width;
    long height = (*bmp_header).height;
    pad = calculate_pad(width);
    (*file_header).filesize = calcSize((*bmp_header).width,(*bmp_header).height,(*file_header).offset,pad);
    fp = fopen(file_name,"wb");
    if(fp == NULL)
    {
        printf("Arquivo: %s não encontrado\n",file_name);
        return 1;
    }
    {
        insert_ushort_into_buffer(buffer,0,(*file_header).filetype);
        fwrite(buffer,sizeof(char),2,fp);
        insert_ulong_into_buffer(buffer,0,(*file_header).filesize);
        fwrite(buffer,sizeof(char),4,fp);
        insert_short_into_buffer(buffer,0,(*file_header).reserved1);
        fwrite(buffer,sizeof(char),2,fp);
        insert_short_into_buffer(buffer,0,(*file_header).reserved2);
        fwrite(buffer,sizeof(char),2,fp);
        insert_ulong_into_buffer(buffer,0,(*file_header).offset);
        fwrite(buffer,sizeof(char),4,fp);
    }
    {
        insert_ulong_into_buffer(buffer,0,(*bmp_header).size);
        fwrite(buffer,sizeof(char),4,fp);
        insert_long_into_buffer(buffer,0,(*bmp_header).width);
        fwrite(buffer,sizeof(char),4,fp);
        insert_long_into_buffer(buffer,0,(*bmp_header).height);
        fwrite(buffer,sizeof(char),4,fp);
        insert_short_into_buffer(buffer,0,(*bmp_header).planes);
        fwrite(buffer,sizeof(char),2,fp);
        insert_short_into_buffer(buffer,0,(*bmp_header).bitsperpixel);
        fwrite(buffer,sizeof(char),2,fp);
        insert_ulong_into_buffer(buffer,0,(*bmp_header).compression);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,(*bmp_header).sizeofbitmap);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,(*bmp_header).horzres);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,(*bmp_header).vertres);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,(*bmp_header).colorsused);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,(*bmp_header).colorsimp);
        fwrite(buffer,sizeof(char),4,fp);
    }
    for(y = height-1;y > -1;y--)
    {
        for(x = 0;x < width; x++)
        {
            position = y*width + x;
            insert_long_into_buffer(buffer,0,imagem[position].blue);
            fwrite(buffer,sizeof(char),1,fp);
            insert_long_into_buffer(buffer,0,imagem[position].green);
            fwrite(buffer,sizeof(char),1,fp);
            insert_long_into_buffer(buffer,0,imagem[position].red);
            fwrite(buffer,sizeof(char),1,fp);
        }
        if(pad > 0)
        {
            fwrite(buffer,sizeof(char),pad,fp);
        }
    }
    fclose(fp);
    return 0;
}

int write_bmp_rgb(char *file_name,bmpfileheader *file_header,bitmapheader *bmp_header,int **red,int **blue,int **green)
{
    char buffer[10] = {0,0,0,0,0,0,0,0,0,0};
    FILE *fp;
    int x = 0, y = 0, pad = 0, position = 0;
    int width  = bmp_header -> width;
    int height = bmp_header -> height;
    pad = calculate_pad(width);
    file_header -> filesize = calcSize(bmp_header -> width,bmp_header -> height,file_header -> offset,pad);
    bmp_header -> sizeofbitmap = sizebmp(bmp_header -> width,bmp_header -> height);
    fp = fopen(file_name,"wb");
    {
        insert_ushort_into_buffer(buffer,0,file_header -> filetype);
        fwrite(buffer,sizeof(char),2,fp);
        insert_ulong_into_buffer (buffer,0,file_header -> filesize);
        fwrite(buffer,sizeof(char),4,fp);
        insert_short_into_buffer (buffer,0,file_header -> reserved1);
        fwrite(buffer,sizeof(char),2,fp);
        insert_short_into_buffer (buffer,0,file_header -> reserved2);
        fwrite(buffer,sizeof(char),2,fp);
        insert_ulong_into_buffer (buffer,0,file_header -> offset);
        fwrite(buffer,sizeof(char),4,fp);
    }
    {
        insert_ulong_into_buffer(buffer,0,bmp_header -> size);
        fwrite(buffer,sizeof(char),4,fp);
        insert_long_into_buffer (buffer,0,bmp_header -> width);
        fwrite(buffer,sizeof(char),4,fp);
        insert_long_into_buffer (buffer,0,bmp_header -> height);
        fwrite(buffer,sizeof(char),4,fp);
        insert_short_into_buffer(buffer,0,bmp_header -> planes);
        fwrite(buffer,sizeof(char),2,fp);
        insert_short_into_buffer(buffer,0,bmp_header -> bitsperpixel);
        fwrite(buffer,sizeof(char),2,fp);
        insert_ulong_into_buffer(buffer,0,bmp_header -> compression);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,sizebmp(width,height));
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,bmp_header -> horzres);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,bmp_header -> vertres);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,bmp_header -> colorsused);
        fwrite(buffer,sizeof(char),4,fp);
        insert_ulong_into_buffer(buffer,0,bmp_header -> colorsimp);
        fwrite(buffer,sizeof(char),4,fp);
    }
    for(y = height-1;y > -1;y--)
    {
        for(x = 0;x < width; x++)
        {
            position = y*width + x;
            insert_long_into_buffer(buffer,0,(*blue)[position]);
            fwrite(buffer,sizeof(char),1,fp);
            insert_long_into_buffer(buffer,0,(*green)[position]);
            fwrite(buffer,sizeof(char),1,fp);
            insert_long_into_buffer(buffer,0,(*red)[position]);
            fwrite(buffer,sizeof(char),1,fp);
        }
        if(pad > 0)
        {
            fwrite(buffer,sizeof(char),pad,fp);
        }
    }
    fclose(fp);
    return 1;
}