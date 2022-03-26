#include "memory.h"

void *memset(void *ptr, s8int value, u32int size_in_bytes) 
{
    u32int i;
    s8int *temp = (s8int *)ptr;
    for (i = 0; i < size_in_bytes; i++) {
        temp[i] = value;
    }
    return ptr;
}

void *memcpy(void *dest, const void *src, u32int n)
{
    u32int i;
    /* If the addresses and the number of bytes are aligned to be able copy WORDs, this would make it faster to copy */
    if ((u32int)dest % sizeof(u32int) == 0 &&
        (u32int)src  % sizeof(u32int) == 0 &&
        n % sizeof(u32int) == 0)
    {
        u32int *d = dest;
        const u32int *s = src;

        for (i = 0; i < n/sizeof(u32int); ++i) {
            d[i] = s[i];
        }
    }
    else {      // it isn't aligned
        u8int *d = dest;
        const u8int *s = src;

        for (i = 0; i < n; ++i) {
            d[i] = s[i];
        }
    }
    return dest;
}

/* TODO Write a kmalloc function */
/* https://cataas.com/cat/cute/says/Please%20don't%20kill%20me */
/*
void *kalloc(u32int size)
{
}
*/
