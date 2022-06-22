#ifndef KERNEL_H
#define KERNEL_H

// Timer Ticks per second
#define TIMER_TICKS 600

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

void KPANIC(char *str);

#endif
