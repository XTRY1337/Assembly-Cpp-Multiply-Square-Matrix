.MODEL FLAT, C				; Use the flat memory model. Use C calling conventions
.DATA						; indicates the start of variable definitions


var_byte DB 1				; Define a variable named 'var_byte' with a size of 1 byte and a value of 1
var_word DW 2				; Define a variable named 'var_word' with a size of 2 bytes and a value of 2
var_dword DD 3				; Define a variable named 'var_dword' with a size of 4 bytes and a value of 3
var_qword DQ 4				; Define a variable named 'var_qdword' with a size of 8 bytes and a value of 4
list_byte DB 1024 DUP(?)	; Define a variable named 'list_byte' with a size of 1*1024 bytes. it's an byte array
list_int DD 0,1,2,3         ; Define a variable named list_int with size 4*4 bytes. It´s an int array 


.CODE						; Indicates the start of the code segment.

add_int PROC				; indicates the function name (used format: add_int(int x1, int x2)) 
	push ebp				; first instruction in the function. Save de EBP in the stack
	mov ebp,esp				; copy the ESP to EBP
	mov eax,[ebp+8]			; get the first parameter (x1)
	add eax,[ebp+12]		; add the first parameter with the second parameter
	pop ebp					; restore the EBP
	ret						; end the function and return to the main
add_int ENDP				; indicates the end of the function. Any other function must be write after this line

END							; indicate the end of the asm file