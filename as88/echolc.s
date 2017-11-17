!!! copy standard input to standard output, skipping spaces
!!! R. Brown, 11/05

	_EXIT = 1
	_READ = 3
	_WRITE = 4
	_STDIN = 0
	_STDOUT = 1

	BUFFSIZE = 80
.SECT .TEXT
start:
	PUSH	endpr-prompt	! print prompt
	PUSH	prompt
	PUSH	_STDOUT		! on standard output
	PUSH	_WRITE
	SYS
	ADD	SP,8		! clean up stack
	PUSH	BUFFSIZE	! read input line
	PUSH	buff
	PUSH	_STDIN		! from standard input
	PUSH	_READ
	SYS
	ADD	SP,8		! clean up stack

	PUSH 	endpr2-prompt2
	PUSH 	prompt2
	PUSH 	_STDOUT
	PUSH 	_WRITE
	SYS
	ADD SP,8

	ADD 	(buff),32
	PUSH 	BUFFSIZE
	PUSH 	buff
	PUSH 	_STDOUT
	PUSH 	_WRITE
	SYS
	ADD SP, 8


.SECT .DATA
prompt:	.ASCII "Enter an upper case letter: "
endpr:
prompt2: .ASCII "The lower-case equivalent is: "
endpr2:
size:	.WORD	0		! length of input

.SECT .BSS
buff:	.SPACE BUFFSIZE
endbuff:
	