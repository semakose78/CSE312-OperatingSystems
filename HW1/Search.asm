        ; 8080 assembler code
        .hexfile Search.hex
        .binfile Search.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        

; fill the array
array:	dw 012H, 034H, 053H, 02AH, 05BH, 06FH, 033H, 021H, 07CH, 0FFH, 0BAH, 0CBH, 0A1H, 01AH, 03BH, 0C3H, 04AH, 05DH, 062H, 0A3H, 0B1H, 05CH, 07FH, 0CCH, 0AAH, 034H; initialize the array

;length of the array
Length: equ 019H

;fill the error string
string: dw 'error!',00AH,00H ; null terminated error string

begin:
	LXI SP,stack 	; always initialize the stack pointer
	MVI A, READ_B	; store the OS call code to A
	call GTU_OS	; call the OS
	LXI D, array ; initialize the array pointer
	MVI H, 0

Loop:
	LDAX D ;load the first element to A
	CMP B ; compare with B
	INX D
	INX D
	JZ subfunc ; if same, then it's found! jump to subfunc for print the index
	INR H ; increment the counter H
	MOV A, H
	CPI 019H ; if it's the end
	JZ subfunc_2 ;jump to subfunc2 for error
	JNZ Loop

subfunc:
	DCX D
	DCX D
	MOV B,H
	MVI A, PRINT_B
	call GTU_OS	; call the OS
	JMP halt

subfunc_2:
	LXI B, string
	MVI A, PRINT_STR	; store the OS call code to A
	call GTU_OS	; call the OS
	JMP halt

halt:	hlt		; end program