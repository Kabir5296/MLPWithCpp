#include <iostream>
#include <vector>
#include "matrix.h"
#include <functional>

class Layer {
public:
    Matrix weight;
    Matrix bias;
    int input_dim, output_dim;

    Layer(int input_dim, int output_dim): input_dim(input_dim), output_dim(output_dim), weight(output_dim, input_dim), bias(output_dim, 1) {
        weight.randomInit(-0.1, 0.1);
        bias.randomInit(-0.1,0.1);
    }

    Matrix forward(Matrix inputMatrix) {
        Matrix result(input_dim, output_dim);
        result = bias.addition(weight.multiplication(inputMatrix));
        return result;
    }

    void printWeight() {
        weight.printMatrix();
    }

    void printBias() {
        bias.printMatrix();
    }
};

int main() {
    Layer input(4, 9);
    Matrix inputs(4,1);

    std::cout<<"WEIGHT"<<std::endl;
    input.printWeight();

    std::cout<<"BIAS"<<std::endl;
    input.printBias();

    std::cout<< "Matrix input initialized" << std::endl;
    inputs.randomInit(-1,1);
    inputs.printMatrix();
    
    std::cout<< "Forward Pass" << std::endl;
    inputs = input.forward(inputs);
    inputs.printMatrix();
}