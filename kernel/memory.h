#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

/* Our stack starts at 0x90000, adding a word size for a better
 * Alignment also as you might have noticed this is a joke
 * I will add memory mangment in the future
 * For now, please don't hunt me
*/
#define KALLOC_ADDRESS (0x90000+sizeof(u32int))

void *memset(void *ptr, s8int value, u32int size_in_bytes);
void *memcpy(void *dest, const void *src, u32int n);
void *kalloc(u32int size);
#endif
