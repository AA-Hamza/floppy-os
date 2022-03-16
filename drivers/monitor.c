#include "common.h"
#include "monitor.h"

u8int cursor_x = 0;
u8int cursor_y = 0;
u16int *video_memory = (u16int *)0xB8000;

static void move_cursor()
{
    u16int cursor_location = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursor_location >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_location >> 8);
}

static void scroll()
{
    // white on black
    u8int attribute_byte = (0 << 4 | 15 & 0x0f);
    u16int blank = 0x20 | (attribute_byte << 8);

    if (cursor_y >= 25) {
        int i;
        for (i = 0*80; i < 24*80; ++i) {
            video_memory[i] = video_memory[i+80];
        }
        for (i = 24*80; i < 25*80; ++i) {
            video_memory[i] = blank;
        }
        cursor_y = 24;
    }
}

void monitor_put(char c) 
{
    //static u8int cursor_y = 0, cursor_x = 0;
    //u16int *video_memory = (u16int *)0xb8000;
    u8int back_colour = 0;
    u8int fore_colour = 15;

    u8int attribute_byte = (back_colour << 4) | (fore_colour & 0x0F);

    u16int attribute = attribute_byte << 8;
    u16int *location;

    // Back space
    if (c == 0x08 && cursor_x) {
        cursor_x--;
    }
    // Tab (8 spaces)
    else if (c == 0x09) {
        cursor_x = (cursor_x+8) & ~(8-1);
    }
    else if (c == '\r') {
        cursor_x = 0;
    }
    else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c >= ' ') {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_y++;
        cursor_x = 0;
    }

    scroll();
    move_cursor();
}

void monitor_clear()
{
    // White on black
    u8int attribute_byte = (0 << 4) | (15 & 0x0F);

    /* Space */
    u16int blank = 32 | (attribute_byte << 8);

    int i;
    for (i = 0; i < 80*25; ++i) {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void monitor_write(char *str)
{
    int i = 0;
    while (str[i]) {
        monitor_put(str[i++]);
    }
}
