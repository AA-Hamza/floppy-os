#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "game.h"
/*
 * BACK_VIDEO_BUFFER_ADDRESS is the address of the back video buffer
 * I initially wanted it to be on the stack, but it blow somehow
 * I know that making it fixed like this is just me flex taping the problem
 * TLDR; this is dumb, but it works for now at least
 */
#define BACK_VIDEO_BUFFER_ADDRESS (0x90001)           // First byte after ebp

void render_scene(u8int *finished_rendering, bird_t *bird, tunnel_t *tunnels, u32int score);
void render_overlay_text(u32int x, u32int y, const char *text, u8int color, u8int shadow_color);
void init_video_buffer();

#endif
