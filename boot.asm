[org 0x7c00]
    mov ax, msg
    call print_string

    mov bp, 0x8000 ; set the stack safely away from us
    mov sp, bp

    mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000
    mov dh, 2 ; read 2 sectors
    ; the bios sets 'dl' for our boot disk number
    ; if you have trouble, use the '-fda' flag: 'qemu -fda file.bin'
    call disk_load

    call print_nl
    
    mov ax, [0x9000] ; retrieve the first loaded word, 0xdada
    call print_hex

    call print_nl

    mov ax, [0x9000 + 512] ; first word from second loaded sector, 0xface
    call print_hex

    jmp $


msg: db "Booting canOS", 0 ; we need to explicitely put the zero byte here
debug: db "  Debugging mode: ",0

%include 'standart_lib.asm'
%include 'disk_load.asm'

;Global variables
BOOT_DRIVE: db 0

; Bootsector
times 510-($-$$) db 0           ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55                       ; magic number that tells the BIOS this is bootable

times  256 dw 0xdada
times  256 dw 0xface
