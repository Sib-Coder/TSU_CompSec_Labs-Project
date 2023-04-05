extern printf

SECTION .data
msg1        db      'x = ', 0h                                          ; message1
msg2        db      'y = ', 0h                                           ; message2
err         db      '(overflow detected, but its all under control)', 0h  ; error message
dbg         db      'Debug number output: ', 0h                           ; debug
dbg2        db      '----', 0h                                      ; debug2
dbg4        db      ' .... ', 0h                                  ; debug4
dbg5        db      0Ah, 'Column maximum: ', 0h                               ; debug5
sep         db      ', ', 0h                                             ; separator
space       db      ' ', 0h                                            ; space
seed        dd      0h
; LAB 10
floatmin:   dd      -0.7
floatmax:   dd      0.7
floath:     dd      0.1
zero:       dd      0
one:        dd      1.0
temp:       dq      0.0
buf1:       dq      0.0
buf2:       dq      0.0
buf3:       dq      0.0
bufi1:      dd      0
cwr:        dd      0

message: db '%f', 10, 0
number: dd 34.25

SECTION .bss
sinput:     resq    255                            ; reserved for input string

SECTION .text
global  main

;------------------------------------------
; Calculate string length
; eax <= (address) of string (string ends with 0h byte)
;
; (int) length => eax
;
slen:
    push    ebx         ; save ebx
    mov     ebx, eax    ; ebx = initial address
 
.nextchar:                 ; loop for each char {
    cmp     byte [eax], 0  ;   if 0h
    jz      .finished      ;      goto end
    inc     eax            ;   else increase eax
    jmp     .nextchar      ; }
 
.finished:
    sub     eax, ebx    ; calculate address difference = length
    pop     ebx         ; restore ebx
    ret
 
 
;------------------------------------------
; String printing function
; eax <= (address) of string 
;
sprint:
    push    edx         ; save edx
    push    ecx         ; save ecx
    push    ebx         ; save ebx
    push    eax         ; save eax
    call    slen
 
    mov     edx, eax    ; len => edx
    pop     eax         ; restore eax
 
    mov     ecx, eax    ; str addr => ecx
    mov     ebx, 1      ; STDOUT
    mov     eax, 4      ; SYS_WRITE
    int     80h         ; KERNEL
 
    pop     ebx         ; restore ebx
    pop     ecx         ; restore ecx
    pop     edx         ; restore edx
    ret

;------------------------------------------
; string print function with LineFeed '\n' to STDOUT
; eax <= (address) of string
;
sprintf:

    call    sprint

    push    eax         ; push eax onto the stack to preserve it while we use the eax register in this function
    mov     eax, 0x0A    ; move 0Ah into eax - 0Ah is the ascii character for a linefeed
    push    eax         ; push the linefeed onto the stack so we can get the address
    mov     eax, esp    ; move the address of the current stack pointer into eax for sprint
    call    sprint      ; call our sprint function
    pop     eax         ; remove our linefeed character from the stack
    pop     eax         ; restore the original value of eax before our function was called
    ret                 ; return to our program
 
;------------------------------------------
; Read input into var
; eax <= (address) of variable
;
sscanf:
    push    edx         ; save edx
    push    ecx         ; save ecx
    push    ebx         ; save ebx
    push    eax         ; save eax
    
    mov     ecx, eax    ; mov address
    
    mov     edx, 255        ; (max length of input = 25
    ;                          as variable should have that length)
    ;    var address IN ECX
    mov     ebx, 0          ; STDIN
    mov     eax, 3          ; SYS_READ
    int     80h             ; KERNEL
    
    pop     eax         ; restore ebx
    pop     ebx         ; restore ebx
    pop     ecx         ; restore ecx
    pop     edx         ; restore edx
    ret

;------------------------------------------
; string to integer conversion
; eax <= (int) parsed number
; ebx <= (int) warning codes from parser
;
atoi:
    ; eax - address of string with number

    push    ecx             ; preserve ecx on the stack to be restored after function runs
    push    edx             ; preserve edx on the stack to be restored after function runs
    push    esi             ; preserve esi on the stack to be restored after function runs
    push    edi
    mov     esi, eax        ; move pointer in eax into esi (our number to convert)
    mov     eax, 0          ; initialise eax with decimal value 0
    mov     ecx, 0          ; initialise ecx with decimal value 0

.multiplyLoop:
    xor     ebx, ebx        ; resets both lower and uppper bytes of ebx to be 0
    mov     bl, [esi+ecx]   ; move a single byte into ebx register's lower half
    cmp     bl, 48          ; compare ebx register's lower half value against ascii value 48 (char value 0)
    jl      .isfinished       ; jump if less than to label finished
    cmp     bl, 57          ; compare ebx register's lower half value against ascii value 57 (char value 9)
    jg      .isfinished       ; jump if greater than to label finished

    sub     bl, 48          ; convert ebx register's lower half to decimal representation of ascii value

    ; ADD overflow check
    add eax, ebx
    jo .overflow2
    ; js .overflow2

    ; MUL overflow check
    mov edi, eax
    mov ebx, 10
    imul edi, ebx
    jo .overflow
    ; js .overflow
    mov eax, edi

    ; add     eax, ebx        ; add ebx to our interger value in eax
    ; jo .overflow
    ; mov     ebx, 10         ; move decimal value 10 into ebx
    ; mul     ebx             ; multiply eax by ebx to get place value
    ; jo .overflow

    inc     ecx             ; increment ecx (our counter register)
    jmp     .multiplyLoop   ; continue multiply loop

.overflow:
    mov ebx, 1
    jmp .return

.overflow2:
    mov ebx, 1
    jmp .finished

.trytoparseanyway:
    inc ecx
    jmp .multiplyLoop

.isfinished:
    cmp     bl, 0
    jne .trytoparseanyway

.finished:
    mov     ebx, 10         ; move decimal value 10 into ebx
    div     ebx             ; divide eax by value in ebx (in this case 10)

.return:
    pop     edi
    pop     esi             ; restore esi from the value we pushed onto the stack at the start
    pop     edx             ; restore edx from the value we pushed onto the stack at the start
    pop     ecx             ; restore ecx from the value we pushed onto the stack at the start
    ;pop     ebx             ; restore ebx from the value we pushed onto the stack at the start

    ret

;------------------------------------------
; scan integer from STDIN
; eax <= (int) scanned number
;
iscanf:
    ;push ebx
    push ecx
    push edx
    push edi
    push esi

    call sscanf
    call atoi

    pop esi
    pop edi
    pop edx
    pop ecx
    ;pop ebx
    
    ret

;------------------------------------------
; integer printing function (itoa)
; eax <= (int) number
;
iprint:

    push    eax             ; preserve eax on the stack to be restored after function runs
    push    ecx             ; preserve ecx on the stack to be restored after function runs
    push    edx             ; preserve edx on the stack to be restored after function runs
    push    esi             ; preserve esi on the stack to be restored after function runs
    mov     ecx, 0          ; counter of how many bytes we need to print in the end

.divideLoop:
    inc     ecx             ; count each byte to print - number of characters
    mov     edx, 0          ; empty edx
    mov     esi, 10         ; mov 10 into esi
    idiv    esi             ; divide eax by esi
    add     edx, 48         ; convert edx to it's ascii representation - edx holds the remainder after a divide instruction
    push    edx             ; push edx (string representation of an intger) onto the stack
    cmp     eax, 0          ; can the integer be divided anymore?
    jnz     .divideLoop      ; jump if not zero to the label divideLoop

.printLoop:
    dec     ecx             ; count down each byte that we put on the stack
    mov     eax, esp        ; mov the stack pointer into eax for printing
    call    sprint          ; call our string print function
    pop     eax             ; remove last character from the stack to move esp forward
    cmp     ecx, 0          ; have we printed all bytes we pushed onto the stack?
    jnz     .printLoop       ; jump is not zero to the label printLoop

    pop     esi             ; restore esi from the value we pushed onto the stack at the start
    pop     edx             ; restore edx from the value we pushed onto the stack at the start
    pop     ecx             ; restore ecx from the value we pushed onto the stack at the start
    pop     eax             ; restore eax from the value we pushed onto the stack at the start
    ret

;------------------------------------------
; integer printing function LineFeed '\n' to STDOUT
; eax <= (int) number
;
iprintf:

    call    iprint          ; call our integer printing function

    push    eax             ; push eax onto the stack to preserve it while we use the eax register in this function
    mov     eax, 0Ah        ; move 0Ah into eax - 0Ah is the ascii character for a linefeed
    push    eax             ; push the linefeed onto the stack so we can get the address
    mov     eax, esp        ; move the address of the current stack pointer into eax for sprint
    call    sprint          ; call our sprint function
    pop     eax             ; remove our linefeed character from the stack
    pop     eax             ; restore the original value of eax before our function was called
    ret    

;------------------------------------------
; Exit program with code 0
;
quit:
    mov     ebx, 0    ; code 0 = no errors
    mov     eax, 1    ; SYS_EXIT
    int     80h       ; KERNEL
    ret

;------------------------------------------
; Print float using GCC printf function
; (use st(0) from FPU stack)
;
floatprint:
    sub     esp, 8
    fst     qword [esp]
    push    message
    call    printf
    add     esp, 12
    ret

;------------------------------------------
; Calculate expression:
; 
; y = ln( x + 1 )/( x - 1)
;
; in:     st(0) <= x
; out:    y => st(0), x => st(1)
;
calculate:

    ; st(i) = 0, i = 1,...,7
    ; call  floatprint
    fst     qword [buf1]    ; buf1 = x

    ; call  debugprint

    ; mov       eax, dbg2
    ; call  sprintf

    ffree   st7
    ffree   st6
    ffree   st5
    ffree   st4
    ffree   st3
    ffree   st2

    fldz
    fldz
    fld dword [one]
    
    fld dword [one]
    fld dword [one]
    fldz
    
    fxch    st6

    fadd    st1, st0         ; st1 = x + 1

    fsub    st2, st0


    fxch st2

    fxch    st1
    fdiv    st0, st1       ; st0 = ( x + 1 )/( x - 1) 


    fxch st3
    fxch st1
    fxch st3


    FYL2X

    FLDL2E

    fxch st1

    fdiv    st0, st1 


    call  floatprint
    fstp    qword [buf3]

    fstp    qword [temp]
    fld     qword [buf1]    ; st0 = x
    fld     qword [buf3]    ; st0 = (x^3 + sqrt(x)) / (e^x + arctg(x)) ^ 2

    ret

 
;------------------------------------------
; Read input, calculate, return result
;
main:

    finit


    fld     dword [floatmin]
    fld     dword [floath]
    faddp   st1
 
    faddp   st1
    fimul   dword [zero]
    fldz
    

    fld     dword [floatmin]
    

    xor     edi, edi
.loop:
    cmp     edi, 15
    jge     .endloop

    mov     eax, msg1
    call    sprint

    call    floatprint
    ; st(0) = x
    ; st(1) = 0

    call    calculate
    ; st(0) = y
    ; st(1) = x
    ; st(2) = 0

    mov     eax, msg2
    call    sprint

    call    floatprint
    ; st(0) = y
    ; st(1) = x = x0
    ; st(2) = 0
    mov     eax, space
    call    sprintf

    ; go up
    fstp    qword [temp]
    ; call  floatprint

    fld     dword [floath]
    ; call  floatprint
    faddp   st1
    ; call  floatprint
    ; st(-1) = floath
    ; st(0) = x = x0 + floath
    ; st(1) = 0

    inc     edi
    jmp     .loop
.endloop:

    call    quit


; ! ! ! ! ! ! ! 
;
; HOW TO COMPILE:
;
; FILE=10; nasm -f elf $FILE.asm && gcc -m32 $FILE.o -o $FILE && ./$FILE

