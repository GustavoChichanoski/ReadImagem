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
pixel img_gauss(pixel **matriz){

    int i, j;
    long max = 0;
    long aux1[3], aux2[3], aux3[3], aux4[3];
    int maxX, maxY;

    aux1[0] = matriz[0][0].blue  - matriz[2][2].blue;
    aux1[1] = matriz[0][0].green - matriz[2][2].green;
    aux1[2] = matriz[0][0].red   - matriz[2][2].red;
    
    aux2[0] = matriz[3][0].blue  - matriz[0][2].blue;
    aux2[1] = matriz[3][0].green - matriz[0][2].green;
    aux2[2] = matriz[3][0].red   - matriz[0][2].red;

    aux3[0] = matriz[1][0].blue  - matriz[1][2].blue;
    aux3[1] = matriz[1][0].green - matriz[1][2].green;
    aux3[2] = matriz[1][0].red   - matriz[1][2].red;

    aux4[0] = matriz[0][1].blue  - matriz[2][1].blue;
    aux4[1] = matriz[0][1].green - matriz[2][1].green;
    aux4[2] = matriz[0][1].red   - matriz[2][1].red;

    if(aux1[0] < 0) aux1[0] *= (-1);
    if(aux1[1] < 0) aux1[1] *= (-1);
    if(aux1[2] < 0) aux1[2] *= (-1);
    
    if(aux2[0] < 0) aux2[0] *= (-1);
    if(aux2[1] < 0) aux2[1] *= (-1);
    if(aux2[2] < 0) aux2[2] *= (-1);
    
    if(aux3[0] < 0) aux3[0] *= (-1);
    if(aux3[1] < 0) aux3[1] *= (-1);
    if(aux3[2] < 0) aux3[2] *= (-1);

    if(aux4[0] < 0) aux4[0] *= (-1);
    if(aux4[1] < 0) aux4[1] *= (-1);
    if(aux4[2] < 0) aux4[2] *= (-1);
    
    return matriz[maxX][maxY];

}

pixel **edge_gauss(long width,long height,pixel **rgb){

    int x, y;
    pixel ref, aux;
    pixel **m_pixel;
    
    aux.blue = 0; aux.green = 0; aux.red = 0; 
    m_pixel = allocate_image_array(3,3);

    for(y = 0; y < height; y++){
        for(x = 0;x < width;x++){
            if(y == 0){
                if(x == 0){ 
                    m_pixel[0][0] = aux; m_pixel[0][1] = aux;         m_pixel[0][2] = aux;
                    m_pixel[1][0] = aux; m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                    m_pixel[2][0] = aux; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                } else {
                    if(x == width-1){
                        m_pixel[0][0] = aux;           m_pixel[0][1] = aux;         m_pixel[0][2] = aux;
                        m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = aux;
                        m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = aux;
                    } else {
                        m_pixel[0][0] = aux;           m_pixel[0][1] = aux;         m_pixel[0][2] = aux;
                        m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                        m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                    }
                }
            } else {
                if(y == (height -1)){
                    if(x == 0){
                        m_pixel[0][0] = aux; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                        m_pixel[1][0] = aux; m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                        m_pixel[2][0] = aux; m_pixel[2][1] = aux;         m_pixel[2][2] = aux;
                    } else {
                        if(x == width-1){
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = aux;
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = aux;
                            m_pixel[2][0] = aux;           m_pixel[2][1] = aux;         m_pixel[2][2] = aux;
                        } else {
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                            m_pixel[2][0] = aux;           m_pixel[2][1] = aux;         m_pixel[2][2] = aux;
                        }
                    }
                } else {
                    if(x == 0){
                        m_pixel[0][0] = aux; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                        m_pixel[1][0] = aux; m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                        m_pixel[2][0] = aux; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                    } else {
                        if(x == width - 1){
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = aux; 
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = aux;
                            m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = aux;
                        } else {
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                            m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                        }
                    }
                }
            }
            ref = rgb[y][x];
            rgb[y][x] = img_homo(m_pixel,ref);
        }
    }

    return rgb;

}

pixel **edge_detector(long width,long height,pixel **rgb){

    int x, y;
    pixel ref, aux;
    pixel **m_pixel;
    
    aux.blue = 0; aux.green = 0; aux.red = 0; 
    m_pixel = allocate_image_array(3,3);

    for(y = 0; y < height; y++){
        for(x = 0;x < width;x++){
            if(y == 0){
                if(x == 0){ 
                    m_pixel[0][0] = aux; m_pixel[0][1] = aux;         m_pixel[0][2] = aux;
                    m_pixel[1][0] = aux; m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                    m_pixel[2][0] = aux; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                } else {
                    if(x == width-1){
                        m_pixel[0][0] = aux;           m_pixel[0][1] = aux;         m_pixel[0][2] = aux;
                        m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = aux;
                        m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = aux;
                    } else {
                        m_pixel[0][0] = aux;           m_pixel[0][1] = aux;         m_pixel[0][2] = aux;
                        m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                        m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                    }
                }
            } else {
                if(y == (height -1)){
                    if(x == 0){
                        m_pixel[0][0] = aux; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                        m_pixel[1][0] = aux; m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                        m_pixel[2][0] = aux; m_pixel[2][1] = aux;         m_pixel[2][2] = aux;
                    } else {
                        if(x == width-1){
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = aux;
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = aux;
                            m_pixel[2][0] = aux;           m_pixel[2][1] = aux;         m_pixel[2][2] = aux;
                        } else {
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                            m_pixel[2][0] = aux;           m_pixel[2][1] = aux;         m_pixel[2][2] = aux;
                        }
                    }
                } else {
                    if(x == 0){
                        m_pixel[0][0] = aux; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                        m_pixel[1][0] = aux; m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                        m_pixel[2][0] = aux; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                    } else {
                        if(x == width - 1){
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = aux; 
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = aux;
                            m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = aux;
                        } else {
                            m_pixel[0][0] = rgb[y-1][x-1]; m_pixel[0][1] = rgb[y-1][x]; m_pixel[0][2] = rgb[y-1][x+1]; 
                            m_pixel[1][0] = rgb[y][x-1];   m_pixel[1][1] = rgb[y][x];   m_pixel[1][2] = rgb[y][x+1];
                            m_pixel[2][0] = rgb[y+1][x-1]; m_pixel[2][2] = rgb[y][x+1]; m_pixel[2][2] = rgb[y+1][x+1];
                        }
                    }
                }
            }
            ref = rgb[y][x];
            rgb[y][x] = img_homo(m_pixel,ref);
        }
    }

    return rgb;

}