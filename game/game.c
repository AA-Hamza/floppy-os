#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "logic.h"
#include "game.h"

bird_t bird;

void game_run()
{
    bird.width = 25;
    bird.height = 25;
    bird.x = SCREEN_WIDTH / 2 - bird.width / 2;
    bird.y = SCREEN_HEIGHT / 2 - bird.height/2;

    init_logic();

    add_keyboard_handler(key_press);     // Key Press From logic
    add_func_to_timer(every_tick);       // Every tick is in logic, gets called by ../kernel/timer.c
}
