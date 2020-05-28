#include "../include/processamento.h"

// pixel *detectorBorda(long width,long height,pixel **rgb);
// pixel *edge_gauss(long width,long height,pixel **rgb);
// pixel *median_filter(long width,long height,pixel **rgb);
// pixel *sub_image(pixel **in,pixel **out,long cols,long rows);
pixel *gray_image(long width,long height,pixel *rgb);
void img_creat_red_to_blue(int *img,int maxPosition,int **red,int **blue,int **green);

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

void img_creat_red_to_blue(int *img,int maxPosition,int **red,int **blue,int **green)
{
    int min = _ONE;
    int max = ONE;
    for(int i = 0;i < maxPosition;i++)
    {
        min = (min > img[i] && img[i] >  ONE) ? img[i] : min;
        max = (max < img[i] && img[i] < _ONE) ? img[i] : max;
    }
    min = (min == 0) ? 1 : min;
    max = (max == 0) ? 1 : max;
    for(int i = 0;i < maxPosition;i++)
    {
        (*red)[i]   = (img[i] > 0) ? 0 : (img[i]*ONE)/min;
        (*blue)[i]  = (img[i] < 0) ? 0 : (img[i]*ONE)/max;
        (*green)[i] = 0;
    }
}