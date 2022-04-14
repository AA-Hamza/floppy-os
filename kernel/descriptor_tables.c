#include "descriptor_tables.h"
#include "kernel.h"
#include "memory.h"

extern void idt_flush(u32int);
static void init_idt();
static void idt_set_gate(u8int, u32int, u16int, u8int);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_descriptor_table()
{
    init_idt();
}

static void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256-1;
    idt_ptr.base  = (u32int)&idt_entries;

    // Make free the idt entries table
    memset((void *)&idt_entries, 0, sizeof(idt_entry_t)*256);

    //Remap the IRQ table. see link http://www.osdev.org/wiki/PIC
    // ICW1
    port_byte_out(0x20, 0x11);      // start initialization for Master PIC
    port_byte_out(0xA0, 0x11);      // start initialization for Slave PIC
    // ICW2
    port_byte_out(0x21, 0x20);      // Set master PIC offset to 32
    port_byte_out(0xA1, 0x28);      // Set slave PIC offset to 40

    // ICW3
    port_byte_out(0x21, 0x04);      // Tell master PIC that there is a slave PIC at 0x4
    port_byte_out(0xA1, 0x02);

    // ICW4 --> enable 8086 mode
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // OCW1 --> enable all IRQs
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    idt_set_gate( 0, (u32int)isr0,  0x08, 0x8E);
    idt_set_gate( 1, (u32int)isr1,  0x08, 0x8E);
    idt_set_gate( 2, (u32int)isr2,  0x08, 0x8E);
    idt_set_gate( 3, (u32int)isr3,  0x08, 0x8E);
    idt_set_gate( 4, (u32int)isr4,  0x08, 0x8E);
    idt_set_gate( 5, (u32int)isr5,  0x08, 0x8E);
    idt_set_gate( 6, (u32int)isr6,  0x08, 0x8E);
    idt_set_gate( 7, (u32int)isr7,  0x08, 0x8E);
    idt_set_gate( 8, (u32int)isr8,  0x08, 0x8E);
    idt_set_gate( 9, (u32int)isr9,  0x08, 0x8E);
    idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);

    idt_set_gate(32, (u32int)irq0,  0x08, 0x8E);
    idt_set_gate(33, (u32int)irq1,  0x08, 0x8E);
    idt_set_gate(34, (u32int)irq2,  0x08, 0x8E);
    idt_set_gate(35, (u32int)irq3,  0x08, 0x8E);
    idt_set_gate(36, (u32int)irq4,  0x08, 0x8E);
    idt_set_gate(37, (u32int)irq5,  0x08, 0x8E);
    idt_set_gate(38, (u32int)irq6,  0x08, 0x8E);
    idt_set_gate(39, (u32int)irq7,  0x08, 0x8E);
    idt_set_gate(40, (u32int)irq8,  0x08, 0x8E);
    idt_set_gate(41, (u32int)irq9,  0x08, 0x8E);
    idt_set_gate(42, (u32int)irq10, 0x08, 0x8E);
    idt_set_gate(43, (u32int)irq11, 0x08, 0x8E);
    idt_set_gate(44, (u32int)irq12, 0x08, 0x8E);
    idt_set_gate(45, (u32int)irq13, 0x08, 0x8E);
    idt_set_gate(46, (u32int)irq14, 0x08, 0x8E);
    idt_set_gate(47, (u32int)irq15, 0x08, 0x8E);

    idt_flush((u32int)&idt_ptr);
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags) 
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;

    idt_entries[num].flags = flags;
}
