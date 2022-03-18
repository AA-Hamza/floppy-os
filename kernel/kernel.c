#include "../drivers/monitor.h"
#include "descriptor_tables.h"
#include "isr.h"
#include "timer.h"
#include "../drivers/keyboard.h"

void _start()
{
    monitor_clear();
    monitor_write("Installing ISRs\n");
    init_descriptor_table();
    asm volatile("sti");
    monitor_write("Press any key\n");
    init_keyboard();
}
