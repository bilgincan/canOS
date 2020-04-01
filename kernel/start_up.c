#include "start_up.h"
#include "../libc/string.h"
#include "kernel.h"
#include "../cpu/timer.h"

void proccess_command(char* command){
  if (strcmp(command, "end") == 0) {
      print("Stopping the CPU. Bye!\n");
      asm volatile("hlt");
  }
  else if(strcontains(command,"echo") == 0){
      int command_length = strlen("echo");
      command += command_length;
      print(command);
  }
  else if(strcmp(command,"show timer") == 0){
    unsigned int time = get_tick();
    print("System time: ");
    print_int(time);
  }
  else{
    print("There is no such a command!!!");
  }
  next_order();
}
