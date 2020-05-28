#include "../include/cnn_exec.h"

void layer_calc_pool(CNN_Neuron **n,int width,int height,int *out_height, int *out_width);
void layer_calc_relu(CNN_Neuron **n,int width,int height);
void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size);
void layer_calc_neuron(CNN_Layer **l,int type);
void layer_calc(CNN_Layer **l);

void layer_calc_pool(CNN_Neuron **n,int width,int height,int *out_height, int *out_width)
{
    CNN_Neuron *n_last;
    n_last = (*n);
    do
    {
        poolingInt(1,n_last -> dendritic -> img,width,height,&(n_last -> out),out_width,out_height);
        n_last = n_last -> next;
    }
    while(n_last -> next != (*n));
}

void layer_calc_relu(CNN_Neuron **n,int width,int height)
{
    int valor;
    CNN_Neuron *n_last;
    n_last = (*n);
    do
    {
        for(int i = 0;i < width * height;i++)
        {
            valor            = n_last -> dendritic -> img[i];
            if(valor < 0)
            {
                n_last -> out[i] = 0;
            } else {
                n_last -> out[i] = valor;
            }
        }
        n_last = n_last -> next;
    }
    while(n_last != (*n));
}

void layer_calc_conv(CNN_Neuron **n,int width,int height,int kernel_size)
{
    CNN_Neuron    *n_last;
    CNN_Dendritic *d_last;
    n_last = (*n);
    do
    {
        d_last = n_last -> dendritic;
        do
        {
            convolucaoInt(d_last -> img,width,height,d_last -> kernel,kernel_size,&(d_last -> intermediate),1);
            d_last = d_last -> next;
        }
        while(d_last != n_last -> dendritic);
        for(int i = 0;i < width * height;i++)
        {
            d_last = n_last -> dendritic;
            n_last -> out[i] = n_last -> bias;
            do
            {
                n_last -> out[i] += d_last -> intermediate[i];
                d_last            = d_last -> next;
            }
            while(d_last != n_last -> dendritic);
        }
    } while(n_last != (*n));
}

void layer_calc_neuron(CNN_Layer **l,int type)
{
    CNN_Neuron *n;
    n = (*l) -> neuron;
    do{
        if(type == CONV)
        {
            layer_calc_conv(&n,(*l) -> img_width,(*l) -> img_height,(*l) -> kernel_size);
        } 
        if(type == RELU)
        {
            layer_calc_relu(&n,(*l) -> img_width,(*l) -> img_height);
        }
        if(type == POOL)
        {
            layer_calc_pool(&n,(*l) -> img_width,(*l) -> img_height,&((*l) -> out_height),&((*l) -> out_width));
        }
        n = n -> next;
    } while(n != (*l) -> neuron);
}

void layer_calc(CNN_Layer **l)
{
    CNN_Layer *l_last;
    l_last = (*l);
    do
    {
        layer_calc_neuron(&l_last, l_last -> type);
        l_last = l_last -> next;
    }
    while(l_last != (*l));
}

/*
The backward computation for a convolution function

Arguments:
dH    -- gradient of the cost with respect to output of the conv layer (H), numpy array of shape (n_H, n_W) assuming channels = 1
cache -- cache of values needed for the conv_backward(), output of conv_forward()

Returns:
dX -- gradient of the cost with respect to input of the conv layer (X), numpy array of shape (n_H_prev, n_W_prev) assuming channels = 1
dW -- gradient of the cost with respect to the weights of the conv layer (W), numpy array of shape (f,f) assuming single filter
*/
/* Retrieving information from the "cache" */
// void cnn_conv_backward(CNN_Layer **l,int **dH)
// {
//     CNN_Neuron    *n_temp;
//     CNN_Dendritic *d_temp;
//     int *dH, *dX;
//     dH = malloc((*l) -> kernel_size * (*l) -> kernel_size * sizeof(int));
//     n_temp = (*l) -> neuron;
//     d_temp = n_temp -> dendritic;

// }

void cnn_rotate180(int *kernel,int kernel_size,int **k_r)
{
    k_r = malloc(kernel_size * kernel_size * sizeof(int));
    for (int i = 0;i < kernel_size;i++)
    {
        for (int j = 0;j < kernel_size;j++)
        {
            (*k_r)[(kernel_size - i - 1)*kernel_size + (kernel_size - j - 1)] = kernel[i*kernel_size + j];
        }
    }
}

    // // (X, W) = cache
    
    // /*Retrieving dimensions from X's shape */
    // (n_H_prev, n_W_prev) = X.shape
    
    // # Retrieving dimensions from W's shape
    // (f, f) = W.shape
    
    // # Retrieving dimensions from dH's shape
    // (n_H, n_W) = dH.shape
    
    // # Initializing dX, dW with the correct shapes
    // dX = np.zeros(X.shape)
    // dW = np.zeros(W.shape)
    
    // # Looping over vertical(h) and horizontal(w) axis of the output
    // for h in range(n_H):
    //     for w in range(n_W):
    //         dX[h:h+f, w:w+f] += W * dH(h,w)
    //         dW += X[h:h+f, w:w+f] * dH(h,w)
    
    // return dX, dW
