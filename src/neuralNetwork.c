#include "../include/bmp.h"
#include "../include/operacaoPixel.h"

#define MIN        0;
#define MED        127;
#define MAX        255; /* DEFAULT */
#define BIAS       1;
#define LEARN_RATE 100;

typedef struct neuron
{
    pixel  Bias;
    pixel *Weigth;
    int    NumberWeigth;
} Neuron;

typedef struct layer
{
    Neuron *Neuron;
    int       NumberNeuron;
} Layer;

typedef struct neuralnetwork
{
    Layer *Layer;
    int     NumberLayer;
} neuralNetwork;

int random_number(int min_num,int max_num);
pixel rootMeanSquare(pixel *error,int neurons);
int floorSqrt(int erro);

neuralNetwork createNeuralNetwork(int numberLayer, int numberNeurons)
{

}

int *multiply(int *matriz,int constant,int maxPosition)
{
    for(int position = 0;position < maxPosition;position++)
    {
        matriz[position] = matriz[position]*constant;
    }
    return matriz;
}

int *hadamard(int *error,int *derivout,int numberOuts)
{
    for(int position = 0;position < numberOuts;position++)
    {
        error[position] = error[position]*derivout[position];
    }
    return error;
}

// example of use: int x = random_number(0,255);
int random_number(int min_num,int max_num)
{
    int result = 0, low_num = 0, high_num = 0;
    low_num    = (min_num < max_num) ? min_num : max_num + 1;
    high_num   = (min_num > max_num) ? min_num : max_num + 1;
    result     = (rand() % (high_num - low_num)) + low_num;
    return result;
}

pixel calcNeuron(Neuron n,pixel *inputs)
{
    pixel sum = igualarCorPixel(0);
    for(int position = 0;position < n.NumberWeigth;position++)
    {
        sum = somaPixel(sum,multiPixel(n.Weigth[position],inputs[position]));
    }
    return sum;
}

pixel rootMeanSquare(pixel *error,int neurons)
{
    pixel sum = igualarCorPixel(0);
    for(int i = 0;i < neurons;i++)
    {
        sum = somaPixel(sum,multiPixel(error[i],error[i]));
    }
    sum       = divPixelporCnt(sum,neurons);
    sum.red   = floorSqrt(sum.red);
    sum.blue  = floorSqrt(sum.blue);
    sum.green = floorSqrt(sum.green);
    return sum;
}

int sign(int x)
{
    if(x == 0)
    {
        return 0;
    } else {
        return (x > 0) ? 1 : -1;
    }
}

int relu(int x)
{
    return (x < 0) ? 0 : x;
}

int drelu(int x)
{
    return (x < 0) ? 0 : 1;
}

int floorSqrt(int erro)
{
    int start = 1, end = erro, ans = 0, mid = (start + end) / 2;
    if(erro == 0 || erro == 1)
    {
        return erro;
    }
    while (start <= end)
    {
        if(mid * mid == erro)
        {
            return mid;
        } else {
            if(mid * mid < erro)
            {
                start = mid + 1;
                ans   = mid;
            } else {
                end = mid - 1;
            }
        }
    }
    return ans;
}