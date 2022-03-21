#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "renderer.h"
#include "game.h"
#include "logic.h"
#include "math.h"

// Our lovely Bird 
extern bird_t bird;

/* The obsticles are tunnels and there are 4 sectoins/tunnels on the main screen
 * and another 2 outside the frame
*/
tunnel_t tunnels[6];          // 4 in the main screen

// Physics
static float gravity = 0;
static s8int stop_game = 0;

// Score
static u32int score = 0;

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
            if ((bird.y+bird.height) >= (SCREEN_HEIGHT-tunnels[i].height)) {
                return 1;       // Collided
            }
            // Check Upper Tunnel
            if (bird.y <= (SCREEN_HEIGHT-tunnels[i].height-TUNNEL_GAP)) {
                return 1;       // Collided
            }
            break;      // Break because other Tunnels haven't come yet
        }
        else {
            if (i == middle_tunnel && above_middle_tunnel == 1) {
                score++;
                above_middle_tunnel = 0;
            }
        }
    }
    if (bird.y+bird.height >= FOREGROUND_START) {
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
            bird.rotation = 0;
            bird.y = SCREEN_HEIGHT/2;
            score = 0;
            initialize_tunnels();
            stop_game = 0;
        }
        else {
            return;
        }
    }
    if (!was_down && (scancode == KEY_UP_1 /* up key */ || scancode == KEY_UP_2 /* space */)) {
        // Check if we are on the edge of the screen
        if (bird.y > 0) {
            gravity = -GRAVITY_UPWARD;
        }
        else {
            //bird.y = 0;
        }
        was_down = 1;
        bird.rotation = -BIRD_MAX_ROTATION;
    }
    // +0x80, means that they are released
    else if (scancode == KEY_UP_1+0x80 || scancode == KEY_UP_2+0x80) {
        was_down = 0;
    }
}

u8int finised_rendering = 1;
void every_tick(u32int tick) 
{
    if (finised_rendering == 1 && !stop_game) {
        bird.y += gravity;
        gravity += GRAVITY_PULLING;
        gravity = min(gravity, GRAVITY_MAX);

        bird.rotation += BIRD_ROTATION;
        bird.rotation = min(bird.rotation, BIRD_MAX_ROTATION);

        update_tunnels();
        if (collided()) {
            stop_game = 1;
            const char lost[] = "Game Over!";
            draw_str(lost, 1+SCREEN_WIDTH/2-sizeof(lost)*8/2+SHADOW_OFFSET, SCREEN_HEIGHT/3+SHADOW_OFFSET, GAME_OVER_SHADOW_COLOR);
            draw_str(lost, 1+SCREEN_WIDTH/2-sizeof(lost)*8/2              , SCREEN_HEIGHT/3              , GAME_OVER_COLOR);
            const char restart_question[] = "Press R to restart";
            draw_str(restart_question, 1+SCREEN_WIDTH/2-sizeof(restart_question)*8/2+SHADOW_OFFSET, SCREEN_HEIGHT/2+SHADOW_OFFSET, GAME_OVER_SHADOW_COLOR);
            draw_str(restart_question, 1+SCREEN_WIDTH/2-sizeof(restart_question)*8/2              , SCREEN_HEIGHT/2, GAME_OVER_COLOR);
            swap_buffers();
        }
        else {
            draw_scene(&finised_rendering, &bird, tunnels, score);
        }

    }
    else {
        return;
    }
}

void initialize_tunnels()
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
}

void init_logic()
{

    const char welcome_msg[] = "Welcome to Floppy OS";
    const char start_play[] = "Press Up arrow/Space Bar to start";

    initialize_tunnels();
    draw_scene(&finised_rendering, &bird, tunnels, 0);
    draw_str(welcome_msg, SCREEN_WIDTH/2+1-sizeof(welcome_msg)*8/2+SHADOW_OFFSET, SCORE_Y+8+20+SHADOW_OFFSET   , 0x0);       // For the shadow effect
    draw_str(welcome_msg, SCREEN_WIDTH/2+1-sizeof(welcome_msg)*8/2              , SCORE_Y+8+20                 , 0x0F);
    draw_str(start_play , SCREEN_WIDTH/2+1-sizeof(start_play)*8/2+SHADOW_OFFSET , SCORE_Y+8+20+20+SHADOW_OFFSET, 0x0);       // For the shadow effect
    draw_str(start_play , SCREEN_WIDTH/2+1-sizeof(start_play)*8/2               , SCORE_Y+8+20+20              , 0x0F);

    swap_buffers();             // To actually Reneder the text above

    stop_game = -1;             // Means the game haven't started yet
    add_keyboard_handler(key_press);     // Key Press From logic
    add_func_to_timer(every_tick);       // Every tick is in logic, gets called by ../kernel/timer.c
}
