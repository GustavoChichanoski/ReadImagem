#include "../include/pooling.h"

pixel maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual);
pixel medPixel(pixel MaximoAnterior, pixel ImagemAtual);

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

int maxPoolingInt(int **matriz,int ordemMatriz)
{
    int length = ordemMatriz * ordemMatriz;
    int max = 0;
    for(int i = 0;i < length;i++)
    {
        if((*matriz)[i] > max)
        {
            max = (*matriz)[i];
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

pixel *matrizPooling(pixel *imagem,pixel *matriz,int height,int width,int y,int x,int ordem)
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
pxMat pooling(int stride,pxMat *img)
{
    pxMat saida;
    pixel max_valor;
    int column = 0, row = 0;
    int pos_x = 0, pos_y = 0, i = 0, j = 0, out_x = 0, out_y = 0;
    // column = img -> column / stride + 1;
    column = (img -> column / stride);
    // column = ((img -> column) / stride) + (stride - img -> column % stride);
    // row    = ((img -> row) / stride) + (stride - img -> row % stride);
    row = img -> row / stride + 1;
    // row = (img -> row / stride);
    saida.row = row;
    saida.column = column;
    saida.image = allocate_image_array(row,column);
    for (pos_y = 0; pos_y < img -> row; pos_y = pos_y + stride)
    {
        for (pos_x = 0; pos_x < img -> column;pos_x = pos_x + stride)
        {
            max_valor = img -> image[pos_y*img -> column + pos_x];
            for (i = pos_x; i < pos_x + stride && i < img -> column;i++)
            {
                for (j = pos_y;j < pos_y + stride && j < img -> row; j++)
                {
                    max_valor = maxValorPixel(max_valor,img -> image[j*img -> column + i]);
                }
            }
            saida.image[out_y*column + out_x] = max_valor;
            out_x++;
        }
        out_x = 0;
        out_y++;
    }
    return saida;
}

/*
    width  : number of column of image
    height : number of row of image
    image  : RGB of image
    stride : how big are the steps of the filter
*/
void poolingInt(int stride,int *img,int img_width,int img_height,int **out,int *out_width,int *out_height)
{
    int max_valor;
    int column = 0, row = 0;
    int pos_x = 0, pos_y = 0, i = 0, j = 0, out_x = 0, out_y = 0;
    column = (img_width  % 2 != 0) ? (img_width  / 2) + 1 : img_width  / 2;
    row    = (img_height % 2 != 0) ? (img_height / 2) + 1 : img_height / 2;
    (*out_height) = row;
    (*out_width)  = column;
    (*out) = (int *) malloc(row * column * sizeof(int));
    for (pos_y = 0; pos_y < img_height; pos_y = pos_y + 2)
    {
        for (pos_x = 0; pos_x < img_width;pos_x = pos_x + 2)
        {
            max_valor = img[pos_y * img_width + pos_x];
            for (i = pos_x; i < pos_x + stride && i < img_width;i++)
            {
                for (j = pos_y;j < pos_y + stride && j < img_height; j++)
                {
                    max_valor = (max_valor > img[j * img_width + i]) ? max_valor : img[j*img_width + i];
                }
            }
            (*out)[out_y * column + out_x] = max_valor;
            out_x++;
        }
        out_x = 0;
        out_y++;
    }
}

pixel maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual)
{
    MaximoAnterior.blue  = (MaximoAnterior.blue  < ImagemAtual.blue ) ? ImagemAtual.blue  : MaximoAnterior.blue;
    MaximoAnterior.red   = (MaximoAnterior.red   < ImagemAtual.red  ) ? ImagemAtual.red   : MaximoAnterior.red;
    MaximoAnterior.green = (MaximoAnterior.green < ImagemAtual.green) ? ImagemAtual.green : MaximoAnterior.green;
    return MaximoAnterior;
}

pixel medPixel(pixel MaximoAnterior, pixel ImagemAtual)
{
    MaximoAnterior.blue  = (MaximoAnterior.blue  + ImagemAtual.blue ) / 2;
    MaximoAnterior.red   = (MaximoAnterior.red   + ImagemAtual.red  ) / 2;
    MaximoAnterior.green = (MaximoAnterior.green + ImagemAtual.green) / 2;
    return MaximoAnterior;
}