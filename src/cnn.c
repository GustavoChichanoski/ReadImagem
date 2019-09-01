#include "../include/cnn.h"

int mask[54] = {
    248,220,100,141,110, 10,123,  2, 15,
    102,124, 52,240,230,120, 10,  1,  5,
     50, 10,  5,120,240, 30, 20, 30, 40,
    192,128, 64,255,128,128,192,  0, 64,
    165,128, 89,255,128,  0,165,128, 89,
    123,110,189,200, 28,100,120,141,179
};

/* Configura o filtro */
pixel *setup_filter(pixel *filtro,int numeroFiltro)
{
 
    int posicao = 0, posFiltro = 0;
 
    for(int nFilter = 0;nFilter < numeroFiltro;nFilter++)
    {
        for(posicao = 0;posicao < 9;posicao++)
        {
            filtro[posicao].blue  = mask[posFiltro];
            filtro[posicao].green = mask[posFiltro+18];
            filtro[posicao].red   = mask[posFiltro+36];
            posFiltro++;
        }
    }

    return filtro;

}

pixel *matrizConvolucao(pixel *imagem,int x,int y,int maxLinhas,int maxColunas,int ordemMatriz)
{

    int meioMatriz       = ordemMatriz/2;
    int linhaReferencia  = y - meioMatriz;
    int colunaReferencia = x - meioMatriz;
    int linhaImagem      = 0;
    int colunaImagem     = 0;
    int linhaMatriz      = 0;
    int colunaMatriz     = 0;
    int posicaoMatriz    = 0;
    pixel *saida, zero;

    printf("Culpa do Malloc ?\n");

    zero  = igualarCorPixel(0);
    saida = allocate_image_array(ordemMatriz,ordemMatriz);

    printf("Nao\n");

    for(linhaMatriz = 0;linhaMatriz < ordemMatriz;linhaMatriz++)
    {
        for(colunaMatriz = 0;colunaMatriz < ordemMatriz;colunaMatriz++)
        {

            linhaImagem          = linhaReferencia  + linhaMatriz;
            colunaImagem         = colunaReferencia + colunaMatriz;
            saida[posicaoMatriz] = zero;

            if( -1 < linhaImagem && linhaImagem < maxLinhas && -1 < colunaImagem && colunaImagem < maxColunas)
            {
                printf("posImagem : %d - %d ",maxColunas*linhaImagem + colunaImagem,maxLinhas*maxColunas);
                printf("posMatriz : %d\n", posicaoMatriz);
                saida[posicaoMatriz] = imagem[maxColunas*linhaImagem + colunaImagem];
            }

            posicaoMatriz++;

        }
    }

    printf("Saiu da matriz Convolucao\n");

    return saida;

}

pixel multConvFilter(pixel *conv,pixel *filter,int n)
{

    int posicao = 0, linhaMax = n*n;
    pixel saida, aux;

    saida = igualarCorPixel(0);

    for(int linhas = 0;linhas < linhaMax;linhas++)
    {
        aux   = multiPixel(conv[posicao],filter[posicao]);
        aux   = divPixelporCnt(aux,255);
        saida = somaPixel(saida,aux);
    }

    return divPixelporCnt(saida,9);

}

pixel *convolucao(int maxLinhas,int maxColunas,pixel *imagem)
{

    pixel *convolucao, *filtro, *saida;
    int linhas, colunas, posicao = 0;

    convolucao   = allocate_image_array(3,3);
    saida        = allocate_image_array(linhas,colunas);
    filtro       = allocate_image_array(6,9);
    filtro       = setup_filter(filtro,2);

    for(linhas = 0;linhas < maxLinhas;linhas++)
    {
        for(colunas = 0;colunas < maxColunas;colunas++)
        {
            printf("Entrou da matriz da Convolucao [%d][%d] - %d",linhas,colunas,posicao);
            convolucao     = matrizConvolucao(imagem,colunas,linhas,maxLinhas,maxColunas,3);
            printf("Saiu   da matriz da Convolucao [%d][%d] - %d\n",linhas,colunas,posicao);
            printf("Entrou na multiplicacao da Convolucao [%d][%d] - %d",linhas,colunas,posicao);
            printf(" - [%d][%d]\n",maxLinhas,maxColunas);
            saida[posicao] = multConvFilter(convolucao,filtro,3);
            printf("Saiu da multiplicacao da Convolucao\n");
            posicao++;
        }
    }

    printf("Saiu da convolucao");

    return saida;

}

pixel *cnn(pixel *imagem,int maxLinhas,int maxColunas)
{
    return convolucao(maxLinhas,maxColunas,imagem);
    /*while(maxLinhas > 20 || maxColunas > 20)
    {
        printf("Saiu da convolucao\n");
        imagem = pooling(imagem,maxLinhas,maxColunas,2,MAX);
        printf("Saiu do pooling\n");
        maxLinhas  /= 2; 
        maxColunas /= 2;
        cnn(imagem,maxLinhas,maxColunas);
    }
    return imagem;*/
}

pixel *relu(pixel *imagem,int lenght)
{

    for(int i = 0;i < lenght;i++)
    {
        if(imagem[i].blue  < 0) imagem[i].blue  = 0;
        if(imagem[i].green < 0) imagem[i].green = 0;
        if(imagem[i].red   < 0) imagem[i].red   = 0;
    }

    return imagem;

}