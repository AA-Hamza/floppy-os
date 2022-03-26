[bits 16]
switch_to_pm:
    cli     ; Stop CPU interrupts (like keyboard and such), why? because the BIOS was handling these things
            ; and it was using 16 bit real mode with interrupt vector, and now all of these is invalid
    lgdt [gdt_descriptor]   ; Load our global descriptor, which defines the size and the start address of GDT table
    
    mov eax, cr0    ; Make the switch to Protected mode
    or eax, 0x1     ; cr0 is set to 0, a control register
    mov cr0, eax    

    jmp CODE_SEG:init_pm    ; Make a far jump to clear CPU pipelining, also update cs (code segment) register to point to the right index in GDT table

[bits 32]
init_pm:
    ; Intialize registers & stack once in PM
    mov ax, DATA_SEG    ; Update all (expect cs) segment registers to point to data segment 
    mov ds, ax

    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x900000        ; Move the stack pointer to nearly the 10 mb mark
    mov esp, ebp

    call BEGIN_PM
