.MODEL FLAT, C								; Use the flat memory model. Use C calling conventions
.DATA										; indicates the start of variable definitions


var_byte DB 1								; Define a variable named 'var_byte' with a size of 1 byte and a value of 1
var_word DW 2								; Define a variable named 'var_word' with a size of 2 bytes and a value of 2
var_dword DD 3								; Define a variable named 'var_dword' with a size of 4 bytes and a value of 3
var_qword DQ 4								; Define a variable named 'var_qdword' with a size of 8 bytes and a value of 4
list_byte DB 1024 DUP(?)					; Define a variable named 'list_byte' with a size of 1*1024 bytes. it's an byte array
list_int DD 0,1,2,3							; Define a variable named list_int with size 4*4 bytes. It´s an int array 


.CODE										; Indicates the start of the code segment.



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




SimpleMultiplyWithXMMFourArrayValues PROC
    push ebp								; Save de EBP in the stack
	mov ebp,esp								; Copy the ESP to EBP

	xor eax, eax							; Clear register EAX
	xor ebx, ebx							; Clear register EBX
	xor ecx, ecx							; Clear register ECX

	mov eax, [esp + 8]						; arrayResult
    mov ebx, [esp + 12]						; arrayOne
    mov ecx, [esp + 16]						; arrayTwo

	xor esi, esi							; Clear register ESI
	pxor xmm0, xmm0							; Clear register XMM0
    mov esi, ebx							; Mov EBX to ESI
    movdqu xmm0, [esi]						; Mov [ESI] to XMM0

	xor esi, esi							; Clear register ESI
	pxor xmm1, xmm1							; Clear register XMM1
    mov esi, ecx							; Mov EBX to ESI
    movdqu xmm1, [esi]						; Mov [ESI] to XMM0

	mulps xmm0, xmm1						; Multiply XMM0 with XMM1

	xor edi, edi							; Clear register EDI
    mov edi, eax							; Mov EAX to EDI
    movdqu [edi], xmm0						; Mov XMM0 to [EDI]

	pop ebp									; Restore the EBP
    ret										; End the function and return to the main
SimpleMultiplyWithXMMFourArrayValues ENDP	; Indicates the end of the function.





MultiplyMatrixWithTransposeAssembly PROC
    push ebp								; Save de EBP in the stack
	mov ebp,esp								; Copy the ESP to EBP


	pop ebp									; Restore the EBP
    ret										; End the function and return to the main
MultiplyMatrixWithTransposeAssembly ENDP	; Indicates the end of the function.


END											; indicate the end of the asm file