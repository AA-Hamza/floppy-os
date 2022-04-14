#include "ports.h"

// Write a byte out to a specified port
void port_byte_out(u16int port, u8int value)
{
    asm volatile("outb %1, %0" : : "d" (port), "a" (value));
}

u8int port_byte_in(u16int port)
{
    u8int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "d" (port));
    return ret;
}

u16int port_word_in(u16int port)
{
    u16int ret;
    asm volatile("inw %1, %0" : "=a" (ret) : "d" (port));
    return ret;
}
