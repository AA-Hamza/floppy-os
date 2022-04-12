# Preview
Text mode branch

# Features
 - [x] Custom Bootloader 
 - [x] x86 at least works on QEMU
 - [x] Keyboard Driver PS/2
 - [x] PIT
 - [x] VGA text mode (`TEXT_MODE`)
 - [x] Fits in a Floppy Disk, who could have guessed?
 - [ ] Memory management, TODO
 - [ ] Works on real hardware, TODO

 
# How to compile?
You will have to build a cross compiler, you could read more about cross compilers [here](https://wiki.osdev.org/GCC_Cross-Compiler). my exact [setup](https://github.com/cfenollosa/os-tutorial/tree/master/11-kernel-crosscompiler).
You also will need `nasm` to compile the assembly code.
once you have `nasm` & `i386-elf-gcc` & `i386-elf-ld` you can use the command `make iso` to generate the raw image, or `make FLOPPY=1 iso` for a bootable floppy disk.

# How to run?
You will have to have `qemu` emulator, (this works for both the `FLOPPY` edition and the `raw` edition).
```
qemu-system-i386 -drive format=raw,file=boot.iso
```

for the floppy edition
```
qemu-system-i386 -fda boot.iso
```

to launch the emulator. alternatively you can simply type `make run`

# How to write my own programs?
For a simple game you will need just these 4 functions
1. `add_keyboard_handler(void (*function_ptr)(unsigned int scancode)` 
    - Takes a function pointer, it passes the key scancode to function.
2.  `add_func_to_timer(void  (*fucntion_ptr)(unsigned int tick))`
	- You can think of this function as the scheduler, `function_ptr` gets called every time the PIC ticks,
	- You use `init_timer(unsigned int frequency)` to specify the frequency.

# Text mode
this project includes 2 ways of writing to the screen
1. video mode: is used to write colors and pixels to the screen, like in the game.
2. text mode: for text based info, it is used here to print some interrupt info, but it will probably have some sort of shell in the feature.

# Disk Read Error!
The "custome bootloader" is dumb, you have to specify the number of sectors to read to load the kernel. for my game it isn't an issue, but for yours it could be. so calculate the number of sectors your kernel is (kernel size / 512 bytes) and change line 32 in `boot/boot_sect.asm` accordingly.

## resources
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

http://www.jamesmolloy.co.uk/tutorial_html/

https://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs#Problem:_Not_using_a_cross-compiler

generally osdev.org has good explanations of low level topics
