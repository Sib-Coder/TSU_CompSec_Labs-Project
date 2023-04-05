SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1
 
segment .data 
 
   msg1 db "Переполнение ", 0xA,0xD ; содержимое строки для вывода
   len1 equ $- msg1 ; длина строки для вывода
   minus db '-'
 
segment .bss
 
   num1 resb 4 ; переменная для числа на четыре байта
   num2 resb 4 ; переменная для числа на четыре байта
   res2 resb 4; переменная для ответа на четыре байта


section	.text
   global _start   
	
_start:

mov esi, 0 ;обнуляем регистр esi
xor edi, edi

entrer_num1:
   mov eax, SYS_READ ; номер системного вызова (sys_read)
   mov ebx, STDIN  ; дескриптор файла (stdin)
   mov ecx, num1 ; переменная, в которую записываеться пользовательский ввод
   mov edx, 1 ; количество байт для считывания
   int 0x80  ; вызов ядра
   
   mov eax, [num1] ;приравнивем регистр eax значению num1
   
    cmp eax, 45
    je minus_num
   
   cmp eax, 57 ;сравниваем значение в регистре eax с 57
   jg cov_num1 ; прыгаем на cov_num1 если eax больше 57 
   
   cmp eax, 48 ;сравниваем значение в регистре eax с 48
   jl cov_num1 ; прыгаем на cov_num1 если eax меньше 48
   


   sub eax, 48 ; отнимаем 48 для конвертации из ASCII в десятичное число
   push eax ; добовляем в стек
   inc esi ;увеличиваем значение регистра esi на 1
   cmp esi, 8
   jg error
   jmp entrer_num1; прыгаем на entrer_num1
   
   
minus_num:
    mov edi, 1
    jmp entrer_num1
   

cov_num1:
    xor eax, eax ;обнуляем eax
    mov ecx, 0; обнуляем ecx 

    
    
    converter1:
       pop edx ; выносим из стека в edx значение
       mov ebx, ecx ; переносим значение из ecx в ebx
       cmp ecx, 0 ;сравниваем значение в регистре ecx с 0
       je next1 ; прыгаем на next1 если ecx равно 0 
       power1:
          imul edx, 10 ; умнажаем регистр edx на 10
          dec ebx ; уменьшаем на 1 регистр ebx
          cmp ebx, 0 ; сравниваем ebx с 0
          jg power1; прыгаем на power1 если ebx больше 0
          
       next1:

       add eax, edx ; прибавляем к eax edx
       inc ecx; увеличиваем ecx на 1
       cmp ecx, esi; сравниваем ecx и esi
       jl converter1 ; прыгаем на converter1 если ecx меньше esi
       
some_log:
    mov [num1], eax ;перемещаем значение из eax в num1
    
mov esi, 0

entrer_num2:
  mov eax, SYS_READ ; номер системного вызова (sys_read)
  mov ebx, STDIN  ; дескриптор файла (stdin)
  mov ecx, num2 ; переменная, в которую записываеться пользовательский ввод
  mov edx, 1 ; количество байт для считывания
  int 0x80  ; вызов ядра
   
  mov eax, [num2] ;приравнивем регистр eax значению num2
   
  cmp eax, 48 ;сравниваем значение в регистре eax с 48
  jl cov_num2 ; прыгаем на cov_num1 если eax меньше 48 
   
  cmp eax, 57 ;сравниваем значение в регистре eax с 57
  jg cov_num2 ; прыгаем на cov_num1 если eax больше 57 

  sub eax, 48 ; отнимаем 48 для конвертации из ASCII в десятичное число
  push eax ; добовляем в стек
  inc esi ;увеличиваем значение регистра esi на 1
  cmp esi, 8
  jg error
  jmp entrer_num2 ; прыгаем на entrer_num2
   
cov_num2:
    xor eax, eax ;обнуляем eax
    mov ecx, 0 ; обнуляем ecx 

    
   converter2:
       pop edx ; выносим из стека в edx значение
       mov ebx, ecx ; переносим значение из ecx в ebx
       cmp ecx, 0 ;сравниваем значение в регистре ecx с 0
       je next2 ; прыгаем на next2 если ecx равно 0 
       power2:
          imul edx, 10 ; умнажаем регистр edx на 10
          dec ebx  ; уменьшаем на 1 регистр ebx
          cmp ebx, 0; сравниваем ebx с 0
          jg power2 ; прыгаем на power2 если ebx больше 0
          
       next2:

       add eax, edx ; прибавляем к eax edx
       inc ecx ; увеличиваем ecx на 1
       cmp ecx, esi ; сравниваем ecx и esi
       jl converter2 ; прыгаем на converter2 если ecx меньше esi
some_log2:
    mov [num2], eax ;перемещаем значение из eax в num2
    
    
finding:
    mov edx, 1 ; перемещаем в edx 1
    mov ecx, [num2] ; перемещаем в ecx значение num2
    mov eax, 1 ; перемещаем в eax 1
    cmp ecx, 0 ; сравниваем ecx с 0
    je zero_pow; прыгаем на zero если ecx равно 0
    
    loop1:
      
       mov ebx, [num1] ; перемещаем в ebx значение num1
       cmp ebx, 0
       je zero
       cmp ebx, 1
       je zero_pow
       loop2:
          add edx, eax ; прибавляем к edx, eax
          jo error ; прыгаем при переполнении
          dec ebx ; уменьшаем ebx на 1
          cmp ebx, 1 ; сравниваем ebx с 1
          jg loop2 ; прыгаем на loop2 если ebx больше 1
        mov eax, edx ;перемещаем в eax edx
        dec ecx ; уменьшаем ecx на 1
        cmp ecx, 0 ; сравниваем ecx с 0
        jg loop1 ; прыгаем на loop1 если ecx больше 0
        jmp end_finding ; прыгаем на end_finding
    
zero:
    mov eax, 0
    jmp end_finding
zero_pow:

    mov eax, 1 ; перемещаем в eax 1
    
end_finding:
    mov esi, 0 ; обнуляем esi
division:

    
  xor edx, edx ; обнуляем edx
  ; перемещаем число 10 в регистр cx
  mov ecx, 10
  ; делим eax на cx
  div ecx
  push edx; записываем edx в стек
  inc esi ;увеличиваем esi на 1
  cmp eax, 0 ; сравниваем eax с 0
  jne division ; прыгаем на division если eax не равно 0
  
cmp edi, 1
jne output

minus_output:
    mov eax, [num2] ; перемещаем в eax значение num2
    xor edx, edx ; обнуляем edx
    ; перемещаем число 10 в регистр cx
    mov ecx, 2
    ; делим eax на cx
    div ecx
    cmp edx, 0
    je output
    
    mov eax, SYS_WRITE ; номер системного вызова (sys_write)        
    mov ebx, STDOUT  ; дескриптор файла (stdout)
    mov ecx, minus   ; строка      
    mov edx, 1 ; длина строки
    int 0x80 ; вызов ядра
    

  
output:  
    pop edx ; выносим из стека в edx значение
    add edx, 48 ; прибавляем 48 для конвертации из десятичного числа в ASCII
  ; перещаем значение edx в переменную res2
  mov [res2], edx    
   
    
  
  
  mov eax, SYS_WRITE ; номер системного вызова (sys_write)        
  mov ebx, STDOUT  ; дескриптор файла (stdout)
  mov ecx, res2   ; строка      
  mov edx, 1 ; длина строки
  int 0x80 ; вызов ядра
  
  dec esi ; уменьшаем значение регистра esi на 1
  cmp esi, 0 ; сравниваем регистр esi с 0
  jg output ; прыгаем на output если esi больше 0
  jmp exit
  
error:
  mov eax, SYS_WRITE ; номер системного вызова (sys_write)        
  mov ebx, STDOUT  ; дескриптор файла (stdout)
  mov ecx, msg1   ; строка      
  mov edx, len1 ; длина строки
  int 0x80 ; вызов ядр

exit:    
   
   mov eax, SYS_EXIT   ; номер системного вызова (sys_exit)
   xor ebx, ebx  ; обнуляем ebx
   int 0x80 ; вызов ядра
