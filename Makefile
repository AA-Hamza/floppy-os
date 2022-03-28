CC=i386-elf-gcc
LD=i386-elf-ld
ASM=nasm

CCFLAGS=-ffreestanding
C_SOURCES=$(wildcard kernel/*.c drivers/*.c)
HEADERS=$(wildcard kernel/*.h drivers/*.h)
OBJ=${C_SOURCES:.c=.o}
GAME_SOURCES=$(wildcard game/*.c)
GAME_HEADERS=$(wildcard game/*.h)
GAME_OBJ=${GAME_SOURCES:.c=.o}

BOOTSECT=boot_sect.bin
KERNEL=kernel.bin
ISO=boot.iso

QEMU=qemu-system-i386

all: iso

run:
	$(QEMU) -drive format=raw,file=$(ISO)

iso: boot/$(BOOTSECT) $(KERNEL)
	cat $^ > $(ISO)

ifdef TEXT_MODE
kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -T linker.ld -o $(KERNEL) --oformat binary $^
else
kernel.bin: kernel/kernel_entry.o ${OBJ} ${GAME_OBJ}
	$(LD) -T linker.ld -o $(KERNEL) --oformat binary $^
endif

ifdef TEXT_MODE
%.o: %.c ${HEADERS}
	$(CC) $(CCFLAGS) -DTEXT_MODE -c $< -o $@
else
%.o: %.c ${HEADERS} ${GAME_HEADERS}
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
