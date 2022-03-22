#ifndef GAME_H
#define GAME_H
#include "../kernel/common.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define KEY_UP_1 72     // UP arrow
#define KEY_UP_2 57     // Spacebar
#define KEY_CONTINUE_PLAYING 19 // R key

#define BACKGROUND_COLOR 0x66

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

#define SCORE_X 156
#define SCORE_Y 10
#define SCORE_COLOR 0x0F

#define SHADOW_OFFSET 0x01
#define GAME_OVER_COLOR 0x70
#define GAME_OVER_SHADOW_COLOR 0x0C


#define FOREGROUND_START (SCREEN_HEIGHT-25) 

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
