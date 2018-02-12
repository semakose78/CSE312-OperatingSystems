        ; 8080 assembler code
        .hexfile Sort.hex
        .binfile Sort.com
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

;fill the array

array:	dw 012H, 034H, 053H, 02AH, 05BH, 06FH, 033H, 021H, 07CH, 0FFH, 0BAH, 0CBH, 0A1H, 01AH, 03BH, 0C3H, 04AH, 05DH, 062H, 0A3H, 0B1H, 05CH, 07FH, 0CCH, 0AAH, 034H, '00AH'; initialize the array

;length of the array
Length: equ 019H

begin:
	LXI SP,stack 	; always initialize the stack pointer
	LXI H, array
	MVI D, 000H
	MVI E, 000H

Loop:
	INR D ; increment counter D
	MOV A, D ; compare D and A
	CPI Length ; if it's the end
	JZ First ; return to the start for recomparing
Cont:	
	MOV A, M ; if it's not the end then move the element of memory to A
	INX H
	INX H
	MOV B, M ; move the next element to B
	CMP B ; compare A and B
	JNC Swap ; swap the numbers if A > B ; swap if A>B
	JC Loop

Swap:
	MOV C, A
	MOV A, B
	MOV B, C
	MOV M, B ; change content
	DCX H
	DCX H
	MOV M, A ; change content
	INX H
	INX H
	JMP Loop

Halt :
	MVI D, Length
	LXI B, array
	MVI A, PRINT_MEM	; store the OS call code to A
	call GTU_OS	; call the OS
	hlt		; end program

First:
	MVI D, 000H
	LXI H, array
	INR E
	MOV A, E
	CPI Length
	JZ Halt
	JMP Cont