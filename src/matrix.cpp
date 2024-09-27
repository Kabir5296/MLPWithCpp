#include <iostream>
#include "matrix.h"
#include <random>

/*
Not implemented:
    1. Zeros matrix
    2. Ones matrix
    3. Elementwise multiplication
*/

Matrix::Matrix(int num_rows, int num_columns): num_rows(num_rows), num_columns(num_columns) {
    data.resize(num_rows);
    for (int i = 0; i < num_rows; i++) {
        data[i].resize(num_columns);
    }
}

Matrix Matrix::addition(const Matrix& other) {
    if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
        std::cout<<"Matrix 1 has dimension "<<data.size()<<"x"<<data[0].size()<<std::endl;
        std::cout<<"Matrix 2 has dimension "<<other.data.size()<<"x"<<other.data[0].size()<<std::endl;
        throw std::runtime_error("Matrix dimensions do not match");
    }
    
    Matrix result(data.size(), data[0].size());

    for (size_t i=0; i<data.size(); i++) {
        for (size_t j=0; j<data[0].size(); j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::multiplication(const Matrix& other) {
    if (data[0].size() != other.data.size()) {
        std::cout<<"Matrix 1 has dimension "<<data.size()<<"x"<<data[0].size()<<std::endl;
        std::cout<<"Matrix 2 has dimension "<<other.data.size()<<"x"<<other.data[0].size()<<std::endl;
        throw std::runtime_error("Matrix dimensions do not match for multiplication");
    }
    
    Matrix result(data.size(), other.data[0].size());

    for (int i=0; i< data.size(); i++) {
        for (int j=0; j<other.data[0].size(); j++) {
            int value = 0;
            for (int k=0; k<data[0].size(); k++) {
                value += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = value;
        }
    }

    return result;
}

Matrix Matrix::transpose() {
    Matrix result(data[0].size(), data.size());

    for (size_t i=0; i<data.size(); i++) {
        for (size_t j=0; j<data[0].size(); j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

void Matrix::randomInit(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);

    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            data[i][j] = dis(gen);
        }
    }
}

Matrix Matrix::mulElementWise(const Matrix& other) {
    if (num_rows != other.num_rows || num_columns != other.num_columns) {
        throw std::runtime_error("The dimension of the matrices must be same for elementwise operation.");
    }
    Matrix result(num_rows, num_columns);
    for (int i=0; i<num_rows; i++) {
        for (int j=0; j<num_columns; j++) {
            result.data[i][j] = data[i][j] * other.data[i][j];
        }
    }
    return result;
}

void Matrix::takeInput() {
    for (int i=0; i < data.size(); i++) {
        for (int j=0; j< data[0].size(); j++) {
            std::cin >> data[i][j];
    }
}
}

void Matrix::printMatrix() {
    for (int i=0; i < data.size(); i++) {
        for (int j=0; j < data[0].size(); j++) {
            std::cout << data[i][j]<< " ";
        }
        std::cout<<"\n";
}
}

void testMatrics() {
    Matrix abdul(4,5), kuddus(4,5);
    abdul.randomInit();
    kuddus.randomInit();

    std::cout << "Testing matrics addition" << std::endl;
    abdul.addition(kuddus);
    kuddus.addition(abdul);
    std::cout << "Addition occured no errors" << std::endl;

    std::cout << "Testing matrics transpose" << std::endl;
    abdul.transpose();
    kuddus.transpose();
    std::cout << "Transpose occured no errors" << std::endl;

    std::cout << "Testing matrics Element Wise Mul" << std::endl;
    abdul.mulElementWise(kuddus);
    kuddus.mulElementWise(abdul);
    std::cout << "Element Wise Mul occured no errors" << std::endl;

    std::cout << "Testing matrics multiplication" << std::endl;
    abdul.multiplication(kuddus.transpose());
    kuddus.multiplication(abdul.transpose());
    std::cout << "Addition occured no errors" << std::endl;
}

// int main() {
//     testMatrics();
//     return 0;
// }