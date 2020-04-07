#include "../include/pooling.h"

int padWidth, padHeight;

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

pixel *pooling(pixel *imagem,int height,int width,int poolingOrdem,int tipo)
{
    
    int posicao = 0, posNovaImg = 0, y = 0, x = 0;
    pixel *matriz,*novaImagem;
    
    matriz     = allocate_image_array(width,height);
    novaImagem = allocate_image_array(width/3,height/3);
    
    for(y = 0;y < height;y += poolingOrdem)
    {
        for(x = 0;x < width;x += poolingOrdem)
        {
            matriz = matrizPooling(imagem,matriz,height,width,y,x,3);
            if(tipo)
            {
                novaImagem[posNovaImg] = maxPooling(matriz,3);
            }
            else
            {
                novaImagem[posNovaImg] = medPooling(matriz,3);
            }
            posNovaImg++;
        }
    }
    
    return novaImagem;
    
}