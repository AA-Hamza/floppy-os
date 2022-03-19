#ifdef TEXT_MODE

#ifndef MONITOR_TEXT_MODE_H
#define MONITOR_TEXT_MODE_H

#include "../kernel/common.h"

// Put a single character
void monitor_put(char c);

//Clear screen
void monitor_clear();

// Put a null terminated string
void monitor_write(char *str);

// Write a decimal to the screen
void monitor_write_num(u32int n);

#endif

#endif
