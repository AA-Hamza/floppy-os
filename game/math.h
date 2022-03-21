#ifndef GAME_MATH_H
#define GAME_MATH_H

#include "game.h"

#define max(a,b) (a) > (b) ? (a) : (b)
#define min(a,b) (a) > (b) ? (b) : (a)

double sine(double angle);
double cosine(double angle);
u32int rand();
#endif
