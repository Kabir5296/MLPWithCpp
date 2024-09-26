#include <iostream>
#include "src/matrix.h"

int main() {
    Matrix demo(6,2), demo2(2,2);

    std::cout << "Input Matrix 1"<<std::endl;
    
    demo.randomInit(-3,4);
    demo.printMatrix();

    std::cout << "Another" << std::endl;

    demo2.randomInit();
    demo2.printMatrix();

    // std::cout << "Input Matrix 2"<<std::endl;
    
    // demo2.takeInput();

    // Matrix sum = demo.addition(demo2);

    // Matrix mul = demo.multiplication(demo2);

    // std::cout << "Sum"<<std::endl;
    // sum.printMatrix();

    // std::cout << "Mul"<<std::endl;
    // mul.printMatrix();

    // std::cout << "Transpose"<<std::endl;
    // demo.transpose().printMatrix();
    
    return 0;
}