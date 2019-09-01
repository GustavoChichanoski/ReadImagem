#ifndef OPERACAOPIXEL_H_INCLUDED
#define OPERACAOPIXEL_H_INCLUDED

#ifdef OPERACAOPIXEL_EXPORTS
    #define OPERACAOPIXEL_API __declspec(dllexport)
#else
    #define OPERACAOPIXEL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
    extern "C" {
#endif

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

#ifdef __cplusplus
    }
#endif

#endif // OPERACAOPIXEL_H_INCLUDED