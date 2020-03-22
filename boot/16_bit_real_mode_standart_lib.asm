; [bits 16]
; .global print_string
; .global print_hex
; .global print_decimal
; .global print_decimal_number_function
; .global calculate_exponential
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

demsg: db "Called",0

; print_decimal:
; push eax
; push ebx
; push ecx
; push edx
;
; xor ecx,ecx
; mov ebx, 10
; print_decimal_loop:
; xor edx,edx
; idiv ebx
; cmp eax, 0
; je last_digit
; inc ecx
; push edx
; jmp print_decimal_loop
;
; last_digit:
; mov bl,dl
; call print_decimal_number_function
;
; printing_loop:
; cmp ecx, 0
; je print_decimal_end
; pop edx
; mov bl, dl
; call print_decimal_number_function
; dec ecx
; jmp printing_loop
;
; print_decimal_end:
; pop edx
; pop ecx
; pop ebx
; pop eax


; give_digit_numbers:
; push ebx
; push ecx
; push edx
; xor ecx, ecx
; cmp eax, 0
; je give_digit_numbers_end
; inc ecx
; mov ebx,10
;
; give_digit_numbers_loop:
; xor edx,edx
; div ebx
; inc ecx
; cmp eax, 1
; je give_digit_numbers_end
; jmp give_digit_numbers_loop
;
; give_digit_numbers_end:
; mov eax,ecx
; pop edx
; pop ecx
; pop ebx
; ret

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
; if needed you can use this, but you didnt test it, if it works right
; calculate_exponential: ; eax -> a ebx -> b ===> a^b
; push ebx
; push edx
;
; calculate_exponential_loop:
; cmp ebx, 0
; je calculate_exponential_end
; imul eax
; jmp calculate_exponential_loop
;
; calculate_exponential_end:
; pop edx
; pop ebx
; ret
