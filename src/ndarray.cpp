#include <iostream>
#include <vector>
#include <random>

class NDArray {
private:
    std::vector<size_t> shape;
    std::vector<size_t> strides;
    std::vector<double> data;
    size_t num_dim;

    size_t calculate_size() const {
        int size = 1;
        for (int i=0; i<num_dim; ++i) {
            size = size*shape[i];
        }
        return size;
    }

    void calculate_strides() {
        strides.resize(num_dim);
        strides[num_dim - 1] = 1;
        for (int i = num_dim - 2; i >= 0; --i) {
            strides[i] = strides[i + 1] * shape[i + 1];
        }
    }

    size_t calculate_index(std::vector<size_t> indices) const {
        if (indices.size() != num_dim) {
            throw std::runtime_error("The dimension of the indices do not match the dimension of array.");
        }
        size_t index = 0;
        for (int i=0; i<indices.size(); ++i) {
            if (indices[i] > shape[i]) {
                throw std::runtime_error("Index out of bound.");
            }
            index += indices[i]*strides[i];
        }
        return index;
    }

public:
    NDArray(std::vector<size_t> shape): shape(shape), num_dim(shape.size()) {
        data.resize(calculate_size());
        calculate_strides();
    }

    void takeInput() {
        std::cout<<"Keep entering the inputs one by one."<<std::endl;
        for (int i=0; i<calculate_size(); ++i) {
            std::cin >> data[i];
        }
        std::cout<<"Input completed. Printing sizes and shapes"<<std::endl;
        printShapeAndStrides();
    }

    double value(std::vector<size_t> indices) {
        return data[calculate_index(indices)];
    }    

    void printArray() {
        throw std::runtime_error("Print function not implemented yet.");
    }

    void printShapeAndStrides() const {
        std::cout<<"size: "<<calculate_size()<<std::endl;
        std::cout<<"Strides: {";
        for (int i=0; i<num_dim; ++i) {
            std::cout<<strides[i]<<",";
        }
        std::cout<<"} \n";

        std::cout<<"Shape: {";
        for (int i=0; i<num_dim; ++i) {
            std::cout<<shape[i]<<",";
        }
        std::cout<<"} \n";
    }



};

int main() {
    NDArray arr({2,2});
    arr.takeInput();
    std::cout << arr.value({1,1}) << std::endl;
}