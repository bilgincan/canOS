#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main() {
    clear_screen();
    isr_install();

    kprint("Hello World! \nHello Kernel!");
}
