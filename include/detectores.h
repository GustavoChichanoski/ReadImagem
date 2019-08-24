#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
<<<<<<< HEAD:include/processamento.h
#include <string.h>
#include <sys\stat.h>
#include <sys\types.h>
=======
>>>>>>> cd62f5450908b31f6fa69edae5249070dc8d1916:include/detectores.h
#include "bmp.h"
#include "conversao.h"

#ifndef DETECTORES_H_INCLUDED
#define DETECTORES_H_INCLUDED

#ifdef __cplusplus
    extern "C" {
#endif

    pixel **detectorBorda(long width,long height,pixel **rgb);
    pixel **edge_gauss(long width,long height,pixel **rgb);
    pixel **median_filter(long width,long height,pixel **rgb);
    pixel **gray_scale(long width,long height,pixel **rgb);
    pixel **sub_image(pixel **in,pixel **out,long cols,long rows);
    
#ifdef __cplusplus
    }
#endif

#endif	/* PROCESSAMENTO_H */
