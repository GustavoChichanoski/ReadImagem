#include <stdio.h>
#include <stdlib.h>
#include "conversao.h"
#include "bmp.h"
#include "operacaoPixel.h"
#include "detectores.h"

int mask1[3][3] = {
    { 0, 0, 0},{-1, 2,-1},{0,0,0}
};

int mask2[3][3] = {
    { 0,-1, 0},{ 0, 2, 0},{ 0,-1, 0}
};

pixel **m_matriz(pixel **rgb,int n,int maxX,int maxY,int x,int y);
pixel   subAbsPixel(pixel a, pixel b);
pixel   img_homo(pixel **matriz,pixel ref,int n);
pixel   img_gauss(pixel **matriz,int n);
pixel  *zero_histograma(pixel *histograma,int gray_levels);

pixel img_median(matriz)
    pixel **matriz;
{

    pixel reg;
    reg = igualarCorPixel(0);

    for(int y = 0;y < 3;y++)
    {
        for(int x = 0;x < 3;x++)
        {
            reg.blue  += matriz[y][x].blue;
            reg.green += matriz[y][x].green;
            reg.red   += matriz[y][x].red;
        }
    }

    reg.blue  /= 9;
    reg.green /= 9;
    reg.red   /= 9;

    return reg;

}

pixel img_gauss(matriz,n)
    pixel **matriz;
    int n;
{

    long max = 0, buffer;
    pixel aux;
    int maxX = 1, maxY = 1, n1 = n - 1, x = 0, y = 0;
    int n2 = n/2;

    for (y = 0;y < n; y++)
    {
        for (x = 0;x < n; x++)
        {
            if(x != n2 || y != n2)
            {
                aux     = subAbsPixel(matriz[y][x],matriz[n1-y][n1-x]);
                buffer  = somaCorPixel(aux);
                if(buffer > max)
                {
                    maxX = x;
                    maxY = y;
                    max = buffer;
                }
            }
        }
    }

    /* matriz[0][0] - matriz[2][2] **
    ** matriz[0][1] - matriz[2][1] **
    ** matriz[0][2] - matriz[2][0] **
    ** matriz[1][0] - matriz[1][2] */

    return matriz[maxX][maxY];

}

pixel **sub_image(in,out,cols,rows)
    pixel **in, **out;
    long cols, rows;
{

    int x, y;

    for(y = 0;y < rows;y++)
    {
        for(x = 0;x < cols;x++)
        {

            out[y][x].blue  = in[y][x].blue  - out[y][x].blue;
            out[y][x].green = in[y][x].green - out[y][x].green;
            out[y][x].red   = in[y][x].red   - out[y][x].red;

        }
    }

    return out;
}

pixel **edge_gauss(maxLinha,maxColuna,imagem)
    long maxColuna, maxLinha;
    pixel **imagem;
{

    int coluna, linha;
    pixel ref, **aux, **m_pixel;
    
    m_pixel = allocate_image_array(3,3);
    aux = allocate_image_array(maxLinha,maxColuna);

    for(linha = 0;linha < maxLinha;linha++)
    {
        for(coluna = 0;coluna < maxColuna;coluna++)
        {
            ref     = imagem[linha][coluna];
            m_pixel = m_matriz(imagem,3,maxColuna,maxLinha,linha,coluna);
            aux[linha][coluna] = img_gauss(m_pixel,3);
        }
    }

    return aux;

}

/* Verifica se a coluna e a linha passada estao dentro da zona valida *
 * Entradas :
 *      minLinhas   - Valor minimo de linhas da matriz
 *      maxLinhas   - Valor maximo de linhas da matriz
 *      minColunas  - Valor minimo de colunas da matriz
 *      maxColunas  - Valor maximo de colunas da matriz
 *      linha       - Valor atual da linha
 *      coluna      - Valor atual da coluna
 * Saida    :
 *      1 - O pixel esta em uma regiao valida
 *      0 - O pixel esta fora da regiao valida
 * */
int zonaImagemValida(minLinhas,maxLinhas,minColunas,maxColunas,linha,coluna)
    int minLinhas, maxLinhas, minColunas, maxColunas, linha, coluna;
{
    /* Verifica se a coluna ou a linha sao menores que o minimo ou se a coluna e a linha sao maiores que o maximo */
    if((minLinhas <= linha && linha < maxLinhas) && (minColunas <= coluna && coluna < maxColunas))
    {
        return 1; /* A coluna esta dentro da zona valida */
    }
    return 0; /* A linha esta fora da zona valida */
}

/* Cria a matriz auxiliar                     *
 * Entradas         :                         *
 *  pixel **imagem  : mapa de pixel da imagem *
 *  n               : ordem da matriz         *
 *  maxColunas      : Valor máximo horizontal *
 *  maxLinhas       : Valor máximo vertical   *
 *  linha           : Valor horizontal atual  *
 *  coluna          : Valor vertical atual    *
 * Saida            :                         *
 *  pixel imagem    : pixel com maior valor   */
pixel **m_matriz(imagem,ordemMatriz,maxColunas,maxLinhas,coluna,linha)
    pixel **imagem;
    int     ordemMatriz, maxColunas, maxLinhas,coluna,linha;
{
    /* Cria um matriz com os valores ao redor */
    pixel **matriz;
    /* Cria um pixel com cores zero */
    pixel pixel0;
    /* Determina o valor do meio da matriz */
    int meioMatriz = ordemMatriz/2;
    /* Contem a coluna do pixel de referencia */
    int colunaReferencia = coluna - meioMatriz;
    /* Contem a linha do pixel de referencia */
    int linhaReferencia = linha - meioMatriz;
    /* Determina a coluna da imagem */
    int colunaImagem    = 0;
    /* Determina a linha da imagem */
    int linhaImagem     = 0;
    /* Determina a coluna da matriz */
    int colunaMatriz    = 0;
    /* Determina a linha da matriz */
    int linhaMatriz     = 0;

    /* Cria um pixel de valor 0 */
    pixel0 = igualarCorPixel(0);
    /* Aloca o espaço da "matriz" na memória */
    matriz = allocate_image_array(ordemMatriz,ordemMatriz);

    /* Percorre as linhas da matriz "matriz" */
    for(linhaMatriz = 0;linhaMatriz < ordemMatriz;linhaMatriz++)
    {
        /* Percorre as colunas da matriz "matriz" */
        for(colunaMatriz = 0;colunaMatriz < ordemMatriz;colunaMatriz++)
        {
            /* Inicia a matriz 'matriz' com um pixel 0 */
            matriz[linhaMatriz][colunaMatriz] = pixel0;
            /* Contem o pixel atual da imagem */
            colunaImagem = colunaReferencia + colunaMatriz;
            /* Contem o pixel atual da imagem */
            linhaImagem  = linhaReferencia  + linhaMatriz;

            if(zonaImagemValida(0,maxLinhas,0,maxColunas,linhaImagem,colunaImagem) == 1)
            {
                matriz[linhaMatriz][colunaMatriz] = imagem[linhaImagem][colunaImagem];
            }

        }
    }

    return matriz;

}

pixel **median_filter(width,height,rgb)
    long width,height;
    pixel **rgb;
{

    int x, y;
    pixel **RGB, **m_pixel, aux;

    aux     = igualarCorPixel(0);
    m_pixel = allocate_image_array(3,3);
    RGB     = allocate_image_array(height,width);

    /*  */
    for(y = 0; y < height; y++)
    {
        /*  */
        for(x = 0; x < width; x++)
        {
            m_pixel = m_matriz(rgb,3,width,height,x,y);
            RGB[y][x] = img_median(m_pixel);
        }
    }

    return RGB;

}

/* Converte a imagem para a escala cinza             *
 * Verifica qual cor é maior: RED, GREEN ou BLUE, e  *
 * considera o valor de todas as cores, como sendo o *
 * o maior valor entre as três cores                 *
 * Entradas :                                        *
 * width    - Numero de colunas da imagem (máximo X) *
 * height   - Numero de linhas da imagem (máximo Y)  *
 * rgb      - Imagem a ser convertida                *
 * Saida    :                                        *
 * pixel**  - Imagem em preto e branco               */
pixel **gray_scale(maxColunas,maxLinhas,imagem)
    long maxColunas,maxLinhas;
    pixel **imagem;
{

    /* Variavel que percorrem a matriz de pixel da imagem */
    int linha, coluna;
    /* Loop para percorrer as linhas da matriz */
    for(linha = 0;linha < maxLinhas;linha++)
    {
        /* Loop para percorrer as colunas da matriz */
        for(coluna = 0;coluna < maxColunas;coluna++)
        {
            imagem[linha][coluna] = maiorCordoPixel(imagem[linha][coluna]);
        }
    }
    return imagem;
}

/* pixel img_homo(matriz,ref,n)         *
 * Entradas:                            *
 * pixel **matriz : matriz de pixel     *
 * pixel   ref    : pixel de referência *
 * int     n      : ordem da matriz     */
pixel img_homo(pixel **matriz,pixel ref,int n){

    long max = 0, aux;
    int x, y, maxX = n/2, maxY = n/2;

    for(y = 0;y < n;y++)
    {
        for(x = 0;x < n;x++)
        {
            /*  */
            matriz[y][x] = subAbsPixel(matriz[y][x],ref);
            aux = somaCorPixel(matriz[y][x]);
            /*  */
            if(aux > max)
            {
                maxX = x; maxY = y; max = aux;
            }
        }
    }
    return matriz[maxY][maxX];
}

/* Realca as bordas da imagem                        *
 * Entradas :                                        *
 * width    - Numero de colunas da imagem (máximo X) *
 * height   - Numero de linhas da imagem (máximo Y)  *
 * rgb      - Imagem a ser convertida                *
 * Saida    :                                        *
 * pixel**  - Imagem com as bordas realçadas         */
pixel **detectorBorda(maxColunas,maxLinhas,imagem)
    long maxColunas, maxLinhas;
    pixel **imagem;
{

    int linha, coluna, ordemMatriz = 3;
    pixel referencia, **m_pixel;

    for(linha = 0;linha < maxLinhas;linha++)
    {
        for(coluna = 0;coluna < maxColunas;coluna++)
        {

            referencia = imagem[linha][coluna];
            m_pixel = m_matriz(imagem,ordemMatriz,maxColunas,maxLinhas,coluna,linha);
            imagem[linha][coluna] = img_homo(m_pixel,referencia,ordemMatriz);

        }
    }

    return imagem;

}
