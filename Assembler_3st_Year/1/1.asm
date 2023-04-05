SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1; это вывода 

section .data
  Nam DD 65900 ;DD - тип по байтам Nam- делимое
  Schas DW 3600 ; 
  
section .bss
  Xnam resb 2 ; другой тип выделения
  
section .text
  global _start
_start:

    mov eax , [Nam] ; адрес Nam  переменная [Nam]
    xor edx, edx ; обнуляем EDX
    mov ebx, 3600 ; Занисим то на что мы делим
    div ebx ; делим EAX на BX
  
    mov eax, edx; перенесли чтобы могли делить
    mov esi, 0
    
division: 
    xor edx, edx; тоже самое что mov EDX, 0
    mov ebx, 10
    div ebx
    
    push rdx; записываем edx в стек
    inc esi ;увеличиваем esi на 1
    cmp eax, 0 ; сравниваем eax с 0
    jne division ; прыгаем на division если eax не равно 0
output:
    pop rdx ; выносим из стека в edx значение
    add edx, 48; добавили 48 переведя в ASCII
    mov [Xnam], edx; в Xnam занесли EDX
  
    mov EAX, SYS_WRITE; системный вывод
    mov EBX,STDOUT
    mov ECX, Xnam
    mov EDX, 1
    int 0x80

    dec esi ; уменьшаем значение регистра esi на 1
    cmp esi, 0 ; сравниваем регистр esi с 0
    jg output ; прыгаем на output если esi больше 0
    
exit:
    mov EAX, SYS_EXIT; завершаем программу
    xor EBX,EBX; обнуляем
    int 0x80
