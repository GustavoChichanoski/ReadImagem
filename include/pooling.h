#include <stdio.h>
#include <malloc.h>
#include "bmp.h"
#include "operacaoPixel.h"

pixel  maxPooling(pixel *matriz,int ordemMatriz);
void   calcPad(int poolingOrdem,int height,int width);
pixel  maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual);
pixel  medPooling(pixel *matriz,int ordemMatriz);
int    calcHeight(int length,int width);
pixel *matrizPooling(pixel *imagem,pixel *matriz,int height,int width,int y,int x,int ordem);
pixel *pooling(int stride,int width,int height,pixel *imagem);