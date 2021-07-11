#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "conversao.h"

pixel *detectorBorda(int width,int height,pixel *imagem);
pixel *edge_gauss(long width,long height,pixel *rgb);
pixel *median_filter(long width,long height,pixel *rgb);
pixel *gray_scale(int width,int height,pixel *rgb);
pixel *sub_image(pixel *in,pixel *out,int cols,int rows);