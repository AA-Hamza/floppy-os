#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../kernel/common.h"
#include "../kernel/isr.h"

void print_letter(u8int scancode);
void init_keyboard();

typedef void (*keyboard_handler_ptr)(u8int scancode);
void add_keyboard_handler(keyboard_handler_ptr func_ptr);

#endif
