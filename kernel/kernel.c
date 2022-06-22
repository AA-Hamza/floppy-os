#include "descriptor_tables.h"
#include "isr.h"
#include "timer.h"
#include "memory.h"
#include "../drivers/keyboard.h"
#include "../game/game.h"

#include "../drivers/monitor.h"

void KPANIC(char *str)
{
    draw_PANIC(str);
    while (1) {}
}

void _start()
{
    init_descriptor_table();    // Initializing IDT, ISR, IRQ
    asm volatile("sti");        // Tell the CPU to continue getting external interrupts We stopped it with cli in ./interrupts.asm
    init_keyboard();            // Initialize keyboard driver
    init_timer(TIMER_TICKS);             // Basically 60 Hz
    init_monitor();
    game_run(60);                 // Run our little game
}
