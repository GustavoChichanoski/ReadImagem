#include "../include/bmp.h"
#include "../include/operacaoPixel.h"

#define MIN                 0;
#define MED                 1;
#define MAX                 2; /* DEFAULT */
#define BIAS                1;
#define TAXA_APRENDIZADO    100;


typedef struct neuronio {

    int *Peso;
    int  Erro;
    int  Saida;

    int  QuantidadeLigacoes;

} Neuronio;

typedef struct camada {
    
    Neuronio* Neuronios;

    int QuantidadeNeuronios;

} Camada;

typedef struct redeNeural {

    Camada  CamadaEntrada;
    Camada *CamadaEscondida;
    Camada  CamadaSaida;

    int QuantidadeEscondidas;

} RedeNeural;

int ReLU(int x);
int limiar(int x);
int derivadaPeso(int esquecimento,int erro,int entrada);
int ReLU(int x);
int limiar(int x);

int ReLU(int x)
{
    if(x < 255)
    {
        return (x > 0) ? x : 0;
    }
    else
    {
        return 255;
    }
}

int limiar(int x)
{
    return (x < 0) ? 0 : 255;
}

int novoPeso(int peso,int erro,int entrada)
{
    return peso + derivadaPeso(10,erro,entrada);
}

/* APRENDIZAGEM POR CORREÇÃO DE ERRO *
 * Regra Delta */
int regraDelta(int esquecimento,int erro,int entrada)
{
    return erro*entrada/esquecimento;
}