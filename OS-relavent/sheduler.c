#include "scheduler.h"
#include "../libc/basic_structs.h"
#include "../libc/string.h"
#include "../cpu/timer.h"

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
  print("  ");
  print_int(running->pid);

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

void block_process(struct process_t* old_process, struct process_t* new_process){
  if(old_process == null){
    __asm__("int $19");
    return;
  }
  if(contains((u32) old_process, all_processes) == FALSE || contains((u32) new_process, all_processes) == FALSE){
    __asm__("int $20");
    return;
  }

  if(contains((u32) old_process, ready_queue) == TRUE){
    int pos = find_index_by_value((u32) old_process, ready_queue);
    remove(pos, ready_queue);
  }
  if(contains((u32) old_process, waiting_queue) == FALSE){
    add((u32) old_process, waiting_queue);
  }
  old_process->status = BLOCKED;
  if(new_process == NULL){
    new_process = (struct process_t*) get(0, all_processes); // if the new_process parameter null, it means init_process
  }
  switch_into_running(new_process);
}

void switch_into_running(struct process_t* process){
  if(process == null){
    __asm__("int $19");
    return;
  }
  if(contains((u32) process, ready_queue) == TRUE){
    int pos = find_index_by_value((u32) process, ready_queue);
    remove(pos, ready_queue);
  }
  if(contains((u32) process, waiting_queue) == TRUE){
    int pos = find_index_by_value((u32) process, waiting_queue);
    remove(pos, waiting_queue);
  }
  process->status = RUNNING;
  running = process;
}

void switch_to_the_timer(){
  inc_tick();
}

struct process_t* get_process_by_pid(u32 pid){

    struct list* tmp = all_processes->begin;

    while(tmp != NULL){
      struct process_t *tmp_process = (struct process_t*) tmp->value;
      u32 tmp_pid = tmp_process->pid;

      if(pid == tmp_pid) return tmp_process;

      tmp = tmp->next;
    }
    return null; // if not found, return null
}

// void dispatcher(struct process_t* process, enum SIGNAL sig){
//
// }
