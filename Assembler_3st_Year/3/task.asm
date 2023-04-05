SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1 ; значения для вывода


section .date 
Nam DD 12;
Qum DD 1;

section .bss
Xnam resb 1 ;

section .text
	global _start
_start:

	xor ebx,ebx;
	mov ebx, [Qum];
	xor eax,eax;
	mov eax, [Nam];

looper:
	inc ebx
	mov eax, [Nam]
	mov ecx, ebx;
	imul ecx, ebx;делаем квадрат
	cmp ecx, eax
	jg exit
	xor edx,edx
	div ecx
	cmp edx,0
	jne looper

	imul ecx, ebx;делаем куб
	xor edx,edx
	mov eax,[Nam]
	div ecx
	cmp edx,0
	je looper
	push rbx

output:
	pop rdx ; выносим из стека в edx значение
	add edx, 48; добавили 48 переведя в ASCII
	mov [Xnam], edx; в Xnam занесли EDX
  
	mov eax, SYS_WRITE; системный вывод
	mov EBX,STDOUT
	mov ECX, Xnam
	mov EDX, 1
	int 0x80



exit:
	mov eax, SYS_EXIT; завершаем програму
	xor ebx,ebx;
	int 0x80
