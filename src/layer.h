#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include "matrix.h"
#include <string.h>
#include <functional>

class Layer {
public:
    Matrix weight;
    Matrix bias;
    std::function<Matrix(Matrix)> activation;
    int input_dim, output_dim;
    Layer(int input_dim, int output_dim, std::function<Matrix(Matrix)> activation);
    Matrix updateBiasMatrixForBatch(int batch_size, Matrix bias);
    Matrix forward(Matrix inputMatrix);
    Matrix activationDummy(Matrix input_matrix);
    void printWeight();
    void printBias();
    void printLayer();
};

#endif