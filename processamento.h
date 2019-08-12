#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <direct.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "bmp.h"
#include "conversao.h"

#ifndef PROCESSAMENTO_H
#define	PROCESSAMENTO_H

#ifdef __cplusplus
    extern "C" {
#endif

    pixel **edge_detector(long width,long height,pixel **rgb);
    pixel **edge_gauss(long width,long height,pixel **rgb);
    
#ifdef __cplusplus
    }
#endif

#endif	/* PROCESSAMENTO_H */