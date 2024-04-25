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


SimpleMultiplyWithXMMAnyArrayValues1D PROC
                push ebp							; Save de EBP in the stack
                mov ebp,esp							; Copy the ESP to EBP

                mov edi, [esp + 8]		            ; Porque os registo guarda apenas os primeiro 4, porque soa registo 32bits 				; arrayResult +8Bytes
                mov ebx, [esp + 12]					; ArrayOne
                mov ecx, [esp + 16]					; ArrayTwo
                mov edx, [esp + 20]                 ; Size

                shr edx, 2                          ; Guardar o valor de quantas veze preciso de fazer o ciclo ; Cada shift é uma divisao por 2, ou seja shift de 2 é dividir por 4

FirtCycleFor:   movdqu xmm0, [ebx]                  ; Como ebx é o inicio do array, estou a mover apenas os 4 primeiros bytes
                movdqu xmm1, [ecx]

                mulps xmm0, xmm1                    ; Multiplicar xmm0 com xmm1
                movdqu [edi], xmm0                  ; Mover o resultado de xmm0 para [edi]

                add ebx, 16                         ; adiciono 16 bytes, porque cada valor ocupa 4
                add ecx, 16
                add edi, 16

                dec edx
                jnz FirtCycleFor

                pop ebp								; Restore the EBP
                ret									; End the function and return to the main
SimpleMultiplyWithXMMAnyArrayValues1D ENDP	        ; Indicates the end of the function.


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

    //---------------------------------------------------------


    SimpleMultiplyWithXMMAnyArrayValues1D PROC
                push ebp							; Save de EBP in the stack
                mov ebp,esp							; Copy the ESP to EBP

                mov edi, [esp + 8]		            ; Porque os registo guarda apenas os primeiro 4, porque soa registo 32bits 				; arrayResult +8Bytes
                mov ebx, [esp + 12]					; ArrayOne
                mov ecx, [esp + 16]					; ArrayTwo
                mov edx, [esp + 20]                 ; Size

                shr edx, 2                          ; Guardar o valor de quantas veze preciso de fazer o ciclo ; Cada shift é uma divisao por 2, ou seja shift de 2 é dividir por 4

FirtCycleFor:   movdqu xmm0, [ebx]                  ; Como ebx é o inicio do array, estou a mover apenas os 4 primeiros bytes
                movdqu xmm1, [ecx]

                mulps xmm0, xmm1                    ; Multiplicar xmm0 com xmm1
                movdqu [edi], xmm0                  ; Mover o resultado de xmm0 para [edi]

                add ebx, 16                         ; adiciono 16 bytes, porque cada valor ocupa 4
                add ecx, 16
                add edi, 16

                dec edx
                jnz FirtCycleFor

                pop ebp								; Restore the EBP
                ret									; End the function and return to the main
SimpleMultiplyWithXMMAnyArrayValues1D ENDP	        ; Indicates the end of the function.


MultiplyMatrixWithAssemblyTrySize8 PROC             ; START Function

    push ebp								        ; Save de EBP in the stack
    mov ebp,esp								        ; Copy the ESP to EBP

    mov edi, [esp + 8]		                        ; ArrayResult
    mov ebx, [esp + 12]						        ; ArrayOne
    mov ecx, [esp + 16]						        ; ArrayTwo

    mov edx, [esp + 20]                             ; Size
    mov counterFirstFor, edx                        ; Save size in counterFirstFor
    mov counterSecondFor, edx                       ; Save size in counterSecondFor
    mov counterSumFourValues, edx                   ; Save size in counterSumFourValues

    imul eax, edx, 4                                ; Create offset - 4 bytes per float * size | 4bytes * edx(size)
    mov offSetVarOne, eax                           ; Save offset

    imul eax, edx                                   ; Create offset 2 - size * offSetVarOne | exd(size) * eax(edx*4)
    mov offSetVarTwo, eax                           ; Save offset 2

    mov eax, [esp + 24]                             ; AuxArray

    FirtCycleFor:                                   ; Start FirtCycleFor

        movdqu xmm0, [ebx]                          ; Move memory start of EBX to XMM0
        movdqu xmm3, [ebx+16]                       ; !!!!!!! ---- HARDCODE TO WORK WITH 8 ---- !!!!!!

        mov counterSecondFor, edx                   ; Reset counterSecondFor to have value of EDX, value of size

        SecondCycleFor:                             ; Start SecondCycleFor

            movdqu xmm1, [ecx]                      ; Move memory start of ECX to XMM1
            movdqu xmm4, [ecx+16]                   ; !!!!!!! ---- HARDCODE TO WORK WITH 8 ---- !!!!!!

            movdqu xmm5, xmm3                       ; !!!!!!! ---- HARDCODE TO WORK WITH 8 ---- !!!!!!
            mulps xmm5, xmm4                        ; !!!!!!! ---- HARDCODE TO WORK WITH 8 ---- !!!!!!
            movdqu [eax+16], xmm5                   ; !!!!!!! ---- HARDCODE TO WORK WITH 8 ---- !!!!!!

            movdqu xmm2, xmm0                       ; Save XMM0 content in XMM2, do this to not change XMM0 content for the next's for's
            mulps xmm2, xmm1                        ; Multiply XMM2 with XMM1 and save result in XMM2
            movdqu [eax], xmm2                      ; Move XMM2 content to memory start of EAX

            mov counterSumFourValues, edx           ; Reset counterSumFourValues to have value of EDX, value of size

            fld dword ptr [floatZero]               ; Add first value to float stack, value 0.0, if I do not do this, the FADDP will not work because they need alreay a value in stack

            SumValuesLoop:                          ; Start SumValuesLoop

                fld dword ptr [eax]                 ; Move value in start memory of EAX to float stack
                faddp                               ; Add the two value in stack and save the value again in the stack

                add eax, 4                          ; Increment eax memory to get the next value Ex: eax = [0] -> eax + 4 -> eax[1]

                dec counterSumFourValues            ; Decrement counterSumFourValues
                jnz SumValuesLoop                   ; End loop if counterSumFourValues is zero | run the loop will counterSumFourValues different of zero

            ;END SumValuesLoop                      ; END SumValuesLoop

            sub eax, offSetVarOne                   ; Sub the number of bytes added to EAX to put EAX back to the initial possition

            fstp dword ptr [edi]                    ; Save the value in stack to EDI memory location

            add edi, 4                              ; Increment EDI with 4 value to use the next position of EDI in the next loop

            add ecx, offSetVarOne                   ; Add offSet to ECX to move the memory to the next 4/8 element Ex: if size 4, offset 16, if size 8 offset 32

            dec counterSecondFor                    ; Decrement counterSecondFor
            jnz SecondCycleFor                      ; End loop if counterSecondFor is zero | run the loop will counterSecondFor different of zero

        ;END SecondCycleFor                         ; END SecondCycleFor

        add ebx, offSetVarOne                       ; Add offSet to EBX to move the memory to the next 4/8 element Ex: if size 4, offset 16, if size 8 offset 32

        sub ecx, offSetVarTwo                       ; Sub the number of bytes added to ECX to put ECX back to the initial memory possition

        dec counterFirstFor                         ; Decrement counterFirstFor
        jnz FirtCycleFor                            ; End loop if counterFirstFor is zero | run the loop will counterFirstFor different of zero

    ;END FirtCycleFor                               ; END FirtCycleFor

    pop ebp									        ; Restore the EBP
    ret										        ; End the function and return to the main

MultiplyMatrixWithAssemblyTrySize8 ENDP             ; END Function


void MultiplyMatrixWithAssemblyTrySize8(float* resultMatrix, float* matrixOne, float* matrixTwo, int size, float* auxArray);


*/