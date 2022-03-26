ENTRY(_start)
phys = 0x00010000;
SECTIONS
{
  .text phys : AT(phys) {
    code = .;
    *(.text)
    *(.rodata)
    . = ALIGN(4K); /* Alignment for better caching */
  }
  .data BLOCK(4K) : AT(phys + (data - code))
  {
    data = .;
    *(.data)
    . = ALIGN(4K); /* Alignment for better caching */
  }
  .bss BLOCK(4K) : AT(phys + (bss - code))
  {
    bss = .;
    *(.bss)
    . = ALIGN(4K); /* Alignment for better caching */
  }
  end = .;
}

