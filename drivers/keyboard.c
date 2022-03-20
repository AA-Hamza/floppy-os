#ifdef TEXT_MODE
#include "monitor_text_mode.h"
#else
#include "monitor.h"
#endif

#include "keyboard.h"

#define KEYBOARD_HANDLER_LIMIT 10
static keyboard_handler_ptr keybard_hanlders[KEYBOARD_HANDLER_LIMIT] = {0};

#ifdef TEXT_MODE
void print_letter_text_mode(u8int scancode)
{
    switch (scancode) {
        case 0x0:
            monitor_write("ERROR\n");
            break;
        case 0x1:
            monitor_write("ESC\n");
            break;
        case 0x2:
            monitor_write("1\n");
            break;
        default:
            if (scancode <= 0x7f) {
                monitor_write("Unknown key down");
            }
            else if (scancode <= 0x39 + 0x80) {
                monitor_write("Key up\n");
                print_letter_text_mode(scancode-0x80);
            }
            else {
                monitor_write("Unkown key up");
            }
            break;
    }
    return;
}
#endif

static void keyboard_callback(registers_t regs)
{
    u8int scancode = port_byte_in(0x60);
    u8int i;
    for (i = 0; i < KEYBOARD_HANDLER_LIMIT; ++i) {
        if (keybard_hanlders[i] == 0)
            continue;
        keybard_hanlders[i](scancode);
    }
}

void init_keyboard() 
{
    register_interrupt_handler(IRQ1, keyboard_callback);
#ifdef TEXT_MODE
    add_keyboard_handler(print_letter_text_mode);
#endif
}

void add_keyboard_handler(keyboard_handler_ptr func_ptr)
{
    static u8int index = 0;
    if (func_ptr != 0)
        keybard_hanlders[index++] = func_ptr;
}
