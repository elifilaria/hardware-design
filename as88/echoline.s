!!! changes capital input letter to corresponding lower case letter in the output

	_EXIT = 1
	_READ = 3
	_WRITE = 4
	_STDIN = 0
	_STDOUT = 1
	_GETCHAR = 117

	MAXBUFF = 100

.SECT .TEXT
start:
	PUSH	endpr-prompt	! print prompt
	PUSH	prompt
	PUSH	_STDOUT		! on standard output
	PUSH	_WRITE
	SYS
	ADD	SP,8		! clean up stack

	PUSH  	MAXBUFF
	PUSH 	buff
	CALL 	getline
	ADD 	SP, 4

getline:
	PUSH 	BX
	PUSH	CX
	PUSH	BP
	MOV		BP,SP
	MOV		BX,8(BP)
	MOV		CX,8(BP)
	ADD		CX,10(BP)
	SUB		CX,1

1:	CMP 	CX, BX	
	JE 		2f
	PUSH	_STDIN		
	PUSH	_GETCHAR
	SYS
	ADD	SP,2		


	CMPB 	AL,-1
	JE 		2f
	MOVB 	(BX), AL
	INC 	BX
	CMPB 	AL, '\n'
	JNE 	1b

2: 	MOVB 	(BX), 0
	MOV 	AX, BX
	SUB 	AX, 8(BP)
	CALL 	byte
	POP 	BP
	POP 	CX
	POP 	BX
	RET
	PUSH	endstr-str

9: 	PUSH 	0
	PUSH 	_EXIT
	SYS

byte:
	PUSH 	str 
	PUSH 	_STDOUT
	PUSH 	_WRITE
	SYS
	ADD SP,8

	PUSH 	0
	PUSH 	_EXIT
	SYS


.SECT .DATA
prompt:	.ASCII "Enter a line of text: "
endpr:
str: .ASCII "You entered: "
endstr:
size:	.WORD	0		! length of input

.SECT .BSS
buff:
	.SPACE MAXBUFF
