    _EXIT   = 1
    _WRITE  = 4
    _STDOUT = 1
    _GETCHAR = 117
    _STDERR = 2

    BUFFSIZE = 100

.SECT .TEXT
start:
0:  PUSH    endpr-prompt !print the first prompt
    PUSH    prompt
    PUSH    _STDERR
    PUSH    _WRITE
    SYS
    ADD     SP,8

    PUSH    BUFFSIZE
    PUSH    buff
    CALL    getline
    ADD     SP,4
    CMP     AX,1
    JE      0b

    PUSH    buff
    CALL    gettrans
    ADD     SP,2
    CMP     AX,0
    JE      0b


1:  PUSH    BUFFSIZE
    PUSH    buff
    CALL    getline
    ADD     SP,4
    CMP     AX,1
    JE      9f

3:  MOV     (inword), 0
    PUSH    buff 
    CALL    translate
    ADD     SP,2
    CMP     AX,1
    JE      9f


4:  PUSH    AX
    PUSH    buff
    PUSH    _STDOUT
    PUSH    _WRITE
    SYS
    ADD     SP,8
    JMP     1b


9:  CALL    print_summary
    PUSH    0
    PUSH    _EXIT
    SYS

getline:
    PUSH    BP
    MOV     BP,SP
    PUSH    BX
    PUSH    CX

    MOV     BX,4(BP)
    MOV     CX,6(BP)
    SUB     CX,1

1:  CMP     CX,BX
    JE      3f
    PUSH    1
    PUSH    _GETCHAR
    SYS
    ADD     SP,4

    CMPB    AL,-1
    JE      3f
    MOVB    (BX),AL
    CMPB    (BX),'\n'
    JE      2f
    INC     BX
    JMP     1b

2:  INC     BX

3:  MOVB    (BX),0
    SUB     BX,4(BP)
    MOV     AX,BX
    POP     CX
    POP     BX
    POP     BP
    RET

gettrans:
    PUSH    BP
    MOV     BP, SP
    PUSH    BX
    MOV     BX, 4(BP)

    PUSH    BX
    CALL    strlen
    ADD     SP,2
    CMP     AX,4
    JNE     1f

    
    CMPB    4(BX),' '
    JE     1f  


    MOVB    CL,(BX)
    MOVB    (inchar),CL
    ADD     BX,2
    MOVB    CL,(BX)
    MOVB    (outchar),CL
    MOV     AX,1
    JMP     2f

1:  MOV     AX,0

2:  POP     BP
    POP     BX
    RET

translate:
    PUSH    BP
    MOV     BP, SP
    PUSH    BX
    PUSH    CX
    PUSH    DX
    MOV     BX, 4(BP)


    MOV     DX, (inword)

1:  CMPB    (BX),0
    JE      9f

2:  CMPB     (BX),'A'
    JL       4f
    CMPB     (BX),'z'
    JG       4f
    INC      (charct)
    CMP      DX,0
    JNE      3f
    INC     (wordct)

    
3:  MOV     DX,1             
    JMP     5f

4:  MOV     DX,0

5:  CMPB    (BX),'\n'
    JNE     6f 
    INC     (linect)

6:  MOVB    AL,(inchar)
    CMPB    (BX),AL
    JNE     7f
    MOVB    AL,(outchar)
    MOVB    (BX),AL
    INC     BX
    JMP     2b

7:  CMPB    (BX), '\n'
    JE      8f

8:  INC     BX
    JMP     1b


9:  MOV     (inword), DX
    SUB     BX, 4(BP)
    MOV     AX, BX
    POP     DX
    POP     CX
    POP     BP
    POP     BX
    RET


print_summary:
    PUSH    (linect)
    PUSH    (wordct)
    PUSH    (charct)
    CALL    rab_print_summary
    ADD SP,6
    RET

.SECT .DATA
prompt:
    .ASCII  "Enter 2 characters for translation: \n"
endpr:

outchar:
    .BYTE   0

inchar:
    .BYTE   0

charct:
    .WORD   0

wordct:
    .WORD   0

linect:
    .WORD   0

inword:
    .WORD   0

.SECT .BSS
buff:   .SPACE BUFFSIZE
endbuff:

