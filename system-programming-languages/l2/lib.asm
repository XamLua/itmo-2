section .text

global string_length
global print_char
global print_newline
global print_string
global print_error
global print_uint
global print_int
global string_equals
global parse_uint
global parse_int
global read_word
global string_copy
global exit
global print_error

exit:
    mov rax, 60
    syscall

print_error:
    push rdi
    call string_length
    pop rsi
    mov rdx, rax 
    mov rax, 1
    mov rdi, 2 
    syscall
    ret

string_length:
	xor rax, rax

	.loop:
		cmp byte[rdi+rax], 0
		je .length_end 
		inc rax
		jmp .loop

	.length_end:
		ret

print_string:
	call string_length
	mov rsi, rdi		;source
	mov rdx, rax		;amount of letters
	mov rax, 1			;write 
	mov rdi, 1			;stdin descriptor
	syscall

	ret

print_char:
	push rdi
	mov rdi, rsp
	call print_string
	pop rdi
	ret

read_char:
	push 0
    xor rax, rax
    xor rdi, rdi
    mov rsi, rsp 
    mov rdx, 1
    syscall
    pop rax
    ret 

read_word:
	push r14
    xor r14, r14 

    .A:
    push rdi
    call read_char
    pop rdi

    cmp al, ' '
    je .A
    cmp al, 10
    je .A
    cmp al, 13
    je .A 
    cmp al, 9 
    je .A

    .B:
    mov byte [rdi + r14], al
    inc r14

    push rdi
    call read_char
    pop rdi
    cmp al, ' '
    je .C
    cmp al, 10
    je .C
    cmp al, 13
    je .C 
    cmp al, 9
    je .C
    test al, al
    jz .C
    cmp r14, 254
    je .C 

    jmp .B

    .C:
    mov byte [rdi + r14], 0
    mov rax, rdi 
    
    pop r14
    ret

print_newline:
	mov rdi, 10		
	call print_char

	ret

string_equals:
	 mov al, byte [rdi]
    cmp al, byte [rsi]
    jne .no
    inc rdi
    inc rsi
    test al, al
    jnz string_equals
    mov rax, 1
    ret
    .no:
    xor rax, rax
    ret 




