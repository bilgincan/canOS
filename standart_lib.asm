[bits 16]

print: ; parameters are stored in ax as char*
push ax
push bx
mov bx, ax
mov ah, 0x0e

print_loop:
mov al, [bx]
cmp al, 0
je end_print
int 0x10
inc bx
jmp print_loop

end_print:
pop bx
pop ax
ret
