#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "kernel.h"
#include "../cpu/idt.h"
#include "start_up.h"

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();

    print("Hello World! \nHello Kernel!\n\n");

    print("canOS is ready for your instructions\n");
    next_order();
}

void user_input(char *input) {
    proccess_command(input);
}

void next_order(){
  print("\n> ");
}
