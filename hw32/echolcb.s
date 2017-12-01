!!! changes capital input letter to corresponding lower case letter in the output

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

	PUSH	1	! read input line
	PUSH	buff
	PUSH	_STDIN		! from standard input
	PUSH	_GETCHAR
	SYS
	ADD	SP,2		! clean up stack
	MOVB 	(buff), AL
	ADDB 	(buff),32
	PUSH 	endstr-str


byte:
	PUSH 	 str 
	PUSH 	_STDOUT
	PUSH 	_WRITE
	SYS
	ADD SP,8

	PUSH 	0
	PUSH 	_EXIT
	SYS


.SECT .DATA
prompt:	.ASCII "Enter an upper case letter: "
endpr:
str: .ASCII "The lower-case equivalent is: "
buff:
	.BYTE 0
	.ASCII "\n"
endstr:
size:	.WORD	0		! length of input

.SECT .BSS

	