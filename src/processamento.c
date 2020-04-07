#include <stdio.h>
#include <stdlib.h>
#include "../include/conversao.h"
#include "../include/bmp.h"
#include "../include/operacaoPixel.h"
#include "../include/processamento.h"

// pixel *detectorBorda(long width,long height,pixel **rgb);
// pixel *edge_gauss(long width,long height,pixel **rgb);
// pixel *median_filter(long width,long height,pixel **rgb);
// pixel *sub_image(pixel **in,pixel **out,long cols,long rows);
pixel *gray_image(long width,long height,pixel *rgb);

pixel *gray_imagem(long width,long height,pixel *rgb)
{
    
    int posicao = 0;
    long luminosity = 0;
    
    for(posicao = 0;posicao < width*height;posicao++)
    {
        luminosity += 3*rgb[posicao].red/10;
        luminosity += 59*rgb[posicao].green/100;
        luminosity += 11*rgb[posicao].blue/100;
        rgb[posicao] = igualarCorPixel(luminosity);
    }
    
    return rgb;
    
}