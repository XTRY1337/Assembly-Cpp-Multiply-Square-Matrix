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



    SimpleMultiplyWithYMMEightArrayValues PROC
    push ebp
    mov ebp, esp

    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx

    mov eax, [esp + 8]
    mov ebx, [esp + 12]
    mov ecx, [esp + 16]

    xor esi, esi
    vpxor ymm0, ymm0, ymm0
    mov esi, ebx
    vmovups ymm0, [esi]

    xor esi, esi
    vpxor ymm1, ymm1, ymm1
    mov esi, ecx
    vmovups ymm1, [esi]

    vmulps ymm0, ymm0, ymm1

    mov edi, eax
    vmovups [edi], ymm0

    pop ebp
    ret
SimpleMultiplyWithYMMEightArrayValues ENDP



Add_int PROC								; indicates the function name (used format: add_int(int x1, int x2))
    push ebp								; first instruction in the function. Save de EBP in the stack
    mov ebp,esp								; copy the ESP to EBP
    mov eax,[ebp+8]							; get the first parameter (x1)
    add eax,[ebp+12]						; add the first parameter with the second parameter
    pop ebp									; restore the EBP
    ret										; end the function and return to the main
Add_int ENDP								; indicates the end of the function. Any other function must be write after this line




Mult_int PROC								; Multiple numbers function
    push ebp
    mov ebp,esp
    mov eax,[ebp+8]
    mov ebx,[ebp+12]
    mul ebx
    pop ebp
    ret
Mult_int ENDP




var_byte DB 1								; Define a variable named 'var_byte' with a size of 1 byte and a value of 1
var_word DW 2								; Define a variable named 'var_word' with a size of 2 bytes and a value of 2
var_dword DD 3								; Define a variable named 'var_dword' with a size of 4 bytes and a value of 3
var_qword DQ 4								; Define a variable named 'var_qdword' with a size of 8 bytes and a value of 4
list_byte DB 1024 DUP(?)					; Define a variable named 'list_byte' with a size of 1*1024 bytes. it's an byte array
list_int DD 0,1,2,3							; Define a variable named list_int with size 4*4 bytes. It´s an int array



fld dword ptr [edi]                     ; adiono o edi[0] à stack de float
                    fld dword ptr [edi+4]                   ; adiono o edi[1] à stack de floats
                    faddp                                   ; somo os dois valores na stack de floats

                    fld dword ptr [edi+8]                   ; volto a adicionar outro valor
                    faddp                                   ; volto a somar os ultimos 2 valores na stack floats

                    fld dword ptr [edi+12]                  ; volto a adicionar outro valor
                    faddp                                   ; volto a somar os ultimos 2 valores na stack floats

                    fstp dword ptr [edi]                    ; guarda a conta final no edi[0]




MultiplyMatrixWithTransposeAssembly PROC

    push ebp								            ; Save de EBP in the stack
    mov ebp,esp								            ; Copy the ESP to EBP

    mov edi, [esp + 8]		                            ; ArrayResult  float**
    mov edi, [edi]                                      ; float*

    mov ebx, [esp + 12]						            ; ArrayOne float**
    mov ebx, [ebx]                                      ; float*

    mov ecx, [esp + 16]						            ; ArrayTwo float**
    mov ecx, [ecx]                                      ; float*

    mov edx, [esp + 20]                                 ; Size
    mov inputSize, edx

    mov eax, [esp + 24]                                 ; Aux array float*

    shr edx, 2                                          ; Divide by 4 the size to get index
    mov auxVarOne, edx                                  ; Save number of times to performe for
    xor edx, edx

    FirtCycleFor:

        movdqu xmm0, [ebx]                              ; Move first 4 elements of ArrayOne to xmm0
        mov auxVarThree, 4

            SecondCycleFor:

                movdqu xmm1, [ecx]                      ; Move first 4 elements of ArrayTwo to xmm1

                mulps xmm0, xmm1                        ; Multiply XMM0 with XMM1 and save result in xmm0
                movdqu [eax], xmm0                      ; Move result to firt 4 element in EDI

                mov auxVarTwo, 3                        ; iniciar auxVarTwo com valor 3 para loop i = 0 i < 3

                fld dword ptr [eax]                     ; adiciono o EDI[0] à stack de float - preciso de adiconar antes senao dentro do ciclo apenas 1 nao funciona

                SumFourValuesLoop:

                    add eax, 4
                    fld dword ptr [eax]
                    faddp                               ; somo os ultimos valores na stack de floats

                    dec auxVarTwo
                    jnz SumFourValuesLoop

                ;END SumFourValuesLoop

                sub eax, 12
                fstp dword ptr [edi]                    ; guarda a conta final no edi[0]  !!!!!!!!!!! PRECISO SOMAR O EDI + 4 POR CADA CICLO PARA GUARDAR NO LUGAR CERTO

                dec auxVarThree
                jnz SecondCycleFor

            ;END SecondCycleFor

        mov ebx, [esp + 12]                             ; Voltar a aceder ao ponteiro onde está o float**
        mov ebx, [ebx + sizeHelper]                        ; ir buscar a outra posição do float*    !!! Este 4 tem de ser pelo numero de ciclos a serem feitos
        ;add sizeHelper, inputSize

        dec auxVarOne                                   ; Decrement edx
        jnz FirtCycleFor                                ; Jump to flag if edx different of 0

    ;END FirtCycleFor

    pop ebp									            ; Restore the EBP
    ret										            ; End the function and return to the main

MultiplyMatrixWithTransposeAssembly ENDP	            ; Indicates the end of the function.
*/