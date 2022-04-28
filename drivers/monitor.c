#include "../kernel/kernel.h"
#include "../kernel/timer.h"
#include "../kernel/memory.h"
#include "../kernel/ports.h"
#include "monitor.h"
#include "../game/assets/font_glyphs.h"

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

void draw_PANIC(char *text)
{
    u32int x, y;
    for (y = 0; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            video_memory[y*SCREEN_WIDTH+x] = 0b11100000;    // RED
        }
    }
    u32int index = 0;
    char chr = text[index];
    while (chr != 0) {
        const u8int *glyph = font_glyphs[(u8int) chr];      // a pointer to the character in font_glyphs in ./assets/font_glyph.h
        u32int index_x, index_y;                            // Bit index in the glyph
        for (index_y = 0; index_y < 8; ++index_y) {
            for (index_x = 0; index_x < 8; ++index_x) {
                if (glyph[index_y] & (1 << index_x)) {
                    video_memory[4*SCREEN_WIDTH+index_y*SCREEN_WIDTH+index_x+index*8+4] = 0xFF; 
                }
            }
        }
        chr = text[++index];
    }
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
