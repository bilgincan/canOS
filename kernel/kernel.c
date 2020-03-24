#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main() {
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $0");
    __asm__ __volatile__("int $3");
}
