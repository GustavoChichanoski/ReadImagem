#pragma once

#include <stdio.h>
#include <stdlib.h>

#define  MED              127
#define  MIN              -255 /* DEFAULT */
#define  MAX              255  /* DEFAULT */
#define  BIAS             1
#define  LEARN_RATE       100
#define  A_360            4095
#define  SQRT_2           5793
#define  A_180            2047
#define  A_90             1023
#define  FORWARD          0
#define  INVERSE          1
#define  MINIMUM_FFT_SIZE 8
#define  MAXIMUM_FFT_SIZE 1048576
#define  POOL             0
#define  CONV             1
#define  RELU             2
#define  LR               400
#define  ONE              4095
#define _ONE              -4095


/* Armazena duas variaveis no mesmo espaco da memoria */
union short_char_union
{
    short s_num;
    char  s_alpha[2];
};

/* Armazena duas variaveis no mesmo espaco da memoria */
union int_char_union
{
    int  i_num;
    char i_alpha[2];
};

/* Armazena duas variaveis no mesmo espaco da memoria */
union long_char_union
{
    long  l_num;
    char  l_alpha[4];
};

/* Armazena duas variaveis no mesmo espaco da memoria */
union float_char_union
{
    float f_num;
    char  f_alpha[4];
};

/* Armazena duas variaveis no mesmo espaco da memoria */
union ushort_char_union
{
    short s_num;
    char  s_alpha[2];
};

/* Armazena duas variaveis no mesmo espaco da memoria */
union uint_char_union
{
    int  i_num;
    char i_alpha[2];
};

/* Armazena duas variaveis no mesmo espaco da memoria */
union ulong_char_union
{
    long  l_num;
    char  l_alpha[4];
};

/* Funcoes que executam as conversões */
void extract_ushort_from_buffer(char buffer[],int lsb,int start,unsigned short *number);
void extract_short_from_buffer(char buffer[],int lsb,int start,short *number);
void extract_long_from_buffer(char buffer[],int lsb,int start,long *number);
void extract_ulong_from_buffer(char buffer[],int lsb,int start,unsigned long *number);

/* Funcoes que inserem valores no buffer */
void insert_ulong_into_buffer(char buffer[],int start,unsigned long number);
void insert_long_into_buffer(char buffer[],int start,long number);
void insert_short_into_buffer(char buffer[],int start,short number);
void insert_ushort_into_buffer(char buffer[],int start,unsigned short number);