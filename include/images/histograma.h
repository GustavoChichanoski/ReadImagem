#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "conversao.h"
#include "bmp.h"
#include "detectores.h"
#include "histograma.h"
#include "operacaoPixel.h"

pixel *suavizar_histograma(pixel *histograma,int gray_levels);
pixel *zero_histograma(pixel *histograma,int gray_levels);
pixel *calculate_histogram(pixel *imagem,int maxLinha,int maxColuna);