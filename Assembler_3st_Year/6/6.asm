SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1 ; значения для вывода
 
 
section .date
    NUMBERS DD  34,  7,  56,  6,  75, 89, 7; наш массив с которым мы работаем
    ;мы можем представить наш массив символов в виде массива чисел
    size DD 7
    NUM DD 7 ; предствим символ в виде числа
                     ; Размер массива
 
section .bss
res1 resb 4
res2 resb 4
 
section .text
        global _start
 
_start:
 ;ecx для loop
 ; eax будем использовать как счётчик для колличества вхождений
   
mov ebx, NUMBERS; занести массив
mov ecx, [size]; Занесли размер
mov eax, 0
mov [res2], eax
 
find:
    mov eax, [NUM]
    mov edx, [ebx]
    cmp edx, eax
    jne next
 
tester:
    mov eax, [res2]; делаем счётчик на колличество символов в массиве и обнуляем его
    inc eax
    mov [res2], eax
 
next:
    add ebx, 4
    loop find
 
mov eax, [res2]
add eax, 48
mov [res2], eax
 
mov eax, SYS_WRITE
mov ebx, STDOUT
mov ecx, res2
mov edx, 1
int 0x80
 
exit:
    mov eax, SYS_EXIT; завершаем програму
    xor ebx,ebx;
    int 0x80
