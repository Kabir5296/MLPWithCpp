#include <iostream>
#include <vector>
#include "matrix.h"
#include <functional>
#include "layer.h"

Layer::Layer(int input_dim, int output_dim): input_dim(input_dim), output_dim(output_dim), weight(output_dim, input_dim), bias(output_dim, 1) {
    /*
    input_dim : number of features from input layer or number of neurons from previous layer.
    output_dim : number of neurons of current layer.
    weight : weight matrix. the dimension is output_dim X input_dim.
    bias : bias matrix. the dimension (for batch size 1, which is default) is output_dim X 1.
    */
    weight.randomInit(-0.1, 0.1);
    bias.randomInit(-0.1,0.1);
}

Matrix Layer::updateBiasMetrixForBatch(int batch_size, Matrix bias) {
    /*
    In case for batch_size greater than one, the bias matrix is extended in dimension and copied for all columns.
    batch_size : number of input data points for each batch.
    bias : bias matrix for single input.
    */
    Matrix biasNew(output_dim, batch_size);
    for (int i=0; i<output_dim; i++) {
        for (int j=0; j<batch_size; j++) {
            biasNew.data[i][j] = bias.data[i][0];
        }
    }
    return biasNew;
}

Matrix Layer::forward(Matrix inputMatrix) {
    /*
    forward propagation, implementation of Wx + b.
    if batch size is greater than 1, the bias matrix is updated.
    */
    if (input_dim != inputMatrix.data.size()) {
        throw std::runtime_error("The input layer size and the first dimension of weights don't match");
    } 
    int batch_size = inputMatrix.data[0].size();
    if (batch_size > 1) 
        bias = updateBiasMetrixForBatch(batch_size, bias);

    Matrix result = bias.addition(weight.multiplication(inputMatrix));
    return result;
}

void Layer::printWeight() {
    weight.printMatrix();
}

void Layer::printBias() {
    bias.printMatrix();
}