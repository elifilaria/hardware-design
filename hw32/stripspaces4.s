!!! copy standard input to standard output, skipping spaces
!!! stripspaces4

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
    mov DX,AX
    add DX,buff     ! set DX to addr of first byte after input
    mov BX,buff     ! initialize loop
1:  !! loop invar: all non-space chars before (BX) have been printed
    cmp BX,DX       ! if unprocessed bytes remain in buff...
    je  9f
    push    (BX)
    call    isspace     ! then if next byte is not a space...
    add SP,2
    cmp AX,1
    je  2f
    push    1       ! print that byte
    push    BX
    push    _STDOUT
    push    _WRITE
    sys
    add SP,8
    push    1       ! print that byte

2:  inc BX      ! move to next char of buff
    jmp 1b      ! end of loop

9:  push    endn-newline
    PUSH    newline
    push    _STDOUT
    push    _WRITE
    sys
    add SP,8
    push    0       ! normal exit status
    push    _EXIT       ! end program
    sys

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



.SECT .DATA
prompt: .ASCII "Enter input: "
endpr:
newline: .ASCII "\n"
endn:
size:   .WORD   0           ! length of input

.SECT .BSS
buff:   .SPACE BUFFSIZE
endbuff:
    
