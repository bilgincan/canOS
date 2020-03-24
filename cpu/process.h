enum status{
  READY, RUNNING, BLOCKED
};

struct pcb{
  //PCB -> proccess control block
  enum status status;
  int priority;
  int pid;
  int ppid;
  int gpid;
};

struct thread{
  struct pcb proccess;
};
