#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../include/bmp.h"

pixel *allocate_image_array(long width,long height);
pixel  multPixelCnt(pixel entrada,int constante);
pixel  igualarCorPixel(int valor);
pixel  divPixelCnt(pixel entrada,int constante);
pixel  somaPixel(pixel a,pixel b);
pixel  subAbsPixel(pixel a, pixel b);
long   somaCorPixel(pixel entrada);
pixel  maiorCordoPixel(pixel entrada);
pixel  multiPixel(pixel a,pixel b);
pixel  multiMatrizPixel(pixel imagem,pixel filtro,int ordemMatriz);
void   organizarPixel(pixel *imagem,int inicio,int fim,pixel *aux);
pxMat  rotate_90_rigth(pxMat img);

/* Aloca o espaco da matriz da imagem na memoria  */
pixel *allocate_image_array(long width,long height)
{
    pixel *imagem;
    imagem = (pixel *) malloc(height*width*sizeof(pixel));
    if(imagem == NULL){
        printf("Socorro o malloc devolveu NULL! \n");
        exit(EXIT_FAILURE);
    }
    return imagem;
}

pixel *realocar_image_array(pixel *imagem,long width,long height)
{
    imagem = ( pixel *) malloc ( height * width * sizeof( pixel ) );
    if(imagem == NULL){
        printf("Socorro o malloc devolveu NULL! \n");
        exit(EXIT_FAILURE);
    }
    return imagem;
}

/* Multiplica o pixel por uma constante   *
 * Entradas :                             *
 * pixel pixel - Pixel a ser multiplicado *
 * int constante - constante multiplicada */
pixel multPixelCnt(pixel entrada,int constante)
{
    entrada.blue  *= constante;
    entrada.green *= constante;
    entrada.red   *= constante;
    return entrada;
}

/* Retorna um pixel com todas as cores com o mesmo valor passado   *
 * Entradas :                                                      *
 * int valor          : Valor que todas as cores iram assumir      *
 * Saida    :                                                      *
 * pixel pixelRetorno : Pixel com todas as cores com o mesmo valor */
pixel igualarCorPixel(int valor)
{
    pixel retorno;
    retorno.blue  = valor; /* A cor azul assume o valor passado */
    retorno.green = valor; /* A cor verde assume o valor passado */
    retorno.red   = valor; /* A cor vermelha assume o valor passado */
    return retorno;
}

/* Divide o pixel por uma constante     *
 * Entradas:                            *
 * int constante - valor a ser divisor  *
 * pixel pixel - pixel no dividendo     *
 * Saida:                               *
 * pixel pixel - pixel dividido         */
pixel divPixelporCnt(pixel entrada,int constante)
{
    /* Divide a cor azul por uma contante e armazena no pixel */
    entrada.blue  /= constante;
    /* Divide a cor verde por uma contante e armazena no pixel */
    entrada.green /= constante;
    /* Divide a cor vermelha por uma contante e armazena no pixel */
    entrada.red   /= constante;
    /* Retorna o pixel que contem o resultado da divisao */
    return entrada;
}

/* Soma as cores de dois pixeis                       *
 * Entradas :                                         *
 * pixel pixel1 - Primeiro pixel a ser somado         *
 * pixel pixel2 - Segundo pixel a ser somado          *
 * Saidas:                                            *
 * pixel resultado - resultado da soma dos dois pixel */
pixel somaPixel(pixel a,pixel b)
{
    /* Soma da cor azul e armazena no pixel1 */
    a.blue  += b.blue;
    /* Soma da cor verde e armazena no pixel1 */
    a.green += b.green;
    /* Soma da cor vermelha e armazena no pixel1 */
    a.red   += b.red;
    /* Retorna o pixel */
    return a;
}

/* Subtrai o valor de dois pixel e retorna o valor absoluto*/
pixel subAbsPixel(pixel a, pixel b)
{
    a.blue  = (b.blue  > a.blue)  ? (b.blue  - a.blue)  : (a.blue  - b.blue);
    a.green = (b.green > a.green) ? (b.green - a.green) : (a.green - b.green);
    a.red   = (b.red   > a.red)   ? (b.red   - a.red)   : (a.red   - b.red);
    return a;
}

/* Retorna a soma de todas as cores de um pixel *
 * Entradas:                                    *
 * pixel pixelEntrada : Pixel de entrada        *
 * Saida              : somaDosPixel            */
long somaCorPixel(pixel entrada)
{
    return (entrada.blue + entrada.green + entrada.red);
}

/* Retorna um pixel, contendo em cada cor, o maior entre as tres cores de um pixel de entrada */
pixel maiorCordoPixel(pixel entrada)
{
    /* Armazena o valor da cor Azul */
    int blue  = entrada.blue;
    /* Armazena o valor da cor Vermelha */
    int red   = entrada.red;
    /* Armazena o valor da cor Verde */
    int green = entrada.green;
    /* Armazena o maior entre as três cores */
    int maiorValor;
    /* Retorna o valor do pixel de retorno */
    pixel retorno;
    
    /* Verifica se a cor azul é maior */
    if((blue >= red) && (blue >= green))
    {
        /* O maior valor encontrado é da cor Azul */
        maiorValor = blue;
    }
    else
    {
        /* Verifica se a cor verde é maior */
        if((green >= red) && (green >= red))
        {
            /* O maior valor encontrado é da cor Verde */
            maiorValor = green;
        }
        else
        {
            /* Caso nem a cor Verde ou Azul seja a maior cor, retorna a vermelha por exclusão */
            /* O maior valor encontrado é da cor Vermelha */
            maiorValor = red;
        }
    }

    /* Configura a cor azul, verde e vermelho como sendo o maior valor achado */
    retorno = igualarCorPixel(maiorValor);

    /* Retorna um pixel com todas as cores com o maior valor achado */
    return retorno;

}

pxMat rotate_90_rigth(pxMat img)
{
    pxMat saida;
    saida.column = img.row;
    saida.row = img.column;
    saida.image = allocate_image_array(saida.row,saida.column);
    int rotate_x, rotate_y, k;
    k = img.row - 1;
    for (rotate_y = 0;rotate_y < img.column;rotate_y++)
    {
        for (rotate_x = 0;rotate_x < img.row;rotate_x++)
        {
            saida.image[rotate_y*img.row + rotate_x] = img.image[rotate_x*img.column + img.column - 1 - rotate_y];
        }
    }
    return saida;
}

/* Multiplica as cores de dois pixels*/
pixel multiPixel(pixel a,pixel b)
{
    a.blue  *= b.blue;
    a.green *= b.green;
    a.red   *= b.red;
    return a;
}

/* Multiplica duas matrizes para realizar uma convolucao */
pixel multiMatrizPixel(pixel imagem, pixel filtro, int ordemMatriz)
{
    int linhas = 0, colunas = 0;
    pixel soma;
    soma = igualarCorPixel(0);
    for(linhas = 0; linhas < ordemMatriz; linhas++)
    {
        for(colunas = 0; colunas < ordemMatriz; colunas++)
        {soma = somaPixel(soma,multiPixel(imagem,filtro));}
    }
    return soma;
}

void merge(pixel *imagem,int ini,int meio,int fim,pixel *aux)
{
    int i = ini,j = meio + 1,k = 0;
    while(i <= meio && j <= fim)
    {
        if(somaCorPixel(imagem[i]) <= somaCorPixel(imagem[j]))
        {aux[k++] = imagem[i++];}
        else
        {aux[k++] = imagem[j++];}
    }
    while(i <= meio)
    {aux[k++] = imagem[i++];}
    while(j <= fim)
    {aux[k++] = imagem[j++];}
    for(i = ini, k = 0;i <= fim;k++,i++)
    {imagem[i] = aux[k];}
}

void organizarPixel(pixel *imagem,int inicio,int fim,pixel *aux)
{
    if(inicio < fim)
    {
        int meio = (inicio + fim)/2;
        organizarPixel(imagem,inicio,meio,aux);
        organizarPixel(imagem,meio+1,fim,aux);
        merge(imagem,inicio,meio,fim,aux);
    }
}