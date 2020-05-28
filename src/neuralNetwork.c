#include "../include/neuralNetwork.h"

int  random_number(int min_num,int max_num);
void ann_layer_calc(rnn_layer **l,int *input,int cnn_size_output,int *target);
void ann_layer_cnn(rnn_layer **l,int CNN_width,int CNN_height,int CNN_neuron ,int neuron_number);
void ann_layer_add(rnn_layer **l,int neuron_number);
void ann_layer_malloc(rnn_layer **layer);
void ann_layer_first(rnn_layer **l, int neuron_number, int input_number);

void ann_matriz_calc(int *a,int *b,int **c,int a_r,int b_r,int b_c);
int  ann_mse(int *labels,int *output,int **error,int o_size);
void ann_relu(int **input,int neuron_number);
void ann_relu_derivate(int *out,int **dS,int out_number);
void ann_transpose(int *a,int **b,int a_r,int a_c);
void ann_constant(int **a,int b,int width);
void ann_hadamart(int *a,int *b,int **c,int i);
void ann_relu_derivate(int *out,int **dS,int out_number);
void ann_train(rnn_layer **l,int *targets,int *input);
void ann_sub(int *a,int *b,int **c, int width);
void ann_sum(int **a,int *b,int size);
void ann_hidden_error(int *gradient,int *kernel_next, int **error, int o_size_next,int o_size);
int *ann_update_kernel(rnn_layer **last,int *gradient,int *input);

// example of use: int x = random_number(0,255);
int random_number(int min_num,int max_num)
{
    int result = 0, low_num = 0, high_num = 0;
    low_num    = (min_num < max_num) ? min_num : max_num + 1;
    high_num   = (min_num > max_num) ? min_num : max_num + 1;
    result     = (rand() % (high_num - low_num)) + low_num;
    return result;
}

void ann_layer_cnn(rnn_layer **l,int CNN_width,int CNN_height,int CNN_neuron ,int neuron_number)
{
    rnn_layer *l_temp;
    ann_layer_malloc(&l_temp);
    l_temp -> prev = NULL;
    l_temp -> next = NULL;
    l_temp -> input_number = CNN_width * CNN_height * CNN_neuron;
    l_temp -> neuron_number = neuron_number;
    l_temp -> kernel = malloc(neuron_number * (l_temp -> input_number + 1) * sizeof(int));
    l_temp -> output = malloc(neuron_number * sizeof(int));
    for(int i = 0;i < neuron_number * (l_temp -> input_number + 1);i++)
    {
        l_temp -> kernel[i] = random_number(_ONE,ONE);
    }
    (*l) = l_temp;
}

void ann_layer_first(rnn_layer **l, int neuron_number, int input_number)
{
    rnn_layer *l_temp;
    ann_layer_malloc(&l_temp);
    l_temp -> prev          = NULL;
    l_temp -> next          = NULL;
    l_temp -> input_number  = input_number;
    l_temp -> neuron_number = neuron_number;
    l_temp -> kernel = malloc(neuron_number * (l_temp -> input_number + 1) * sizeof(int));
    l_temp -> output = malloc(neuron_number * sizeof(int));
    for(int i = 0;i < neuron_number * (l_temp -> input_number + 1);i++)
    {
        l_temp -> kernel[i] = random_number(_ONE,ONE);
    }
    (*l) = l_temp;
}

void ann_layer_add(rnn_layer **l,int neuron_number)
{
    rnn_layer *l_temp;
    rnn_layer *l_last;
    ann_layer_malloc(&l_temp);
    l_last = (*l);
    while(l_last -> next != NULL)
    {
        l_last = l_last -> next;
    }
    l_temp -> prev                  = l_last;
    l_temp -> input_number          = l_last -> neuron_number;
    l_temp -> neuron_number         = neuron_number;
    l_temp -> kernel                = malloc((l_last -> neuron_number + 1) * l_temp -> neuron_number * sizeof(int));
    l_temp -> output                = malloc(l_temp -> neuron_number * sizeof(int));
    l_temp -> output[neuron_number] = ONE;
    for(int i = 0;i < (l_last -> neuron_number + 1) * l_temp -> neuron_number;i++)
    {
        l_temp -> kernel[i] = random_number(_ONE,ONE);
    }
    l_last -> next = l_temp;
}

void ann_layer_malloc(rnn_layer **layer)
{
    (*layer)           = malloc(sizeof(rnn_layer));
    (*layer) -> next   = malloc(sizeof(rnn_layer));
    (*layer) -> prev   = malloc(sizeof(rnn_layer));
    (*layer) -> next   = NULL;
    (*layer) -> prev   = NULL;
}

void ann_layer_calc(rnn_layer **l,int *input,int cnn_size_output,int *target)
{
    rnn_layer  *l_last;
    int *img;
    l_last               = (*l);
    img                  = malloc((cnn_size_output + 1) * sizeof(int));
    img                  = input;
    img[cnn_size_output] = ONE;
    ann_matriz_calc(l_last -> kernel, img,&(l_last -> output),l_last -> neuron_number,l_last -> input_number + 1,1);
    if(l_last -> next != NULL)
    {
        l_last = l_last -> next;
        while(l_last -> next != NULL)
        {
            free(img);
            int *img = malloc((l_last -> prev -> input_number + 1)*sizeof(int));
            img = l_last -> prev -> output;
            img[l_last -> prev -> input_number] = ONE;
            ann_matriz_calc
            (
                l_last -> kernel,
                img,
                &(l_last -> output),
                l_last -> neuron_number,
                l_last -> input_number,
                1
            );
            l_last = l_last -> next;
        }
        free(img);
        int *img = malloc((l_last -> input_number + 1) * sizeof(int));
        img = l_last -> prev -> output;
        img[l_last -> input_number] = ONE;
        ann_matriz_calc(l_last -> kernel,l_last -> prev -> output,&(l_last -> output),l_last -> neuron_number,l_last -> input_number,1);
    }
    ann_train(l,target,input);
}

void ann_relu(int **input,int neuron_number)
{
    for(int i = 0;i < neuron_number;i++)
    {
        (*input)[i] = ((*input)[i] < 0) ? 0 : (*input)[i];
    }
}

void ann_matriz_calc(int *a,int *b,int **c,int a_r,int b_r,int b_c)
{
    /* a = l x m : a_r x b_r *
    ** b = m x n : b_r x b_c *
    ** c = l x n : a_r x b_c */
    int pos = 0, i = 0, j = 0, k = 0;
    int soma = 0;
    for (i = 0;i < a_r;i++)
    {
        for (j = 0;j < b_c;j++)
        {
            soma = 0;
            for(k = 0;k < b_r;k++)
            {
                soma += (a[i*b_r + k] * b[k*b_c + j]) / ONE;
            }
            (*c)[pos] = soma;
            pos++;
        }
    }
}

int  next_power_2(int number)
{
    int pot = 0;
    while(number / 2 > 2)
    {
        pot++;
        number /= 2;
    }
    return (number == 0) ? pot : pot + 1;
}

void complex_mult(int a_r,int a_i,int b_r,int b_i,int *r_r,int *r_i)
{
    *r_r = a_r*b_r - a_i*b_i;
    *r_i = a_r*b_i + a_i*b_r;
}

/* Artigo : DeLTA: GPU Performance Model for Deep Learning Applications with In-depth Memory System Traffic Analysis 
 * https://leonardoaraujosantos.gitbooks.io/artificial-inteligence/content/making_faster.html
 * https://blog.usejournal.com/understanding-winograd-fast-convolution-a75458744ff
 * cd : "file:///C:/Users/usuario/Documents/Library/DeLTA_GPU_Performance_Model_for_Deep_Learning_Appl.pdf"
*/
// void im2col(int *img,int img_width,int img_height,int number_img,int **out,int *out_width,int *out_height)
// {
//     out_width = number_img * 
//     out = malloc()
//     for(int o_r = 0;o_r < out_height;o_r++)
//     {
//         for(int o_c = 0;o_c < out_width;o_c++)
//         {
//         for (int i = 0;i < img_height;i++)
//             {
//                 for (int j = 0;j < img_width;j++)
//                 {
//                     out[o_r * out_width + o_r] = img[(i + o_r)*img_width + (j + o_c)];
//                 }
//             }
//         }
//     }
// }

int  ann_mse(int *labels,int *output,int **error,int o_size)
{
    int mse = 0;
    for(int i = 0;i < o_size;i++)
    {
        (*error)[i]  = labels[i] - output[i];
        (*error)[i] *= (*error)[i];
        (*error)[i] /= ONE;
        (*error)[i] /= 2;
        mse         += (*error)[i]/2;
    }
    return mse;
}

void ann_relu_derivate(int *out,int **dS,int out_number)
{
    for(int i = 0;i < out_number;i++)
    {
        (*dS)[i] = (out[i] < 0) ? 0 : ONE;
    }
}

void ann_transpose(int *a,int **b,int a_r,int a_c)
{
    for(int i = 0;i < a_r*a_c;i++)
    {
        for (int j = 0;j < a_c;j++)
        {
            (*b)[j*a_r + i] = a[i*a_c + j];
        }
    }
}

void ann_constant(int **a,int b,int width)
{
    for(int i = 0;i < width;i++)
    {
        (*a)[i] *= b;
        (*a)[i] /= ONE;
        (*a)[i] += 1;
    }
}

void ann_hadamart(int *a,int *b,int **c,int width)
{
    for(int i = 0;i < width;i++)
    {
        (*c)[i] = (a[i] * b[i]) / ONE;
    }
}

void ann_train(rnn_layer **l,int *targets,int *input)
{
    rnn_layer  *last;
    last       = (*l);
    while(last -> next != NULL){last = last -> next;}
    int i_size = last -> input_number + 1, o_size = last -> neuron_number;
    int max    = i_size * o_size;
    int *error, *d_output, *hidden, *gradient, *d_w;
    error    = malloc(o_size * sizeof(int));
    d_output = malloc(o_size * sizeof(int));
    gradient = malloc(o_size * sizeof(int));
    hidden   = malloc(i_size * sizeof(int));
    d_w      = malloc(max * sizeof(int));
    if(last -> prev != NULL)
    {
        hidden = last -> prev -> output;
    } else {
        hidden = input;
    }
    hidden[i_size] = ONE;
    ann_sub(last -> output,targets,&error,o_size);
    ann_relu_derivate(last -> output,&d_output,o_size);
    ann_hadamart(error,d_output,&gradient,o_size);
    ann_matriz_calc(gradient,hidden,&d_w,o_size,1,i_size);
    ann_constant(&d_w,LR,max);
    ann_sum(&(last -> kernel),d_w,max);
    if(last -> prev == NULL)
    {
        return;
    }
    last = last -> prev;
    while(last -> prev != NULL)
    {
        int *temp_gradient = malloc(last -> neuron_number * sizeof(int));
        temp_gradient = ann_update_kernel(&last,gradient,last -> prev -> output);
        free(gradient);
        gradient = realloc(gradient,last -> neuron_number * sizeof(int));
        gradient = temp_gradient;
        last = last -> prev;
    }
    gradient = ann_update_kernel(&last,gradient,input);
}

int *ann_update_kernel(rnn_layer **last,int *gradient,int *input)
{
    int i_size     = (*last) -> input_number + 1;
    int o_size     = (*last) -> neuron_number;
    int max        = i_size * o_size;
    int *error     = malloc(o_size * sizeof(int));
    int *d_output  = malloc(o_size * sizeof(int));
    int *gradient2 = malloc(o_size * sizeof(int));
    int *d_w       = malloc(i_size * o_size * sizeof(int));
    ann_hidden_error(gradient,(*last) -> next -> kernel,&error,(*last) -> next -> neuron_number,o_size);
    ann_relu_derivate((*last) -> output,&d_output,o_size);
    ann_hadamart(error,d_output,&gradient2,o_size);
    ann_matriz_calc(gradient2,input,&d_w,o_size,1,i_size);
    ann_constant(&d_w,LR,max);
    ann_sum(&((*last) -> kernel),d_w,max);
    free(d_w);
    free(error);
    free(d_output);
    return gradient2;
}

void ann_hidden_error(int *gradient,int *kernel_next, int **error, int o_size_next,int o_size)
{
    for(int i = 0;i < o_size;i++)
    {
        (*error)[i] = 0;
        for(int j = 0;j < o_size_next;j++)
        {
            (*error)[i] += kernel_next[i*o_size + j];
        }
        (*error)[i] *= gradient[i];
    }
}

void ann_kernel_column(int *kernel,int **out,int i_size,int o_size,int m)
{
    for(int i = 0;i < o_size;i++)
    {
        (*out)[i] = kernel[i*i_size + m];
    }
}

void ann_sub(int *a,int *b,int **c, int width)
{
    for(int i = 0;i < width;i++)
    {
        (*c)[i] = a[i] - b[i];
    }
}

void ann_sum(int **a,int *b,int size)
{
    for(int i = 0;i < size;i++)
    {
        (*a)[i] += b[i];
    }
}