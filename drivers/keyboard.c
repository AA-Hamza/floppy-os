#include "keyboard.h"
#include "monitor.h"

void print_letter(u8int scancode)
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
                print_letter(scancode-0x80);
            }
            else {
                monitor_write("Unkown key up");
            }
            break;
    }
}

static void keyboard_callback(registers_t regs)
{
    u8int scancode = port_byte_in(0x60);
    print_letter(scancode);
}

void init_keyboard() 
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
