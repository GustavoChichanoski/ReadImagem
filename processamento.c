#include <stdio.h>
#include <stdlib.h>
#include "conversao.h"
#include "bmp.h"

pixel img_homo(pixel **matriz,pixel ref){

    int i, j;
    long max = 0, aux;
    int maxX, maxY;

    for(j = 0;j < 3;j++){
        for(i = 0;i < 3;i++){
            aux = ref.blue - matriz[j][i].blue;
            if(aux < 0){
                matriz[j][i].blue = aux*(-1);
            } else{
                matriz[j][i].blue = aux;
            }
            aux = ref.green - matriz[j][i].green;
            if(aux < 0){
                matriz[j][i].green = aux*(-1);
            } else{
                matriz[j][i].green = aux;
            }
            aux = ref.red - matriz[j][i].red;
            if(aux < 0){
                matriz[j][i].red = aux*(-1);
            } else{
                matriz[j][i].red = aux;
            }
            aux = matriz[j][i].red + matriz[j][i].green + matriz[j][i].blue;
            if(aux > max){
                maxX = i; maxY = j;
            }
        }
    }

    return matriz[maxX][maxY];

}

pixel **edge_detector(long width,long height,pixel **rgb){

    int x, y;
    pixel ref;
    pixel **m_pixel,**img_homogenity;
    
    m_pixel = allocate_image_array(3,3);
    img_homogenity = allocate_image_array(width,height);

    for(y = 0; y < height; y++){
        for(x = 0;x < width;x++){
            if(y == 0){
                if(x == 0){
                    m_pixel[0][0].blue = 0; m_pixel[0][0].green = 0; m_pixel[0][0].red = 0;
                    m_pixel[1][0].blue = 0; m_pixel[1][0].green = 0; m_pixel[1][0].red = 0;
                    m_pixel[2][0].blue = 0; m_pixel[2][0].green = 0; m_pixel[2][0].red = 0;
                    m_pixel[0][1].blue = 0; m_pixel[0][1].green = 0; m_pixel[0][1].red = 0;
                    m_pixel[0][2].blue = 0; m_pixel[0][2].green = 0; m_pixel[0][2].red = 0;
                }
                if(x == width-1){
                    m_pixel[0][0].blue = 0; m_pixel[0][0].green = 0; m_pixel[0][0].red = 0;
                    m_pixel[1][2].blue = 0; m_pixel[1][2].green = 0; m_pixel[1][2].red = 0;
                    m_pixel[2][2].blue = 0; m_pixel[2][2].green = 0; m_pixel[2][2].red = 0;
                    m_pixel[0][1].blue = 0; m_pixel[0][1].green = 0; m_pixel[0][1].red = 0;
                    m_pixel[0][2].blue = 0; m_pixel[0][2].green = 0; m_pixel[0][2].red = 0;
                }
            }
            if(y == height -1){
                if(x == 0){
                    m_pixel[0][0].blue = 0; m_pixel[0][0].green = 0; m_pixel[0][0].red = 0;
                    m_pixel[1][0].blue = 0; m_pixel[1][0].green = 0; m_pixel[1][0].red = 0;
                    m_pixel[2][0].blue = 0; m_pixel[2][0].green = 0; m_pixel[2][0].red = 0;
                    m_pixel[2][1].blue = 0; m_pixel[2][1].green = 0; m_pixel[2][1].red = 0;
                    m_pixel[2][2].blue = 0; m_pixel[2][2].green = 0; m_pixel[2][2].red = 0;
                }
                if(x == width-1){
                    m_pixel[0][2].blue = 0; m_pixel[0][2].green = 0; m_pixel[0][2].red = 0;
                    m_pixel[1][2].blue = 0; m_pixel[1][2].green = 0; m_pixel[1][2].red = 0;
                    m_pixel[2][0].blue = 0; m_pixel[2][0].green = 0; m_pixel[2][0].red = 0;
                    m_pixel[2][1].blue = 0; m_pixel[2][1].green = 0; m_pixel[2][1].red = 0;
                    m_pixel[2][2].blue = 0; m_pixel[2][2].green = 0; m_pixel[2][2].red = 0;
                }
            }
            ref = rgb[y][x];
            img_homogenity[y][x] = img_homo(m_pixel,ref);
        }
    }

    free_image_array(m_pixel,3,3);
    return img_homogenity;

}