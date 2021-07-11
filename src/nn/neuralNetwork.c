#include "../include/nn/neuralNetwork.h"

int    random_number(int min_num,int max_num);
pixel  rootMeanSquare(pixel *error,int neurons);
int    floorSqrt(int erro);
Matriz calcErro(Matriz real,int *setpoint);
Matriz setup_weight(Matriz weigths);
int    removeLayer(Layer *l,int index);

void fillPesos(Layer *l)
{
    Layer *p;
    for (p = l;p != NULL;p = p -> next)
    {
        for (int i = 0;i < l -> height * l -> width;i++)
        {
            p -> weight.mat[i] = random_number(MIN,MAX);
        }
    }
}

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

pxMat setupKernel(pxMat weigths)
{
    for (int i = 0;i < weigths.row * weigths.column;i++)
    {
        weigths.image[i].red   = random_number(-255,256);
        weigths.image[i].blue  = random_number(-255,256);
        weigths.image[i].green = random_number(-255,256);
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

Layer *init(void)
{
    return NULL;
}

Layer *insertHead(Layer *l,int input,int output)
{
    Layer  *novo          = (Layer *) malloc(sizeof(Layer));
    novo -> weight.mat    = (int *) malloc(input * output * sizeof(int));
    novo -> weight.column = input;
    novo -> weight.row    = output;
    novo -> weight        = setup_weight(novo -> weight);
    novo -> next          = l;
    return novo;
}

void imprime(Layer *l)
{
    Layer *p;
    for (p = l;p != NULL;p = p -> next)
    {
        for(int i = 0;i < p -> height;i++)
        {
            for(int j = 0;j < p -> width;j++)
            {
                if(j == 0 && i != 0)
                {
                    printf("\n");
                }
                printf("%d\t",p -> weight.mat[i * p -> width + j]);
            }
        }
    }
}

int empty(Layer *l)
{
    return (l == NULL) ? 1 : 0;
}

void freeCamada(Layer *l)
{
    Layer *p = l;
    while(p != NULL)
    {
        Layer *t = p -> next;
        free(p);
        p = t;
    }
}