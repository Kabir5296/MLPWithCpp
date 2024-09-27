#include "matrix.h"
#include <iostream>

Matrix activationReLU(Matrix input_matrix) {
    for (int i=0; i<input_matrix.num_rows; i++) {
        for (int j=0; j<input_matrix.num_columns; j++) {
            if (input_matrix.data[i][j] < 0) {
                input_matrix.data[i][j] = 0;
            }
        }
    }
    return input_matrix;
}