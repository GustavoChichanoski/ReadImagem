#pragma once

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

void fpga_FFT(int *inputR,int *inputI,int N,int type);