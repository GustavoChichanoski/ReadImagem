#pragma once

#include <stdio.h>
#include <malloc.h>
#include "conversao.h"
#include "bmp.h"
#include "detectores.h"

long   somaCorPixel(pixel pixelEntrada);
pixel  maiorCordoPixel(pixel pixelEntrada);
pixel  subAbsPixel(pixel a, pixel b);
pixel  somaPixel(pixel pixel1,pixel pixel2);
pixel  divPixelporCnt(pixel pixel,int constante);
pixel  igualarCorPixel(int valor);
pixel *allocate_image_array(long width,long height);
pixel  multiMatrizPixel(pixel imagem,pixel filtro,int ordemMatriz);
pixel  multiPixel(pixel a,pixel b);
pxMat  rotate_90_rigth(pxMat img);
pixel  subAbsPixel(pixel a, pixel b);
pixel  subPixel(pixel a,pixel b);