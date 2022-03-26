[org 0x7c00]
jmp start_bootloader
resb 0x50                       ; Reserve white space as some BIOSes rewrite the first bytes after 0x7c00
start_bootloader:
KERNEL_OFFSET equ 0x10000       ; Kernel code will be loaded at this address

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

%ifdef TEXT_MODE
mov bx, MSG_REAL_MODE
call print_string
%else
call video_mode
%endif

call load_kernel

call switch_to_pm

jmp $

%include "print/print_string.asm"
%include "video/video_mode.asm"
%include "disk/disk_load.asm"
%include "pm/gdt.asm"
%include "pm/print_string_pm.asm"
%include "pm/switch_to_pm.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET/0x10
; TODO Automate, we shouldn't enter the number of sectors manually, sector = 512 bytes
%ifdef TEXT_MODE
    mov dh, 24        ;; Change that when the kernel gets bigger
%else
    mov dh, 40        ;; Change that when the kernel gets bigger
%endif
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]
BEGIN_PM:
    ;mov ebx, MSG_PROT_MODE
    ;call print_string_pm

    call KERNEL_OFFSET

    jmp $

BOOT_DRIVE      db 0
MSG_REAL_MODE   db "Started in 16-bit Real mode", 0
MSG_PROT_MODE   db "Landed in 32-bit Mode :)", 0
MSG_LOAD_KERNEL db "... Loading kernel into memory ...", 0

times 510-($-$$) db 0
dw 0xaa55
