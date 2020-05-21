#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"
#include "conversao.h"
#include "operacaoPixel.h"

#ifndef PROCESSAMENTO_H_INCLUDED
#define PROCESSAMENTO_H_INCLUDED

#ifdef __cplusplus
    extern "C" {
#endif
    
    pixel *gray_image(long width,long height,pixel *rgb);
    void img_creat_red_to_blue(int *img,int maxPosition,int **red,int **blue,int **green);
    
#ifdef __cplusplus
    }
#endif

#endif	/* PROCESSAMENTO_H */
