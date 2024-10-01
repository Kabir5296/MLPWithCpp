#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <optional>
#include <stdexcept>
#include <functional>

/*
n-Dimensional array implementation in C++.
How it works:
    Uses shapes and strides for n-Dim array, the actual array is saved in an 1D array in the memory.
Methods:
    calculateSize: calculates size of the 1D representation of an n-D array.
    calculateStrides: Given a shape, calculates the strides array.
    calculateIndex: Converts a given index in the n-Dim array to position in the 1D representation.
    indexToIndices: Does the exact reverse of the previous.
    T: Transpose function to be applied on current data. **Currently only implemented full transpose.**
    transpose: Transpose function to be used on external data. **Currently only implemented full transpose.**
    reshape: Reshaping the n-Dim array.
    zeroInit: Initializes the array with all 0 values.
    randomInit: Initializes the array with random values.
    operator[]: Uses [] operator to access array elements. i.e., arr[{i,j,k}] for a 3D array.
*/

template<typename T>
class NDArray {
private:
    std::vector<size_t> shape;
    std::vector<size_t> strides;
    std::vector<T> data;
    size_t num_dim;

    size_t calculateSize(std::vector<size_t> shape) const {
        size_t size = 1;
        for (size_t i=0; i<num_dim; ++i) {
            size = size*shape[i];
        }
        return size;
    }

    static std::vector<size_t> calculateStrides(size_t num_dim, std::vector<size_t> shape) {
        std::vector<size_t> strides;
        strides.resize(num_dim);
        strides[num_dim - 1] = 1;
        for (int i = static_cast<int>(num_dim) - 2; i >= 0; --i) {
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

    void printVector() const {
        std::cout << "[" ;
        for (size_t i=0; i<shape.size(); ++i) {
            std::cout << data[i] << "," <std::endl;
        }
        std::cout << "]" << std::endl;
    }

public:
    NDArray(std::vector<size_t> shape): shape(shape), num_dim(shape.size()), strides(calculateStrides(shape.size(), shape)) {
        data.resize(calculateSize(shape));
    }

    std::vector<size_t> getShape() {
        return shape;
    }

    std::vector<size_t> getStrides() {
        return strides;
    }

    size_t getDims() {
        return num_dim;
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

    bool operator==(const NDArray& other) const {
        if (data.size() != other.data.size() || shape != other.shape)
            return false;
        return std::equal(data.begin(), data.end(), other.data.begin());
    }

    bool operator!=(const NDArray& other) const {
        return !(*this == other);
    }

    void transposeInPlace() {
        std::vector<size_t> oldShape = shape;
        std::vector<size_t> oldStrides = strides;

        std::reverse(shape.begin(), shape.end());
        strides = calculateStrides(num_dim, shape);
        
        std::vector<T> transposeData(data.size());
        std::vector<size_t> oldIndices(num_dim,0);

        for (size_t i=0; i<data.size(); ++i) {
            oldIndices = indexToIndices(i);
            std::reverse(oldIndices.begin(), oldIndices.end());
            size_t newIndex = calculateIndex(oldIndices);
            transposeData[newIndex] = data[i];            
        }
        data = std::move(transposeData);
    }

    static NDArray transpose(NDArray arr) {
        std::vector<size_t> oldShape = arr.shape;
        std::vector<size_t> oldStrides = arr.strides;

        std::reverse(arr.shape.begin(), arr.shape.end());
        arr.strides = calculateStrides(arr.num_dim, arr.shape);
        
        std::vector<T> transposeData(arr.data.size());
        std::vector<size_t> oldIndices(arr.num_dim,0);

        for (size_t i=0; i<arr.data.size(); ++i) {
            oldIndices = indexToIndices(i);
            std::reverse(oldIndices.begin(), oldIndices.end());
            size_t newIndex = calculateIndex(oldIndices);
            transposeData[newIndex] = arr.data[i];            
        }
        arr.data = std::move(transposeData);
        return arr;
    }

    static std::vector<size_t> broadcastShape(std::vector<size_t> biggerShape, std::vector<size_t> smallerShape) {
        if (biggerShape.size() < smallerShape.size())
            std::swap(biggerShape, smallerShape);

        smallerShape.insert(smallerShape.begin(), biggerShape.size() - smallerShape.size(),1);
        const size_t maxDim = smallerShape.size();
        std::vector<size_t> newShape(maxDim);

        for (size_t i=0; i<maxDim; ++i) {
            const size_t smallDim = smallerShape[maxDim -i -1];
            const size_t bigDim = biggerShape[maxDim -i -1];

            if (smallDim  == bigDim) {
                newShape[maxDim -i -1] = smallDim;
                continue;
            }
            else if (smallDim == 1) {
                newShape[maxDim -i -1] = bigDim;
                continue;
            }
            else if (bigDim == 1) {
                newShape[maxDim -i -1] = smallDim;
                continue;
            }
            else {
                throw std::runtime_error("Not compatible for broadcasting.");
            }
        }
        return newShape;

    }

    template<typename BinaryOperation>
    NDArray elementWise(const NDArray& other, BinaryOperation op) const {
        std::vector<size_t> newShape = broadcastShape(this->shape, other.shape);
        NDArray<T> newArray(newShape);

        std::vector<size_t> this_strides = this->strides;
        std::vector<size_t> other_strides = other.strides;
        std::vector<size_t> new_strides = newArray.strides;

        // Pad this_strides and other_strides with 0 if necessary
        this_strides.insert(this_strides.begin(), newShape.size() - this_strides.size(), 0);
        other_strides.insert(other_strides.begin(), newShape.size() - other_strides.size(), 0);

        std::vector<size_t> indices(newShape.size(), 0);
        size_t total_elements = newArray.calculateSize(newShape);

        for (size_t i = 0; i < total_elements; ++i) {
            size_t this_index = 0;
            size_t other_index = 0;

            for (size_t dim = 0; dim < newShape.size(); ++dim) {
                this_index += (indices[dim] % this->shape[dim]) * this_strides[dim];
                other_index += (indices[dim] % other.shape[dim]) * other_strides[dim];
            }

            newArray.data[i] =  op(this->data[this_index], other.data[other_index]);

            // Update indices
            for (int dim = newShape.size() - 1; dim >= 0; --dim) {
                if (++indices[dim] < newShape[dim]) {
                    break;
                }
                indices[dim] = 0;
            }
        }

        return newArray;
    }

    NDArray operator+(const NDArray& other) {
        return (this->elementWise(other, std::plus<T>()));
    }

    NDArray operator-(const NDArray& other) {
        return (this->elementWise(other, std::minus<T>()));
    }

    NDArray operator*(const NDArray& other) {
        return (this->elementWise(other, std::multiplies<T>()));
    }

    NDArray operator/(const NDArray& other) {
        return (this->elementWise(other, std::divides<T>()));
    }

    void zeroInit() {
        std::fill(data.begin(), data.end(), T(0.0));
    }

    void randomInit(T min = T(-0.1), T max = T(0.1), std::optional<unsigned> seed = std::nullopt) {
        std::default_random_engine gen;
        if (seed) 
            gen.seed(*seed);
        else {           
            std::random_device rd;
            gen.seed(rd());
        } 
        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dis(min, max);
            std::generate(data.begin(), data.end(), [&]() {return dis(gen);});
        }
        else {
            std::uniform_real_distribution<T> dis(min, max);
            std::generate(data.begin(), data.end(), [&]() {return dis(gen);});
        }
    }

    T operator[](std::vector<size_t> indices) {
        return data[calculateIndex(indices)];
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

int main() {
    NDArray<float> arr({2,3,1});
    arr.randomInit(0.1, 1);
    arr.printShapeAndStrides();
    NDArray<float> arr2({2,1,3});
    arr2.randomInit(0.1, 1);
    arr2.printShapeAndStrides();
    
    NDArray arr3 = arr / arr2; 

    for (size_t i=0; i<arr3.getShape().size(); ++i) {
        std::cout<<arr3.getShape()[i]<<",";
    }
    std::cout<<std::endl;
}