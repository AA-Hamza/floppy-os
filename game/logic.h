#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game.h"

// Handle keyboard presses
void key_press(u8int scancode);
// The PIC calls this function
void every_tick(u32int tick);

void init_logic();
#endif
