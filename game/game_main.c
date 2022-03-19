#include "../drivers/keyboard.h"
#include "../kernel/timer.h"

u8int back_video_buffer[320*200] = {0};

typedef struct bird_struct {
    u16int x;
    u16int y;
} bird;

u32int temp = 0;

void key_press(u8int scancode)
{
    temp += 10000;
}

void every_tick(u32int tick) 
{
    u8int *video_memory_2 = (u8int *)(0xA0000);
    u16int x, y;

    for (y = 0; y < 200; ++y) {
        for (x = 0; x < 320; ++x) {
            video_memory_2[y*320+x] = (u8int)(temp+x+y+tick);
        }
    }
}

void game_main()
{
    add_keyboard_handler(0, key_press);
    add_func_to_timer(0, every_tick);
}
