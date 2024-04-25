#include <iostream>

#define LIMITE_RANDOM_NUMBER 10

//---------------- External Assembly Functions Section ----------------

extern "C" {

    // Test Multiply 1D array, any size
    void SimpleMultiplyWithXMMAnyArrayValues1D(float* arrayResult, float* arrayOne, float* arrayTwo, int size);

    // Main Function WORKING WITH SIZE 4 NOW
    void MultiplyMatrixWithAssembly(float* resultMatrix, float* matrixOne, float* matrixTwo, int size, float* auxArray);

}

//---------------------------------------------------------------------

//---------------- Complementary Functions Section ----------------

void FreeMemory(float* matrix) {
    delete[] matrix;
}

int HandleInputValue() {

    int size;

    do {
        std::cout << "Please enter a number that is a multiple of 4: ";
        std::cin >> size;

        // Validate entry
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter numbers only!" << std::endl;
            continue;
        }

        // Validate number
        if (size % 4 != 0 || size <= 0) {
            std::cout << "The entered number is not a multiple of 4!" << std::endl;
            continue;
        }

        return size;

    } while (true);
}

float* CreateRandomFlatMatrix(int size) {

    float* matrix = new float[size * size];     // (float*)malloc(size * size);

    for (int i = 0; i < size * size; ++i)
        matrix[i] = static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / LIMITE_RANDOM_NUMBER)); //Numbers between 0 and LIMITE_RANDOM_NUMBER

    return matrix;
}

void PrintMatrix(float* matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i * size + j];
            if (j < size - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\n" << std::endl;
}

void TransposeMatrix(float* matrix, int size) {
    float* tempMatrix = new float[size * size];

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            tempMatrix[i * size + j] = matrix[j * size + i];

    for (int i = 0; i < size * size; ++i)
        matrix[i] = tempMatrix[i];

    delete[] tempMatrix;
}

void MultiplyFlatMatrixes(float* resultMatrix, float* matrixOne, float* matrixTwo, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultMatrix[i * size + j] = 0.0f;
            for (int k = 0; k < size; k++) {
                resultMatrix[i * size + j] += matrixOne[i * size + k] * matrixTwo[j * size + k];
            }
        }
    }
}

//------------------------------------------------------------------

int main()
{
    // Console size input
    int size = HandleInputValue();

    // Aux Array
    float* auxArray = new float[size];                      // (float*)malloc(size);

    // Create Matrix's
    float* matrixAssemblyResult = new float[size * size];   // (float*)malloc(size * size);
    float* matrixCppResult = new float[size * size];        // (float*)malloc(size * size);
    float* matrixOne = CreateRandomFlatMatrix(size);
    float* matrixTwo = CreateRandomFlatMatrix(size);

    // Print Matrix's
    std::cout << "-- Matrix One --" << std::endl;
    PrintMatrix(matrixOne, size);

    std::cout << "-- Matrix Two --" << std::endl;
    PrintMatrix(matrixTwo, size);

    std::cout << "-- Matrix Two Transposed --" << std::endl;
    TransposeMatrix(matrixTwo, size);
    PrintMatrix(matrixTwo, size);

    // Assembly result
    std::cout << "-- Assembly Matrix Result --" << std::endl;
    MultiplyMatrixWithAssembly(matrixAssemblyResult, matrixOne, matrixTwo, size, auxArray);
    PrintMatrix(matrixAssemblyResult, size);

    // Cpp result
    std::cout << "-- C++ Matrix Result --" << std::endl;
    MultiplyFlatMatrixes(matrixCppResult, matrixOne, matrixTwo, size);
    PrintMatrix(matrixCppResult, size);

    // Free memory
    FreeMemory(matrixAssemblyResult);
    FreeMemory(matrixCppResult);
    FreeMemory(matrixOne);
    FreeMemory(matrixTwo);

    // Stop application
    return 0;
}