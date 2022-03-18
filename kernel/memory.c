#include "memory.h"

void *memset(void *ptr, s8int value, u32int size_in_bytes) 
{
    u32int i;
    char *temp = (char *)ptr;
    for (i = 0; i < size_in_bytes; i++) {
        temp[i] = value;
    }
    return ptr;
}
