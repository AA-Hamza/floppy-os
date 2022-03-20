#include "renderer.h"
#include "logic.h"

#define BACK_VIDEO_BUFFER_ADDRESS 0x1e8480 //that is 2mb mark, & it is a free memory by design
#define BACKGROUND_COLOR 0x66
#define FOREGROUND_COLOR 0x43
#define BIRD_COLOR 0x8B
#define TUNNEL_COLOR 0x30
#define TUNNEL_SECTION_WIDTH (SCREEN_WIDTH/4)

// We render to this buffer, then copy when we are done (screen tearing)
static u8int *back_video_buffer = (u8int *)(BACK_VIDEO_BUFFER_ADDRESS);
static u8int *main_video_buffer = (u8int *)(0xA0000);
//extern bird_t bird;

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
    u16int x, y;
    for (y = FOREGROUND_START; y < SCREEN_HEIGHT; ++y) {
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
            // Lower Tunnel
            for (y = SCREEN_HEIGHT-tunnels[i].height; y < FOREGROUND_START; ++y) {
                for (x = tunnels[i].x; x < tunnels[i].x+TUNNEL_WIDTH; ++x) {
                    if (x > 0 && x < SCREEN_WIDTH) {
                        back_video_buffer[y*SCREEN_WIDTH+x] = TUNNEL_COLOR;
                    }
                }
            }
            
            // Upper Tunnel
            for (y = 0; y < SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP; ++y) {
                for (x = tunnels[i].x; x < tunnels[i].x+TUNNEL_WIDTH; ++x) {
                    if (x > 0 && x < SCREEN_WIDTH) {
                        back_video_buffer[y*SCREEN_WIDTH+x] = TUNNEL_COLOR;
                    }
                }
            }
        }
    }
}
static void draw_bird(bird_t *bird)
{
    u16int x, y;
    for (y = bird->y; y < bird->height+bird->y; ++y) {
        for (x = bird->x; x < bird->x+bird->width; ++x) {
            back_video_buffer[y*SCREEN_WIDTH+x] = BIRD_COLOR;
        }
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
