# Preview

This a very simple x86 operating system that just have enough to play small games, you can [try using it on your browser](https://aa-hamza.github.io/floppy-os/)

![Floppy OS preivew](./preview/preview.mp4)

# Features
 - [x] Custom Bootloader 
 - [x] x86 at least works on QEMU
 - [x] Keyboard Driver PS/2
 - [x] PIT
 - [x] 320x200 Video mode [Mode 13h](https://en.wikipedia.org/wiki/VGA_text_mode)
 - [x] Modifiable (meaning you can replace flappybird game easily), the game isn't hard coded like other alternatives.
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

# How to write my own game?
For a simple game you will need just these 4 functions
1. `add_keyboard_handler(void (*function_ptr)(unsigned int scancode)` 
    - Takes a function pointer, it passes the key scancode to function.
2.  `get_timer(void)`
    - Gets you the current tick
3. `draw_screen(unsigned char *video_buffer)` 
    - to draw the buffer on the screen, it resides in `drivers/monitor.h`, also the video_buffer size should be `320x200`. for more [info](https://en.wikipedia.org/wiki/Mode_13h)

and you all set, you can develop something like flappybird out of it.

# Text mode
this project includes 2 ways of writing to the screen
1. video mode: is used to write colors and pixels to the screen, like in the game.
2. text mode: for text based info, it is used here to print some interrupt info, but it will probably have some sort of shell in the feature.
### You can choose text mode branch in the repo, this is the Video mode branch

# Disk Read Error!
The "custome bootloader" is dumb, you have to specify the number of sectors to read to load the kernel. for my game it isn't an issue, but for yours it could be. so calculate the number of sectors your kernel is (kernel size / 512 bytes) and change line 32 in `boot/boot_sect.asm` accordingly.

## resources
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

http://www.jamesmolloy.co.uk/tutorial_html/

https://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs#Problem:_Not_using_a_cross-compiler

generally osdev.org has good explanations of low level topics
