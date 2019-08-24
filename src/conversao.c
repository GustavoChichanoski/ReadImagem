#include <stdio.h>
#include "../include/conversao.h"

/* extract_ushort_from_buffer(...)
 * This takes a two byte unsiged
 * short out of a buffer of characters.
 * It is important to know the byte order LSB or MSB. */
void extract_ushort_from_buffer(buffer,lsb,start,number)
    char buffer[];
    int lsb, start;
    unsigned short *number;
{
    union ushort_char_union lcu;
    if(lsb == 1){
        lcu.s_alpha[0] = buffer[start+0];
        lcu.s_alpha[1] = buffer[start+1];
    } else {
        lcu.s_alpha[0] = buffer[start+1];
        lcu.s_alpha[1] = buffer[start+0];
    }
    *number = lcu.s_num;
}/* Converte um vetor de char para short */

/* extract_short_from_buffer(...)
 * This takes a two byte short out of a buffer of characters.
 * It is important to know the byte order LSB or MSB. */
void extract_short_from_buffer(buffer,lsb,start,number)
    char buffer[];
    int lsb, start;
    short *number;
{
    union short_char_union lcu;
    if(lsb == 1){
        lcu.s_alpha[0] = buffer[start+0];
        lcu.s_alpha[1] = buffer[start+1];
    } else {
        lcu.s_alpha[0] = buffer[start+1];
        lcu.s_alpha[1] = buffer[start+0];
    }
    *number = lcu.s_num;
}

/* Converte um vetor de char para long */
void extract_long_from_buffer(buffer, lsb, start, number)
    char buffer[];
    int lsb, start;
    long *number;
{
    union long_char_union lcu;
    if(lsb == 1){
        lcu.l_alpha[0] = buffer[start+0];
        lcu.l_alpha[1] = buffer[start+1];
        lcu.l_alpha[2] = buffer[start+2];
        lcu.l_alpha[3] = buffer[start+3];
    } else {
        lcu.l_alpha[0] = buffer[start+3];
        lcu.l_alpha[1] = buffer[start+2];
        lcu.l_alpha[2] = buffer[start+1];
        lcu.l_alpha[3] = buffer[start+0];
    }
    *number = lcu.l_num;
} /* Ends c2l */

/* Converte um vetor de char para unsigned long */
void extract_ulong_from_buffer(buffer,lsb,start,number)
    char buffer[];
    int lsb, start;
    unsigned long *number;
{
    union ulong_char_union lcu;
    if(lsb == 1){
        lcu.l_alpha[0] = buffer[start+0];
        lcu.l_alpha[1] = buffer[start+1];
        lcu.l_alpha[2] = buffer[start+2];
        lcu.l_alpha[3] = buffer[start+3];
    } else {
        lcu.l_alpha[0] = buffer[start+3];
        lcu.l_alpha[1] = buffer[start+2];
        lcu.l_alpha[2] = buffer[start+1];
        lcu.l_alpha[3] = buffer[start+0];
    }
    *number = lcu.l_num;
}

/* Insere 2 bytes no arquivo de imagem */
void insert_short_into_buffer(buffer,start,number)
    char buffer[];
    int start;
    short number;
{
    union short_char_union lsu;
    lsu.s_num = number;
    buffer[start+0] = lsu.s_alpha[0];
    buffer[start+1] = lsu.s_alpha[1];
} /* Ends insert_short_into_buffer */

/* Insere dois bytes no arquivo de imagem */
void insert_ushort_into_buffer(buffer,start,number)
    char buffer[];
    int start;
    unsigned short number;
{
    union ushort_char_union lsu;
    lsu.s_num = number;
    buffer[start+1] = lsu.s_alpha[1];
    buffer[start+0] = lsu.s_alpha[0];
}

/* Insere quatro bytes no arquivo de imagem */
void insert_long_into_buffer(buffer,start,number)
    char buffer[];
    int start;
    long number;
{
    union long_char_union lsu;
    lsu.l_num = number;
    buffer[start+0] = lsu.l_alpha[0];
    buffer[start+1] = lsu.l_alpha[1];
    buffer[start+2] = lsu.l_alpha[2];
    buffer[start+3] = lsu.l_alpha[3];
} /* Ends insert_short_into_buffer */

/* insert_ulong_into_buffer(...)                                        *
 * This inserts a four byte unsigned long into a buffer of characters.  *
 * It does this is LSB order.                                           */
void insert_ulong_into_buffer(buffer,start,number)
    char buffer[];
    int start;
    unsigned long number;
{
    union ulong_char_union lsu;
    lsu.l_num = number;
    buffer[start+0] = lsu.l_alpha[0];
    buffer[start+1] = lsu.l_alpha[1];
    buffer[start+2] = lsu.l_alpha[2];
    buffer[start+3] = lsu.l_alpha[3];
}/* Ends insert_ulong_into_buffer */