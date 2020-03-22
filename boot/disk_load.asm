[bits 16]
disk_load:
pusha
push dx

mov ah, 0x02 ; BIOS read mode
mov al, dh
mov cl, 2
mov ch, 0x00
mov dh, 0x00


int 0x13
jc disk_error

pop dx
cmp dh,al
jne sectors_error
popa
ret

disk_error:

mov ax, disk_error_msg
call print_string_nl
mov al,ah
xor ah,ah
call print_hex
jmp disk_loop

sectors_error:
mov ax, sectors_error_msg
call print_string_nl

disk_loop:
popa
jmp $

disk_error_msg: db "DISK ERROR", 0
sectors_error_msg: db "SECTOR ERROR",0
