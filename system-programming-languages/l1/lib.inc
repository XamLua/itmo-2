section .text

print_error:
    push rdi
    call string_length
    pop rsi
    mov rdx, rax 
    mov rax, 1
    mov rdi, 2 
    syscall
    ret

exit: 
    xor rdi, rdi
    mov rax, 60
    syscall

string_length:

    xor rax, rax                
    .loop:
        cmp byte[rdi+rax], 0    ; Сравниваем байт в памяти с текущим символом строки с нулем
        jz .end                 ; Если он ноль - дошли до конца - завершаем цикл 
        inc rax                 ; Иначе увеличиваем счётчик длины строки
        jmp .loop               ; Повторяем
    .end:
        ret

print_string:

    call string_length          ; Получаем длину строки
    mov rdx, rax                ; Записываем количество байт для вывода
    mov rsi, rdi                ; Адрес начала строки
    mov rdi, 1                  ; Дескриптор stdout
    mov rax, 1                  ; Номер системного вызова
    syscall
    ret


print_char:
    push rdi
    mov rdi, rsp
    call print_string
    pop rdi
    ret

print_newline:

    mov rdi, 0xA
    call print_char
    ret



print_uint:
    
    mov rsi, rsp
    mov rax, rdi
    xor rdx, rdx                
    push 0
    mov rcx, 10                 

    .loop:
        xor rdx, rdx
        div rcx
        add dl, 0x30            
        mov [rsp], dl  
        dec rsp
        cmp rax, 0
        jne .loop

    inc rsp                 
    mov rdi, rsp
    push rsi
    call print_string
    pop rsi
    mov rsp, rsi
    ret

print_int:
    cmp rdi, 0
    jge print_uint
    push rdi
    mov rdi, "-"
    call print_char
    pop rdi
    neg rdi
    jmp print_uint
    ret

string_equals:
    xor rcx, rcx
    .loop:
        mov r10b, [rdi+rcx] 
        mov r11b, [rsi+rcx]
        cmp r10b, r11b
        jne .fail
        inc rcx
        cmp r10b, 0
        je .null
        jmp .loop
    .null:
        cmp r11b, 0
        jne .fail
        mov rax, 1
        ret
    .fail:
        mov rax, 0
        ret


read_char:
    xor rax, rax
    mov rdx, 1
    xor rdi, rdi
    push 0
    mov rsi, rsp
    syscall
    pop rax
    ret 

read_word:
    push r12
    push r13
    push r14
    mov r12, rdi
    mov r13, rsi
    xor r14, r14

    .read_loop:
        call read_char
        cmp al, 0x09
        je .read_loop
        cmp al, 0xA
        je .read_loop
        cmp al, 0x20
        je .read_loop
        cmp al, 0
        je .success

        .word_loop:
            mov byte[r12 + r14], al
            inc r14
            cmp r14, r13
            ja .fail

        call read_char
        cmp al, 0
        je .success
        cmp al, 0x09
        je .success
        cmp al, 0xA
        je .success
        cmp al, 0x20
        je .success

        jmp .word_loop

    .fail:
        xor rax, rax
        pop r14
        pop r13
        pop r12
        ret

    .success:
        mov byte[r12 + r14], 0
        mov rax, r12
        mov rdx, r14
        pop r14
        pop r13
        pop r12
        ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rsi, rsi
    xor rcx, rcx
    xor rax, rax
    mov r10, 10
        .loop:
        mov sil, [rdi+rcx]
        cmp sil, 0x30
        jb .done
        cmp sil, 0x39
        ja .done
        sub sil, 0x30
        mul r10
        add rax, rsi
        inc rcx
        jmp .loop
    .done:
        mov rdx, rcx
        ret 

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    cmp byte[rdi], '-'
    je .negative
    call parse_uint
    ret
    .negative:
        inc rdi
        call parse_uint
        cmp rdx, 0
        je .done
        neg rax
        inc rdx
    .done:
        ret 

; rdi = source
; rsi = dest
; rdx = dest length 
string_copy:
    push rdx                    ;Caller-saved регистры                                        
    push rdi                    
    push rsi                    
    call string_length
    pop rsi
    pop rdi
    pop rdx
    inc rax                     ;Учтём нуль-терминатор
    cmp rax, rdx
    jg .not_enough_space

    push rsi

    .loop:
        mov cl, byte[rdi]
        mov byte[rsi], cl
        inc rdi
        inc rsi
        dec rax
        jnz .loop

    pop rax                     ;Восстановим ранее сохранённое значение
    ret

    .not_enough_space:  
        xor rax, rax
        ret
