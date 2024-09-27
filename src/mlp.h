#include "iostream"
#include "layer.h"
#include "matrix.h"
#include <vector>

class MultiLayerPerceptron {
public:
    int input_size, output_size;
    std::vector <int> hidden_size;
    std::vector <Layer> layers;
    MultiLayerPerceptron(int input_size, int output_size, std::vector <int> hidden_size);
    Matrix forward(Matrix input_data);
    void printMLP();
};