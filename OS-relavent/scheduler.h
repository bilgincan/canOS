#include "process.h"

enum SIGNAL{
  end, kill, interrupt, block
};

void init_scheduler();
void debug_info();
void start_new_process(struct process_t* process);
void block_process(struct process_t* process, struct process_t* new_process);
void switch_into_running(struct process_t* process);
struct process_t* get_process_by_pid(u32 pid);
//todo: implement dispatcher
void dispatcher(struct process_t* process, enum SIGNAL sig);
