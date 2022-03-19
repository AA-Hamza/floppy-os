#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "game.h"
#include "renderer.h"

#define GRAVITY_PULLING 1.0f
#define GRAVITY_UPWARD -10
#define GRAVITY_MAX 10
#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) > (b) ? (b) : (a)

static float gravity = 0;     // Gravity
extern bird_t bird;
extern tunnel_t *tunnels;

void key_press(u8int scancode)
{
    static u8int was_down = 0;
    if (!was_down && (scancode == 72 /* up key */ || scancode == 57 /* space */)) {
        if (bird.y > bird.height) {
            gravity = GRAVITY_UPWARD;
        }
        else {
            bird.y = 0;
        }
        was_down = 1;
    }
    // Key up, means that they are released
    else if (scancode == 72+0x80 || scancode == 57+0x80) {
        was_down = 0;
    }
}

u8int finised_rendering = 1;
void every_tick(u32int tick) 
{
    if (finised_rendering == 1) {
        bird.y += gravity;
        if (bird.y+bird.height > SCREEN_HEIGHT) {
            bird.y = SCREEN_HEIGHT-bird.height;
        }
        //if (tick %= 100)
        gravity += GRAVITY_PULLING;
        gravity = min(gravity, GRAVITY_MAX);
        u32int n = 0;
        draw_scene(&finised_rendering, &bird, tunnels, n);
    }
    else {
        return;
    }
}
