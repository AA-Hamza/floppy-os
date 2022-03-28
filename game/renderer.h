#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "game.h"

void render_scene(u8int *finished_rendering, bird_t *bird, tunnel_t *tunnels, u32int score);
void render_overlay_text(u32int x, u32int y, const char *text, u8int color, u8int shadow_color);

#endif
