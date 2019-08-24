/* 
 * Free FFT and convolution (C)
 * 
 * Copyright (c) 2019 Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/free-small-fft-in-multiple-languages
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int mask1[3][3] = {{1,1,1},{1,1,0},{1,0,0}};

pixel **setup_filter(int **maskBlue,int **maskGreen,int **maskRed,pixel **filtro,int ordemMatriz)
{
    for(int i = 0;i < ordemMatriz;i++)
    {
        for(int j = 0;j < ordemMatriz;j++)
        {
            filtro[i][j].blue  = maskBlue[i][j];
            filtro[i][j].green = maskGreen[i][j];
            filtro[i][j].red   = maskRed[i][j];
        }
    }
    return filtro;
}

void fft(int maxLinhas,int maxColunas,pixel **imagem)
{
    pixel **matriz_aux;
    int linhas, colunas;

    matriz_aux = allocate_image_array(3,3);

    for(linhas = 0;linhas < maxLinhas;linhas++)
    {
        for(colunas = 0;colunas < maxColunas;colunas++)
        {
            matriz_aux = m
        }
    }
}
