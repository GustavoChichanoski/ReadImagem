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
    #include "cnn.h"
    
    typedef struct camada
    {
        Matriz weight, input, output;
        struct Camada *prev, *next;
    } Camada;

    typedef struct redeNeural
    {
        Camada *head;
        int     QuantidadeEscondidas;
    } RedeNeural;

    int     random_number  (int min_num,int max_num);
    int     floorSqrt      (int erro);
    int     floorSqrt      (int erro);
    pixel   rootMeanSquare (pixel *error,int neurons);
    Matriz  calcErro       (Matriz real,int *setpoint);
    Matriz  setup_weight   (Matriz weigths);
    Matriz  derivada_output(Camada *c);
    Matriz  calculate_error(Camada *c,int *label);

    #ifdef __cplusplus
        extern "C" }
    #endif

#endif