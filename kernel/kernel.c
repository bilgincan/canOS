#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "kernel.h"
#include "../cpu/idt.h"
#include "start_up.h"
#include "../libc/basic_structs.h"
#include "../OS-relavent/process.h"

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();

    print("DEBUG MODE:\n");
    init_scheduler();

    struct process_t test = {READY, 0x10, 2, 2, 1, 1, null, "test"};
    start_new_process(&test);

    debug_info();

    block_process(&test);

    debug_info();

    // print("Hello World! \nHello Kernel!\n\n");
    //
    // print("canOS is ready for your instructions\n");
    // next_order();
}

void user_input(char *input) {
    proccess_command(input);
}

void next_order(){
  print("\n> ");
}
