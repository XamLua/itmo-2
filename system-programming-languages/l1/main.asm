global main

section .data 
message db "Hello, world!", 10

section .text
main:
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, 14
    syscall