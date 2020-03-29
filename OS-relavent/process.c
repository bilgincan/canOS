#include "process.h"
#include "../libc/mem.h"
#include "../libc/basic_structs.h"
#include "../libc/string.h"

enum status st;
struct list* process_list;

struct process_t* init_process(){
  u32 size_in_memory = 0x10;
  struct process_t *address_room = (struct process_t*) kmalloc(size_in_memory, 1, null);
  // if needed, change here after you implement the schedulers
  address_room->allocated_size_in_memory;
  address_room->status = RUNNING;
  address_room->priority = 1;
  address_room->pid = 1;
  address_room->ppid = 1;
  address_room->gpid = 1;
  address_room->start_address = (u32*) address_room;
  address_room->process_name = "init process \0";

  return address_room;
}
