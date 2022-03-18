#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../kernel/common.h"
#include "../kernel/isr.h"

void print_letter(u8int scancode);
//static void keyboard_callback(registers_t *regs);
void init_keyboard();
#endif
