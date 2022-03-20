#ifndef GAME_H
#define GAME_H
#include "../kernel/common.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define BACKGROUND_COLOR 0x66
#define FOREGROUND_COLOR 0x43
#define BIRD_COLOR 0x8B
#define TUNNEL_COLOR 0x30

#define GRAVITY_PULLING 0.3f
#define GRAVITY_UPWARD 3
#define GRAVITY_MAX 2
#define WORLD_SPEED 1
#define BIRD_ROTATION 0.05f
#define BIRD_MAX_ROTATION 1.0f

#define TUNNEL_SECTION_WIDTH (SCREEN_WIDTH/4)
#define TUNNEL_MIN_HEIGHT (30)
#define TUNNEL_MAX_HEIGHT (120)
#define TUNNEL_GAP (50)
#define TUNNEL_WIDTH (20)

#define FOREGROUND_START (SCREEN_HEIGHT-25) 

#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) > (b) ? (b) : (a)

typedef struct bird_struct {
    s16int x;
    s16int y;
    u16int width;
    u16int height;
    double rotation;
} bird_t;

typedef struct tunnel_struct {
    s16int x;
    u16int height;
} tunnel_t;

void game_run();

#endif
