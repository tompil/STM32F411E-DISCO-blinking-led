EXTERN(__reset_handler)

_min_heap_size = 0x200;
_min_stack_size = 0x400;

MEMORY
{
  FLASH  (rx)   :  ORIGIN = 0x00000000,  LENGTH = 512K
  RAM    (rwx)  :  ORIGIN = 0x20000000,  LENGTH = 128K
}

_stack_end = ORIGIN(RAM) + LENGTH(RAM);

ENTRY(main)

SECTIONS
{
  . = ORIGIN(FLASH);

  .isr_vector : ALIGN(4)
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text : ALIGN(4)
  {
    _stext = .;
    *(.text)
    *(.text.*)
    *(.glue_7t)
    *(.glue_t)
    _etext = .;
  } > FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH

  .ARM.exidx :
  {
    __exidx_start = .;
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    __exidx_end = .;
  } > FLASH

  .rodata : ALIGN(4)
  {
    *(.rodata)
    *(.rodata.*)
  } > FLASH

  _init_data_start = LOADADDR(.data);

  .data : ALIGN(4)
  {
    FILL(0xFF)
    PROVIDE(_data_start = .);
    *(.data)
    *(.data.*)
    PROVIDE(_data_end = .);
  } > RAM AT > FLASH

  .bss (NOLOAD) : ALIGN(4)
  {
    PROVIDE(_bss_start = .);
    *(.bss)
    *(.bss.*)
    *(COMMON)
    PROVIDE(_bss_end = .);
  } > RAM

  .noinit (NOLOAD) : ALIGN(4)
  {
    *(.noinit)
    *(.noinit.*)
    *(COMMON)
  } > RAM

  .heap (NOLOAD) : ALIGN(4)
  {
    . = _min_heap_size + _min_stack_size;
  } > RAM

  /DISCARD/ :
  {
    libgcc.a ( * )
    libg.a ( * )
    libc.a ( * )
    libm.a ( * )
    libnosys.a ( * )
  }
}
