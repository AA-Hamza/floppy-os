#ifndef MONITOR_H
#define MONITOR_H

#include "../kernel/kernel.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

void draw_screen(u8int *buffer);
void draw_pixel(u32int x, u32int y, u8int color);
void draw_PANIC(char *text);
void init_monitor();

#endif
