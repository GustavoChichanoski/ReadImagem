#pragma once
    
    #ifdef NEURALNETWORK_EXPORTS
        #define NEURALNETWORK_API __declspec(dllexport)
    #else
        #define NEURALNETWORK_API __declspec(dllimport)
    #endif
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    #include <stdio.h>
    #include <malloc.h>
    #include <string.h>
    #include "operacaoPixel.h"
    #include "pooling.h"

    #ifdef __cplusplus
        extern "C" }
    #endif