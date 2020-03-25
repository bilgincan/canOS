#include "types.h"

enum status{
  READY, RUNNING, BLOCKED
};

struct pcb{
  //PCB -> proccess control block
  enum status status;
  u32 priority;
  u32 pid;
  u32 ppid;
  u32 gpid;
};

struct thread{
  struct pcb proccess;
};
