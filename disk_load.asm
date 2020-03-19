disk_load:
push dx

mov ah, 0x02 ; BIOS read mode
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02

int 0x13

jc disk_error

pop dx
cmp dh,al
jne disk_error

ret

disk_error:

mov ax, disk_error_msg
call print_string
ret

disk_error_msg: db 10,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,"DISK ERROR", 0
