[bits 32]
VIDEO_MEMORY equ 0xb8000    ; Start of Video buffer in VGA
WHITE_ON_BLACK equ 0x0f

; Prints a null terminated string pointed to by EBX
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

    print_string_pm_loop:
        mov al, [ebx]   ; Store char in AL
        mov ah, WHITE_ON_BLACK  ; attributes in AH

        cmp al, 0
        je print_string_pm_done

        mov [edx], ax   ; Store char and attributes to the current character cell

        add ebx, 1  ; Move 1 char
        add edx, 2  ; Each 2 bytes represent 1 char on screen, so moving 2 bytes means moving to the next character cell

        jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
