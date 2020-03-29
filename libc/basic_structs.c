#include "basic_structs.h"
#include "../cpu/types.h"
#include "string.h"
#include "mem.h"

struct list* find_end_of_list(struct list* l);
struct list* find_list(int i, struct list* l);

struct list* init_list(){
  //initilize, I didnt understand how this worked but it works
  struct list* pointer = (struct list*) kmalloc(12,0,null);
  pointer->begin = NULL;
  pointer->value = NULL;
  pointer->next = NULL;
  return pointer;
}
//*************************************************
//** be sure if you need to use kmalloc in mem.c **
//*************************************************
struct list* add(u32 n, struct list* l){
  if(l == NULL){
    __asm__("int $19");
    return 0;
  }
  if (l->begin == NULL){
    l->begin = l;
    l->value = n;
    return l;
  }
  else{
    struct list* pointer = (struct list*) kmalloc(12,0,null);
    pointer->begin = l;
    pointer->value = n;
    pointer->next = null;

    l = find_end_of_list(l);
    l->next = pointer;
    return l;
  }
}

void printList(struct list* l){
  int i = 0;
  if(l->begin == NULL){
    print("empty List \n");
  }else{
    print("\nList: \n");
    int i = 0;
    do{
      print_int(i++);
      print(". element: ");
      print_int(l->value);
      print("\n");
      l = l->next;
    }while( l != NULL);
  }
}

u32 get(int i, struct list* l){
  struct list* m = find_list(i, l);
  return m->value;
}

//dont forget to write free, after you implement kfree function
struct list* remove(int i, struct list* l){
  if(i == 0){
    kfree(12,0,l->begin);
    l->begin = l->next;
    return l;
  }
  struct list* m = find_list(i-1,l);
  kfree(12,0,m->next);
  m->next = m->next->next;
  return l;
}

struct list* find_list(int i, struct list* l){
  int size = size_list(l);
  if(i > size){
    //an exception can be thrown here
    __asm__("int $5");
    return null;
  }else{
    for(int j = 0; j < i; j++){
      l = l->next;
    }
    return l;
  }
}

int size_list(struct list* l){
  if(l == NULL){
    __asm__("int $19");
    return 0;
  }else{
    int i = 1;
    while(l->next != NULL){
      l = l->next;
      i++;
    }
    return i++;
  }
}


struct list* find_end_of_list(struct list* l){
  if(l->next == NULL){
    return l;
  }
  while(l->next != NULL){
    l = l->next;
  }
  return l;
}

enum boolean contains(u32 n, struct list* list){
  if(list == NULL){
    __asm__("int $19");
    return null;
  }
  int size = size_list(list);

  while(list != NULL){
    u32 val = list->value;
    if(val == n) return TRUE;
    else list = list->next;
  }
  return FALSE;
}

int find_index_by_value(u32 n, struct list* l){
  if(contains(n, l) == FALSE){
    return -1;
  }else{
    int i = 0;
    while(l != NULL){
      u32 val = l->value;
      if(val == n) return i;
      i++;
    }
  }
  return -1;
}
