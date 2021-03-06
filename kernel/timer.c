#include "timer.h"
#include "isr.h"
#include "ports.h"


u32int tick = 0;

u32int get_timer(void) 
{
    return tick;
}


static void timer_callback(registers_t regs)
{
    tick++;
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
