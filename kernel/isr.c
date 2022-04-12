#include "common.h"
#include "isr.h"

#include "../drivers/monitor_text_mode.h"

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs)
{
    monitor_write("Recieved interrupt: ");
    monitor_write_num(regs.int_no);
    monitor_put('\n');
    return;
}

void irq_handler(registers_t regs)
{
    if (regs.int_no >= 40) {
        port_byte_out(0xA0, 0x20);      // Send reset slave PIC
    }
    // Send reset signal to the master PIC
    port_byte_out(0x20, 0x20);  

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}
