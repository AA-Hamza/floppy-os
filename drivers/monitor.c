#include "../kernel/common.h"
#include "../kernel/timer.h"
#include "../kernel/memory.h"
#include "monitor.h"

static u8int *video_memory = (u8int *)0xA0000;

static void fill_screen_garbage(u32int tick)
{
    u32int x, y;
    for (y = 0; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            video_memory[y*SCREEN_WIDTH+x] = (u8int)((x+y)+tick);
        }
    }
}

void draw_screen(u8int *buffer)
{
    memcpy(video_memory, buffer, SCREEN_HEIGHT*SCREEN_WIDTH);
}

void draw_pixel(u32int x, u32int y, u8int color)
{
    video_memory[y*SCREEN_WIDTH+x] = color;
}

