CC=i386-elf-gcc
LD=i386-elf-ld
ASM=nasm

CCFLAGS=-ffreestanding
C_SOURCES=$(wildcard kernel/*.c drivers/*.c game/*.c)
HEADERS=$(wildcard kernel/*.h drivers/*.h game/*.c)
OBJ=${C_SOURCES:.c=.o}

BOOTSECT=boot_sect.bin
KERNEL=kernel.bin
ISO=boot.iso

QEMU=qemu-system-i386
QEMU_FLAGS=-fda		# For floppy disk

all: clean iso

run:
	$(QEMU) $(QEMU_FLAGS) $(ISO)
rund:
	qemu-system-i386 -drive format=raw,file=boot.iso

iso: boot/$(BOOTSECT) $(KERNEL)
	cat $^ > $(ISO)

kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -T linker.ld -o $(KERNEL) --oformat binary $^

%.o: %.c ${HEADERS}
ifdef TEXT_MODE
	$(CC) $(CCFLAGS) -DTEXT_MODE -c $< -o $@
else
	$(CC) $(CCFLAGS) -c $< -o $@
endif

%.o : %.asm
	$(ASM) $< -f elf -I 'kernel/' -o $@

%.bin: %.asm
ifdef TEXT_MODE
	$(ASM) $< -DTEXT_MODE -f bin -I 'boot/' -o $@
else
	$(ASM) $< -f bin -I 'boot/' -o $@
endif

clean:
	rm -fr *.bin *.dis *.o $(ISO) *.map
	rm -fr kernel/*.o boot/*.bin drivers/*.o -rf game/*.o

kernel.dis: kernel
	ndisasm -b 32 $< > $@
