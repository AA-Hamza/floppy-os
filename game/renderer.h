#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "game.h"
void draw_scene(u8int *finished_rendering, bird_t *bird, tunnel_t *tunnels, u32int score);
void draw_str(const char *str, u32int x, u32int y, u8int color);
void swap_buffers();
#endif
