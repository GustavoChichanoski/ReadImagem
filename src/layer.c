#include "../include/layer.h"

typedef struct layer
{
    int *input;
    int *output;
    int *weigth;
    int  number_neuron;
    int  input_number;
    int  output_number;
} Layer;

Layer Dense(int units,int activation,int bias);

Layer createLayer()
{
    Layer *l;
    l = (Layer *) malloc(sizeof(Layer));
}

Layer Dense(int units,int activation,int bias)
{
    Layer = createLayer
}