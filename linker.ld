ENTRY(_start)
phys = 0x00001000;
SECTIONS
{
  .text phys : AT(phys) {
    code = .;
    *(.text)
    *(.rodata)
    . = ALIGN(4K); /* Alignment for better caching */
  }
  .data : AT(phys + (data - code))
  {
    data = .;
    *(.data)
    . = ALIGN(4K); /* Alignment for better caching */
  }
  .bss : AT(phys + (bss - code))
  {
    bss = .;
    *(.bss)
    . = ALIGN(4K); /* Alignment for better caching */
  }
  end = .;
}

