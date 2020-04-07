#include "../include/cnn.h"

#define RELU 0

unsigned long kernel_Image[25] = {1,1,1,0,0, 0,1,1,1,0, 0,0,1,1,1, 0,0,1,1,0, 0,1,1,0,0};
unsigned long resultado[9]     = {4,3,4,2,4,3,2,3,4};

void   imprimeMatriz(int width,int height,pixel *matriz);
int    random_number(int min_num,int max_num);
void   testeConvolucao();

pixel *convolucao
(
    long img_width,long img_height,pixel *image,
    int kernel_degree,pixel *kernel
);

// example of use: int x = random_number(0,255);
int random_number(int min_num,int max_num)
{
    int result = 0, low_num = 0, high_num = 0;
    low_num    = (min_num < max_num) ? min_num : max_num + 1;
    high_num   = (min_num > max_num) ? min_num : max_num + 1;
    result     = (rand() % (high_num - low_num)) + low_num;
    return result;
}

void testeConvolucao()
{
    printf("Teste Convoluacao:\n");
    int teste[9]   = {1,0,1,0,1,0,1,0,1};
    int conv[25]   = {1,1,1,0,0, 0,1,1,1,0, 0,0,1,1,1, 0,0,1,1,0, 0,1,1,0,0};
    int result[25] = {2,2,3,1,1, 1,4,3,4,1, 1,2,4,3,3, 1,2,3,4,1, 0,2,2,1,1};

    pixel *kernel; pixel *imagem;pixel *out;

    kernel = allocate_image_array(3,3);
    out    = allocate_image_array(5,5);
    imagem = allocate_image_array(5,5);

    for(int position = 0;position < 9;position++)
    {
        kernel[position] = igualarCorPixel(teste[position]);
    }
    for(int position = 0;position < 25;position++)
    {
        imagem[position] = igualarCorPixel(conv[position]);
    }

    out = convolucao(5,5,imagem,3,kernel);

    printf("Matriz Saida:\n");
    imprimeMatriz(5,5,out);

}

void imprimeMatriz(int width,int height,pixel *matriz)
{
    for(int position = 0;position < width*height;position++)
    {
        int pos_x = position % width;
        int pos_y = position / width;
        if(pos_x == 0 && pos_y != 0)
        {
            printf("\n");
        }
        printf("\t[%d][%d] : %d",pos_y,pos_x,matriz[position]);
    }
}

pixel *fill_matriz(pixel *a,int b[], int length)
{
    for(int position = 0;position < length;position++)
    {
        a[position] = igualarCorPixel(b[position]);
    }
}

pixel *setup_kernel(pixel *kernel,int max_position)
{
    for(int position = 0;position < max_position;position++)
    {
        kernel[position] = igualarCorPixel(random_number(0,255));
    }
    return kernel;
}

pixel *convolucao
(
    long img_width,long img_height,pixel *image,
    int kernel_degree,pixel *kernel
)
{
    pixel *saida;
    
    saida = allocate_image_array(image[0].width,image[0].heigth);
    int img_pos_max    = img_width*img_height;
    int kernel_pos_max = kernel_degree*kernel_degree;
    
    for(int img_pos = 0;img_pos < img_pos_max;img_pos++)
    {
        int img_pos_y = img_pos / img_width;
        int img_pos_x = img_pos % img_width;
        saida[img_pos] = igualarCorPixel(0);
        for(int kernel_pos = 0;kernel_pos < kernel_pos_max;kernel_pos++)
        {
            int kernel_pos_x = kernel_pos / kernel_degree;
            int kernel_pos_y = kernel_pos % kernel_degree;
            int position_x   = img_pos_x + kernel_pos_x - kernel_degree/2;
            int position_y   = img_pos_y + kernel_pos_y - kernel_degree/2;
            if(-1 < position_x && position_x < img_width)
            {
                if(-1 < position_y && position_y < img_height)
                {
                    int position   = position_y*img_width + position_x;
                    saida[img_pos] = somaPixel(saida[img_pos],multiPixel(kernel[kernel_pos],image[position]));
                }
            }
        }
    }
    return saida;
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

pixel medValorPixel(pixel medAnt, pixel image)
{
    return divPixelporCnt(somaPixel(medAnt,image),2);
}

pixel maxValorPixel(pixel MaximoAnterior, pixel ImagemAtual)
{
    pixel c;
    c.blue  = (MaximoAnterior.blue  < ImagemAtual.blue)  ? ImagemAtual.blue  : MaximoAnterior.blue;
    c.red   = (MaximoAnterior.red   < ImagemAtual.red)   ? ImagemAtual.red   : MaximoAnterior.red;
    c.green = (MaximoAnterior.green < ImagemAtual.green) ? ImagemAtual.green : MaximoAnterior.green;
    return c;
}

pixel reluPixel(pixel data)
{
    data.red   = (data.red   < 0) ? 0 : data.red;
    data.blue  = (data.blue  < 0) ? 0 : data.blue;
    data.green = (data.green < 0) ? 0 : data.green;
    return data;
}

pixel *relu(int width,int height,pixel *imagem)
{
    for(int position = 0;position < width*height;position++)
    {
        imagem[position] = reluPixel(imagem[position]);
    }
}