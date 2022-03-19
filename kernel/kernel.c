#include "descriptor_tables.h"
#include "isr.h"
#include "timer.h"
#include "../drivers/keyboard.h"
#include "../game/game_main.c"

#ifdef TEXT_MODE
    #include "../drivers/monitor_text_mode.h"
#else
    #include "../drivers/monitor.h"
#endif


void _start()
{
    init_descriptor_table(); // Initializing IDT, ISR, IRQ

    asm volatile("sti");    // Tell the CPU to continue getting external interrupts We stopped it with cli in ./interrupts.asm

    init_keyboard(); // Initialize keyboard driver

#ifdef TEXT_MODE
    monitor_clear();
    monitor_write("Installing ISRs\n");
    monitor_write("Press any key\n");

#else
    // Add draw_screen function to index 0 in timer functions
    //add_func_to_timer(0, draw_screen);
    init_timer(60);
    game_main();
#endif
}
