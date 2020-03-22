#include "../drivers/screen.h"

void main() {
    char *kernel_msg = "Hello World! Hello Kernel";
    //char* a = 'a';
    clear_screen();
    kprint(kernel_msg);

    //int i = 0;
    //int col = 4;
    // while([kernel_msg] != 0){
    //
    // }
    // print_char('H',4,4,GREEN_ON_BLACK);
    // print_char('e',5,4,GREEN_ON_BLACK);
    // print_char('l',6,4,GREEN_ON_BLACK);
    // print_char('l',7,4,GREEN_ON_BLACK);
    // print_char('o',8,4,GREEN_ON_BLACK);
    // print_char('!',9,4,GREEN_ON_BLACK);
}
