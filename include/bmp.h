/* File:   read_BMP.h
 * Author: Gustavo
 * Library for read bmp files
 * Created on 2 de Agosto de 2019, 14:14 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef BMP_H   
#define	BMP_H

#ifdef __cplusplus 
    extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "conversao.h"
#include "bmp.h"
#include "detectores.h"
#include "histograma.h"
#include "operacaoPixel.h"

/* structs of Header BMP                                *
 * A seguir as definições de struct com as informações  *
 * necessárias para se ler os cabeçalhos dos arquivos   *
 * bmp                                                  *
*/

/* bitmapheader                                                     *
 * Contem as informações relacionada a imagem                       *
 * unsigned long size[4]         - tamanho da imagem                *
 * long width[4]                 - comprimento da imagem            *
 * long heigth[4]                - comprimento da imagem            *
 * unsigned short planes[2]      - não sei                          *
 * unsigned short bitperpixel[2] - bit por pixel                    *
 * unsigned long compression[4]  - compressão da imagem em arquivo  *
 * unsigned long horzres[4]      -                                  *
 * unsigned long vertres[4]      -                                  *
 * unsigned long colorused[4]    - cores usadas                     *
 * unsigned long colorimp[4]     - cores importantes                */
typedef struct {
    unsigned long       size;
    long                width;
    long                height;
    unsigned short int  planes;
    unsigned short int  bitsperpixel;
    unsigned long       compression;
    unsigned long       sizeofbitmap;
    unsigned long       horzres;
    unsigned long       vertres;
    unsigned long       colorsused;
    unsigned long       colorsimp;
} bitmapheader; /* bitmapheader */

/* bmpFileHeader                                                                   *
 * Contem as informações relacionado ao arquivo bmp                                *
 * unsigned short filetype[2] - Assinatura do arquivo                              *
 * unsigned long filesize[4]  - Armazena o total do arquivo                        *
 * short reserved1[2]         - Não utiliza 0x00                                    *
 * short reserved2[2]         - Não utiliza 0x00                                   *
 * unsigned long offset[4]    - Distância do inicio do arquivo ao inicio da imagem */
typedef struct {
    /* 2 Bytes - Assinatura do arquivo: 
     * os caracteres ASCII "BM" ou (424D)h.É a identificação de ser realmente BMP. */
    unsigned short int filetype;
    /* 4 Bytes - Tamanho do arquivo em Bytes */
    unsigned long   filesize;
    /* 2 Bytes - Campo reservado 1 para uso futuro deve ser ZERO */
    short           reserved1;
    /* 2 Bytes - Campo reservado 2 para uso futuro deve ser ZERO */
    short           reserved2;

    /* 4 Bytes - Especifica o deslocamento, em bytes, 
     * para o início da área de dados da imagem, a partir 
     * do início deste cabeçalho.
     * - Se a imagem usa paleta, este campo tem tamanho = 14+40+(4 x NumeroDeCores)
     * - Se a imagem for true color, este campo tem tamanho = 14+40=54 
     */
    unsigned long   offset;
} bmpfileheader; /* bmpfileheader */

/* RGB                          *
 * Armazena as cores da imagem  *
 * unsigned long red[4]         *
 * unsigned long blue[4]        *
 * unsigned long green[4]       */
typedef struct {
    unsigned long blue;
    unsigned long green;
    unsigned long red;
} pixel; /* pixel */


int     read_bmp_header(char *file_name,bitmapheader *bmp_header);
int     read_bmp_file_header(char *file_name,bmpfileheader *file_header);
pixel **read_bmp_image(char *file_name,pixel **array,bmpfileheader *file_header,bitmapheader *bmheader);
int     calculate_pad(long width);
int     is_a_bmp(char *file_name);
int     does_not_exist(char file_name[]);
pixel **allocate_image_array(long height,long width);
int     write_bmp(char *file_name,bmpfileheader *file_header,bitmapheader *bmp_header,pixel **rgb);
int     free_image_array(pixel **the_array,long width,long height);

#ifdef __cplusplus
    }
#endif

#endif /* READ_BMP_H */
