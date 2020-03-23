#include "../drivers/screen.h"

void main() {
    char *kernel_msg = "Hello World!\n Hello Kernel!";
    //char* a = 'a';
    //clear_screen();
    kprint(kernel_msg);
}
