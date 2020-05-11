#include "../include/cnn.h"

void   convolucaoInt(int **img,int img_width,int img_height,int **kernel,int kernel_width,int kernel_height,int **out,int *out_width, int *out_heigth,int stride)
{
    int i = 0, j = 0, k = 0, l = 0;
    int img_pos = 0, kernel_pos = 0;
    for (i = 0;i < img_height;i++)
    {
        for (j = 0;j < img_width;j++)
        {
            (*out)[img_pos] = 0;
            for(int l = -kernel_height/2;l < kernel_height/2;l++)
            {
                for(int k = -kernel_width/2;k < kernel_width/2;k++)
                {
                    kernel_pos++;
                    if(i + k > 0 && i + k < img_height && j + k < img_width && j + k > 0)
                    {
                        (*out)[img_pos] += (*kernel)[kernel_pos]*(*img)[(i + k)*img_width + (j + k)];
                    }
                }
            }
            kernel_pos = 0;
            img_pos++;
        }
    }
}

void   imprimeMatriz(pxMat matriz);
Size   createSize(int row,int column);
void   testeConvolucao();
int    sqr(int a);
void   swap(int *x,int *y);
pixel *setup_kernel(pxMat kernel);
pxMat  cnn(pxMat img,int kernel_degree);
pixel  reluPixel(pixel data);