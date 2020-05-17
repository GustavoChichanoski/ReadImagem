#ifndef FFT_H_INCLUDED
    
    #define FFT_H_INCLUDED
    
    #ifdef FFT_EXPORTS
        #define FFT_API __declspec(dllexport)
    #else
        #define FFT_API __declspec(dllimport)
    #endif
    
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    
    #define A_360            4095
    #define SQRT_2           5793
    #define A_180            2047
    #define A_90             1023
    #define FORWARD          0
    #define INVERSE          1
    #define MINIMUM_FFT_SIZE 8
    #define MAXIMUM_FFT_SIZE 1048576
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    void fpga_FFT(int *inputR,int *inputI,int N,int type);

    #ifdef __cplusplus
        extern "C" }
    #endif
    
#endif