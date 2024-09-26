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

void MultiLayerPerceptron::printMLP() {
    for (int i=0; i < layers.size(); i++) {
        layers[i].printLayer();
    }
}