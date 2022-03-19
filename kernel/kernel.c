#include "../drivers/monitor.h"
#include "descriptor_tables.h"
#include "isr.h"
#include "timer.h"
#include "../drivers/keyboard.h"


void _start()
{
    monitor_write("Installing ISRs\n");

    // Initializing IDT, ISR, IRQ
    init_descriptor_table();
    // Tell the CPU to continue getting external interrupts
    // We stopped it with cli in ./interrupts.asm
    asm volatile("sti");    

    //char *video_memory = (char *)(0xA0000);
    //int i;
    //for (i = 0; i < 1000; ++i) {
    //    video_memory[i] = i;
    //}
    //asm volatile("int $0x10");    

    monitor_clear();
    monitor_write("Press any key\n");
    init_keyboard();
}
