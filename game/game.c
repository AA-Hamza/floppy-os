#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "logic.h"
#include "game.h"

bird_t bird;

void game_run()
{
    bird.width = 15;
    bird.height = 15;
    bird.x = SCREEN_WIDTH / 2 - bird.width / 2;     // Not really needed, maybe for future changes
    bird.y = SCREEN_HEIGHT / 2 - bird.height/2;

    init_logic();
}
