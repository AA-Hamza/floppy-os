#ifndef RENDERER_HELPER_H
#define RENDERER_HELPER_H

#include "game.h"

void write_background(u8int *video_buffer);
void write_foreground(u8int *video_buffer);
void write_tunnels(u8int *video_buffer, tunnel_t *tunnels);
void write_bird(u8int *video_buffer, bird_t *bird);
void write_str(u8int *video_buffer, const char *str, u32int x, u32int y, u8int color);
void write_score(u8int *video_buffer, u32int score);

#endif
