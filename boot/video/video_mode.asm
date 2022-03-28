video_mode:
    pusha
    mov ah, 0x00
    mov al, 0x13
    int 0x10
    popa
    ret
