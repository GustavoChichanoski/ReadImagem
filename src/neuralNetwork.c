#include "../include/neuralNetwork.h"

#define MIN        0
#define MED        127
#define MAX        255 /* DEFAULT */
#define BIAS       1
#define LEARN_RATE 100

int    random_number(int min_num,int max_num);
pixel  rootMeanSquare(pixel *error,int neurons);
int    floorSqrt(int erro);
Matriz calcErro(Matriz real,int *setpoint);
Matriz setup_weight(Matriz weigths);

Matriz calcErro(Matriz real,int *setpoint)
{
    for(int i = 0;i < real.column*real.row;i++)
    {
        real.mat[i] = setpoint[i] - real.mat[i];
    }
    return real;
}

Matriz setup_weight(Matriz weigths)
{
    for (int i = 0;i < weigths.row * weigths.column;i++)
    {
        weigths.mat[i] = random_number(-255,256);
    }
    return weigths;
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

int relu(int x)
{
    return (x < 0) ? 0 : x;
}

int derivadaRelu(int x)
{
    return (x < 0) ? 0 : 1;
}

int floorSqrt(int erro)
{
    int start, end, ans, mid;
    start = 1; 
    end = erro; 
    ans = 0; 
    mid = (start + end) / 2;
    if(erro == 0 || erro == 1){return erro;}
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