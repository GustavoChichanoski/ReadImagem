#ifndef DETECTORES_H_INCLUDED
#define DETECTORES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "conversao.h"

#ifdef DETECTORES_EXPORTS
    #define DETECTORES_API __declspec(dllexport)
#else
    #define DETECTORES_API __declspec(dllimport)
#endif

#ifdef __cplusplus
    extern "C" {
#endif

    pixel *detectorBorda(int width,int height,pixel *imagem);
    pixel *edge_gauss(long width,long height,pixel *rgb);
    pixel *median_filter(long width,long height,pixel *rgb);
    pixel *gray_scale(long width,long height,pixel *rgb);
    pixel *sub_image(pixel *in,pixel *out,long cols,long rows);
    
#ifdef __cplusplus
    }
#endif

#endif /* PROCESSAMENTO_H */
