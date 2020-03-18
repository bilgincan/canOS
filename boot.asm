[bits 16]    ; use 16 bits
[org 0x7c00] ; sets the start address

init:
  mov ax,msg
  call print
  ret

msg: db "Hello World!", 0 ; we need to explicitely put the zero byte here

%include 'standart_lib.asm'

times 510-($-$$) db 0           ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55                       ; magic number that tells the BIOS this is bootable
