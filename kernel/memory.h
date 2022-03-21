#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

void *memset(void *ptr, s8int value, u32int size_in_bytes);
void *memcpy(void *dest, const void *src, u32int n);
#endif
