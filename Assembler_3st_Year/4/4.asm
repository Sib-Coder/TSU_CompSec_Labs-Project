SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1 ; значения для вывода


section .date 
    Nam DD 2; наше число которое мы проверяем


section .bss
    Xnam resb 4
    ;Dal resb 4
    hell resb 4 


section .text
	global _start

_start:

mov eax, 1
mov [hell], eax
looper:
xor edx, edx
mov eax, [Nam]; занесли в ax Nam
mov ecx, [hell]; занесли в регистр
div ecx; деление ax - первая цифра в dx - два оставщихся 
;добавляем 1


cmp edx,0
jne check

mov eax, [hell]
outputer:

xor edx, edx ; обнуляем edx
  ; перемещаем число 10 в регистр cx
  mov ecx, 10
  ; делим eax на cx
  div ecx
  push rdx; записываем edx в стек
  inc esi ;увеличиваем esi на 1
  cmp eax, 0 ; сравниваем eax с 0
  jne outputer ; прыгаем на division если eax не равно 0

output:
  pop rdx ; выносим из стека в edx значение
    add edx, 48 ; прибавляем 48 для конвертации из десятичного числа в ASCII
  ; перещаем значение edx в переменную res2
  mov [Xnam], edx    
     
  mov eax, SYS_WRITE ; номер системного вызова (sys_write)        
  mov ebx, STDOUT  ; дескриптор файла (stdout)
  mov ecx, Xnam   ; строка      
  mov edx, 1 ; длина строки
  int 0x80 ; вызов ядра
  
  dec esi ; уменьшаем значение регистра esi на 1
  cmp esi, 0 ; сравниваем регистр esi с 0
  jg output ; прыгаем на output если esi больше 0

check:

mov ecx, [hell]
inc ecx
mov [hell], ecx 
; mov [AHHAHAHAHAHAHAHAHHAHAHA], ecx
cmp ecx, [Nam]
jl looper
; тут мы 
	



exit:
	mov eax, SYS_EXIT; завершаем програму
	xor ebx,ebx;
	int 0x80
