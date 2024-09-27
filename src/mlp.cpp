#include "iostream"
#include "layer.h"
#include "matrix.h"
#include <vector>
#include "mlp.h"

MultiLayerPerceptron::MultiLayerPerceptron(int input_size, int output_size, std::vector <int> hidden_size) : input_size(input_size), output_size(output_size), hidden_size(hidden_size) {
    layers.push_back(Layer(input_size, hidden_size[0]));

    for (int i=1; i<hidden_size.size(); i++) {
        layers.push_back(Layer(hidden_size[i-1], hidden_size[i]));
    }
    layers.push_back(Layer(hidden_size.back(), output_size));
}

Matrix MultiLayerPerceptron::forward(Matrix input_data) {
    int num_layers = layers.size();
    for (int i=0; i<num_layers; i++) {
        input_data = layers[i].forward(input_data);
    }
    return input_data;
}

void MultiLayerPerceptron::printMLP() {
    for (int i=0; i < layers.size(); i++) {
        layers[i].printLayer();
    }
}

void testMLP() {
    int input_size, output_size, batch_size;

    std::cout<<"Enter input size"<<std::endl;
    std::cin>>input_size;

    std::cout<<"Enter output size"<<std::endl;
    std::cin>>output_size;

    std::cout<< "Create a MLP of "<<input_size<<"  input size, "<<output_size<<" output size and {5,6,7,8,9,10} hidden sizes" << '\n';
    MultiLayerPerceptron newMlp(input_size,output_size,{5,6,7,8,9,10});
    newMlp.printMLP();

    std::cout<< "MLP Define DONE" << '\n';

    std::cout<<"Enter batch size"<<std::endl;
    std::cin>>batch_size;

    Matrix input_data(input_size, batch_size);

    std::cout<< "Going Forward" <<std::endl;
    Matrix result = newMlp.forward(input_data);
    result.printMatrix();

    std::cout<< "MLP forward DONE" << '\n';
}

// int main() {
//     testMLP();
//     return 0;
// }