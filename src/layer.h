#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include "matrix.h"

class Layer {
public:
    Matrix weight;
    Matrix bias;
    int input_dim, output_dim;
    Layer(int input_dim, int output_dim);
    Matrix updateBiasMetrixForBatch(int batch_size, Matrix bias);
    Matrix forward(Matrix inputMatrix);
    void printWeight();
    void printBias();
};

#endif