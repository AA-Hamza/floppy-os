#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "game.h"
#include "renderer.h"

#define GRAVITY_PULLING 1.0f
#define GRAVITY_UPWARD -10
#define GRAVITY_MAX 10
#define WORLD_SPEED 1.0f
#define TUNNEL_SECTION_WIDTH (SCREEN_WIDTH/4)
#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) > (b) ? (b) : (a)


static float gravity = 0;     // Gravity
extern bird_t bird;
tunnel_t tunnels[6];          // 4 in the main screen

u32int rand()
{
    static u32int next = 1;
    next = next * 1103515243 + 12345;
    return (u32int)(next / 65536) % 32768;
}

static void update_tunnels()     // Six tunnels/sections
{
    // section is 80
    u16int x, y;
    u16int i;
    for (i = 0; i < 6 ; ++i) {
        if (tunnels[i].x < -TUNNEL_SECTION_WIDTH) {        // Move it to the front by replacing tunnel[i].x with section 6
            tunnels[i].height = (u16int)(rand()%100);
            tunnels[i].x = SCREEN_WIDTH + TUNNEL_SECTION_WIDTH;
        }
        tunnels[i].x -= WORLD_SPEED;
    }
}

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

void every_tick(u32int tick) 
{
    static u8int finised_rendering = 1;
    if (finised_rendering == 1) {
        bird.y += gravity;
        if (bird.y+bird.height > SCREEN_HEIGHT) {
            bird.y = SCREEN_HEIGHT-bird.height;
        }
        gravity += GRAVITY_PULLING;
        gravity = min(gravity, GRAVITY_MAX);
        u32int n = 1;

        update_tunnels();
        draw_scene(&finised_rendering, &bird, tunnels);
    }
    else {
        return;
    }
}

void init_logic()
{
    tunnels[0].height = SCREEN_HEIGHT/3;
    tunnels[0].x = -40;
    tunnels[1].height = SCREEN_HEIGHT/2;
    tunnels[1].x = 40;
    tunnels[2].height = SCREEN_HEIGHT/1;
    tunnels[2].x = 120;
    tunnels[3].height = SCREEN_HEIGHT/1;
    tunnels[3].x = 200;
    tunnels[4].height = SCREEN_HEIGHT/4;
    tunnels[4].x = 280;
    tunnels[5].height = SCREEN_HEIGHT/2;
    tunnels[5].x = 360;
}
