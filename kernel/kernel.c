#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "kernel.h"
#include "../cpu/idt.h"
#include "start_up.h"
#include "../libc/basic_structs.h"

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();

    print("DEBUG MODE:\n");
    struct list l = init_list();

    for(u32 i = 0; i < 6; i++){
      add(i, &l);
    }
    print("\n");
    printList(&l);
    print_int(size_list(&l));
    print("\n");
    print_int(get(3,&l));
    print("\n");
    remove(4,&l);
    printList(&l);

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
