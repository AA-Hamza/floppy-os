#include "renderer.h"

#define BACKGROUND_COLOR 0x0E

// We render to this buffer, then copy when we are done (screen tearing)
static u8int back_video_buffer[SCREEN_HEIGHT*SCREEN_WIDTH];
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
static void draw_forground()
{

}
static void draw_tunnels(tunnel_t *tunnels_t)
{

}
static void draw_bird(bird_t *bird)
{

}
static void swap_buffers() {
    u32int i;
    for (i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; ++i) {
        main_video_buffer[i] = back_video_buffer[i];
    }
}
void draw_scene(u8int *finised_rendering, bird_t *bird, tunnel_t *tunnels, u32int n)
{
    *finised_rendering = 0;
    draw_background();
    swap_buffers();
    *finised_rendering = 1;
}
