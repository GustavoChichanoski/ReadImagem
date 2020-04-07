#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "operacaoPixel.h"
#include "pooling.h"

int    random_number(int min_num,int max_num);
pixel *setup_filter(pixel *filtro,int numeroFiltro);
pixel *matrizConvolucao(pixel *imagem,int x,int y,int maxLinhas,int maxColunas,int n);
pixel  multConvFilter(pixel *conv,pixel *filter,int n);
pixel *Conv2D(int maxRow,int maxColumn,pixel *image,int kernel_size,pixel *kernel);
void   testeConvolucao();