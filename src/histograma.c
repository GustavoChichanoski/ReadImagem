#include <stdio.h>
#include <stdlib.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/detectores.h"
#include "../include/histograma.h"
#include "../include/operacaoPixel.h"

pixel *suavizar_histograma(pixel *histograma,int gray_levels);
pixel *zero_histograma(pixel *histograma,int gray_levels);
pixel *calcular_histogrma(pixel *imagem,pixel *histograma,int maxLinha,int maxColuna);
pixel  cumulativeDistribuiton(pixel *histograma,int N);

pixel  cumulativeDistribuiton(pixel *histograma,int N)
{

    pixel saida;

    for(int i = 0;i < 256;i++)
    {
        saida.blue  += histograma[i].blue;
        saida.green += histograma[i].green;
        saida.red   += histograma[i].red;
    }

    return divPixelporCnt(saida,255);

}

/* Funcao que suaviza o histograma obtido                  *
 * Entradas :                                              *
 * pixel *histograma - contem o histograma da imagem       *
 * int gray_levels - leveis de cor da imagem               *
 * Saidas :                                                *
 * pixel *histograma - retorna o novo histograma suavizado */
pixel *suavizar_histograma(histograma,gray_levels)
    pixel *histograma;
    int gray_levels;
{
    int i;
    pixel *new_histograma;

    new_histograma = malloc(gray_levels*sizeof(pixel*));
    new_histograma = zero_histograma(new_histograma,gray_levels);

    new_histograma[0] = divPixelporCnt(somaPixel(histograma[0],histograma[1]),2);
    new_histograma[gray_levels] = divPixelporCnt(somaPixel(histograma[gray_levels-2],histograma[gray_levels-1]),2);

    for(i = 0;i < gray_levels - 1;i++)
    {
        new_histograma[i] = divPixelporCnt(somaPixel(somaPixel(histograma[i-1],histograma[i]),histograma[i+1]),3);
    }

    for(i = 0;i < gray_levels;i++)
    {
        histograma[i] = new_histograma[i];
    }

    return histograma;

}

/* Funcao que zera o histograma                         *
 * Entrada :                                            *
 * pixel *histograma - grafico de brilho da cor         *
 * int gray_levels - valor maximo que a cor pode variar *
 * Saidas:                                              *
 * pixel *histograma - Histograma completado com zero   */
pixel *zero_histograma(histograma,gray_levels)
    pixel *histograma;
    int gray_levels;
{
    int i;
    for(i = 0;i < gray_levels;i++)
    {
        histograma[i] = igualarCorPixel(0);
    } 
    return histograma;
}

/* Calcula o valor do histograma de uma imagem        *
 * Entradas :                                         *
 * pixel **imagem    - Imagem a se obter o histograma *
 * int maxLinha      - Valor maximo das linhas        *
 * int maxColuna     - Valor maximo das colunas       *
 * pixel *histograma - vetor de pixel de 256 posicoes *
 * Saidas :                                           */
pixel *calcular_histogrma(imagem,histograma,maxLinha,maxColuna)
    pixel *imagem, *histograma;
    int maxLinha, maxColuna;
{

    pixel brilhoCor;
    int linha, coluna;

    for(int brilho = 0;brilho < 256;brilho++)
    {
        histograma[brilho] = igualarCorPixel(0);
    }

    for(linha = 0;linha < maxLinha;linha++)
    {
        for(coluna = 0;coluna < maxColuna;coluna++)
        {
            brilhoCor = imagem[linha*maxColuna + coluna];
            histograma[brilhoCor.blue].blue   += 1;
            histograma[brilhoCor.green].green += 1;
            histograma[brilhoCor.red].red     += 1;
        }
    }

    return histograma;

}