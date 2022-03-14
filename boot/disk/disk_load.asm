; @params dx ------------*
;       dl=boot drive <--|--> dh = # sectors
;         bx --> Memory store location
disk_load:
    push dx

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00        ; Cylinder 0
    mov dh, 0x00        ; Head 0
    mov cl, 0x02        ; Sector (offset) 2, base 1
    int 0x13            ; Actual reading

    jc disk_error

    pop dx
    cmp dh, al
    jne disk_error

    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG:
    db "Disk read error!", 0
