#ifndef POOLING_H_INCLUDED

    #define POOLING_H_INCLUDED

    #ifdef POOLING_EXPORTS
        #define POOLING_API __declspec(dllexport)
    #else
        #define POOLING_API __declspec(dllimport)
    #endif

    #ifdef __cplusplus
        extern "C" {
    #endif

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
    pxMat  pooling(int stride, pxMat *imagem);

    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif