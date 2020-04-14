#include "../include/bmp.h"
#include "../include/operacaoPixel.h"
#include "../include/operacaoMatriz.h"
#include "../include/neuralNetwork.h"

#define MIN        0
#define MED        127
#define MAX        255 /* DEFAULT */
#define BIAS       1
#define LEARN_RATE 100

Camada *head = NULL;

int    random_number(int min_num,int max_num);
pixel  rootMeanSquare(pixel *error,int neurons);
int    floorSqrt(int erro);
Matriz calcErro(Matriz real,int *setpoint);
Matriz setup_weight(Matriz weigths);
Matriz derivada_output(Camada *c);
Matriz calculate_error(Camada *c,int *label);

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

Camada Dense(Camada *l,int neurons,int input,int output)
{
    if(l -> next != NULL)
    {
        while(l -> next != NULL){l = l -> next;}
        Camada *c;
        l -> next          = c;
        c -> prev          = l;
        c -> next          = NULL;
        c -> input.column  = 1;
        c -> input.row     = l -> output.row;
        c -> output.column = 1;
        c -> output.row    = neurons;
        c -> weight.column = c -> input.column;
        c -> weight.row    = c -> output.column;
        c -> weight        = setup_weight(c -> weight);
    } else {
        l -> next          = NULL;
        l -> input.column  = 1;
        l -> input.row     = input;
        l -> output.column = 1;
        l -> output.row    = neurons;
        l -> weight.row    = l -> input.row;
        l -> weight.column = l -> output.row;
        l -> weight        = setup_weight(l -> weight);
    }
}

Camada *calculate_Outputs(Camada *c)
{
    c -> output = multiplyMatriz(c -> input,c -> weight);
    for(int i = 0;i < c -> output.column * c -> output.row;i++)
    {c -> output.mat[i] = relu(c -> output.mat[i]);}
    return c;
}

Camada *fit_weigth(Camada *c,int *label)
{
    Matriz delta_weight, error, dOutput, tHidden;
    
    while(c -> next != NULL){c = (Camada *) c -> next;}
    
    tHidden      = create_matriz(c -> input.row ,c -> input.column);
    error        = create_matriz(c -> output.row,c -> output.column);
    dOutput      = create_matriz(c -> output.row,c -> output.column);
    delta_weight = create_matriz(c -> weight.row,c -> weight.column);
    
    tHidden = transposed(c -> input);
    dOutput = derivada_output(c);
    error   = calculate_error(c,label);
    error   = hadamart(error,dOutput);
    tHidden = divConst(tHidden,LEARN_RATE);
    error   = multiplyMatriz(error,tHidden);
    error   = somaMatrizes(c -> weight, error);
}

Matriz calculate_error(Camada *c,int *label)
{
    for(int i = 0;i < c -> output.row*c -> output.column;i++)
    {
        c -> output.mat[i] = label[i] - c -> output.mat[i];
    }
    return c -> output;
}

Matriz derivada_output(Camada *c)
{
    for (int i = 0;i < c -> output.row * c -> output.column;i++)
    {
        c -> output.mat[i] = derivadaRelu(c -> output.mat[i]);
    }
    return c -> output;
}