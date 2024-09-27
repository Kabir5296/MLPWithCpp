#include <iostream>
#include "matrix.h"
#include "layer.h"

/*
Not implemented:
    1. Backward
    2. Load state dict
*/

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

Matrix Layer::updateBiasMatrixForBatch(int batch_size, Matrix bias) {
    /*
    In case for batch_size greater than one, the bias matrix is extended in dimension and copied for all columns.
    batch_size : number of input data points for each batch.
    bias : bias matrix for single input.
    */
    std::cout<<"batching biases for better calculation"<<std::endl;
    bias = bias.transpose();
    for (int i =0; i<batch_size-1; i++) {
        bias.data.push_back(bias.data[0]);
    }
    bias = bias.transpose();
    return bias;
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
        bias = updateBiasMatrixForBatch(batch_size, bias);

    Matrix result = bias.addition(weight.multiplication(inputMatrix));
    return result;
}

void Layer::printWeight() {
    weight.printMatrix();
}

void Layer::printBias() {
    bias.printMatrix();
}

void Layer::printLayer() {
    std::cout<<"Layer of dimension "<<input_dim<<" X "<<output_dim<<std::endl;
    std::cout<<"\n Weights are: \n"<<std::endl;
    weight.printMatrix();
    std::cout<<"\n Biases are: \n"<<std::endl;
    bias.printMatrix();
    std::cout<<"\n"<<std::endl;
}

void testLayer() {
    int layer_input_size, layer_output_size, input_feature_size, input_batch_size;
    
    std::cout << "Enter layer input size" << std::endl;
    std::cin >> layer_input_size;

    std::cout << "Enter layer output size" << std::endl;
    std::cin >> layer_output_size;

    std::cout << "Enter input feature size" << std::endl;
    std::cin >> input_feature_size;

    std::cout << "Enter batch size" << std::endl;
    std::cin >> input_batch_size;

    std::cout << "Initializing layer and input matrix" << std::endl;

    Layer input(layer_input_size, layer_output_size);
    Matrix inputs(input_feature_size,input_batch_size);

    std::cout << "WEIGHT" << '\n';
    input.printWeight();

    std::cout << "BIAS" << '\n';
    input.printBias();

    std::cout<< "Matrix input initialized" << '\n';
    inputs.randomInit(-1,1);
    inputs.printMatrix();
    
    std::cout<< "Forward Pass" << '\n';
    inputs = input.forward(inputs);
    inputs.printMatrix();

    std::cout<< "LAYERS CODE RUN SUCCESSFUL" << '\n';
}

// int main() {
//     testLayer();
//     return 0;
// }