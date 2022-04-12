CC=i386-elf-gcc
LD=i386-elf-ld
ASM=nasm

CCFLAGS=-ffreestanding -O1
C_SOURCES=$(wildcard kernel/*.c drivers/*.c)
HEADERS=$(wildcard kernel/*.h drivers/*.h)
OBJ=${C_SOURCES:.c=.o}

BOOTSECT=boot_sect.bin
KERNEL=kernel.bin
ISO=boot.iso

QEMU=qemu-system-i386

all: iso

run:
	$(QEMU) -drive format=raw,file=$(ISO)

iso: boot/$(BOOTSECT) $(KERNEL)
	cat $^ > $(ISO)

kernel.bin: kernel/kernel_entry.o ${OBJ}
	$(LD) -T linker.ld -o $(KERNEL) --oformat binary $^

%.o: %.c ${HEADERS}
	$(CC) $(CCFLAGS) -DTEXT_MODE -c $< -o $@

%.o : %.asm
	$(ASM) $< -f elf -I 'kernel/' -o $@

%.bin: %.asm
ifdef FLOPPY
	$(ASM) $< -DTEXT_MODE -DFLOPPY -f bin -I 'boot/' -o $@
else
	$(ASM) $< -DTEXT_MODE -f bin -I 'boot/' -o $@
endif

clean:
	rm -fr *.bin *.dis *.o $(ISO) *.map
	rm -fr kernel/*.o boot/*.bin drivers/*.o

kernel.dis: kernel
	ndisasm -b 32 $< > $@
