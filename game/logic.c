#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "game.h"
#include "renderer.h"
#include "logic.h"

// Our lovely Bird 
extern bird_t bird;

/* The obsticles are tunnels and there are 4 sectoins/tunnels on the main screen
 * and another 2 outside the frame
*/
tunnel_t tunnels[6];          // 4 in the main screen

// Physics
static float gravity = 0;
static u8int stop_game = 0;

// Psuedo-Random function to generate the heights of the tunnels
static u32int rand()
{
    static u32int next = 42;
    next = next * 1103515243 + 12345;
    return (u32int)(next / 65536) % 32768;
}

// Update Tunnels positions 
//float world_x = 0;
static void update_tunnels()
{
    //world_x += WORLD_SPEED;
    u16int x, y;
    u16int i, tries = 0;
    for (i = 0; i < 6 ; ++i) {
        if (tunnels[i].x < -TUNNEL_SECTION_WIDTH) {        // Move it to the front by replacing tunnel[i].x with section 6
            while (tries < 3) {     // The user gets a tunnel-free section if the rand() outputs 3 times below TUNNEL_MIN_HEIGHT
                tunnels[i].height = (u16int)(rand()%TUNNEL_MAX_HEIGHT);
                if (tunnels[i].height >= TUNNEL_MIN_HEIGHT) {
                    break;
                }
                else {
                    tunnels[i].height = 0;
                }
                tries++;
            }
            tries = 0;
            tunnels[i].x = SCREEN_WIDTH + TUNNEL_SECTION_WIDTH;
        }
        //if (world_x > 1.0f) {
        tunnels[i].x -= WORLD_SPEED;//(s16int)world_x;
            //world_x = 0;
        //}
    }
}
static u8int collided()
{
    u8int i;
    for (i = 0; i < 6; ++i) {
        if (tunnels[i].height == 0)
            continue;
        if (tunnels[i].x < (bird.x+bird.width) && tunnels[i].x > bird.x) {      // The bird is above that
            // Check lower
            if ((bird.y+bird.height) >= (SCREEN_HEIGHT-tunnels[i].height)) {
                return 1;       // Collided
            }
            else if (bird.y < (SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP)) {
                return 1;       // Collided
            }
            return 0;
        }
        if (bird.y+bird.height > FOREGROUND_START) {
            return 1;
        }
    }
    return 0;
}

void key_press(u8int scancode)
{
    static u8int was_down = 0;
    if (scancode == 19) {
        stop_game = 0;
    }
    if (!was_down && (scancode == 72 /* up key */ || scancode == 57 /* space */)) {
        if (bird.y > bird.height) {
            gravity = -GRAVITY_UPWARD;
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
    if (finised_rendering == 1 && !stop_game) {
        bird.y += gravity;
        if (bird.y+bird.height > SCREEN_HEIGHT) {
            bird.y = SCREEN_HEIGHT-bird.height;
        }
        gravity += GRAVITY_PULLING;
        gravity = min(gravity, GRAVITY_MAX);
        u32int n = 1;

        update_tunnels();
        if (collided()) {
            stop_game = 1;
        }
        draw_scene(&finised_rendering, &bird, tunnels);
    }
    else {
        return;
    }
}

void init_logic()
{
    tunnels[0].height = 0; 
    tunnels[0].x = -40;
    tunnels[1].height = 0; 
    tunnels[1].x = 40;
    tunnels[2].height = 0; 
    tunnels[2].x = 120;
    tunnels[3].height = 0; 
    tunnels[3].x = 200;
    tunnels[4].height = 0; 
    tunnels[4].x = 280;
    tunnels[5].height = 0; 
    tunnels[5].x = 360;

    add_keyboard_handler(key_press);     // Key Press From logic
    add_func_to_timer(every_tick);       // Every tick is in logic, gets called by ../kernel/timer.c
}
