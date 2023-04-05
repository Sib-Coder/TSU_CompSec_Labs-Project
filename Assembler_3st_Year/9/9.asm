%macro sysout 2
    mov     ecx, %1  ;msg
    mov     edx, %2  ;len
    mov     ebx, 1   
    mov     eax, 4   
    int     0x80
%endmacro            ; Печать на консоль


%macro print_msg 1
    mov     ecx,16      ; ecx=16
    mov     edx,1       ; edx=1  
%%loop_begin:    
    dec     ecx
    mov     ax, %1      
    and     ax,dx       ;выделяем бит
    cmp     ax,0
    je      %%loop0
    mov     byte [msg+ecx], '1'    
    jmp     %%loop_end
%%loop0:    
    mov     byte [msg+ecx], '0'
%%loop_end: 
    shl     edx, 1  ;dx - 1bit mask
    cmp     ecx, 0
    jnz     %%loop_begin
    sysout  msg, len
%endmacro                 ; Подготовка строки для вывода двоичного слова.Входной параметр - откуда число. Адрес строки = msg. 


section .text
global _start
_start:
    sysout  msg, len    
    print_msg [mini]    ; вывод на экран  вектора начала интервала
    print_msg [maxi]    ; вывод на экран  вектора конца интервала
   
    xor     eax,eax
    xor     ebx,ebx
    mov     ax, [mini]  ; вектор левого
    mov     bx, [maxi]  ; вектора правого края
    xor     ax, bx
    mov     [xorm], ax
    not     word [xorm] ; инвертированный ксор векторов интервала
    print_msg [xorm]    ; вывод маски на экран
    print_msg [vecx]     ; вывод на экран проверяемого вектора
   
    mov     ax, [maxi]  ; вектор интервала, крайний, любой из двух
    and     ax, [xorm]  ; mask
    mov     bx, [vecx]  ; проверяемый вектор
    and     bx, [xorm]  ; mask
    cmp     ax,bx
    jne     exit_no
exit_yes:
   sysout itog_yes, len_yes  ; вывод результата
   jmp  exit
exit_no:
   sysout itog_no, len_no
exit:  
    mov     eax, 1    
    int     0x80
    
section .data
   wid16 dw 16
    xorm dw 0
    vecx dw 0010101001010100b   ; проверяемый булев вектор
    mini dw 0000101001000000b   ; начало интервала
    maxi dw 0010111101010100b   ; конец интервала
    msg  db  "################",13,10
    len  equ $ - msg
itog_no  db "Этот вектор не "
itog_yes db "принадлежит интервалу",13,10
len_no   equ $-itog_no
len_yes  equ $-itog_yes
