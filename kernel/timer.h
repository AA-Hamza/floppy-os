#ifndef TIMER_H
#define TIMER_H

#include "common.h"
void init_timer(u32int frequency);

typedef void (*function_ptr)(u32int);
void add_func_to_timer(u8int, function_ptr);
#endif
