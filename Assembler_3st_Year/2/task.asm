SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1 ; значения для вывода


section .date 
Nam DW 122;  наше 3-х значное число
Del DW 100; 
Del2 DW 10;

msg db 'True',0xa 
len equ $ - msg; считаем длину

msg2 db 'False',0xa
len2 equ $ - msg2;

section .bss
Perv resb 1;
Vtor resb 1;
Tri resb 1;

section .text
	global _start
_start:

	xor dx, dx; обнуляем edx
	mov ax, [Nam]; занесли в ax Num
	mov cx, [Del]; занесли в регистр
	div cx; деление ax - первая цифра в dx - два оставщихся 
	mov [Perv], ax; освободили ax
	mov ax, dx; занесли остатки
	xor dx, dx; очистили dx
	mov cx , [Del2]
	div cx; всегда передаём на что мы делим
	mov [Vtor], ax; занёс второе число 
	mov [Tri], dx; третие готово

	cmp ax ,[Perv]
	je equal

	cmp dx, [Perv]
	je equal

	cmp ax, dx
	je equal
	


no_equal:;прыгаем сюда при проходе всех условий 
	mov edx, len2;
        mov ecx, msg2
        mov ebx, STDOUT
        mov eax, SYS_WRITE
        int 0x80
	jmp exit; прыгаем на выход

equal: 
	mov edx, len;
	mov ecx, msg
	mov ebx, STDOUT
	mov eax, SYS_WRITE
	int 0x80


exit:
	mov eax, SYS_EXIT; завершаем програму
	xor ebx,ebx;
	int 0x80

