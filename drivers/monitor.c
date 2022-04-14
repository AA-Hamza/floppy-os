#include "../kernel/kernel.h"
#include "../kernel/timer.h"
#include "../kernel/memory.h"
#include "../kernel/ports.h"
#include "monitor.h"

// VGA control port addresses
#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

static u8int *video_memory = (u8int *)0xA0000;

void draw_screen(u8int *buffer)
{
    memcpy(video_memory, buffer, SCREEN_HEIGHT*SCREEN_WIDTH);
}

void draw_pixel(u32int x, u32int y, u8int color)
{
    video_memory[y*SCREEN_WIDTH+x] = color;
}

void init_monitor()
{
    // Configure mode 13h palette with RRRGGGBB color
    port_byte_out(PALETTE_MASK, 0xff);
    port_byte_out(PALETTE_WRITE, 0x0);

    u8int i;
    for (i = 0; i < 255; ++i) {
        port_byte_out(PALETTE_DATA, (((i>>5) & 0x7) * (256 / 8)) / 4);
        port_byte_out(PALETTE_DATA, (((i>>2) & 0x7) * (256 / 8)) / 4);
        port_byte_out(PALETTE_DATA, (((i>>0) & 0x3) * (256 / 4)) / 4);
    }

    // set color 255 = white
    port_byte_out(PALETTE_DATA, 0x3F);
    port_byte_out(PALETTE_DATA, 0x3F);
    port_byte_out(PALETTE_DATA, 0x3F);

}
