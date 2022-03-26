; @params dx ------------*
;       dl=boot drive <--|--> dh = # sectors
;         bx --> kernel memory segment
disk_load:
    push dx

    mov [num_sectors], dh
    mov si, disk_packet
    mov word [mem_segment], bx
    mov word [sector], 1

    mov ah, 0x42
    int 0x13
    jc disk_error

    pop dx
    ret


DISK_ERROR_MSG:
    db "Disk read error!", 0

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

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
