/*


//---------------- Test Code ----------------
// Example code calling assembly function
int sum = Add_int(2, 3);
int mult = Mult_int(4, 5);

// Create matrix's
float** matrixOne = CreateMatrixWithRandomValues(size);
float** matrixTwo = CreateMatrixWithRandomValues(size);

// Multiply matrix's
float** matrixResult = MultiplyMatrix(matrixOne, matrixTwo, size);

// Print result matrix
PrintMatrix(matrixResult, size, "-- Matrix Result --");

// Transpose Matrix Test
// For Assembly, it's easier to do the transpose first so we can use the xmm register to multiply line by line.
float** transposeMatrix = Transpose(matrixResult, size);
PrintMatrix(transposeMatrix, size, "-- Matrix Result --");

// Free memory
FreeMemory(matrixOne, size);
FreeMemory(matrixTwo, size);
FreeMemory(matrixResult, size);
//--------------------------------------------


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
freeMemory(resultMatrix);





// TODO: Remove Later
    int* array1 = (int*)malloc(sizeof(int) * 4);
    int* array2 = (int*)malloc(sizeof(int) * 4);
    int* arrayResult1 = (int*)malloc(sizeof(int) * 4);  // int x 4 elements

    for (int i = 0; i < size; i++) {
        arrayResult1[i] = 0;
        array1[i] = i;
        array2[i] = i + 1;
    }

    //Pointer Array - Soma
    __asm {
        xor esi, esi
        mov esi, array1
        movdqu xmm0, [esi] // Carrega os valores do primeiro array em xmm0

        xor esi, esi
        mov esi, array2
        movdqu xmm1, [esi] // Carrega os valores do segundo array em xmm1

        paddb xmm0, xmm1 // Soma 4 registros ao mesmo tempo

        xor edi, edi
        mov edi, arrayResult1 // Carrega o endereço do array de resultado em esi
        movdqu[edi], xmm0
    }

    float* array11 = (float*)malloc(sizeof(float) * 4);
    float* array22 = (float*)malloc(sizeof(float) * 4);
    float* arrayResult11 = (float*)malloc(sizeof(float) * 4);  // int x 4 elements

    for (int i = 0; i < size; i++) {
        arrayResult11[i] = 0;
        array11[i] = i;
        array22[i] = i + 1;
    }

    //Pointer Array - Multiplicaçao float
    __asm {
        xor esi, esi
        mov esi, array11
        movdqu xmm0, [esi] // Carrega os valores do primeiro array em xmm0

        xor esi, esi
        mov esi, array22
        movdqu xmm1, [esi] // Carrega os valores do segundo array em xmm1

        mulps xmm0, xmm1 // Multiplicaçao 4 registros ao mesmo tempo | mulps(Multiplicaçao de floats)  pmulld(Multiplcaçao de inteiros)

        xor edi, edi
        mov edi, arrayResult11 // Carrega o endereço do array de resultado em esi
        movdqu[edi], xmm0
    }


    int arrayResult[4] = {0, 0, 0, 0};
    int ar1[4] = { 0, 1, 2, 3 };
    int ar2[4] = { 1, 2, 3, 4 };

    //Normal Array - Soma
    __asm {

        xor esi, esi
        lea esi, ar1
        movdqu xmm0, [esi] // Carrega os valores do primeiro array em xmm0  // Porque movdqa nao funciona?

        xor esi, esi
        lea esi, ar2
        movdqu xmm1, [esi] // Carrega os valores do segundo array em xmm1

        paddb xmm0, xmm1 // Soma 4 registos ao mesmo tempo

        movdqu[arrayResult], xmm0 // Passar o conteudo de xmm0 para o endereço de memoria arrayResult
    }




    // MULTIPLY 2 ARRAYS

    __asm {
        xor esi, esi
        mov esi, array1
        movdqu xmm0, [esi]

        xor esi, esi
        mov esi, array2
        movdqu xmm1, [esi]

        mulps xmm0, xmm1

        xor edi, edi
        mov edi, arrayResult
        movdqu[edi], xmm0
    }


*/