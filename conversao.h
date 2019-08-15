#ifndef CONVERSAO_H_INCLUDED
#define CONVERSAO_H_INCLUDED

#ifdef CONVERSAO_EXPORTS
    #define CONVERSAO_API __declspec(dllexport)
#else
    #define CONVERSAO_API __declspec(dllimport)
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* Armazena duas variaveis no mesmo espa�o da memoria */
union short_char_union{
    short s_num;
    char  s_alpha[2];
};

union int_char_union{
    int  i_num;
    char i_alpha[2];
};

union long_char_union{
    long  l_num;
    char  l_alpha[4];
};

union float_char_union{
    float f_num;
    char  f_alpha[4];
};

union ushort_char_union{
    short s_num;
    char  s_alpha[2];
};

union uint_char_union{
    int  i_num;
    char i_alpha[2];
};

union ulong_char_union{
    long  l_num;
    char  l_alpha[4];
};

/* Funções que executam as conversões */
void extract_ushort_from_buffer(char buffer[],int lsb,int start,unsigned short *number);
void extract_short_from_buffer(char buffer[],int lsb,int start,short *number);
void extract_long_from_buffer(char buffer[],int lsb,int start,long *number);
void extract_ulong_from_buffer(char buffer[],int lsb,int start,unsigned long *number);

/* Insere valores no buffer */
void insert_ulong_into_buffer(char buffer[],int start,unsigned long number);
void insert_long_into_buffer(char buffer[],int start,long number);
void insert_short_into_buffer(char buffer[],int start,short number);
void insert_ushort_into_buffer(char buffer[],int start,unsigned short number);

#ifdef __cplusplus
    }
#endif

#endif // CONVERSAO_H_INCLUDED
