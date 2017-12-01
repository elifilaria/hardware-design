    _EXIT = 1
    _READ = 3
    _WRITE = 4
    _STDIN = 0
    _STDOUT = 1

    BUFFSIZE = 80
.SECT .TEXT
start:
    push    endpr-prompt    ! print prompt
    push    prompt
    push    _STDOUT     ! on standard output
    push    _WRITE
    sys
    add SP,8        ! clean up stack
    push    BUFFSIZE    ! read input line
    push    buff
    push    _STDIN      ! from standard input
    push    _READ
    sys
    add SP,8        ! clean up stack

    !! assert: AX holds number of bytes that were read
    MOV DX,AX
    add DX,buff     ! set DX to addr of first byte after input
    MOV BX,buff     ! initialize loop
1:  !! loop invar: all non-space chars before (BX) have been printed
    CMP BX,DX       ! if unprocessed bytes remain in buff...
    JE  9f
    CMPB    (BX),'A'    ! then if next byte is not a space...
    JL 	3f
    CMPB (BX), 'Z'
    JG 3f
    ADDB (BX),32

3:  
	push    1
	push BX
	push 	_STDOUT
    push    _WRITE
    sys
    add SP,8
    INC BX
    JMP 1b      ! end of loop

9:  push    0       ! normal exit status
    push    _EXIT       ! end program
    sys

.SECT .DATA
prompt: .ASCII "Enter input: "
endpr:
size:   .WORD   0       ! length of input

.SECT .BSS
buff:   .SPACE BUFFSIZE
endbuff:
    !1  set up stack frame
    !   save registers (BP, 2)
    !2  Body of function
    ! CMPB 4(BP), ' '
    ! 3 Asign value to AX
    ! 4 restore BP and return
    !ALMOST A PRIMATIVE IF IFELSE ELSE FUNC