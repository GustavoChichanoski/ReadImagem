#include <stdio.h>
#include <stdlib.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/operacaoPixel.h"
#include "../include/detectores.h"

int mask1[9] = { 0, 0, 0,-1, 2,-1, 0, 0, 0};

int mask2[9] = { 0,-1, 0, 0, 2, 0, 0,-1, 0};

pixel *m_matriz(pixel *rgb,int n,int maxX,int maxY,int x,int y);
pixel  subAbsPixel(pixel a, pixel b);
pixel  img_homo(pixel *matriz,pixel ref,int n);
pixel  img_gauss(pixel *matriz,int n);
pixel *zero_histograma(pixel *histograma,int gray_levels);

pixel img_median(pixel *matriz,int ordem)
{
    int posicao, ordem2;
    pixel reg;
    reg = igualarCorPixel(0);
    posicao = 0;
    ordem2 = ordem * ordem;
    for(int y = 0;y < ordem;y++)
    {
        for(int x = 0;x < ordem;x++)
        {
            reg.blue  += matriz[posicao].blue;
            reg.green += matriz[posicao].green;
            reg.red   += matriz[posicao].red;
            posicao++;
        }
    }
    reg.blue  /= ordem2;
    reg.green /= ordem2;
    reg.red   /= ordem2;
    return reg;
}

pixel img_gauss(pixel *matriz,int n)
{
    long max = 0, buffer;
    pixel aux;
    int maxX = 1, maxY = 1, n1 = n - 1, x = 0, y = 0, n2 = n/2;
    for (y = 0;y < n; y++)
    {
        for (x = 0;x < n; x++)
        {
            if(x != n2 || y != n2)
            {
                aux     = subAbsPixel(matriz[y*n+x],matriz[(n1-y)*n + n1-x]);
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
    return matriz[maxY*3+maxX];
}

pixel *sub_image(pixel *in,pixel *out,int cols,int rows)
{
    int x, y;
    int posicao = 0;
    for(y = 0;y < rows;y++)
    {
        for(x = 0;x < cols;x++)
        {
            out[posicao].blue  = in[posicao].blue  - out[posicao].blue;
            out[posicao].green = in[posicao].green - out[posicao].green;
            out[posicao].red   = in[posicao].red   - out[posicao].red;
            posicao++;
        }
    }
    return out;
}

pixel *edge_gauss(long maxLinha,long maxColuna,pixel *imagem)
{
    int coluna, linha, posicao = 0;
    pixel *aux, *m_pixel;
    m_pixel = allocate_image_array(3,3);
    aux = allocate_image_array(maxLinha,maxColuna);
    for(linha = 0;linha < maxLinha;linha++)
    {
        for(coluna = 0;coluna < maxColuna;coluna++)
        {
            m_pixel = m_matriz(imagem,3,maxColuna,maxLinha,linha,coluna);
            aux[posicao] = img_gauss(m_pixel,3);
            posicao++;
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
int zonaImagemValida(int minL,int maxL,int minC,int maxC,int linha,int coluna)
{
    /* Verifica se a coluna ou a linha sao menores que o minimo ou se a coluna e a linha sao maiores que o maximo */
    if((minL <= linha && linha < maxL) && (minC <= coluna && coluna < maxC))
    {
        return 1; /* A coluna esta dentro da zona valida */
    }
    return 0; /* A linha esta fora da zona valida */
}

/* Cria a matriz auxiliar                   *
 * Entradas       :                         *
 *  pixel *imagem : mapa de pixel da imagem *
 *  ordemMatriz   : ordem da matriz         *
 *  maxLinhas     : Valor máximo vertical   *
 *  maxColunas    : Valor máximo horizontal *
 *  linha         : Valor horizontal atual  *
 *  coluna        : Valor vertical atual    *
 * Saida          :                         *
 *  pixel imagem  : pixel com maior valor   */
pixel *m_matriz(imagem,ordemMatriz,maxLinhas,maxColunas,linha,coluna)
    pixel *imagem;
    int    ordemMatriz,maxLinhas,maxColunas,linha,coluna;
{
    /* Cria um matriz com os valores ao redor */
    pixel *matriz;
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
    int posicao;
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
            posicao = linhaMatriz*ordemMatriz + colunaMatriz;
            /* Inicia a matriz 'matriz' com um pixel 0 */
            matriz[posicao] = pixel0;
            /* Contem o pixel atual da imagem */
            colunaImagem = colunaReferencia + colunaMatriz;
            /* Contem o pixel atual da imagem */
            linhaImagem  = linhaReferencia  + linhaMatriz;

            if(zonaImagemValida(0,maxLinhas,0,maxColunas,linhaImagem,colunaImagem) == 1)
            {
                matriz[posicao] = imagem[linhaImagem*maxColunas + colunaImagem];
            }

        }
    }

    return matriz;

}

pixel *median_filter(long width,long height,pixel *imagem)
{
    int x, y;
    pixel *saida, *m_pixel;
    m_pixel = allocate_image_array(3,3);
    saida   = allocate_image_array(height,width);
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            m_pixel = m_matriz(imagem,3,width,height,x,y);
            saida[y*width + x] = img_median(m_pixel,3);
        }
    }
    return saida;
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
pixel *gray_scale(int maxColunas,int maxLinhas,pixel *imagem)
{
    /* Variavel que percorrem a matriz de pixel da imagem */
    int linha, coluna, posicao = 0;
    /* Loop para percorrer as linhas da matriz */
    for(linha = 0;linha < maxLinhas;linha++)
    {
        /* Loop para percorrer as colunas da matriz */
        for(coluna = 0;coluna < maxColunas;coluna++)
        {
            imagem[posicao] = igualarCorPixel(imagem[posicao].blue);
            posicao++;
        }
    }
    return imagem;
}

/* pixel img_homo(matriz,ref,n)         *
 * Entradas:                            *
 * pixel **matriz : matriz de pixel     *
 * pixel   ref    : pixel de referência *
 * int     n      : ordem da matriz     */
pixel img_homo(pixel *matriz,pixel ref,int n)
{
    long max = 0, aux;
    int x, y, n2 = n/2;
    int posicao = 0, posicaoMax = (n2)*n+n2+1;
    for(y = 0;y < n;y++)
    {
        for(x = 0;x < n;x++)
        {
            /*  */
            matriz[posicao] = subAbsPixel(matriz[posicao],ref);
            aux = somaCorPixel(matriz[posicao]);
            /*  */
            if(aux > max)
            {
                posicaoMax = posicao;
                max = aux;
            }
            posicao++;
        }
    }
    return matriz[posicaoMax];
}

/* Realca as bordas da imagem                        *
 * Entradas :                                        *
 * width    - Numero de colunas da imagem (máximo X) *
 * height   - Numero de linhas da imagem (máximo Y)  *
 * rgb      - Imagem a ser convertida                *
 * Saida    :                                        *
 * pixel**  - Imagem com as bordas realçadas         */
pixel *detectorBorda(int maxColunas,int maxLinhas,pixel *imagem)
{
    int linha, coluna, ordemMatriz = 3,posicao = 0;
    pixel referencia, *m_pixel;
    for(linha = 0;linha < maxLinhas;linha++)
    {
        for(coluna = 0;coluna < maxColunas;coluna++)
        {
            referencia = imagem[posicao];
            m_pixel = m_matriz(imagem,ordemMatriz,maxLinhas,maxColunas,linha,coluna);
            imagem[posicao] = img_homo(m_pixel,referencia,ordemMatriz);
            posicao++;
        }
    }
    return imagem;
}