C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

all: os-image

run: all
	qemu-system-x86_64 os-image

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

kernel.bin: kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary --entry main

kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf64 -o $@

%.o: %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf32 -o $@

%.bin: %.asm
	nasm $< -f bin -I 'boot/' -o $@

clean:
	rm -fr *.bin *.dis *.o os-image *.map
	rm -fr kernel/*.o boot/*.bin drivers/*.o

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@
