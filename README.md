# Preview
This a very simple x86 operating system that just have enough to play small games
![Floppy OS preivew gif](./preview/preview.gif)

# Features
 - [x] Custom Bootloader 
 - [x] x86 compatible, at least works on QEMU
 - [x] Modifiable (meaning you can replace flappybird game easily), the game isn't hard coded like other alternatives.
 - [x] Fits in a Floppy Disk, who could have guessed?
 - [ ] Memory management, TODO
 - [ ] Works on real hardware, TODO

 
# How to compile?
You will have to build a cross compiler, you could read more about cross compilers [here](https://wiki.osdev.org/GCC_Cross-Compiler). my exact [setup](https://github.com/cfenollosa/os-tutorial/tree/master/11-kernel-crosscompiler).
You also will need `nasm` to compile the assembly code.
once you have `nasm` & `i386-elf-gcc` & `i386-elf-ld` you can use the command `make iso` to generate the bootable iso.

# How to run?
You will have to have `qemu` emulator.
```
qemu-system-i386 -fda boot.iso
```
to launch the emulator. alternatively you can simply type `make run`

# How to write my own game?
For a simple game you will need just these 4 functions
1. `add_keyboard_handler(void (*function_ptr)(unsigned int scancode)` 
	--> Takes a function pointer, it passes the key scancode to function.
2.  `add_func_to_timer(void  (*fucntion_ptr)(unsigned int tick))`
	--> You can think of this function as the scheduler, `function_ptr` gets called every time the PIC ticks,
	--> You use `init_timer(unsigned int frequency)` to specify the frequency.
	--> it is mainly used to draw on the screen, in my example (frequency = 60 Hz)
3. `draw_screen(unsigned char *video_buffer)` to draw the buffer on the screen, it resides in 	`drivers/monitor.h`, also the video_buffer size should be `320x200`. for more [info](https://en.wikipedia.org/wiki/Mode_13h)
4. `kalloc` which resides in `kernel/memory.h`, if you want more memory other than the stack.

and you all set, you can develop something like flappybird out of it.

# Text mode
this project includes 2 ways of writing to the screen
1. video mode: is used to write colors and pixels to the screen, like in the game.
2. text mode: for text based info, it is used here to print some interrupt info, but it will probably have some sort of shell in the feature.
 
to use text mode you just type `make TEXT_MODE=1 iso` & `make TEXT_MODE=1 run`.

## resources
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
http://www.jamesmolloy.co.uk/tutorial_html/
https://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs#Problem:_Not_using_a_cross-compiler
generally osdev.org has good explanations of low level topics
