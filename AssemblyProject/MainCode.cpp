#include <iostream>
#include <chrono>
#include "AssemblyFunctions.h"

#define LIMITE_RANDOM_NUMBER 10

#define FLAG_ASSEMBLY
#define FLAG_CPP

//---------------- Complementary Functions Section ----------------

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

float RandomFloatValue() {
    //Numbers between 0 and LIMITE_RANDOM_NUMBER
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / LIMITE_RANDOM_NUMBER));
}

float* CreateRandomFlatMatrix(int size) {

    float* matrix = (float*)_aligned_malloc(size * size * sizeof(float), 16);     

    for (int i = 0; i < size * size; ++i)
        matrix[i] = RandomFloatValue(); 

    return matrix;
}

void PrintMatrix(float* matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i * size + j];
            if (j < size - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}

void MultiplyFlatMatrixes(float* resultMatrix, float* matrixOne, float* matrixTwo, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultMatrix[i * size + j] = 0.0f;
            for (int k = 0; k < size; k++)
                resultMatrix[i * size + j] += matrixOne[i * size + k] * matrixTwo[j * size + k];
        }
    }
}

void TransposeMatrixCpp(float* matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            float temp = matrix[i * size + j];
            matrix[i * size + j] = matrix[j * size + i];
            matrix[j * size + i] = temp;
        }
    }
}

void PrintExecutionTime(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    std::chrono::steady_clock::duration durationTime = end - start;
    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::microseconds>(durationTime).count() << " ms" << std::endl;
    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(durationTime).count() << " ns\n" << std::endl;
}

//------------------------------------------------------------------

int main()
{
    // Console size input
    int size = HandleInputValue();

    // Create Matrix's
    float* matrixAssemblyResult = (float*)_aligned_malloc(size * size * sizeof(float), 16);
    float* matrixCppResult = (float*)_aligned_malloc(size * size * sizeof(float), 16);
    float* matrixOne = CreateRandomFlatMatrix(size);
    float* matrixTwo = CreateRandomFlatMatrix(size);

    // Print Matrix's
    std::cout << "-- Matrix One --" << std::endl;
    PrintMatrix(matrixOne, size);

    std::cout << "-- Matrix Two --" << std::endl;
    PrintMatrix(matrixTwo, size);

    TransposeMatrixAssembly(matrixTwo, size);
    PrintMatrix(matrixTwo, size);

#ifdef FLAG_ASSEMBLY
    // Assembly Transpose
    std::cout << "-- Matrix Two Assembly Transposed --" << std::endl;
    std::chrono::steady_clock::time_point startTransposeAssemblyFunction = std::chrono::high_resolution_clock::now();
    TransposeMatrixAssembly(matrixTwo, size);
    std::chrono::steady_clock::time_point endTransposeAssemblyFunction = std::chrono::high_resolution_clock::now();
    PrintMatrix(matrixTwo, size);

    // Print Execution time
    PrintExecutionTime(startTransposeAssemblyFunction, endTransposeAssemblyFunction);
#endif

#ifdef FLAG_CPP
    // Cpp Transpose Calculation time
    TransposeMatrixAssembly(matrixTwo, size); // Transpose again to get original matrix 
    std::cout << "-- Matrix Cpp Transposed Example --" << std::endl;
    std::chrono::steady_clock::time_point startTransposeCppFunction = std::chrono::high_resolution_clock::now();
    TransposeMatrixCpp(matrixTwo, size);
    std::chrono::steady_clock::time_point endTransposeCppFunction = std::chrono::high_resolution_clock::now();
    PrintMatrix(matrixTwo, size);

    //Print Execution time
    PrintExecutionTime(startTransposeCppFunction, endTransposeCppFunction);
#endif

#ifdef FLAG_ASSEMBLY
    // Assembly result
    std::cout << "-- Assembly Matrix Result --" << std::endl;
    std::chrono::steady_clock::time_point startAssemblyFunction = std::chrono::high_resolution_clock::now();
    MultiplyMatrixWithAssembly(matrixAssemblyResult, matrixOne, matrixTwo, size);
    std::chrono::steady_clock::time_point endAssemblyFunction = std::chrono::high_resolution_clock::now();
    PrintMatrix(matrixAssemblyResult, size);

    //Print Execution time
    PrintExecutionTime(startAssemblyFunction, endAssemblyFunction);
#endif

#ifdef FLAG_CPP
    // Cpp result
    std::cout << "-- C++ Matrix Result --" << std::endl;
    std::chrono::steady_clock::time_point startCppFunction = std::chrono::high_resolution_clock::now();
    MultiplyFlatMatrixes(matrixCppResult, matrixOne, matrixTwo, size);
    std::chrono::steady_clock::time_point endCppFunction = std::chrono::high_resolution_clock::now();
    PrintMatrix(matrixCppResult, size);

    //Print Execution time
    PrintExecutionTime(startCppFunction, endCppFunction);
#endif

    // Free memory
    _aligned_free(matrixAssemblyResult);
    _aligned_free(matrixCppResult);
    _aligned_free(matrixOne);
    _aligned_free(matrixTwo);

    // Stop application
    return 0;
}