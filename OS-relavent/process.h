#include "../cpu/types.h"

enum status{
  READY, RUNNING, BLOCKED
};

struct proccess_t{
  //PCB -> proccess control block
  enum status status;
  u32 priority;
  u32 pid;
  u32 ppid;
  u32 gpid;
  u32 start_address;
};

typedef struct {
  u32 ds; /* Data segment selector */
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
  u32 int_no, err_code; /* Interrupt number and error code (if applicable) */
  u32 eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;

struct thread_t{
  struct proccess_t proccess;
  u32 start_address;
  registers_t registers;
};


void init_process();
