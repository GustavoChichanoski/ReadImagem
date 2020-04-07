#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"
#include "conversao.h"

#ifndef PROCESSAMENTO_H_INCLUDED
#define PROCESSAMENTO_H_INCLUDED

#ifdef __cplusplus
    extern "C" {
#endif
    
    pixel *gray_image(long width,long height,pixel *rgb);
    
#ifdef __cplusplus
    }
#endif

#endif	/* PROCESSAMENTO_H */
