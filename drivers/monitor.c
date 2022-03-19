#ifndef TEXT_MODE
#include "../kernel/common.h"
#include "monitor.h"

u8int *video_memory = (u8int *)0xA0000;

void fill_screen()
{
    int i, j;
    for (i = 0; i < 320; ++i) {
        for (j = 0; j < 200; ++j) {
            video_memory[i] = (u8int)i*j;
        }
    }
}
#endif
