#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "operacaoPixel.h"
#include "pooling.h"

pixel *setup_filter(pixel *filtro,int numeroFiltro);
pixel *matrizConvolucao(pixel *imagem,int x,int y,int maxLinhas,int maxColunas,int n);
pixel  multConvFilter(pixel *conv,pixel *filter,int n);
pixel *convolucao(int maxLinhas,int maxColunas,pixel *imagem);
pixel *cnn(pixel *imagem,int maxLinhas,int maxColunas);