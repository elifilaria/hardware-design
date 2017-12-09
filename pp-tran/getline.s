
	_EXIT = 1
	_WRITE = 4
	_STDOUT = 1
	_STDIN = 0
	_GETCHAR = 117

	MAXBUFF = 80

.SECT .TEXT
start:
	PUSH	endpr-prompt	! print prompt
	PUSH	prompt
	PUSH	_STDOUT		! on standard output
	PUSH	_WRITE
	SYS
	ADD	SP,8

	PUSH 	MAXBUFF
	PUSH 	buff
	CALL 	getline
	ADD 	SP,4


getline:
	PUSH 	BP
	PUSH 	BX
	PUSH 	CX
	MOV 	SP,BP
	MOV 	BX,4(BP)

1: 	PUSH 	DX
	MOV 	DX, 6(BP)
	SUB 	DX, 1
	CMP 	DX, BX
	JE 		2f
	PUSH 	_GETCHAR
	SYS
	ADD 	SP,2
	CMP 	AX,-1
	JE 		2f
	MOV 	BX, AX
	INC 	BX
	CMPB 	(BX), '\n'
	JE 	 	2f
	JMP 	1b

2: 	PUSH 	0
	PUSH 	_EXIT
	SYS
	JMP 	3f

3: 	MOV 	(BX),'0'
	SUB 	BX, 4(BP)
	MOV  	CX, BX
	POP 	CX
	POP 	BX
	POP 	BP
	RET



.SECT .DATA
prompt:	.ASCII "Enter a line of text: "
endpr:
buff: .SPACE MAXBUFF
.SECT .BSS