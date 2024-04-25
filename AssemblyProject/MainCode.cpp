#include <iostream>

#define LIMITE_RANDOM_NUMBER 10

//---------------- External Assembly Functions Section ----------------
extern "C" {
    // Test Multiply 1D array, any size
    void SimpleMultiplyWithXMMAnyArrayValues1D(float* arrayResult, float* arrayOne, float* arrayTwo, int size);

    // Main Function
    void MultiplyMatrixWithAssembly(float* resultMatrix, float* matrixOne, float* matrixTwo, int size, float* auxArray);
}

//---------------- Complementary Functions Section ----------------
float** AllocateMemoryForMatrix(int size) {
    float** matrix = new float* [size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new float[size];

    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            matrix[i][k] = 0;

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
            newMatrix[i][j] = static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / LIMITE_RANDOM_NUMBER)); //Numbers between 0 and LIMITE_RANDOM_NUMBER

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

float* CreateFlatMatrix(int size) {
    
    //int totalSize = size * size * sizeof(float);
    float* matrix = new float[size * size];//(float*)malloc(size * size * sizeof(float));

    for (int i = 0; i < size * size; ++i)
        matrix[i] = static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / LIMITE_RANDOM_NUMBER)); //Numbers between 0 and LIMITE_RANDOM_NUMBER

    return matrix;
}

float* CreateEmptyFlatMatrix(int size) {

    //int totalSize = size * size * sizeof(float);
    float* matrix = new float[size * size];//(float*)malloc(size * size * sizeof(float));

    for (int i = 0; i < size * size; ++i)
        matrix[i] = 0;

    return matrix;
}

void PrintMatrixsss(float* matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        std::cout << matrix[i];
        if (i < size * size - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void PrintMatrixsss2(float* matrix, int size) {
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

void Transpose2(float* matrix, int size) {
    float* tempMatrix = new float[size * size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tempMatrix[i * size + j] = matrix[j * size + i];
        }
    }

    for (int i = 0; i < size * size; ++i) {
        matrix[i] = tempMatrix[i];
    }

    delete[] tempMatrix;
}

void MultiplyFlatMatrices(float* resultMatrix, float* matrixOne, float* matrixTwo, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            resultMatrix[i * size + j] = 0.0f;
            for (int k = 0; k < size; k++) {
                resultMatrix[i * size + j] += matrixOne[i * size + k] * matrixTwo[j * size + k];
            }
        }
    }
}

int main()
{
    // Console size input
    int size = HandleInputValue();

    //Test 2
    float* matrixResult = CreateEmptyFlatMatrix(size);
    float* matrixT1 = CreateFlatMatrix(size);
    float* matrixT2 = CreateFlatMatrix(size);

    std::cout << "Matriz original T1:" << std::endl;
    PrintMatrixsss2(matrixT1, size);

    std::cout << "Matriz original T2:" << std::endl;
    PrintMatrixsss2(matrixT2, size);

    std::cout << "Matriz transpose T2:" << std::endl;
    Transpose2(matrixT2, size);
    PrintMatrixsss2(matrixT2, size);

    float* auxArray = new float[size]; //(float*)malloc(sizeof(float) * size);
    CleanPositionsArray(auxArray, size);

    std::cout << "Assembly Result:" << std::endl;
    MultiplyMatrixWithAssembly(matrixResult, matrixT1, matrixT2, size, auxArray);
    PrintMatrixsss2(matrixResult, size);

    std::cout << "C++ Result:" << std::endl;
    float* matrixResult1 = CreateEmptyFlatMatrix(size);
    MultiplyFlatMatrices(matrixResult1, matrixT1, matrixT2, size);
    PrintMatrixsss2(matrixResult1, size);

    return 0;

    // Create Matrix's
    /*float** matrixResult = AllocateMemoryForMatrix(size);
    float** matrixOne = CreateMatrixWithRandomValues(size);
    float** transposeMatrix = Transpose(CreateMatrixWithRandomValues(size), size);

    // Create Aux Array
    float*  auxArray = (float*)malloc(sizeof(float) * size);
    CleanPositionsArray(auxArray,4);

    // C++ Result
    // TODO

    // Assembly Result
    MultiplyMatrixWithTransposeAssembly(matrixResult, matrixOne, transposeMatrix, 4, auxArray);

    FreeMemory(matrixResult, size);
    FreeMemory(matrixOne, size);
    FreeMemory(transposeMatrix, size);*/
    //FreeMemory(auxArray, size);

    return 0;

    //--------- Test Code - AULA DIA 24 --------------------
    /*float* arrayResultSize8 = (float*)malloc(sizeof(float) * 8);
    float* array1Size8 = (float*)malloc(sizeof(float) * 8);
    float* array2Size8 = (float*)malloc(sizeof(float) * 8);

    CleanPositionsArray(arrayResultSize8, 8);
    PopulateArray(array1Size8, 8);
    PopulateArray(array2Size8, 8);

    SimpleMultiplyWithXMMAnyArrayValues1D(arrayResultSize8, array1Size8, array2Size8, 8);

    // TODO: Remove Later
    //--------------------- TEST CODE ----------------------

    // Double Pointer Test
    float** matrixOneToAssembly2 = CreateMatrixWithRandomValues(size);

    float** matrix = new float* [4]; // Digo que para o duplo ponteiro vai ser o endereço de memoria = a um array de ponteiros float com tamanho 4
    for (int i = 0; i < 4; ++i)
        matrix[i] = new float[4]; // Para cada uma das posiçoes do array de ponteiros atribuo o valor de um novo array de floats

    for (int i = 0; i < 4; i++)
        matrix[0][i] = i;

    for (int i = 0; i < 4; i++)
        matrix[1][i] = i + 1;

    for (int i = 0; i < 4; i++)
        matrix[2][i] = i + 2;

    for (int i = 0; i < 4; i++)
        matrix[3][i] = i + 3;

    //PrintMatrix(matrixOneToAssembly2, size, "-- Matrix Result Test Double Pointer --");
    TestDoublePointer(matrix);


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

    //---------------------------------------------------------*/

    // Stop application
    return 0;
}