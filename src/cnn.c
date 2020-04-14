#include "../include/cnn.h"

#define RELU   0
#define STRIDE 2

unsigned long kernel_Image[25] = {1,1,1,0,0, 0,1,1,1,0, 0,0,1,1,1, 0,0,1,1,0, 0,1,1,0,0};
unsigned long resultado[9]     = {4,3,4,2,4,3,2,3,4};

void   imprimeMatriz(Size mat,pixel *matriz);
void   testeConvolucao();

pixel *convolucao
(
    long img_width,long img_height,pixel *image,int stride,
    int kernel_degree,pixel *kernel
);

void testeConvolucao()
{
    printf("Teste Convoluacao:\n");
    int teste[9]   = {1,0,1, 0,1,0, 1,0,1};
    int conv[25]   = {1,1,1,0,0, 0,1,1,1,0, 0,0,1,1,1, 0,0,1,1,0, 0,1,1,0,0};
    int result[25] = {2,2,3,1,1, 1,4,3,4,1, 1,2,4,3,3, 1,2,3,4,1, 0,2,2,1,1};
    pixel *kernel, *imagem, *out;

    imagem = allocate_image_array(5,5);
    kernel = allocate_image_array(3,3);
    out    = allocate_image_array(5,5);
    
    for(int position = 0;position < 25;position++)
    {
        if(position < 9)
        {
            kernel[position] = igualarCorPixel(teste[position]);
        }
        imagem[position] = igualarCorPixel(conv[position]);
    }
    
    out = convolucao(5,5,imagem,STRIDE,3,kernel);
    Size out_size;
    out_size.column = 5;
    out_size.row = 5;
    printf("Matriz Saida:\n");
    imprimeMatriz(out_size,out);
}

void imprimeMatriz(Size mat,pixel *matriz)
{
    for(int position = 0;position < mat.column*mat.row;position++)
    {
        int pos_x = position % mat.column;
        int pos_y = position / mat.row;
        if(pos_x == 0 && pos_y != 0)
        {
            printf("\n");
        }
        printf("\t[%d][%d] : %d",pos_y,pos_x,matriz[position].red);
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

int validZone(int pos_x,int pos_y,int *size)
{
    int out = ((-1 < pos_x && -1 < pos_y) && (pos_x < size[0] && pos_y < size[1])) ? 1 : 0;
    return out;
}

pixel *convolucao
(
    long img_width,long img_height,pixel *image,int stride,
    int kernel_degree,pixel *kernel
)
{
    int padding, size[2],img_size[2];
    int img_pos_max, img_pos,img_pos_y,img_pos_x;
    int kernel_pos_max, kernel_pos, kernel_pos_x, kernel_pos_y;
    int position_x, position_y, position;
    pixel *saida;
    
    // padding = (img_width - 1) / 2;
    img_size[0] = img_width;
    img_size[1] = img_height;
    size[0] = (img_width  / stride);
    size[1] = (img_height / stride);
    saida   = allocate_image_array(size[1],size[0]);
    img_pos_max    = img_width*img_height;
    kernel_pos_max = kernel_degree*kernel_degree;
    img_pos = 0;

    while (img_pos < img_pos_max)
    {
        saida[img_pos] = igualarCorPixel(0);
        img_pos_y = img_pos / img_width;
        img_pos_x = img_pos % img_width;
        kernel_pos = 0;
        while(kernel_pos < kernel_pos_max)
        {
            kernel_pos_x = kernel_pos / kernel_degree;
            kernel_pos_y = kernel_pos % kernel_degree;
            printf("img_pos_max : %d - ",img_pos);
            printf("[%d]",img_pos_y);
            printf("[%d]\t",img_pos_x);
            printf("kernel_pos : %d",kernel_pos);
            printf(" [%d][%d]\t",kernel_pos_x,kernel_pos_y);
            printf("kernel_pos_max : %d \t",kernel_pos_max);
            printf("kernel_degree : %d\t",kernel_degree);
            position_x   = img_pos_x + kernel_pos_x - kernel_degree/2;
            position_y   = img_pos_y + kernel_pos_y - kernel_degree/2;
            position       = position_y*img_size[0] + position_x;
            if(validZone(position_x,position_y,img_size))
            {
                printf("position : %d\t",position);
                printf("[%d]",position_y);
                printf("[%d]\t",position_x);
                saida[img_pos] = somaPixel(saida[img_pos],multiPixel(kernel[kernel_pos],image[position]));
            }
            kernel_pos = kernel_pos+stride;
            printf("\n");
        }
        if(img_pos + stride < img_width)
        {
            img_pos++;
        } else {
            img_pos = img_pos + stride;
        }
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