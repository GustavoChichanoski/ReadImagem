#include "../include/complexo.h"

complexo complexo_sum(complexo a,complexo b)
{
    a.imag += b.imag;
    a.real += b.real;
    return a;
}

complexo complexo_mult(complexo a,complexo b)
{
    complexo c;
    c.real = a.real*b.real - a.imag*b.imag;
    c.imag = a.imag*b.imag + a.imag*b.real;
    return c;
}