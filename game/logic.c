#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "renderer.h"
#include "../utils/math.h"
#include "../utils/string.h"
#include "logic.h"


// Our lovely Bird 
extern bird_t bird;

/* The obsticles are tunnels and there are 4 sectoins/tunnels on the main screen
 * and another 2 outside the frame
*/
tunnel_t tunnels[6];          // 4 in the main screen

// Rendering Lock
u8int finished_rendering = 1;

// Physics
static float gravity = 0;
static s8int stop_game = 0;

// Score
static u32int score = 0;

// Messages
static const char welcome_msg[] = "Welcome to Floppy OS";
static const char start_play[] = "Press Up arrow/Space Bar to start";
static const char lost[] = "Game Over!";
static const char restart_question[] = "Press R to restart";

void initialize_tunnels();

// Update Tunnels positions 
static void update_tunnels()
{
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
        tunnels[i].x -= WORLD_SPEED;//(s16int)world_x;
    }
}

/* Fuction to detect if the bird has collided with any objects in the scene
 * It also handles the score
 */
static u8int collided()
{
    static u8int above_middle_tunnel = 0;
    static u8int middle_tunnel = 0;
    u8int i;
    for (i = 0; i < 6; ++i) {
        if (tunnels[i].height == 0)
            continue;
        // if the tunnel is the one in the middle, check if the bird collided with it
        if (tunnels[i].x < (bird.x+bird.width) && (tunnels[i].x+TUNNEL_WIDTH) > bird.x) {
            above_middle_tunnel = 1;
            middle_tunnel = i;
            // Check Lower Tunnel
            if ((bird.y+bird.height) > (SCREEN_HEIGHT-tunnels[i].height)) {
                above_middle_tunnel = 0;
                return 1;       // Collided
            }
            // Check Upper Tunnel
            if (bird.y < (SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP)) {
                above_middle_tunnel = 0;
                return 1;       // Collided
            }
            break;      // Break because other Tunnels haven't come yet
        }
        else {
            if (i == middle_tunnel && above_middle_tunnel == 1 && tunnels[i].height != 0) {
                score++;
                above_middle_tunnel = 0;
            }
        }
    }
    if (bird.y+bird.height > FOREGROUND_START) {
        return 1;
    }
    return 0;
}

void key_press(u8int scancode)
{
    static u8int was_down = 0;
    if (stop_game == -1 && (scancode == KEY_UP_1 || scancode == KEY_UP_2)) {        // Start the game, this only works at the start screen
        stop_game = 0;
    }
    if (stop_game == 1) {
        if (scancode == KEY_CONTINUE_PLAYING) {
            bird.y = SCREEN_HEIGHT/2;       // Place the bird in the middle of the screen
            gravity = -GRAVITY_UPWARD;     // Make it go up
            bird.rotation = -BIRD_MAX_ROTATION;          // The bird 
            score = 0;
            initialize_tunnels();
            stop_game = 0;
        }
        else {
            return;
        }
    }
    if (!was_down && (scancode == KEY_UP_1 /* up key */ || scancode == KEY_UP_2 /* space */)) {
        gravity = -GRAVITY_UPWARD;
        was_down = 1;
        bird.rotation = -BIRD_MAX_ROTATION;
    }
    // +0x80, means that they are released
    else if (scancode == KEY_UP_1+0x80 || scancode == KEY_UP_2+0x80) {
        was_down = 0;
    }
}

void handle_frame(u32int tick) 
{
    static u32int old_tick = 0;
    if (finished_rendering == 1 && !stop_game) {
        bird.y += gravity;
        if (bird.y < 0) {
            bird.y = 0;
        }
        gravity += GRAVITY_PULLING;
        gravity = min(gravity, GRAVITY_MAX);

        bird.rotation += BIRD_ROTATION;
        bird.rotation = min(bird.rotation, BIRD_MAX_ROTATION);

        update_tunnels();

        // We don't have to check every frame for collision, also this saves a bit of power in the browser edition
        if (collided()) {
            stop_game = 1;
            render_overlay_text(1+SCREEN_WIDTH/2-sizeof(lost)*8/2, SCREEN_HEIGHT/3, lost, GAME_OVER_COLOR, GAME_OVER_SHADOW_COLOR);
            render_overlay_text(1+SCREEN_WIDTH/2-sizeof(restart_question)*8/2, SCREEN_HEIGHT/2, restart_question, GAME_OVER_COLOR, GAME_OVER_SHADOW_COLOR);
        }
        else {
            render_scene(&finished_rendering, &bird, tunnels, score);
        }

        // Render number of ticks taken by the frame
        char buff[80];
        itoa(tick-old_tick, buff, 10);
        render_overlay_text(10, 0, buff,GAME_OVER_COLOR, GAME_OVER_SHADOW_COLOR);
        old_tick = tick;
    }
}

void initialize_tunnels()
{
    u8int i = 0;
    s32int x;
    for (x = -40; x <= 360; x += 80) {
        tunnels[i].height = 0;      // 0 height --> don't display
        tunnels[i].x      = x;      // assigning initial x coordinates
        i++;
    }
}

void init_logic(const int fps)
{
    // Initial Frame
    initialize_tunnels();
    render_scene(&finished_rendering, &bird, tunnels, 0);

    // Welcome Messages
    render_overlay_text(SCREEN_WIDTH/2+1-sizeof(welcome_msg)*8/2, SCORE_Y+8+20, welcome_msg, 0xFF, 0x00);
    render_overlay_text(SCREEN_WIDTH/2+1-sizeof(start_play)*8/2, SCORE_Y+8+20+20, start_play, 0xFF, 0x00);

    stop_game = -1;                      // Means the game haven't started yet
    add_keyboard_handler(key_press);     // Key Press logic

    // 
    u32int last_frame = 0;
    while (1) {
        const u32int now = get_timer();
        if ((now - last_frame) >= (TIMER_TICKS / fps)) {
            last_frame = now;
            handle_frame(now);
        }
    }
}
