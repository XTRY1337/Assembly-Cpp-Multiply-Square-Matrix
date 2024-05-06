.MODEL FLAT, C								        ; Use the flat memory model. Use C calling conventions

.DATA										        ; Indicates the start of variable definitions


; ------------------ General Vars ------------------

floatSize dd 4


; ------------------ MultiplyMatrixWithAssembly Function Vars ------------------

offSetVarOne dd 0                                   ; Var offSetVarOne          
offSetVarTwo dd 0                                   ; Var offSetVarTwo          
                                                                                
counterFirstFor dd 0                                ; Var counterFirstFor       
counterSecondFor dd 0                               ; Var counterSecondFor      
counterSizeAfterShift dd 0                          ; Var counterSizeAfterShift


; ------------------ TransposeMatrixAssembly Function Vars ------------------

counterFirstForTranspose dd 0                       ; Var counterFirstFor       
counterSecondForTranspose dd 0                      ; Var counterSecondFor
counterSizeAfterShiftTranspose dd 0                 ; Var counterSizeAfterShiftTranspose

auxValue1 dd 0                                      ; Var auxValue1
auxValue2 dd 0                                      ; Var auxValue2

; ------------------ Main Code ------------------

.CODE										        ; Indicates the start of the code segment.


; ------------------ MultiplyMatrixWithAssembly Function ------------------

MultiplyMatrixWithAssembly PROC                     ; START Function

    push ebp								        ; Save de EBP in the stack
    mov ebp,esp								        ; Copy the ESP to EBP

    mov edi, [ebp + 8]		                        ; ArrayResult
    mov ebx, [ebp + 12]						        ; ArrayOne
    mov ecx, [ebp + 16]						        ; ArrayTwo
    mov edx, [ebp + 20]                             ; Size

    mov counterFirstFor, edx                        ; Save size in counterFirstFor
    mov counterSecondFor, edx                       ; Save size in counterSecondFor
    mov counterSizeAfterShift, edx                  ; Save size in counterSizeAfterShift

    shr counterSizeAfterShift, 2                    ; Shift value 2 times = divide value by 4
    mov esi, counterSizeAfterShift                  ; Save value in register ESI to restore value after loops

    imul eax, edx, 4                                ; Create offset - 4 bytes per float * size | 4bytes * edx(size)
    mov offSetVarOne, eax                           ; Save offset

    imul eax, edx                                   ; Create offset 2 - size * offSetVarOne | exd(size) * eax(edx*4) and keep the edx value
    mov offSetVarTwo, eax                           ; Save offset 2

    FirtCycleFor:                                   ; START FirtCycleFor

        movdqa xmm0, [ebx]                          ; Move memory start of EBX to XMM0

        mov counterSecondFor, edx                   ; Reset counterSecondFor to have value of EDX, value of size

        SecondCycleFor:                             ; START SecondCycleFor
            
            movdqa xmm1, [ecx]                      ; Move memory start of ECX to XMM1

            mov counterSizeAfterShift, esi          ; Reset counterSizeAfterShift to have value of ESI, value of (size/4)

            pxor xmm3, xmm3                         ; Reset Accumulator to the next calculation
            xor eax, eax                            ; Reset EAX

            ThirdCycleFor:                          ; START ThirdCycleFor
                
                movdqa xmm0, [ebx+eax]              ; Move memory start of EBX again to XMM0
                movdqa xmm1, [ecx+eax]              ; Move memory start of ECX again to XMM1

                movdqa xmm2, xmm0                   ; Save XMM0 content in XMM2, do this to not change XMM0 content for the next's for's
                mulps xmm2, xmm1                    ; Multiply XMM2 with XMM1 and save result in XMM2

                addps xmm3, xmm2                    ; Accumulator, add values in vertical

                add eax, 16                         ; Add 16 to move EAX 16 bytes

                dec counterSizeAfterShift           ; Decrement counterSizeAfterShift
                jnz ThirdCycleFor                   ; End loop if counterSizeAfterShift is zero

            ;END ThirdCycleFor                      ; END ThirdCycleFor

            haddps xmm3, xmm3                       ; Example "haddps xmm1, xmm2" = xmm1[xmm2[0] + xmm2[1], xmm2[2] + xmm2[3], xmm1[0] + xmm1[1], xmm1[2] + xmm1[3]]
            haddps xmm3, xmm3                       ; Example "haddps xmm1, xmm2" = xmm1[xmm2[0] + xmm2[1], xmm2[2] + xmm2[3], xmm1[0] + xmm1[1], xmm1[2] + xmm1[3]]

            movss dword ptr [edi], xmm3             ; Mover o ultimo valor de xmm3/resultado da soma, xmm3[3], para o endereço de memoria EDI

            add edi, 4                              ; Increment EDI with 4 value to use the next position of EDI in the next loop  

            add ecx, offSetVarOne                   ; Add offSet to ECX to move the memory to the next 4/8 element Ex: if size 4, offset 16, if size 8 offset 32

            dec counterSecondFor                    ; Decrement counterSecondFor
            jnz SecondCycleFor                      ; End loop if counterSecondFor is zero
            
        ;END SecondCycleFor                         ; END SecondCycleFor

        add ebx, offSetVarOne                       ; Add offSet to EBX to move the memory to the next 4/8 element Ex: if size 4, offset 16, if size 8 offset 32

        sub ecx, offSetVarTwo                       ; Sub the number of bytes added to ECX to put ECX back to the initial memory possition

        dec counterFirstFor                         ; Decrement counterFirstFor        
        jnz FirtCycleFor                            ; End loop if counterFirstFor is zero

    ;END FirtCycleFor                               ; END FirtCycleFor

    pop ebp									        ; Restore the EBP
    ret										        ; End the function and return to the main

MultiplyMatrixWithAssembly ENDP                     ; END Function


; ------------------ TransposeMatrixAssembly Function ------------------

TransposeMatrixAssembly PROC                        ; START Function

    push ebp								        ; Save de EBP in the stack
    mov ebp,esp								        ; Copy the ESP to EBP

    mov edi, [ebp + 8]		                        ; MatrixToTranspose
    mov ebx, [ebp + 12]						        ; Size

    mov auxValue1, 0                                ; Reset auxValue1 to have value 0
    mov auxValue2, 0                                ; Reset auxValue2 to have value 0

    mov counterFirstForTranspose, 0                 ; Reset counterFirstForTranspose to have value of 0

    FirtCycleFor:                                   ; START FirtCycleFor
        
        mov counterSecondForTranspose, 1            ; Reset counterSecondForTranspose to have value of 1
        mov eax, counterFirstForTranspose           ; Mov counterSecondForTranspose to EAX
        add counterSecondForTranspose, eax          ; counterSecondForTranspose = counterFirstForTranspose + 1

        SecondCycleFor:                             ; START SecondCycleFor
            
            cmp counterSecondForTranspose, ebx
            je CylTest

            mov eax, ebx                            ; Move value of EBX to EAX, EAX = size      |
            imul counterFirstForTranspose           ; EAX = EAX * counterFirstForTranspose(i)   | - > EAX = [i * size + j]
            add eax, counterSecondForTranspose      ; EAX = EAX + counterSecondForTranspose(j)  |

            imul floatSize                          ; EAX = EAX * floatSize(4)
            mov auxValue1, eax                      ; Move value of EAX to auxVal1

            mov eax, ebx                            ; Move value of ECX to EAX, EAX = size      |
            imul counterSecondForTranspose          ; EAX = EAX * counterSecondForTranspose(j)  | - > EAX = [j * size + i]
            add eax, counterFirstForTranspose       ; EAX = EAX + counterFirstForTranspose(i)   |

            imul floatSize                          ; EAX = EAX * floatSize(4)
            mov auxValue2, eax                      ; Move value of EAX to auxVal2

            mov eax, auxValue1
            mov ecx, [edi + eax]                    ;float temp = matrix[i * size + j];

            mov esi, auxValue2
            mov esi, [edi + esi]
            mov [edi + eax], esi                    ;matrix[i * size + j] = matrix[j * size + i];
                              
            mov esi, auxValue2
            mov [edi + esi], ecx                    ;matrix[j * size + i] = temp;

            inc counterSecondForTranspose           ; Increment counterSecondForTranspose
            cmp counterSecondForTranspose, ebx      ; Compare counterSecondForTranspose with ebx      
            jne SecondCycleFor                      ; End loop if comparation is true

        ;END SecondCycleFor                         ; END SecondCycleFor

        CylTest:

        inc counterFirstForTranspose                ; Increment counterFirstForTranspose
        cmp counterFirstForTranspose, ebx           ; Compare counterFirstForTranspose with ebx       
        jne FirtCycleFor                            ; End loop if comparation is true

    ;END FirtCycleFor                               ; END FirtCycleFor

    pop ebp									        ; Restore the EBP
    ret										        ; End the function and return to the main

TransposeMatrixAssembly ENDP                        ; END Function

END											        ; Indicate the end of the asm file