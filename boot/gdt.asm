; Used to make the switch to 32bit Protected mode
; GDT stands for Global Descriptor Table
gdt_start:

gdt_null:
    ; GDT table starts with a null 8 bytes (8 bytes is the size of an entry)
    dd 0x0      ; dd is declare double word which means 4 bytes in current mode (16 bit)
    dd 0x0

gdt_code:
    ; The code segment descriptor
    ; Base=0x0, limit=0xfffff
    ; First flag: (present) 1 / (privilege aka ring) 00 / (descriptor type) 1   --> 1001b
    ; type flags: (code)1 / (conforming)0 / (readable)1 / (accessed)0           --> 1010b
    ; 2nd flags: (granularity)1 / (32-bit default)1 / (64-bit seg)0 / (AVL)0    --> 1100b
    dw 0xffff       ; Limit (bits 0-15)
    dw 0x0          ; Base (bits 0-15)
    db 0x0          ; Base (bits 16-23)
    db 10011010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit (bits 16-19)
    db 0x0          ; Base (bits 24-31)

gdt_data:
    ; Data segment
    ; Base=0x0, limit=0xfffff (OVERLAPPING)
    ; Basically same as gdt_code
    ; Type flags: (code)0 / (expand down)0 / (writible)1 / (accessed)0 --> 0010b
    dw 0xffff       ; Limit (bits 0-15)
    dw 0x0          ; Base (bits 0-15)
    db 0x0          ; Base (bits 16-23)
    db 10010010b    ; 1st flags, type flags
    db 11001111b    ; 2nd flags, limit (bits 16-19)
    db 0x0          ; Base (bits 24-31)

gdt_end:
    ; Putting a label so the assembler can calculate the size of the GDT.

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of our GDT, always one less of the true size
    dd gdt_start                ; Put the start address of gdt_start

; Define constants for the GDT segment descriptor offsets, so that 
; For example when DS=DATA_SEG, the CPU knows what we are talking about Data segment
; As (0x0 = NULL, 0x08 = Code, 0x10 = Data)
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
