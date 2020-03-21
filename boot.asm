[org 0x7c00]
KERNEL_OFFSET equ 0x1000
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov ax, BOOT_MSG
    call print_string_nl

    call load_kernel
    call switch_to_pm
    jmp $


    %include "disk_load.asm"
    %include "16_bit_real_mode_standart_lib.asm"
    %include "32_bit_protected_mode_standart_lib.asm"
    %include "32_bit_switch.asm"
    %include "gdt.asm"


[bits 16]
load_kernel:
    mov ax, MSG_LOAD_KERNEL
    call print_string_nl

    mov bx, KERNEL_OFFSET
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret


[bits 32]
  BEGIN_PM:
    mov eax, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET
    jmp $


;Global variables
BOOT_DRIVE: db 0
BOOT_MSG db "Booting canOS", 0 ; we need to explicitely put the zero byte here
MSG_PROT_MODE db "Entering in 32-bit protected mode",0
MSG_LOAD_KERNEL db "Loading kernel into memory"


; Bootsector
times 510-($-$$) db 0           ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55                       ; magic number that tells the BIOS this is bootable
