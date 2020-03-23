; [bits 16]
; .global print_string
; .global print_hex
; .global print_decimal
; .global print_nl

print_string: ; parameters are stored in ax as char*
push ax
push bx
mov bx, ax
mov ah, 0x0e

print_string_loop:
mov al, [bx]
cmp al, 0
je end_print_string
int 0x10
inc bx
jmp print_string_loop

end_print_string:
pop bx
pop ax
ret


print_hex:
push eax
push ebx
push cx
push edx
push esi

mov ebx, eax
mov ah, 0x0e
mov al, '0'
int 0x10
mov al, 'x'
int 0x10
cmp ebx, 0
je result_is_zero
; use ecx for bit mask
mov esi, 0xf0000000
mov edx, ebx
mov cl,28
xor ch,ch ; use as bool value for the first zero detection

print_hex_loop:
cmp esi, 0
je end_print_hex
and ebx,esi
cmp ebx,0
je zero_detected
inc ch
shr ebx, cl
cmp bl, 10
jl print_decimal_number
jge print_hex_number

prepare_for_other_it_print_hex_loop:
shr esi,4
mov ebx,edx
cmp cl, 0
jg dec_cl
jmp print_hex_loop
dec_cl:
sub cl, 4
jmp print_hex_loop

result_is_zero:
call print_decimal_number_function
jmp end_print_hex

zero_detected:
cmp ch, 0
je prepare_for_other_it_print_hex_loop
jmp print_decimal_number

print_decimal_number:
call print_decimal_number_function
jmp prepare_for_other_it_print_hex_loop

print_hex_number:
add bl, 55
mov al, bl
int 0x10
jmp prepare_for_other_it_print_hex_loop

end_print_hex:
pop esi
pop edx
pop cx
pop ebx
pop eax
ret


print_decimal_number_function:
push ax
push bx
mov ah,0x0e
add bl, 0x30
mov al,bl
int 0x10
pop bx
pop ax
ret

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

print_string_nl:
    call print_string
    call print_nl
