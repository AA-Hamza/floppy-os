#include "font.h"
//#include "../drivers/monitor.h"
#include "game.h"

void draw_char(char chr, u32int x, u32int y, u8int color) 
{
    const u8int *glyph = font_glyphs[(u8int) chr];

    u32int xx, yy;
    for (yy = 0; yy < 8; ++yy) {
        for (xx = 0; xx < 8; ++xx) {
            if (glyph[yy] && (1 << xx)) {
                //draw_pixel(x, y, color);
            }
        }
    }
}
