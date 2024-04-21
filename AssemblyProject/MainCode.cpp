#include <iostream>

#define LIMITE_RANDOM_NUMBER 10

//---------------- External Assembly Functions Section ----------------
extern "C" {
    int add_int(int, int);
}

//---------------- Complementary Functions Section ----------------
float** allocateMemoryForMatrix(int size) {
    float** matrix = new float* [size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new float[size];

    return matrix;
}

void printMatrix(float** resultMatrix, int size) {
    std::cout << "Matrix result:" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << resultMatrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}

float** createMatrixWithRandomValues(int size) {

    float** newMatrix = allocateMemoryForMatrix(size);

    // Fill matrix with random values
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            newMatrix[i][j] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / LIMITE_RANDOM_NUMBER)); //Numbers between 0 and LIMITE_RANDOM_NUMBER

    //Print created Matrix
    printMatrix(newMatrix, size);

    return newMatrix;
}

void freeMemory(float** resultMatrix, int size) {
    for (int i = 0; i < size; ++i)
        delete[] resultMatrix[i];
    delete[] resultMatrix;
}
//-----------------------------------------------------------------

// Function to replicate in Assembly - Example 2
float** multiplyMatrix(float** matrixOne, float** matrixTwo, int size) {

    float** resultMatrix = allocateMemoryForMatrix(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < size; k++) {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }

    return resultMatrix;
}

int handleInputValue() {

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

int main()
{
    // Example code calling assembly function
    int sum = add_int(2, 3);

    // Console input
    int size = handleInputValue();
    
    // Create matrix's
    float** matrixOne = createMatrixWithRandomValues(size);
    float** matrixTwo = createMatrixWithRandomValues(size);

    // Multiply matrix's
    float** matrixResult = multiplyMatrix(matrixOne, matrixTwo, size);

    // Print result matrix
    printMatrix(matrixResult, size);
    
    // Free memory
    freeMemory(matrixOne, size);
    freeMemory(matrixTwo, size);
    freeMemory(matrixResult, size);

    // Stop application
    return 0;
}





//CODE TO TRY MANUAL IMPLEMENTATION
// 
//#define SIZE 4

//If seed is necessary
//srand(time(0));

//FUNCTIONS
// Function to replicate in Assembly - Example 1
/*float** multiplyMatrix(float matrixOne[][SIZE], float matrixTwo[][SIZE]) {

    float** resultMatrix = allocateMemoryForMatrix();

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

//INT MAIN
if (SIZE % 4 != 0) {
    std::cout << "The size is not a multiple of 4" << std::endl;
    return;
}

//---------------- MANUAL IMPLEMENTATION ----------------
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
printMatrix(resultMatrix);

// Free memory
freeMemory(resultMatrix);*/