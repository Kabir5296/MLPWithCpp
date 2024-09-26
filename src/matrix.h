#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>


class Matrix {
public:
    std::vector<std::vector<float>> data;
    Matrix(int num_rows, int num_columns);
    Matrix addition(const Matrix& other);
    Matrix multiplication(const Matrix& other);
    Matrix transpose();
    void randomInit(float min = -0.1, float max = 0.1);
    void takeInput();
    void printMatrix();
};

#endif