.MODEL FLAT, C								; Use the flat memory model. Use C calling conventions
.DATA										; indicates the start of variable definitions

offSetVar dd 0
counterFirstFor dd 0
counterSecondFor dd 0
counterSumFourValues dd 0

.CODE										; Indicates the start of the code segment.

MultiplyMatrixWithAssembly PROC

    push ebp								            ; Save de EBP in the stack
    mov ebp,esp								            ; Copy the ESP to EBP

    mov edi, [esp + 8]		                            ; ArrayResult
    mov ebx, [esp + 12]						            ; ArrayOne
    mov ecx, [esp + 16]						            ; ArrayTwo

    mov edx, [esp + 20]                                 ; Size
    mov counterFirstFor, edx
    mov counterSecondFor, edx
    mov counterSumFourValues, edx

    imul eax, edx, 4                                    ; Create offset - 4 bytes per float * size
    mov offSetVar, eax                                  ; Save offset
    mov eax, [esp + 24]                                 ; AuxArray

    FirtCycleFor:

        movdqu xmm0, [ebx]

        mov counterSecondFor, edx

        SecondCycleFor:
            
            movdqu xmm1, [ecx]
            mulps xmm0, xmm1
            movdqu [eax], xmm0

            mov counterSumFourValues, edx
            sub counterSumFourValues, 1

            fld dword ptr [eax]                     ; adiciono o EAX[0] à stack de float - preciso de adiconar antes senao dentro do ciclo apenas 1 nao funciona

            SumValuesLoop:

                add eax, 4
                fld dword ptr [eax]
                faddp                               ; somo os ultimos valores na stack de floats

                dec counterSumFourValues
                jnz SumValuesLoop

            ;END SumValuesLoop

            sub eax, 12                             ; !! Nao pode sert hardcode 12, por 12 é se for size 4, se for 8, ja vai efetuar o add eax 7 vez já é 4 * 7
            fstp dword ptr [edi]                    ; !! Preciso incremetar o edi para poder percorer [0][0], [0][1], etc

            add edi, edx                            ; Incrementar o edi + size, ex: +4 faz com que o proximo registo fique no edi[0,1]

            add ecx, offSetVar

            dec counterSecondFor
            jnz SecondCycleFor
            
        ;END SecondCycleFor

        add ebx, offSetVar

        sub ecx, 64                                  ; Remover o add do ecx para voltar ao inicio, ora se fizer o segundoFor 4 vezer, signifca que ecx = 4 * 16; sub ecx 64  !! Remover hardcode

        dec counterFirstFor                                   
        jnz FirtCycleFor

    ;END FirtCycleFor

    pop ebp									            ; Restore the EBP
    ret										            ; End the function and return to the main

MultiplyMatrixWithAssembly ENDP







SimpleMultiplyWithXMMAnyArrayValues1D PROC
                push ebp								; Save de EBP in the stack
	            mov ebp,esp								; Copy the ESP to EBP

	            mov edi, [esp + 8]		                ; Porque os registo guarda apenas os primeiro 4, porque soa registo 32bits 				; arrayResult +8Bytes
                mov ebx, [esp + 12]						; ArrayOne
                mov ecx, [esp + 16]						; ArrayTwo
                mov edx, [esp + 20]                     ; Size

                shr edx, 2                              ; Guardar o valor de quantas veze preciso de fazer o ciclo ; Cada shift é uma divisao por 2, ou seja shift de 2 é dividir por 4                                         

FirtCycleFor:   movdqu xmm0, [ebx]                      ; Como ebx é o inicio do array, estou a mover apenas os 4 primeiros bytes
                movdqu xmm1, [ecx]

                mulps xmm0, xmm1                        ; Multiplicar xmm0 com xmm1
                movdqu [edi], xmm0                      ; Mover o resultado de xmm0 para [edi]

                add ebx, 16                             ; adiciono 16 bytes, porque cada valor ocupa 4  
                add ecx, 16        
                add edi, 16

                dec edx
                jnz FirtCycleFor

	            pop ebp									; Restore the EBP
                ret										; End the function and return to the main
SimpleMultiplyWithXMMAnyArrayValues1D ENDP	        ; Indicates the end of the function.


END											; indicate the end of the asm file