#ifndef NEURALNETWORK_H_INCLUDED
    
    #ifdef NEURALNETWORK_EXPORTS
        #define NEURALNETWORK_API __declspec(dllexport)
    #else
        #define NEURALNETWORK_API __declspec(dllimport)
    #endif
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    #include <malloc.h>
    #include <stdio.h>
    #include "bmp.h"
    #include "operacaoMatriz.h"

    int     random_number  (int min_num,int max_num);
    int     floorSqrt      (int erro);
    int     floorSqrt      (int erro);
    pixel   rootMeanSquare (pixel *error,int neurons);
    Matriz  calcErro       (Matriz real,int *setpoint);
    Matriz  setup_weight   (Matriz weigths);

    #ifdef __cplusplus
        extern "C" }
    #endif

#endif