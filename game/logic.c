#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "game.h"
#include "renderer.h"

#define GRAVITY_PULLING 1
#define GRAVITY_UPWARD -10
#define GRAVITY_MAX 10
#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) > (b) ? (b) : (a)

static s32int gravity = 0;     // Gravity
extern bird_t bird;
extern tunnel_t *tunnels;

void key_press(u8int scancode)
{
    if (scancode <= 0x7f) {     // Basically means key down
        if (bird.y > bird.height) {
            gravity = GRAVITY_UPWARD;
        }
        else {
            bird.y = 0;
        }
    }
}

u8int finised_rendering = 0;
void every_tick(u32int tick) 
{
    if (finised_rendering == 1) {
        bird.y += gravity;
        gravity += GRAVITY_PULLING;
        gravity = max(gravity, GRAVITY_MAX);
        u32int n = 0;
        draw_scene(&finised_rendering, &bird, tunnels, n);
    }
    /*
    if (bird.y > SCREEN_HEIGHT-bird.height) {
        bird.y = SCREEN_HEIGHT-bird.height;
    }
    */
}
