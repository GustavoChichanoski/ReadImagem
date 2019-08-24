#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/detectores.h"

long somaCorPixel(pixel pixelEntrada);
pixel maiorCordoPixel(pixel pixelEntrada);
pixel subAbsPixel(pixel a, pixel b);
pixel somaPixel(pixel pixel1,pixel pixel2);
pixel divPixelCnt(pixel pixel,int constante);
pixel multPixelCnt(pixel pixel,int constante);
pixel igualarCorPixel(int valor);
pixel **allocate_image_array(long width,long height);

/* Aloca o espaco da matriz da imagem na memoria  */
pixel **allocate_image_array(long width,long height){
    pixel **rgb;
    int pad = calculate_pad(width);
    rgb = malloc(height*sizeof(pixel*));
    if(rgb == NULL){
        printf("Socorro o malloc devolveu NULL! \n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i < height;++i){
        rgb[i] = malloc((width+pad)*sizeof(pixel));
        if(rgb[i] == NULL){
            printf("Socorro o malloc devolveu NULL\n");
            exit(EXIT_FAILURE);
        }
    }
    return rgb;
}

/* Multiplica o pixel por uma constante   *
 * Entradas :                             *
 * pixel pixel - Pixel a ser multiplicado *
 * int constante - constante multiplicada */
pixel multPixelCnt(pixel pixel,int constante)
{
    pixel.blue  *= constante;
    pixel.green *= constante;
    pixel.red   *= constante;
    return pixel;
}

/* Retorna um pixel com todas as cores com o mesmo valor passado   *
 * Entradas :                                                      *
 * int valor          : Valor que todas as cores iram assumir      *
 * Saida    :                                                      *
 * pixel pixelRetorno : Pixel com todas as cores com o mesmo valor */
pixel igualarCorPixel(int valor)
{

    pixel pixelRetorno;

    pixelRetorno.blue  = valor; /* A cor azul assume o valor passado */
    pixelRetorno.green = valor; /* A cor verde assume o valor passado */
    pixelRetorno.red   = valor; /* A cor vermelha assume o valor passado */

    return pixelRetorno;

}

/* Divide o pixel por uma constante     *
 * Entradas:                            *
 * int constante - valor a ser divisor  *
 * pixel pixel - pixel no dividendo     *
 * Saida:                               *
 * pixel pixel - pixel dividido         */
pixel divPixelporCnt(pixel pixel,int constante)
{
    /* Divide a cor azul por uma contante e armazena no pixel */
    pixel.blue  /= constante;
    /* Divide a cor verde por uma contante e armazena no pixel */
    pixel.green /= constante;
    /* Divide a cor vermelha por uma contante e armazena no pixel */
    pixel.red   /= constante;
    /* Retorna o pixel que contem o resultado da divisao */
    return pixel;
}

/* Soma as cores de dois pixeis                       *
 * Entradas :                                         *
 * pixel pixel1 - Primeiro pixel a ser somado         *
 * pixel pixel2 - Segundo pixel a ser somado          *
 * Saidas:                                            *
 * pixel resultado - resultado da soma dos dois pixel */
pixel somaPixel(pixel pixel1,pixel pixel2)
{
    /* Soma da cor azul e armazena no pixel1 */
    pixel1.blue  += pixel2.blue;
    /* Soma da cor verde e armazena no pixel1 */
    pixel1.green += pixel2.green;
    /* Soma da cor vermelha e armazena no pixel1 */
    pixel1.red   += pixel2.red;
    /* Retorna o pixel1 */
    return pixel1;
}

/* Subtrai o valor de dois pixel e retorna o valor absoluto*/
pixel subAbsPixel(pixel a, pixel b)
{

    pixel resultado;

    if(b.blue > a.blue) {
        resultado.blue = b.blue - a.blue;
    }
    else {
        resultado.blue = a.blue - b.blue;
    }

    if(b.green > a.green) {
        resultado.green = b.green - a.green;
    }
    else {
        resultado.green = a.green - b.green;
    }

    if(b.red > a.red) {
        resultado.red = b.red - a.red;
    }
    else {
        resultado.red = a.red - b.red;
    }

    return resultado;

}

/* Retorna a soma de todas as cores de um pixel *
 * Entradas:                                    *
 * pixel pixelEntrada : Pixel de entrada        *
 * Saida              : somaDosPixel            */
long somaCorPixel(pixel pixelEntrada)
{
    long somaDosPixel = (pixelEntrada.blue + pixelEntrada.green + pixelEntrada.red); 
    return somaDosPixel;
}

/* Retorna um pixel, contendo em cada cor, o maior entre as tres cores de um pixel de entrada */
pixel maiorCordoPixel(pixel pixelEntrada)
{
    /* Armazena o valor da cor Azul */
    int blue = pixelEntrada.blue;
    /* Armazena o valor da cor Vermelha */
    int red  = pixelEntrada.red;
    /* Armazena o valor da cor Verde */
    int green = pixelEntrada.green;
    /* Armazena o maior entre as três cores */
    int maiorValor;
    /* Retorna o valor do pixel de retorno */
    pixel pixelRetorno;

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
    pixelRetorno = igualarCorPixel(maiorValor);

    /* Retorna um pixel com todas as cores com o maior valor achado */
    return pixelRetorno;

}

pixel multiPixel(pixel a,pixel b)
{

    a.blue  *= b.blue;
    a.green *= b.green;
    a.green *= b.red;

    return a;

}

/* Multiplica duas matrizes para realizar uma convolucao */
pixel multiMatrizPixel(pixel imagem,pixel filtro,int ordemMatriz)
{
    pixel soma;

    soma = igualarCorPixel(0);

    for(int linhas = 0;linhas < ordemMatriz;linhas++)
    {
        for(int colunas = 0;colunas < ordemMatriz;colunas++)
        {
            soma = somaPixel(soma,multiPixel(imagem,filtro));
        }
    }

    return soma;

}