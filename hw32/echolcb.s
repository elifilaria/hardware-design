!!! copy standard input to standard output, skipping spaces
!!! R. Brown, 11/05

	_EXIT = 1
	_READ = 3
	_WRITE = 4
	_STDIN = 0
	_STDOUT = 1
	_GETCHAR = 117

	BUFFSIZE = 80


.SECT .TEXT
start:
	PUSH	endpr-prompt	! print prompt
	PUSH	prompt
	PUSH	_STDOUT		! on standard output
	PUSH	_WRITE
	SYS
	ADD	SP,8		! clean up stack

	PUSH 	1
	PUSH	buff
	PUSH	_STDIN		! from standard input
	PUSH	_GETCHAR
	SYS
	ADD	SP,2		! clean up stack

	MOVB 	(buff+1), 10

	PUSH 	1
	MOVB 	(BX), AL
	ADDB	(BX), 32


	PUSH 	endpr2-prompt2
	PUSH 	prompt2
	PUSH 	_STDOUT
	PUSH 	_WRITE
	SYS
	ADD SP,8
	PUSH 	1
	PUSH 	BX	
	PUSH 	_STDOUT
	PUSH 	_WRITE
	SYS
	ADD SP, 8


	PUSH 	0
	PUSH 	_EXIT
	SYS


.SECT .DATA
prompt:	.ASCII "Enter an upper case letter: "
endpr:
prompt2: .ASCII "The lower-case equivalent is: "
endpr2:
size:	.WORD	0		! length of input

.SECT .BSS
buff:	.SPACE 2
.SECT .BSS
endbuff:
	