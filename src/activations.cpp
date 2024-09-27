#include "matrix.h"
#include <iostream>
#include <cmath>

Matrix relu(Matrix input_matrix) {
    for (int i=0; i<input_matrix.num_rows; i++) {
        for (int j=0; j<input_matrix.num_columns; j++) {
            if (input_matrix.data[i][j] < 0) {
                input_matrix.data[i][j] = 0;
            }
        }
    }
    return input_matrix;
}

Matrix sigmoid(Matrix input_matrix) {
    for (int i=0; i<input_matrix.num_rows; i++) {
        for (int j=0; j<input_matrix.num_columns; j++) {
            input_matrix.data[i][j] = 1 / (1 + exp(-(input_matrix.data[i][j])));
        }
    }
    return input_matrix;
}

Matrix sigmoid(Matrix input_matrix) {
    for (int i=0; i<input_matrix.num_rows; i++) {
        for (int j=0; j<input_matrix.num_columns; j++) {
            float x = input_matrix.data[i][j];
            input_matrix.data[i][j] = (exp(x) - exp(-x))/(exp(x) + exp(-x));
        }
    }
    return input_matrix;
}

void testActivations() {
    Matrix a(4,5);
    a.takeInput();
    
    std::cout<<"testing Relu"<<std::endl;
    relu(a).printMatrix();

    std::cout<<"testing Sigmoid"<<std::endl;
    sigmoid(a).printMatrix();
}

// int main() {
//     testActivations();
//     return 0;
// }