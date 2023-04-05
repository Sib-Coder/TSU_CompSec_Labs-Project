global _start
	section .text
; вывод числа
print_uint:
		mov rax, rdi	;заносим rdi в rax для деления
		mov r11, 10		;заносим 10 в r11
		mov r10, 0		;r10 счётчик
	
	.loop1:
		mov rdx, 0
		div r11			;остаток от деления пушим на стек
		push rdx

		inc r10
		cmp rax, 0		
	jne .loop1

	.loop2:
		pop r8			;достаём цифру из стека
		add r8 , '0'	;для представления в ASCII
		mov [noob], r8

						;печатаем цифру
		mov rax, 1
		mov rdi, 1
		mov rdx, 1
		mov rsi, noob
		syscall
		
		dec r10
		test r10, r10		;пока не  r10 == 0
		jnz .loop2

		ret 
; печатаем символ с новой строки
print_newline:
		mov qword[noob], 10
		mov rax, 1
		mov rdi, 1
		mov rdx, 1
		mov rsi, noob
		syscall
		ret
; печатаем пробел
print_space:
		mov qword[noob], ' '
		mov rax, 1
		mov rdi, 1
		mov rdx, 1
		mov rsi, noob
		syscall
		ret
; печатаем число со знаком
print_int:
		cmp rdi, 0
		jge .else
		xor rdi, 0xffffffffffffffff
		add rdi, 1	
		push rdi

		mov byte[newb], '-'
		mov rsi, newb
		mov rax, 1
		mov rdi, 1
		mov rdx, 1
		syscall

		pop rdi
		.else:
		
		call print_uint
		ret

parse_uint:				;возвращаем положительное число в rax и число цифр в rbx
		mov r10, 0
		mov r8, 0
		mov rax, 0
	.loop:
		mov r8b, [rdi+r10]
	
		cmp r8, 0
		je .end

		mov r9, 10
		mul r9

		sub r8b, '0'
		add rax, r8

		inc r10
		
		jmp .loop
	.end:
		mov rdx, r10
		ret

parse_int:				;возвращаем отрицательное число в rax и число цифр в rbx
		mov r8, 0
		mov r8b, [rdi]

		cmp r8b, '-'
		je .neg
		
		call parse_uint
		ret

	.neg:

		lea rdi, [rdi+1]
			
		call parse_uint 	

		inc rdx
		xor rax, 0xffffffffffffffff
		inc rax
		ret

read_char:					;возвращаем считанный символ
		push 0

		mov rax, 0
		mov rdi, 0
		mov rsi, rsp
		mov rdx, 1
		syscall

		pop rax
		ret

read_word:					;возвращаем буфер адреса или 0 в rax
		mov r8, rdi
		mov r9, rsi
		mov r10, 0
	
	.star:

		call read_char

		mov [r8+r10], rax
		inc r10

		cmp rax, ' '
		je .end

		cmp r10, r9
		jle .cont
		mov rax, 0
		ret

	.cont:
		cmp rax, 0
		je .end
		cmp rax, 10
		je .end

		jmp .star

	.end:
		dec r10
		mov byte[r8+r10], 0
		mov rax, r8
		ret

print_string: ; печатаем строчку :)
		mov r8, 0
	.loop:

		mov r9b, [rdi+r8]
		
		cmp r9b, 0
		je .end
		
		mov r10, rdi
		add r10, r8

		inc r8
		push rdi

		mov rax, 1
		mov rdi, 1
		mov rdx, 1
		mov rsi, r10
		syscall

		pop rdi
		jmp .loop
	.end:
		call print_newline
		ret


read_int:   ;считываем число
		mov rdi, str
		mov rsi, 12
		call read_word
		mov rdi, rax
		call parse_int
		ret

read_matrix:    ;считываем матрицу
		mov r8, rdi 		;адрес
		mov r9, rsi			;колличество строк
		mov r10, rdx 		;колличество столбцов
		mov r11, 0 			;счётчик

		mov rax, r9
		mul r10

		mov r9, rax 		;общее колличество эллементов в матрице

	.loop:
		push r8
		push r9
		push r11
		call read_int
		pop r11
		pop r9
		pop r8
		mov [r8+r11*8], rax
		inc r11

		cmp r11, r9
		jl .loop

	.end:
		ret

print_matrix: ; печатаем матрицу
		mov r11, 0  		;счётчик
		mov r8, 0			;счётчик строк
		mov r9, 0			;счётчик столбцов

	.loop1:
		mov r9, 0
	.loop2:
		push rdi
		push rsi
		push rdx
		push r11
		push r8
		push r9

		mov rdi, [rdi+r11*8]
		call print_int
		call print_space

		pop r9
		pop r8
		pop r11
		pop rdx
		pop rsi
		pop rdi

		inc r11
		inc r9
		cmp r9, rdx
		jl .loop2

		push rdi
		push rsi
		push rdx
		push r11
		push r8
		push r9

		call print_newline

		pop r9
		pop r8
		pop r11
		pop rdx
		pop rsi
		pop rdi
		
		inc r8
		cmp r8, rsi
		jl .loop1

		ret

_start:					
							;считываем m, n, p, q
		call read_int
		mov [m], rax

		call read_int
		mov [n], rax

		call read_int
		mov [p], rax

		call read_int
		mov [q], rax

		mov rdi, mat1
		mov rsi, [m]
		mov rdx, [n]
		call read_matrix

		mov rdi, mat2
		mov rsi, [p]
		mov rdx, [q]
		call read_matrix

		mov r12, [n]		;матрицы не могут быть умножены
		mov r13, [p]
		cmp r12, r13
		jne ending

							;вычисляем
		mov r8, [m]
		mov r9, [n]
		mov r10, [q]
		mov rdi, prod
		mov r15, 0			
		mov rbx, 0			;частная сумма

		mov r12, 0     		;i
	.loop1:
		mov r13, 0  		;j
	.loop2:
		mov r14, 0  		;k
		mov rbx, 0			
	.loop3:

		mov rax, r12
		mul r9
		add rax, r14
		mov rsi, 8
		mul rsi

		push qword[mat1+rax]	

		mov rax, r14
		mul r10
		add rax, r13
		mov rsi, 8
		mul rsi

		push qword[mat2+rax]	

		pop rsi
		pop rax
		mul rsi

		add rbx, rax 			; c[i][j] += a[i][k]*b[k][j]

		inc r14
		cmp r14, r9
		jl .loop3

		mov [rdi+r15*8], rbx
		inc r15

		inc r13
		cmp r13, r10
		jl .loop2

		inc r12
		cmp r12, r8
		jl .loop1

		mov rdi, prod
		mov rsi, [m]
		mov rdx, [q]
		call print_matrix

		jmp exit

	ending:	
		mov rdi, 0
		call print_int
		call print_newline
        jmp exit

exit:
    mov rax, 1
    xor rbx, rbx
	int 0x80

	section .data
noob: dq 0
newb: db 0



	section .bss
str: resb 10
mat1: resq 100
mat2: resq 100
prod: resq 100
m: resq 1
n: resq 1
p: resq 1
q: resq 1