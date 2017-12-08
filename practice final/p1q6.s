
	_EXIT = 1
	_WRITE = 4
	_STDOUT = 1
	NUMCHAR = 80

.SECT .TEXT

	PUSH 	NUMCHAR
	PUSH 	buff
	CALL 	count_spaces
	ADD SP,4

!	PUSH 	2
!	PUSH 	spacect
!	PUSH 	_STDOUT
!	PUSH 	_WRITE
!	SYS
!	ADD SP,8	


count_spaces:
1:	PUSH 	BP
	MOV 	SP, BP
	PUSH 	BX
	MOV 	BX, 4(BP)
	PUSH 	DX
	MOV 	DX, 4(BP)
	ADD 	DX, 6(BP)
	PUSH 	CX
	MOV 	CX, 0
 	CMP 	BX, DX
	JE 		2f
	PUSH 	(BX)
	CALL 	isspace
	ADD 	SP,2
	INC 	CX
	INC 	BX
	JMP 	1b


2: 	ADD 	CX, (spacect)
	RET
	JMP 3f

3: 	POP 	CX
	POP 	DX
	POP 	BX
	POP 	BP
	RET


isspace:
0:  push    BX
    push    BP
    mov BP,SP
1:  cmpb    (BX),' '
    je  2f
    cmpb    (BX),0x9
    JLE 2f
    cmpb    (BX),0xD
    JL  2f
    jmp 3f
2:  mov AX,1
    jmp 4f
3:  mov AX,0
4:  pop BP
    pop BX
    ret


.SECT.DATA
buff: .ASCII "My name is Elif Ilaria "
spacect: .WORD 0

.SECT .BSS
