#ifndef GAME_H
#define GAME_H
#include "../kernel/common.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

typedef struct bird_struct {
    s16int x;
    s16int y;
    u16int width;
    u16int height;
} bird_t;

typedef struct tunnel_struct {
    s16int x;
    s16int y;
    u16int width;
    u16int gap;
} tunnel_t;

void game_run();

#endif
