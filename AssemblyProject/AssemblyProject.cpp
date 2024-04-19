#include <iostream>

#define SIZE 4

float** multiplyMatrix(float matrixOne[][SIZE], float matrixTwo[][SIZE]) {
    
    float** resultMatrix = new float* [SIZE];
    for (int i = 0; i < SIZE; ++i) {
        resultMatrix[i] = new float[SIZE];
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }

    return resultMatrix;
}

void printResult(float** resultMatrix) {
    std::cout << "Matrix result:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << resultMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void freeMemory(float** resultMatrix) {
    for (int i = 0; i < SIZE; ++i)
        delete[] resultMatrix[i];
    delete[] resultMatrix;
}

int main()
{
    // Sample matrix one
    float matrixOne[SIZE][SIZE] = { 
                                  { 1.0f,  2.0f,  3.0f,  4.0f  },
                                  { 5.0f,  6.0f,  7.0f,  8.0f  },
                                  { 9.0f,  10.0f, 11.0f, 12.0f },
                                  { 13.0f, 14.0f, 15.0f, 16.0f }
                                  };

    // Sample matrix two
    float matrixTwo[SIZE][SIZE] = {
                                  { 1.0f, 0.0f, 0.0f, 0.0f },
                                  { 0.0f, 1.0f, 0.0f, 0.0f },
                                  { 0.0f, 0.0f, 1.0f, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f }
                                  };
    // Matrix result
    float** resultMatrix = multiplyMatrix(matrixOne, matrixTwo);

    // Print result
    printResult(resultMatrix);

    // Free memory
    freeMemory(resultMatrix);

    // Stop Application
    return 0;
}