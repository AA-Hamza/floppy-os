; @params dx ------------*
;       dl=boot drive <--|--> dh = # sectors
;         bx --> Memory store location
disk_load:
    push dx
    ;mov cx, 20      ; Loop counter 

    mov [num_sectors], dh
    mov si, disk_packet
    mov word [mem_segment], 0x100
    mov word [sector], 1

;sector_loop:
    mov ah, 0x42
    int 0x13
    cmp ah, 0
    jne disk_error
    ;jmp $

    ;add word [sector], 1         ; Reading more 64 sectors, resulting 0x8000 bytes, about 32K bytes
    ;add word [mem_offset], 512     ; Adding 0x8000 to the mem_offset
    ;jnc sector_same_mem_segment

    ;;; Increment mem_segment, reset mem_offset if on differet mem_segment
    ;add word [mem_segment], 0x1000
    ;mov word [mem_offset], 0x0000
;sector_same_mem_segment:
    ;loop sector_loop    ; Decrement cx and loops if nonzero

    pop dx
    ret


DISK_ERROR_MSG:
    db "Disk read error!", 0

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    ;jmp $

;int 0x13 packet, https://wiki.osdev.org/Disk_access_using_the_BIOS_(INT_13h)
disk_packet:
    db 0x10     ;; size of packet (16 bytes)
    db 0x00     ;; always 0
num_sectors:
    dw 0x0000   ;; number of sectors
mem_offset:
    dw 0x0000   ;; transfer buffer mem_offset
mem_segment:
    dw 0x0000   ;; transfer buffer mem_segment
sector:
    dq 0x00000000
