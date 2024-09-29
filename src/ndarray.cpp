#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <random>
#include <optional>

class NDArray {
private:
    std::vector<size_t> shape;
    std::vector<size_t> strides;
    std::vector<double> data;
    size_t num_dim;

    size_t calculateSize(std::vector<size_t> shape) const {
        size_t size = 1;
        for (size_t i=0; i<num_dim; ++i) {
            size = size*shape[i];
        }
        return size;
    }

    std::vector<size_t> calculateStrides(size_t num_dim, std::vector<size_t> shape) const {
        std::vector<size_t> strides;
        strides.resize(num_dim);
        strides[num_dim - 1] = 1;
        for (size_t i = num_dim - 2; i >= 0; --i) {
            strides[i] = strides[i + 1] * shape[i + 1];
        }
        return strides;
    }

    size_t calculateIndex(std::vector<size_t> indices) const {
        if (indices.size() != num_dim) {
            throw std::runtime_error("The dimension of the indices do not match the dimension of array.");
        }
        size_t index = 0;
        for (size_t i=0; i<indices.size(); ++i) {
            if (indices[i] > shape[i]) {
                throw std::runtime_error("Index out of bound.");
            }
            index += indices[i]*strides[i];
        }
        return index;
    }

    std::vector<size_t> indexToIndices(size_t flatIndex) const {
        std::vector<size_t> indices(num_dim);
        
        for (size_t i = 0; i < num_dim; ++i) {
            indices[i] = flatIndex / strides[i];
            flatIndex %= strides[i];
        }
        
        return indices;
    }

public:
    NDArray(std::vector<size_t> shape): shape(shape), num_dim(shape.size()), strides(calculateStrides(num_dim, shape)) {
        data.resize(calculateSize(shape));
    }

    void takeInput() {
        std::cout<<"Keep entering the inputs one by one."<<std::endl;
        for (size_t i=0; i<calculateSize(shape); ++i) {
            std::cin >> data[i];
        }
        std::cout<<"Input completed. Printing sizes and shapes"<<std::endl;
        printShapeAndStrides();
    }

    void reshape(std::vector<size_t> new_shape) {
        if (calculateSize(new_shape) != calculateSize(shape)) {
            throw std::runtime_error("The new shape can't be applied");
        }
        shape = new_shape;
        num_dim = new_shape.size();
        strides = calculateStrides(num_dim, new_shape);
    }

    void transpose() {
        std::vector<size_t> oldShape = shape;
        std::vector<size_t> oldStrides = strides;

        std::reverse(shape.begin(), shape.end());
        strides = calculateStrides(num_dim, shape);
        
        std::vector<double> transpose_data(data.size());

        for (size_t i=0; i<data.size(); ++i) {
            std::vector <size_t> oldIndices = indexToIndices(i);
            std::reverse(oldIndices.begin(), oldIndices.end());
            size_t newIndex = calculateIndex(oldIndices);
            transpose_data[newIndex] = data[i];            
        }
        data = std::move(transpose_data);
    }

    void zeroInit() {
        std::fill(data.begin(), data.end(), 0.0);
    }

    void randomInit(double min=-0.1, double max=0.1, std::optional<unsigned> seed = std::nullopt) {
        std::default_random_engine gen;
        if (seed) 
            gen.seed(*seed);
        else {           
            std::random_device rd;
            gen.seed(rd());
        }
        std::uniform_real_distribution<double> dis(min, max);
        std::generate(data.begin(), data.end(), [&]() {return dis(gen);});
    }

    double operator[](std::vector<size_t> indices) {
        return data[calculateIndex(indices)];
    }    

    void printArray() {
        throw std::runtime_error("Print function not implemented yet.");
    }

    void printShapeAndStrides() const {
        std::cout<<"size: "<<calculateSize(shape)<<std::endl;
        std::cout<<"Strides: {";
        for (size_t i=0; i<num_dim; ++i) {
            std::cout<<strides[i]<<",";
        }
        std::cout<<"} \n";

        std::cout<<"Shape: {";
        for (size_t i=0; i<num_dim; ++i) {
            std::cout<<shape[i]<<",";
        }
        std::cout<<"} \n";
    }

};

// int main() {
//     NDArray arr({2,2});
//     arr.takeInput();
//     std::cout << arr[{1,1}] << std::endl;
// }