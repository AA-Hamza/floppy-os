#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game.h"
#define TUNNEL_GAP 50
#define TUNNEL_WIDTH 20
#define FOREGROUND_START (SCREEN_HEIGHT-25)  


void key_press(u8int scancode);
void every_tick(u32int tick);
void init_logic();
#endif
