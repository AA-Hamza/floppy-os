#include "../drivers/monitor.h"
#include "renderer.h"
#include "logic.h"
#include "game.h"
#include "math.h"
#include "assets/bird_img.h"
#include "assets/foreground_img.h"
#include "assets/tunnel_img.h"
//#include "font.h"
#include "assets/font_glyphs.h"

/*
 * This is the dumbest way you can do this, but It works for now at least
 */
#define BACK_VIDEO_BUFFER_ADDRESS 0x1e8480  // That is 2mb mark, & it is a free memory by design

// We render to this buffer, then copy when we are done (screen tearing)
static u8int *back_video_buffer = (u8int *)(BACK_VIDEO_BUFFER_ADDRESS);

static void draw_background();
static void draw_foreground();
static void draw_tunnels(tunnel_t *tunnels);
static void draw_bird(bird_t *bird);
static void draw_score(u32int score);
void swap_buffers();         // For the double buffering

void draw_scene(u8int *finised_rendering, bird_t *bird, tunnel_t *tunnels, u32int score)
{
    // This pointer is used to tell the caller function that this scene hasn't finished
    // Rendering yet. Wait until it finishes.
    *finised_rendering = 0;
    draw_background();
    draw_foreground();
    draw_tunnels(tunnels);
    draw_bird(bird);
    draw_score(score);
    swap_buffers();
    
    *finised_rendering = 1;
    return;
}

static void draw_background()
{
    u16int x, y;
    for (y = 0; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            back_video_buffer[y*SCREEN_WIDTH+x] = BACKGROUND_COLOR;
        }
    }
}

static void draw_foreground()
{
    static s8int foreground_x = 0;
    foreground_x -= WORLD_SPEED;
    if (foreground_x <= -FOREGROUND_SIZE) {
        foreground_x = 0;
    }

    s16int x, y;
    s16int x_index=0, y_index=0;
    for (y = FOREGROUND_START; y < FOREGROUND_START+FOREGROUND_SIZE; ++y) {
        for (x = foreground_x; x < SCREEN_WIDTH; ++x) {
            if (x >= 0) {
                back_video_buffer[y*SCREEN_WIDTH+x] = foreground_img[y_index][x_index];
            }
            x_index++;
            x_index %= FOREGROUND_SIZE;
        }
        x_index = 0;
        y_index++;
    }
    for (y = FOREGROUND_START+FOREGROUND_SIZE; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            back_video_buffer[y*SCREEN_WIDTH+x] = FOREGROUND_COLOR;
        }
    }
}

static void draw_tunnels(tunnel_t *tunnels)     // Six tunnels/sections
{
    u16int i;
    for (i = 0; i < 6; ++i) {
        if (tunnels[i].height > 0) {
            s16int x, y;
            s16int index_x = 0, index_y = 0;
            // Lower Tunnel
            for (y = SCREEN_HEIGHT-tunnels[i].height ; y < SCREEN_HEIGHT-tunnels[i].height+4; ++y) {
                for (x = tunnels[i].x-3; x < tunnels[i].x+TUNNEL_WIDTH+3; ++x) {
                    if (x >= 0 && x < SCREEN_WIDTH) {
                        back_video_buffer[y*SCREEN_WIDTH+x] = tunnel_top[index_y][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
                index_y++;
            }
            index_x = 0;
            for (y = SCREEN_HEIGHT-tunnels[i].height+4; y < FOREGROUND_START; ++y) {
                for (x = tunnels[i].x; x < tunnels[i].x+TUNNEL_WIDTH; ++x) {
                    if (x >= 0 && x < SCREEN_WIDTH) {
                        back_video_buffer[y*SCREEN_WIDTH+x] = tunnel_layer[0][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
            }
            
            // Upper Tunnel
            index_x = 0;
            for (y = 0; y < SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP-4; ++y) {
                for (x = tunnels[i].x; x < tunnels[i].x+TUNNEL_WIDTH; ++x) {
                    if (x > 0 && x < SCREEN_WIDTH) {
                        back_video_buffer[y*SCREEN_WIDTH+x] = tunnel_layer[0][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
            }
            index_y = 0;
            for (y = SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP-4; y < SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP; ++y) {
                for (x = tunnels[i].x-3; x < tunnels[i].x+TUNNEL_WIDTH+3; ++x) {
                    if (x >= 0 && x < SCREEN_WIDTH) {
                        back_video_buffer[y*SCREEN_WIDTH+x] = tunnel_top[index_y][index_x];
                    }
                    index_x++;
                }
                index_x = 0;
                index_y++;
            }
        }
    }
}

static void draw_bird(bird_t *bird)
{
    s32int x, y;
    s32int index_y = 0, index_x = 0;
    const double bird_center_x = bird->x+bird->width/2.0f;
    const double bird_center_y = bird->y+bird->height/2.0f;
    const double rotation_cosine = cosine(bird->rotation);
    const double rotation_sine = sine(bird->rotation);
    for (y = bird->y; y < bird->height+bird->y; ++y) {
        for (x = bird->x; x < bird->x+bird->width; ++x) {
            if (bird_img[index_y][index_x] != 0x0) {        // If there data to draw, 0x0 means it is transparent
                double dx = ((double) x) - bird_center_x;
                double dy = ((double) y) - bird_center_y;

                double new_x = rotation_cosine*dx - rotation_sine*dy + bird_center_x;
                double new_y = rotation_cosine*dy + rotation_sine*dx + bird_center_y;
                back_video_buffer[((u32int)(new_y+0.5))*SCREEN_WIDTH+((u32int)(new_x+0.5))] = bird_img[index_y][index_x];
            }
            index_x++;
        }
        index_x = 0;
        index_y++;
    }
}


// Set a pixel in the back_video_buffer
inline void set_pixel(u32int x, u32int y, u8int color)
{
    back_video_buffer[y*SCREEN_WIDTH+x] = color;
}

// Draw a single char to the back buffer
static void draw_char(char chr, u32int x, u32int y, u8int color)
{
    const u8int *glyph = font_glyphs[(u8int) chr];
    u32int xx, yy;
    for (yy = 0; yy < 8; ++yy) {
        for (xx = 0; xx < 8; ++xx) {
            if (glyph[yy] & (1 << xx)) {
                set_pixel(x+xx, y+yy, color);
            }
        }
    }
}

// Draw a null terminated string into the back buffer
void draw_str(const char *str, u32int x, u32int y, u8int color)
{
    char c;
    while ((c = *str++) != 0) {
        draw_char(c, x, y, color);
        x += 8;
    }
}

static void draw_score(u32int score) {
    char buff[80];
    u32int i = 0;
    do {
        buff[i++] = '0' + score % 10 ;
    } while (score /= 10);
    buff[i] = 0;
    // Swap all before the null
    u32int j;
    for (j = 0; j < i-1; ++j) {
        char temp = buff[j];
        buff[j] = buff[i-1-j];
        buff[i-1-j] = temp;
    }
    // For the Shadow effect
    draw_str(buff, SCORE_X+1, SCORE_Y+1, 0x0);
    draw_str(buff, SCORE_X, SCORE_Y, SCORE_COLOR);
}

void swap_buffers() {
    draw_screen(back_video_buffer);
}
