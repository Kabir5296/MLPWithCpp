#include <iostream>
#include "src/matrix.h"
#include "src/layer.h"

int main() {
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

    std::cout<< "CODE RUN SUCCESSFUL" << '\n';
}