#include "renderer.h"
#include "logic.h"
#include "game.h"
#include "math.h"
#include "assets/bird_img.h"
#include "assets/foreground_img.h"
#include "assets/tunnel_img.h"

#define BACK_VIDEO_BUFFER_ADDRESS 0x1e8480 //that is 2mb mark, & it is a free memory by design

// We render to this buffer, then copy when we are done (screen tearing)
static u8int *back_video_buffer = (u8int *)(BACK_VIDEO_BUFFER_ADDRESS);
static u8int *main_video_buffer = (u8int *)(0xA0000);

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
    //s32int new_x, new_y;
    s32int index_y = 0, index_x = 0;
    const double bird_center_x = bird->x+bird->width/2.0f;
    const double bird_center_y = bird->y+bird->height/2.0f;
    const double rotation_cosine = cosine(bird->rotation);
    const double rotation_sine = sine(bird->rotation);
    for (y = bird->y; y < bird->height+bird->y; ++y) {
        for (x = bird->x; x < bird->x+bird->width; ++x) {
            if (bird_img[index_y][index_x] != 0x0) {
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

static void swap_buffers() {
    u32int i;
    for (i = 0; i < ((u32int)SCREEN_HEIGHT)*SCREEN_WIDTH; ++i) {
        main_video_buffer[i] = back_video_buffer[i];
    }
}

void draw_scene(u8int *finised_rendering, bird_t *bird, tunnel_t *tunnels)
{
    *finised_rendering = 0;
    draw_background();
    draw_foreground();
    draw_tunnels(tunnels);
    draw_bird(bird);
    swap_buffers();
    
    *finised_rendering = 1;
}
