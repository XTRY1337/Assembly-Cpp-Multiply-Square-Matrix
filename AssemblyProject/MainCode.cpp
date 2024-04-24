#include <iostream>

#define LIMITE_RANDOM_NUMBER 10

//---------------- External Assembly Functions Section ----------------
extern "C" {
    // Test Functions
    int Add_int(int, int);
    int Mult_int(int, int);
    
    // Test Multiply 4 values at the same time with XMM register
    void SimpleMultiplyWithXMMFourArrayValues(float* arrayResult, float* arrayOne, float* arrayTwo);

    // Main Function
    void MultiplyMatrixWithTransposeAssembly(float** resultMatrix, float** matrixOne, float** matrixTwo, int size);
}

//---------------- Complementary Functions Section ----------------
float** AllocateMemoryForMatrix(int size) {
    float** matrix = new float* [size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new float[size];

    return matrix;
}

void PrintMatrix(float** resultMatrix, int size, const char* customText) {
    std::cout << customText << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std::cout << resultMatrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}

float** CreateMatrixWithRandomValues(int size) {

    float** newMatrix = AllocateMemoryForMatrix(size);

    // Fill matrix with random values
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            newMatrix[i][j] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / LIMITE_RANDOM_NUMBER)); //Numbers between 0 and LIMITE_RANDOM_NUMBER

    //Print created Matrix
    PrintMatrix(newMatrix, size, "-- Created Matrix --");

    return newMatrix;
}

void FreeMemory(float** resultMatrix, int size) {
    for (int i = 0; i < size; ++i)
        delete[] resultMatrix[i];
    delete[] resultMatrix;
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

float** Transpose(float** matrix, int size) {

    float** transposedMatrix = AllocateMemoryForMatrix(size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            transposedMatrix[j][i] = matrix[i][j];

    //Print created Matrix
    PrintMatrix(transposedMatrix, size, "-- Transposed Matrix --");

    return transposedMatrix;
}

//-----------------------------------------------------------------

// Multiply Matrix with Alloc Memory
float** MultiplyMatrix(float** matrixOne, float** matrixTwo, int size) {

    float** resultMatrix = AllocateMemoryForMatrix(size);

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

// Multiply Matrix without Alloc Memory
void MultiplyMatrix(float** resultMatrix, float** matrixOne, float** matrixTwo, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < size; k++) {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
}

//---------------- FUNCTION TO REPLICATE IN ASSEMBLY ----------------
void MultiplyMatrixWithTransposeCpp(float** resultMatrix, float** matrixOne, float** matrixTwo, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < size; k++) {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[j][k];
            }
        }
    }
}

// TODO: Remove Later
void PopulateArray(float* array, int size) {
    for (int i = 0; i < size; i++)
        array[i] = i;
}

void CleanPositionsArray(float* array, int size) {
    for (int i = 0; i < size; i++)
        array[i] = 0;
}

int main()
{
    // Console size input
    int size = HandleInputValue();

    // TODO: Remove Later
    //--------------------- TEST CODE ----------------------
    float* arrayResult = (float*)malloc(sizeof(float) * size);
    float* array1 = (float*)malloc(sizeof(float) * size);
    float* array2 = (float*)malloc(sizeof(float) * size);
    
    CleanPositionsArray(arrayResult, size);
    PopulateArray(array1, size);
    PopulateArray(array2, size);

    SimpleMultiplyWithXMMFourArrayValues(arrayResult, array1, array2);
    //-------------------- END TEST CODE --------------------



    //---------------- Validate result with normal code --------------------------
    float** matrixOneToAssembly = CreateMatrixWithRandomValues(size); //1º
    float** matrixTwoToAssembly = CreateMatrixWithRandomValues(size); //1º
    float** matrixResultFromAssembly = MultiplyMatrix(matrixOneToAssembly, matrixTwoToAssembly, size); //3º
    PrintMatrix(matrixResultFromAssembly, size, "-- Matrix Result From Assembly --");//5º
    //---------------- Test Transpose(Result need to be the same) ----------------
    float** transposeMatrix = Transpose(matrixTwoToAssembly, size);
    float** resultMatrix = AllocateMemoryForMatrix(size);
    MultiplyMatrixWithTransposeCpp(resultMatrix, matrixOneToAssembly, transposeMatrix, size);
    PrintMatrix(resultMatrix, size, "-- Matrix Result Using Transpose Matrix --");
    //----------------------------------------------------------------------------



    // NOTE: Result from previus code need to be the same as assembly code



    //---------------- Using Assembly Function ----------------

    // 1º Create 2 Matrix's
    //float** matrixOneToAssembly = CreateMatrixWithRandomValues(size);
    //float** matrixTwoToAssembly = CreateMatrixWithRandomValues(size);
    
    // 2º Transpose the second one
    // float** transposeMatrix = Transpose(matrixTwoToAssembly, size);
    
    // 3º Allocate memory for result matrix
    // float** resultMatrix = AllocateMemoryForMatrix(size);

    // 4º Use Assembly function
    // MultiplyMatrixWithTransposeAssembly(resultMatrix, matrixOneToAssembly, transposeMatrix, size);
    
    // 5º Get the returned value and print on console
    // PrintMatrix(resultMatrix, size, "-- Matrix Result From Assembly Code --");

    // 6º Free memory for all pointer
    // FreeMemory(matrixOneToAssembly, size);
    // FreeMemory(matrixTwoToAssembly, size);
    // FreeMemory(transposeMatrix, size);
    // FreeMemory(resultMatrix, size); 

    //---------------------------------------------------------

    // Stop application
    return 0;
}