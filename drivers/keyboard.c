#include "monitor_text_mode.h"

#include "keyboard.h"

#define KEYBOARD_HANDLER_LIMIT 10
static keyboard_handler_ptr keyboard_handlers[KEYBOARD_HANDLER_LIMIT] = {0};

char kbd_US [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};


void print_letter_text_mode(u8int scancode)
{
    monitor_put(kbd_US[scancode]);
    /*
    switch (scancode) {
        case 0x0:
            monitor_write("ERROR\n");
            break;
        default:
            if (scancode <= 0x7f) {
                monitor_write("key down scancode: ");
                monitor_write_num(scancode);
                monitor_write(" suggested char: ");
                monitor_put(kbd_US[scancode]);
                monitor_put('\n');
            }
            else if (scancode <= 0x39 + 0x80) {
                monitor_write("Key up\n");
                print_letter_text_mode(scancode-0x80);
            }
            else {
                monitor_write("key up\n");
            }
            break;
    }
    return;
    */
}

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
    add_keyboard_handler(print_letter_text_mode);
}

void add_keyboard_handler(keyboard_handler_ptr func_ptr)
{
    static u8int index = 0;
    if (func_ptr != 0)
        keyboard_handlers[index++] = func_ptr;
}
