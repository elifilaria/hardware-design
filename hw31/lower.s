! Example assembly program
! RAB 11/05
        
        _EXIT   = 1             
        _READ   = 3             
        _WRITE  = 4             
        _STDIN  = 0             
        _STDOUT = 1
        _GETCHAR = 117

.SECT .TEXT                     
start:                          ! print prompt, as detailed in the next five instructions
        push    buff-prompt     ! third arg is length of prompt
        push    prompt          ! second arg is address of prompt
        push    _STDOUT         ! first arg is standard output
        push    _WRITE          ! name of the OS function being called
        sys                     ! perform the system call
        add     SP,8            ! clean up stack
                        
        push    2               ! read two characters...
        push    buff            ! into buff...
        push    _STDIN          ! from standard input
        push    _GETCHAR
        sys
        add     SP,2            ! clean up stack
                                ! store value in variable AL
        push    2               ! then print those characters
        movb    (BX),AL
        add     (BX),32
        push    BX
        push    _STDOUT         ! on standard output
        push    _WRITE
        sys
        add     SP,8            ! clean up stack

        push    0               ! exit with normal exit status
        push    _EXIT           
        sys                     
        
.SECT .DATA                     
prompt:                         
.ASCII  "Enter a line of characters:  "         
buff:   .SPACE	2
.SECT .BSS