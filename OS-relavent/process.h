#include "../cpu/types.h"
#include "../cpu/isr.h"

enum status{
  READY, RUNNING, BLOCKED
};

struct process_t{
  //PCB -> proccess control block
  enum status status;
  u32 allocated_size_in_memory;
  u32 priority;
  u32 pid;
  u32 ppid;
  u32 gpid;
  u32* start_address;
  char* process_name;
};

struct thread_t{
  struct process_t proccess;
  u32* start_address;
  registers_t registers;
};


struct process_t* init_process();
struct process_t* create_new_process(char* process_name);
