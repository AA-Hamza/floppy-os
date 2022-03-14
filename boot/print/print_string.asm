; This function takes bx as a parameter
print_string:
    pusha       ; Pushes CPU registers
    mov ah, 0x0e    ; BIOS teletype

    loop:
        ; Is it null yet
        cmp byte [bx], 0        ; value at bx == 0
        je outside_loop

        ; Print
        mov al, [bx]
        int 0x10    ; Print Char in al

        ; Increment and loop
        add bx, 1
        jmp loop

    outside_loop:
        popa        ; Restores CPU registers 
        ret         ; return to Caller
