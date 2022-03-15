#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// Put a single character
void monitor_put(char c);

//Clear screen
void monitor_clear();

// Put a null terminated string
void monitor_write(char *str);

#endif
