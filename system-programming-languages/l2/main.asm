%include "colon.inc"
%include "words.inc"

extern read_word
extern string_length
extern print_newline
extern print_string
extern print_error
extern find_word
extern string_equals
extern exit

global _start

section .rodata
msg_noword: db "Word does not exist",0

section .text
_start:
	push rbp
	mov rbp, rsp
	sub rsp, 256
	mov rdi, rsp
	call read_word
	mov rdi, rax
	mov rsi, lw
	call find_word
	test rax, rax
	jz .bad

	add rax, 8
	push rax
	mov rax, [rsp]
	mov rdi, rax
	call string_length	
	pop rdi
	add rdi, rax
	inc rdi
	call print_string
	call print_newline
	mov rsp, rbp
	pop rbp
	mov rdi, 0
	jmp _start

.bad:
	mov rdi, msg_noword
	call print_error
	call print_newline

	mov rsp, rbp
	pop rbp
	mov rdi, 0
	jmp _start