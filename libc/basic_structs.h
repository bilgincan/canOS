#define NULL 0
#define null 0

#include "../cpu/types.h"

struct list{
  struct list* begin;
  u32 value;
  struct list* next;
};

enum boolean{
  TRUE, FALSE
};

struct list* init_list();
struct list* add(u32 n, struct list* l);
u32 get(int i, struct list* l);
struct list* remove(int i, struct list* l); //removes ith element in the list
int size_list(struct list* l);
void printList(struct list* l);
enum boolean contains(u32 n, struct list* list);
int find_index_by_value(u32 n, struct list* l);
