#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "kernel.h"
#include "../cpu/idt.h"
#include "start_up.h"
#include "../libc/basic_structs.h"
#include "../OS-relavent/scheduler.h"

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();
    init_timer(500);
    init_scheduler();

    struct process_t* timer = create_new_process("kernel_timer", 4, 1, 1, 15);
    start_new_process(timer);


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
