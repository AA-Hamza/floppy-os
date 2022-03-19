C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

all: os-image

run: clean all 
	qemu-system-i386 -fda os-image

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

kernel.bin: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 --oformat binary $^ --entry _start

%.o: %.c ${HEADERS}
ifdef TEXT_MODE
	i386-elf-gcc -DTEXT_MODE -ffreestanding -c $< -o $@
else
	i386-elf-gcc -ffreestanding -c $< -o $@
endif

%.o : %.asm
	nasm $< -f elf -I 'kernel/' -o $@

%.bin: %.asm
ifdef TEXT_MODE
	nasm $< -DTEXT_MODE -f bin -I 'boot/' -o $@
else
	nasm $< -f bin -I 'boot/' -o $@
endif

clean:
	rm -fr *.bin *.dis *.o os-image *.map
	rm -fr kernel/*.o boot/*.bin drivers/*.o

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@
