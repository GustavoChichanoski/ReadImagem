#include <stdio.h>
#include <malloc.h>
#include "bmp.h"
#include "operacaoPixel.h"

#define MAX 1
#define MED 0

pixel  maxPooling(pixel *matriz,int ordemMatriz);
void   calcPad(int poolingOrdem,int height,int width);
pixel  maxPooling(pixel *matriz,int ordemMatriz);
pixel  medPooling(pixel *matriz,int ordemMatriz);
int    calcHeight(int length,int width);
pixel *matrizPooling(pixel *imagem,pixel *matriz,int height,int width,int y,int x,int ordem);
pixel *pooling(pixel *imagem,int height,int width,int poolingOrdem,int tipo);