#include "process.h"
#include "../libc/mem.h"
#include "../libc/basic_structs.h"
#include "../libc/string.h"

enum status st;
int next_pid = 1;

struct process_t* create_new_process(char* process_name, u32 size_in_memory, u32 ppid, u32 gpid, u32 priority);

struct process_t* init_process(){
  u32 size_in_memory = 0x10;

  return create_new_process("init_process", 0x10, 1, 1,null);
}

struct process_t* create_new_process(char* process_name, u32 size_in_memory, u32 ppid, u32 gpid, u32 priority){
  size_in_memory += 30; //for the struct informations
  struct process_t *address_room = (struct process_t*) kmalloc(size_in_memory, 1, null);
  address_room->allocated_size_in_memory = size_in_memory;
  address_room->status = READY;

  if(priority == NULL) address_room->priority = 5;
  else address_room->priority = priority;

  address_room->pid = next_pid++;

  if(address_room->ppid == NULL) address_room->ppid = 1; // if there is no parent, then it is the child of the init process
  else address_room->ppid = ppid;

  if(address_room->gpid == NULL) address_room->gpid = 1; //same logic as parent id
  else address_room->gpid = gpid;

  address_room->start_address = (u32*) address_room;
  if(process_name == NULL) __asm__ ("int $19"); //throw null pointer exception
  address_room->process_name = process_name;

  return address_room;
}
