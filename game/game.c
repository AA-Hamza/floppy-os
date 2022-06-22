#include "../drivers/keyboard.h"
#include "../kernel/timer.h"
#include "logic.h"
#include "game.h"

bird_t bird;

void game_run(void)
{
    bird.width = 16;
    bird.height = 16;
    bird.x = SCREEN_WIDTH / 2 - bird.width / 2;     // Not really needed, maybe for future changes
    bird.y = SCREEN_HEIGHT / 2 - bird.height/2;
    bird.rotation = 0.0f;

    init_logic(60);
}
