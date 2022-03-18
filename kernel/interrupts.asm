[global idt_flush]              ; It means that jdt_flush will be called from C, specifically (./descriptor_tables.c)
idt_flush:
    mov eax, [esp+4]            ; Get the parameter of the function
    lidt [eax]
    ret

%macro ISR_NOERRCODE 1          ; Define a macro, taking one parameter
    [global isr%1]
    isr%1:
        cli
        push byte 0             ; Some interrupts have some error code needed to be passed as a parameter
                                ; So we define a dummy value of 0 as error code to be able to call isr_common_stub
        push byte %1
        jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
    [global isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8       ; Requires an error code
ISR_NOERRCODE 9
ISR_ERRCODE 10      ; Requires an error code
ISR_ERRCODE 11      ; Requires an error code
ISR_ERRCODE 12      ; Requires an error code
ISR_ERRCODE 13      ; Requires an error code
ISR_ERRCODE 14      ; Requires an error code
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

[extern isr_handler]
isr_common_stub:
    pusha

    mov ax, ds              ; Lower 16-bits of eax = ds
    push eax                ; Save the data segment descriptor

    mov ax, 0x10            ; Load the kernel Data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Hand over stack to C function
    push esp
    call isr_handler
    ; Pop stack pointer again
    pop esp

    pop eax                 ; Reload the original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8              ; Cleans up the pushed error code and pushed ISR number
                            ; That we did early in the file
    sti
    iret                    ; Pops CS, EIP, EFLAGS, SS, ESP


;;;;;;;;;;;;;;;;
;;;   IRQ    ;;;
;;;;;;;;;;;;;;;;

%macro IRQ 2        ; A stub for an IRQ, first parameter is IRQ number, the second is the ISR number it is mapped to
    [global irq%1]
    irq%1:
        cli
        push byte 0
        push byte %2
        jmp irq_common_stub
%endmacro

IRQ  0, 32
IRQ  1, 33
IRQ  2, 34
IRQ  3, 35
IRQ  4, 36
IRQ  5, 37
IRQ  6, 38
IRQ  7, 39
IRQ  8, 40
IRQ  9, 41
IRQ  10, 42
IRQ  11, 43
IRQ  12, 44
IRQ  13, 45
IRQ  14, 46
IRQ  15, 47

[extern irq_handler]    ; in isr.c
irq_common_stub:
    pusha

    mov ax, ds
    push eax    ; Save the data segment at the stack

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop eax     ; reload the saved/original data segment
    mov ds, ax
    mov es, ax
    mov es, ax
    mov gs, ax

    popa
    add esp, 8  ; Clean the pushed error code and pushed ISR number
    sti
    iret
