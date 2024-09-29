#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <random>
#include <optional>

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

template<typename Tem>
class NDArray {
private:
    std::vector<size_t> shape;
    std::vector<size_t> strides;
    std::vector<Tem> data;
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

    bool operator==(const NDArray& other) const {
        if (data.size() != other.data.size() || shape != other.shape)
            return false;
        return std::equal(data.begin(), data.end(), other.data.begin());
    }

    bool operator!=(const NDArray& other) const {
        return !(*this == other);
    }

    void T() {
        std::vector<size_t> oldShape = shape;
        std::vector<size_t> oldStrides = strides;

        std::reverse(shape.begin(), shape.end());
        strides = calculateStrides(num_dim, shape);
        
        std::vector<Tem> transposeData(data.size());
        std::vector<size_t> oldIndices(num_dim,0);

        for (size_t i=0; i<data.size(); ++i) {
            oldIndices = indexToIndices(i);
            std::reverse(oldIndices.begin(), oldIndices.end());
            size_t newIndex = calculateIndex(oldIndices);
            transposeData[newIndex] = data[i];            
        }
        data = std::move(transposeData);
    }

    NDArray transpose(NDArray arr) const {
        std::vector<size_t> oldShape = arr.shape;
        std::vector<size_t> oldStrides = arr.strides;

        std::reverse(arr.shape.begin(), arr.shape.end());
        arr.strides = calculateStrides(arr.num_dim, arr.shape);
        
        std::vector<Tem> transposeData(arr.data.size());
        std::vector<size_t> oldIndices(num_dim,0);

        for (size_t i=0; i<arr.data.size(); ++i) {
            oldIndices = indexToIndices(i);
            std::reverse(oldIndices.begin(), oldIndices.end());
            size_t newIndex = calculateIndex(oldIndices);
            transposeData[newIndex] = arr.data[i];            
        }
        arr.data = std::move(transposeData);
        return arr;
    }

    void zeroInit() {
        std::fill(data.begin(), data.end(), Tem(0.0));
    }

    void randomInit(Tem min = Tem(-0.1), Tem max = Tem(0.1), std::optional<unsigned> seed = std::nullopt) {
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

    Tem operator[](std::vector<size_t> indices) {
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