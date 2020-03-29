#include "scheduler.h"
#include "../libc/basic_structs.h"
#include "../libc/string.h"

struct list* all_processes; // for debugging, please delete after you are done with this list
struct list* ready_queue;
struct list* waiting_queue;
struct process_t* running;

void init_scheduler(){
  all_processes = init_list();
  ready_queue = init_list();
  waiting_queue = init_list();

  start_new_process(init_process());
}

void debug_info(){
  print("All processes: \n");
  printList(all_processes);

  print("\nReady_queue: \n");
  printList(ready_queue);

  print("\nRunning process: ");
  print_int((u32 *) running);
  print("   ");
  print(running->process_name);

  print("\nWaiting List:");
  printList(waiting_queue);
}

void start_new_process(struct process_t* process){
  add(process,all_processes);

  if(running == NULL){
    running = process;
    process->status = RUNNING;
  }else{
    add(process,ready_queue);
    process->status = READY;
  }
}

void block_process(struct process_t* process){
  if(process == null){
    __asm__("int $19");
    return;
  }
  if(contains((u32) process, all_processes) == FALSE){
    __asm__("int $20");
    return;
  }

  if(contains((u32) process, ready_queue) == TRUE){
    int pos = find_index_by_value((u32) process, ready_queue);
    remove(pos, ready_queue);
  }
  if(contains((u32) process, waiting_queue) == FALSE){
    add((u32) process, waiting_queue);
  }
  process->status = BLOCKED;
}
