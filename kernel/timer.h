#ifndef TIMER_H
#define TIMER_H

// Timer Ticks per second
//#define TIMER_TICKS 363 
#define TIMER_TICKS 60

#include "kernel.h"
void init_timer(u32int frequency);
u32int get_timer(void);
#endif
