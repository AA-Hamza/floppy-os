#ifndef PORTS_H
#define PORTS_H

#include "kernel.h"

void port_byte_out(u16int port, u8int value);
u8int port_byte_in(u16int port);
u16int port_word_in(u16int port);

#endif
