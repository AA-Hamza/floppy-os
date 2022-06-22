#ifndef TIMER_H
#define TIMER_H

#include "kernel.h"
void init_timer(u32int frequency);
u32int get_timer(void);
#endif
