#ifndef TEXT_MODE
#include "../kernel/common.h"
#include "../kernel/timer.h"
#include "monitor.h"

static u8int *video_memory = (u8int *)0xA0000;

static void fill_screen(u32int tick)
{
    u32int x, y;
    for (y = 0; y < 200; ++y) {
        for (x = 0; x < 320; ++x) {
            video_memory[y*320+x] = (u8int)((x+y)+tick);
        }
    }
}

void draw_screen(u32int tick)
{
    tick++;
    fill_screen(tick);
}
#endif
