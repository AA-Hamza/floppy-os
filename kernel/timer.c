#include "timer.h"
#include "isr.h"
#include "ports.h"

#define TIMER_FUNCTIONS 10

u32int tick = 0;
static function_ptr functions_handlers[TIMER_FUNCTIONS];

static void timer_callback(registers_t regs)
{
    tick++;
    u32int i;
    /*
     * Notice that this is blocking
     * meaning that if it takes more than one tick for these functions, timer_callback won't be called
     * and your tick won't be incremented.
     */
    for (i = 0; i < TIMER_FUNCTIONS; ++i) {
        if (functions_handlers[i] != 0) {
            functions_handlers[i](tick);
        }
        else {
            break;
        }
    }
}

void add_func_to_timer(function_ptr func) 
{
    static u8int index = 0;
    if (func != 0) {
        functions_handlers[index++] = func;
    }
}

void init_timer(u32int frequency)
{
    // Register our call
    register_interrupt_handler(IRQ0, &timer_callback);

    // the value we send to the PIT is the value to divide it's input clock
    // Note divisor must be small enough to fit into 16 bits
    u32int divisor = 1193180/frequency;

    // send the command byte, 0x36 means in repeating mode
    port_byte_out(0x43, 0x36);

    // Divisor has to be sent byte-wise, lower & upper bytes
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)((divisor>>8) & 0xFF);

    // Sending out the frequency divisor
    port_byte_out(0x40, l);
    port_byte_out(0x40, h);
}
