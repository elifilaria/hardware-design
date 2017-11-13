! Simple "hello world" program
! heavily commented for first-time assembly programmers

	_EXIT	= 1		! define the symbol _EXIT
	_WRITE	= 4		! define the symbol _WRITE
	_STDOUT	= 1		! define the symbol _STDOUT

.SECT .TEXT			! begin the code segment (.TEXT)
start:				! optional label for first instr
	MOV	CX,endhw-hw	! move length of string to CX
	PUSH	CX		! perform _WRITE:  push arg3
	PUSH	hw		!    push arg2
	PUSH	_STDOUT		!    push arg1
	PUSH	_WRITE		!    push system-call number
	SYS			!    perform system call
	ADD	SP,8		!    clean up the stack
	SUB	CX,AX		! subtract return value from len
	PUSH	CX		! perform _EXIT:  push arg1
	PUSH	_EXIT		!    push system-call number
	SYS			!    perform system call

.SECT .DATA			! begin data segment (.DATA)
hw:				! label for string value
.ASCII	"Hello World\n"		! contents of string
.ASCII	"Hello World\n"
endhw:	.BYTE	0		! label for computing string len
	
.SECT .BSS			! begin zero-initialized data
				! segment (.BSS), which is empty