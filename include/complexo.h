#ifndef COMPLEXO_H_INCLUDED
    
    #define COMPLEXO_H_INCLUDED
    
    #ifdef COMPLEXO_EXPORTS
        #define COMPLEXO_API __declspec(dllexport)
    #else
        #define COMPLEXO_API __declspec(dllimport)
    #endif
    
    #ifdef __cplusplus
        extern "C" {
    #endif
    
    typedef struct
    {
        int real,imag;
    } complexo;

    #ifdef __cplusplus
        extern "C" }
    #endif

#endif