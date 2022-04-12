#include "descriptor_tables.h"
#include "isr.h"
#include "timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/monitor_text_mode.h"


void _start()
{
    init_descriptor_table();    // Initializing IDT, ISR, IRQ
    asm volatile("sti");        // Tell the CPU to continue getting external interrupts We stopped it with cli in ./interrupts.asm

    init_keyboard();            // Initialize keyboard driver
    //init_timer(60);             // Basically 60 Hz

    monitor_clear();
    monitor_write("Installing ISRs\n");
    monitor_write("Press any key\n");
    monitor_write(
            " ______ _      ____  _____  _______     __   ____   _____\n"
            "|  ____| |    / __ \\|  __ \\|  __ \\ \\   / /  / __ \\ / ____|\n"
            "| |__  | |   | |  | | |__) | |__) \\ \\_/ /  | |  | | (___\n"
            "|  __| | |   | |  | |  ___/|  ___/ \\   /   | |  | |\\___ \\\n"
            "| |    | |___| |__| | |    | |      | |    | |__| |____) |\n"
            "|_|    |______\\____/|_|    |_|      |_|     \\____/|_____/\n" 
    );
                                                           
                                                           
}
