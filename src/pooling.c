#include "../include/pooling.h"

int padWidth, padHeight;

pixel maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual);

void calcPad(int poolingOrdem,int height, int width)
{
    padWidth  = width  % poolingOrdem;
    padHeight = height % poolingOrdem;
}

pixel maxPooling(pixel *matriz,int ordemMatriz)
{
    
    int length = ordemMatriz*ordemMatriz, i = 0;
    pixel max;
    
    max = igualarCorPixel(0);
    
    for(i = 0; i < length; i++)
    {
        if(matriz[i].blue > max.blue)
        {
            max.blue  = matriz[i].blue;
        }
        if(matriz[i].green > max.green)
        {
            max.green = matriz[i].green;
        }
        if(matriz[i].red > max.red)
        {
            max.red   = matriz[i].red;
        }
    }
    
    return max;
    
}

pixel medPooling(pixel *matriz,int ordemMatriz)
{
    
    int length = ordemMatriz*ordemMatriz, i = 0;
    pixel med;
    
    med = igualarCorPixel(0);
    
    for(i = 0; i < length; i++)
    {
        med.blue  += matriz[i].blue;
        med.green += matriz[i].green;
        med.red   += matriz[i].red;
    }
    
    med = divPixelporCnt(med,length);
    
    return med;
    
}

int calcHeight(int length,int width)
{
    return length / width;
}

pixel *matrizPooling(imagem,matriz,height,width,y,x,ordem)
    int height, width, y, x,ordem;
    pixel *imagem, *matriz;
{

    int posicao = y*width + x, posicaoPool = 0, j = 0, i = 0;

    for(j = 0; j < ordem; j++)
    {
        for(i = 0; i < ordem; i++)
        {
            if((j + y) < height || (i + x) < width)
            {
                matriz[posicaoPool] = imagem[posicao];
            }
            else
            {
                matriz[posicaoPool] = igualarCorPixel(0);
            }
            posicaoPool++;
        }
    }
    return matriz;
}

/*
    width  : number of column of image
    height : number of row of image
    image  : RGB of image
    stride : how big are the steps of the filter
*/
pixel *pooling(int stride,int width,int height,pixel *imagem)
{
    pixel *saida;
    saida = allocate_image_array(width/stride + (width % stride),height/stride + (height % stride));
    int pos_x = 0, pos_y = 0;
    for (pos_y = 0; pos_y < height; pos_y + stride)
    {
        for (pos_x = 0; pos_x < width; pos_x + stride)
        {
            pixel max_valor = imagem[pos_x*width + pos_x];
            for (int i = pos_x;i < pos_x + stride && i < width;i++)
            {
                for (int j = pos_y;j < pos_y + stride && j < height;j++)
                {
                    max_valor = maxValorPixel(max_valor,imagem[pos_y*width + pos_x]);
                }
            }
            saida[pos_y*width + pos_x] = max_valor;
        }
    }
    return saida;
}

pixel maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual)
{
    pixel c;
    c.blue  = (MaximoAnterior.blue  < ImagemAtual.blue)  ? ImagemAtual.blue  : MaximoAnterior.blue;
    c.red   = (MaximoAnterior.red   < ImagemAtual.red)   ? ImagemAtual.red   : MaximoAnterior.red;
    c.green = (MaximoAnterior.green < ImagemAtual.green) ? ImagemAtual.green : MaximoAnterior.green;
    return c;
}