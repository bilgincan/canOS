C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
# $@ = target file
# $< = first dependency
# $^ = all dependencies
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CFLAGS = -m32 -ffreestanding -c

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: boot/kernel_entry.o ${OBJ}
	 ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary
	 #i386-elf-ld
kernel/kernel_entry.o: boot/kernel_entry.asm
	nasm $< -f elf32 -o $@
# compilation in 64-bit
kernel/kernel.o: kernel/kernel.c drivers/ports.h drivers/ports.c
	  gcc -m32 -ffreestanding -Wall -c $< -o $@
# i386-elf-gcc -ffreestanding -c
# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.bin: boot/boot.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -drive format=raw,file=os-image.bin

kernel.elf: boot/kernel_entry.o ${OBJ}
		ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
		gcc ${CFLAGS} $< -o $@

%.o: %.asm
		nasm $< -f elf -o $@

%.bin: %.asm
		nasm $< -f bin -o $@

clean:
		rm -rf *.bin *.dis *.o os-image.bin *.elf
		rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o
