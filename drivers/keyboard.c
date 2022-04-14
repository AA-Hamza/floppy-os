#include "monitor.h"
#include "../kernel/ports.h"
#include "keyboard.h"

#define KEYBOARD_HANDLER_LIMIT 10
static keyboard_handler_ptr keyboard_handlers[KEYBOARD_HANDLER_LIMIT] = {0};

static void keyboard_callback(registers_t regs)
{
    u8int scancode = port_byte_in(0x60);
    u8int i;
    for (i = 0; i < KEYBOARD_HANDLER_LIMIT; ++i) {
        if (keyboard_handlers[i] != 0) {
            keyboard_handlers[i](scancode);
        }
        else {
            break;
        }
    }
}

void init_keyboard() 
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void add_keyboard_handler(keyboard_handler_ptr func_ptr)
{
    static u8int index = 0;
    if (func_ptr != 0)
        keyboard_handlers[index++] = func_ptr;
}
