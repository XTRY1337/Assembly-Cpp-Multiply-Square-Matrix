.MODEL FLAT, C								        ; Use the flat memory model. Use C calling conventions

.DATA										        ; Indicates the start of variable definitions

offSetVarOne dd 0                                   ; Var offSetVarOne
offSetVarTwo dd 0                                   ; Var offSetVarTwo
counterFirstFor dd 0                                ; Var counterFirstFor
counterSecondFor dd 0                               ; Var counterSecondFor
counterSumFourValues dd 0                           ; Var counterSumFourValues
floatZero dd 0.0                                    ; Var floatZero

.CODE										        ; Indicates the start of the code segment.

MultiplyMatrixWithAssembly PROC                     ; START Function

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

        mov counterSecondFor, edx                   ; Reset counterSecondFor to have value of EDX, value of size

        SecondCycleFor:                             ; Start SecondCycleFor
            
            movdqu xmm1, [ecx]                      ; Move memory start of ECX to XMM1

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

MultiplyMatrixWithAssembly ENDP                     ; END Function

END											        ; Indicate the end of the asm file