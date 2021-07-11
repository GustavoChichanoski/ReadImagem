#pragma once

#include <stdio.h>
#include <malloc.h>
#include "..\images\bmp.h"
#include "..\images\operacaoPixel.h"

pixel  maxPooling(pixel *matriz,int ordemMatriz);
void   calcPad(int poolingOrdem,int height,int width);
pixel  maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual);
pixel  medPooling(pixel *matriz,int ordemMatriz);
int    calcHeight(int length,int width);
pixel *matrizPooling(pixel *imagem,pixel *matriz,int height,int width,int y,int x,int ordem);
pxMat  pooling(int stride, pxMat *imagem);
void   poolingInt(int stride,int *img,int img_width,int img_height,int **out,int *out_width,int *out_height);