!Modified: 12 December 2017
!Author: 
!Elif Yurtseven - 2017



    _EXIT   = 1
    _WRITE  = 4
    _STDOUT = 1
    _GETCHAR = 117
    _STDERR = 2

    BUFFSIZE = 100

.SECT .TEXT
start:
0:  PUSH    endpr-prompt !print prompt
    PUSH    prompt
    PUSH    _STDERR !on standard error
    PUSH    _WRITE
    SYS !system call
    ADD     SP,8 !clean up stack

!call getline for line explaining the translation
    PUSH    BUFFSIZE !first argument of getline
    PUSH    buff !arg2 getline
    CALL    getline
    ADD     SP,4
    CMP     AX,1 !check return of getline if one character inputted go back to beginning (one char is newline)
    JE      0b

!call gettrans
    PUSH    buff
    CALL    gettrans
    ADD     SP,2
    CMP     AX,0 !if gettrans returns 0 no char is ready to translate go back to beginning
    JE      0b

!call getline again for line to translate
1:  PUSH    BUFFSIZE
    PUSH    buff
    CALL    getline
    ADD     SP,2
    CMP     AX,1
    JE      9f

3:  MOV     (inword), 0
    PUSH    buff 
    CALL    translate
    ADD     SP,2
    CMP     AX,1
    JE      9f


4:  PUSH    AX !push the number of characters (return of getline function)
    PUSH    buff
    PUSH    _STDOUT !on standard output because this is the translation
    PUSH    _WRITE
    SYS
    ADD     SP,8
    JMP     1b


9:  CALL    print_summary !print tje summary
    PUSH    0
    PUSH    _EXIT
    SYS

getline:
!set up stack and registers
    PUSH    BP
    MOV     BP,SP
    PUSH    BX
    PUSH    CX

    MOV     BX,4(BP)
    MOV     CX,6(BP) !address of last character
    SUB     CX,1

1:  CMP     CX,BX !check when BX reaches last char
    JE      3f
    PUSH    1
    PUSH    _GETCHAR !read the characters with getchar
    SYS
    ADD     SP,4

    CMPB    AL,-1 !check if input char is valid
    JE      3f !if so call translate function 
    MOVB    (BX),AL !if not move it to BX
    CMPB    (BX),'\n' !leave getline when input is a newline
    JE      2f 
    INC     BX
    JMP     1b

2:  INC     BX

!when BX is at last character
3:  MOVB    (BX),0 !put nullbyte in BX (end of it)
    SUB     BX,4(BP) !put number of characters in AX (return value)
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

    PUSH    BX !address of input characters as argument 
    CALL    strlen
    ADD     SP,2
    CMP     AX,4 !does input have correct length?
    JNE     1f !if so go to next character

    
    CMPB    4(BX),' ' !check if it is space character
    JE     1f  !if not retrun 0, gettrans is not successful because input was not correct format


    MOVB    CL,(BX) 
    MOVB    (inchar),CL !copy char to inchar
    ADD     BX,2
    MOVB    CL,(BX)
    MOVB    (outchar),CL !copy third char into outchar
    MOV     AX,1 !make return value 1
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


    MOV     DX, (inword) !initialize DX as inword (1 if inside a word, 0 if otside)

1:  CMPB    (BX),0 !check if first character is nullbyte
    JE      9f

2:  CMPB     (BX),'A' !check if the input is a upper or lower case character
    JL       4f
    CMPB     (BX),'z'
    JG       4f
    INC      (charcount)
    CMP      DX,0 !check if inside a word
    JNE      3f
    INC     (wordcount) !if was not in a word and encountererd a character increment wordcount

    
3:  MOV     DX,1            !set DX to 1 meaning that we are now inside a word  
    JMP     5f

4:  MOV     DX,0

5:  CMPB    (BX),'\n'
    JNE     6f 
    INC     (linecount) !if newline increment linecount

6:  MOVB    AL,(inchar) !copy inchar to AL
    CMPB    (BX),AL !if AL not equal to BX do not switch the character
    JNE     7f
    MOVB    AL,(outchar) !if it is switch inchar character with outchar character
    MOVB    (BX),AL
    INC     (changedchar) !every time you switch, increment the counter for changedchar
    INC     BX !check next character
    JMP     2b

7:  CMPB    (BX), '\n'
    JE      8f

8:  INC     BX !check next character
    JMP     1b


9:  MOV     (inword), DX !set DX to inword to keep track of whether you are inside or outside of a word in case you run out of BUFFSIZE
    SUB     BX, 4(BP)
    MOV     AX, BX !set return value
    POP     DX !clean up registers
    POP     CX
    POP     BP
    POP     BX
    RET !return AX


print_summary:
    PUSH endpr2-prompt2 !push prompt2
    PUSH prompt2
    PUSH _STDERR !on standard error
    PUSH _WRITE
    SYS
    ADD SP,8

    PUSH (charcount)
    PUSH _STDERR
    CALL printdec
    ADD SP,4
    PUSH endpr3-prompt3
    PUSH prompt3
    PUSH _STDERR
    PUSH _WRITE
    SYS
    ADD SP,8

    PUSH (wordcount)
    PUSH _STDERR
    CALL printdec
    ADD SP,4
    PUSH endpr4-prompt4
    PUSH prompt4
    PUSH _STDERR
    PUSH _WRITE
    SYS
    ADD SP,8

    PUSH (linecount)
    PUSH _STDERR
    CALL printdec
    ADD SP,4
    PUSH endpr5-prompt5
    PUSH prompt5
    PUSH _STDERR
    PUSH _WRITE
    SYS
    ADD SP,8

    PUSH (changedchar)
    PUSH _STDERR
    CALL printdec
    ADD SP,4
    PUSH endpr6-prompt6
    PUSH prompt6
    PUSH _STDERR
    PUSH _WRITE
    SYS
    ADD SP,8

.SECT .DATA
prompt:
    .ASCII  "Enter 2 characters for translation: \n"
endpr:

prompt2:
    .ASCII "Summary: \n"
endpr2:

prompt3:
    .ASCII " characters\n"
endpr3:

prompt4:
    .ASCII " words\n"
endpr4:

prompt5:
    .ASCII " lines\n"
endpr5:

prompt6:
    .ASCII " changed characters\n"
endpr6:

outchar:
    .BYTE   0

inchar:
    .BYTE   0

charcount:
    .WORD   0

wordcount:
    .WORD   0

linecount:
    .WORD   0

inword:
    .WORD   0

changedchar:
    .WORD   0

.SECT .BSS
buff:   .SPACE BUFFSIZE
endbuff:

