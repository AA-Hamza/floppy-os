[bits 32]
[extern _start]
call _start
jmp $

%include "./interrupts.asm"
