#include "mem.h"
#include "basic_structs.h"

void memory_copy(u8 *source, u8 *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

u32 free_mem_addr = 0x10000;
/* Implementation is just a pointer to some free memory which
 * keeps growing */
u32* kmalloc(u32 size, int align, u32 *phys_addr) {
    /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    /* Save also the physical address */
    if (phys_addr) *phys_addr = free_mem_addr;

    u32 ret = free_mem_addr;
    free_mem_addr += size; /* Remember to increment the pointer */
    return (u32 *) ret;
}

u32* kfree(u32 size, int aligned, u32 *phys_addr){
  if( phys_addr == null){
      return null;
  }
  if (aligned == 1 && (free_mem_addr & 0xFFFFF000)) {
      free_mem_addr &= 0xFFFFF000;
      free_mem_addr -= 0x1000;
  }
  free_mem_addr -= size; /* Remember to increment the pointer */

  /* Save also the physical address */
  if (phys_addr) *phys_addr = free_mem_addr;

  return (u32 *)free_mem_addr;

}
