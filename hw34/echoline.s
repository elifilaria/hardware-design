	_EXIT 	= 1
	_READ	= 3
	_WRITE 	= 4
	_STDOUT = 1
	_STDIN = 1
	_STDERR = 2
	_GETCHAR = 117

	MAXBUFF = 100

.SECT .TEXT
start:
0:	push	endprompt2-prompt2
	push	prompt2
	push	_STDOUT
	push	_WRITE
 	sys
 	add	SP,8
 	push	5
	push	buff
	call	getline
	add	SP,4
	push	buff
	call	gettrans
	add	SP,2
	add	AX,1 !gives AX an intial value to start loop
1:	cmp	AX,0
	je	2f
	push	endprompt-prompt1
	push	prompt1
	push 	_STDOUT
	push	_WRITE
	sys
	add	SP,8
	push	MAXBUFF
	push	buff
	call	getline
	add	SP,2
	push	buff

	call	translate
	add	SP,2
	jmp	1b
2:	push    0               ! exit with normal exit status
        push    _EXIT           
        sys
	
getline:
	push	BX
	push	CX
	push	BP
	mov		BP,SP
	mov		BX,8(BP)
	mov		CX,8(BP)
	add		CX,10(BP)
	sub		CX,1

1:	cmp		CX,BX
	je		2f
	push	_GETCHAR
	sys

	add		SP,2
	cmpb	AL,-1
	je		2f
	movb	(BX),AL
	inc		BX
	cmpb	AL,'\n'
	JNE		1b

2:	movb	(BX),0
	mov		AX, BX
	sub		AX,8(BP)
	pop		BP
	pop		CX
	pop		BX
	ret
gettrans:
	push	BX
	push	BP
	mov		BP,SP
	mov		BX,6(BP) !Store argument in BX
	movb	CL, (BX)
	movb	(inchar),CL
1:	inc		BX
	cmpb	(BX),' '
	je		1b
	movb	CL, (BX)
	movb	(outchar),CL

	
	mov		AX,1
	pop		BP
	pop		BX
	ret



translate:
	push	BX
	push	BP
	mov		BP,SP
	mov		BX,6(BP)
	
1:	inc		(charcount)
	cmpb	(BX),'\n'
	je		4f
	cmpb	(BX),' '
	je		2f
	movb	CL,(inchar)
	cmpb	(BX),CL
	je		3f
2:	push	1		! print that byte
	push	BX
	push	_STDOUT
	push	_WRITE
	sys
	add		SP,8
	inc		BX
	jmp		1b
	
3:	movb	CL,(outchar)
	movb	(BX),CL
	push	1		! print that byte
	push	BX
	push	_STDOUT
	push	_WRITE
	sys
	add		SP,8
	inc		BX
	jmp		1b

4:	call	printnl
	inc		(linecount)
	push	(linecount)
	push	_STDERR
	call	printdec
	call	printnl
	add		SP,4
	pop		BP
	pop		BX
	ret
	

	
print_summary:
	push	1
	push	wordcount
	push	_STDOUT
	push	_WRITE
	sys
	add		SP,8
	call	printnl
	ret


.SECT .BSS
buff:
	.SPACE	MAXBUFF
	
.SECT .DATA
prompt1:
	.ASCII	"Enter add line of text: "
endprompt:
	
prompt2:
	.ASCII	"Enter 2 characters for translation: "
endprompt2:	

outchar:
	.BYTE	0
inchar:
	.BYTE	0
charcount:
	.WORD	0
wordcount:
	.WORD	0
linecount:
	.WORD	0
inword:
	.WORD	0