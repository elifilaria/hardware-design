! Example assembly program
! crypt

        _EXIT   = 1             
        _READ   = 3             
        _WRITE  = 4             
        _STDIN  = 0             
        _STDOUT = 1 


.SECT .TEXT
start:
	PUSH	buff-prompt
	PUSH	prompt
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	PUSH	5
	PUSH	buff
	PUSH	_STDIN
	PUSH	_READ
	SYS
	ADD	SP,8
	MOV	BX,buff
	PUSH	(BX)
	CALL 	crypt
	ADD	SP,2
	PUSH	5
	PUSH	BX
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	PUSH	0
	PUSH	_EXIT
	SYS
	
	
crypt:
1:	PUSH	BX
	PUSH	BP
	MOV	BP,SP
	CMPB	(BX),0x7F
	JE	4f
	CMPB	(BX),0x20
	JGE	2f
	CMPB	(BX),0x7F
	JGE	3f
2:	ADD	(BX),4
	JMP	4f
3:	SUB	(BX),0x5F
4:	MOV	AX,(BX)
	POP	BP
	POP	BX
	RET

.SECT .DATA                     
prompt:                         
.ASCII  "Enter a character for a cryptic:  then press ENTER:  "         
buff:   .SPACE	5
.SECT .BSS
