#ifndef COMPLEX_H_INCLUDED
    
    #define COMPLEX_H_INCLUDED
    
    #ifdef COMPLEX_EXPORTS
        #define COMPLEX_API __declspec(dllexport)
    #else
        #define COMPLEX_API __declspec(dllimport)
    #endif
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    #include "operacaoPixel.h"
    #include "pooling.h"
    #include "operacaoMatriz.h"
    #include "neuralNetwork.h"
    
    complex  mult(complex z1, complex z2);
    complex  soma(complex z1, complex z2);
    void     reverteBit(complex *x, int N);
    void     mostraResultado(complex *x1, int N);
    void     fft(complex *x, int N);
    complex  W(int n, int kk);
    complex *le(int *N);
    int      sinoide(int angulo);
    int      cose(int angulo,int inverter);
    int      sine(int angulo,int inverter);
    int      factorial(int x);
    int      logN(int n,int base);
    int reverse(int num,int lg_n);
     
    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif