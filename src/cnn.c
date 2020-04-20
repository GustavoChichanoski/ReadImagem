#include "../include/cnn.h"

#define RELU   0
#define STRIDE 1

void   imprimeMatriz(pxMat matriz);
Size   createSize(int row,int column);
void   testeConvolucao();
int    sqr(int a);
void   swap(int *x,int *y);
pixel *setup_kernel(pxMat kernel);

pxMat convolucao(pxMat image,pxMat kernel,int stride);

int   sqr(int a)
{
    return a*a;
}

void testeConvolucao()
{
    printf("Teste Convolucao:\n");
    int teste[9]   = {0,0,0, 0,255,0, 0,0,0};
    int conv[30]   = {1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5};
    int result[25] = {2,2,3,1,1, 1,4,3,4,1, 1,2,4,3,3, 1,2,3,4,1, 0,2,2,1,1};
    int position   = 0;
    pxMat kernel, imagem, out;
    kernel.column = 3;
    kernel.row    = 3;
    imagem.column = 5;
    imagem.row    = 5;
    imagem.image  = allocate_image_array(6,5);
    kernel.image  = allocate_image_array(3,3);
    out.image     = allocate_image_array(6,5);
    for(position  = 0;position < 25;position++)
    {
        if(position < 9)
        {
            kernel.image[position] = igualarCorPixel(teste[position]);
        }
        imagem.image[position] = igualarCorPixel(conv[position]);
    }
    out = convolucao(imagem,kernel,STRIDE);
    printf("Matriz teste:\n");
    imprimeMatriz(imagem);
    printf("\nMatriz kernel:\n");
    imprimeMatriz(kernel);
    printf("\nMatriz Saida:\n");
    imprimeMatriz(out);
    kernel = pooling(2,out);
    printf("\n");
    printf("\nMatriz Pooling:\n");
    imprimeMatriz(kernel);
    printf("\n");
}

void imprimeMatriz(pxMat mat)
{
    for(int position = 0;position < mat.column*mat.row;position++)
    {
        int pos_y = position / mat.row;
        int pos_x = position % mat.column;
        if(pos_x == 0 && pos_y != 0)
        {
            printf("\n");
        }
        printf("\t%d",mat.image[position]);
    }
}

pixel *fill_matriz(pxMat a,int b[])
{
    for(int position = 0;position < a.row * a.column;position++)
    {
        a.image[position] = igualarCorPixel(b[position]);
    }
}

pxMat cnn(pxMat img,int kernel_degree)
{
    pxMat kernel;
    int position;
    int teste[9]  = {-1,-2,-1, 0,0,0, 1,2,1};
    kernel.column = 3;
    kernel.row    = 3;
    kernel.image  = allocate_image_array(3,3);
    kernel.image  = setup_kernel(kernel);
    for(position  = 0;position < 9;position++)
    {
        kernel.image[position] = igualarCorPixel(teste[position]);
    }
    img = convolucao(img,kernel,1);
    // img = pooling(2,img);
    return img;
}

pixel *setup_kernel(pxMat kernel)
{
    for(int position = 0;position < sqr(kernel.row);position++)
    {
        kernel.image[position] = igualarCorPixel(random_number(0,255));
    }
    return kernel.image;
}

int validZone(int pos_x,int pos_y,pxMat img)
{
    return ((-1 < pos_x && -1 < pos_y) && (pos_x < img.column && pos_y < img.row)) ? 1 : 0;
}

pxMat convolucao(pxMat img,pxMat kernel,int stride)
{
    int padding;
    int img_pos_max, out_pos,out_pos_y,out_pos_x;
    int kernel_pos_max, kernel_pos, kernel_pos_x, kernel_pos_y;
    int position, position_x, position_y;
    pxMat saida;
    pixel aux;
    saida.column    = (img.column / stride); 
    saida.row       = (img.row    / stride);
    saida.image    = allocate_image_array(saida.row,saida.column);
    img_pos_max    = saida.row * saida.column;
    kernel_pos_max = sqr(kernel.row);
    out_pos        = 0;
    while (out_pos < img_pos_max)
    {
        saida.image[out_pos] = igualarCorPixel(0);
        out_pos_y      = out_pos / img.column;
        out_pos_x      = out_pos % img.row;
        for(kernel_pos = 0;kernel_pos < kernel_pos_max;kernel_pos++)
        {
            kernel_pos_y = kernel_pos / kernel.row;
            kernel_pos_x = kernel_pos % kernel.row;
            position_y   = out_pos_y  + kernel_pos_y - kernel.row / 2;
            position_x   = out_pos_x  + kernel_pos_x - kernel.row / 2;
            position     = position_y * img.column   + position_x;
            if(validZone(position_x,position_y,img))
            {
                aux            = multiPixel(kernel.image[kernel_pos],img.image[position]);
                saida.image[out_pos] = somaPixel(saida.image[out_pos],divPixelporCnt(aux,255));
            }
        }
        out_pos = out_pos + stride;
    }
    return saida;
}

pixel medValorPixel(pixel medAnt, pixel image)
{
    return divPixelporCnt(somaPixel(medAnt,image),2);
}

pixel reluPixel(pixel data)
{
    data.red   = (data.red   < 0) ? 0 : data.red;
    data.blue  = (data.blue  < 0) ? 0 : data.blue;
    data.green = (data.green < 0) ? 0 : data.green;
    return data;
}

void swap(int *x,int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}