/*
 * Copyright 2020-2025 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file yt_linker.ld
 * @brief 
 * 
 */











/* MEMORY MAP */
MEMORY
{
    MEMORY_IVT   (RX) : ORIGIN = 0x0, LENGTH = 0xc0
    MEMORY_TEXT   (RX) : ORIGIN = 0xc0, LENGTH = 0x1ff40
    MEMORY_IVT_RAM   (RW) : ORIGIN = 0x20000000, LENGTH = 0xc0
    MEMORY_STACK   (RW) : ORIGIN = 0x20003c00, LENGTH = 0x400
    MEMORY_RAM   (RW) : ORIGIN = 0x200000c0, LENGTH = 0x3b40
}
/* SECTIONS */
SECTIONS
{

    .IVT  : {
        
        . = ALIGN(4);
        IVT_start = .;
        isr_vector_region_start = .;
        KEEP(*(.isr_vector))
        isr_vector_region_end = .;
        
        IVT_end = .;
    } > MEMORY_IVT
   
    



    .TEXT  : {
        
        TEXT_start = .;
        i_region_start = .;
        *(i)
        *(i*)
        i_region_end = .;
        
        rodata_region_start = .;
        *(.rodata)
        *(.rodata*)
        rodata_region_end = .;
        
        text_region_start = .;
        *(.text)
        *(.text*)
        text_region_end = .;
        
        . = ALIGN(4);
        TEXT_end = .;
    } > MEMORY_TEXT
   
    



    .ARM  : {
        
        ARM_start = .;
        ARM.exidx_region_start = .;
        *(.ARM.exidx)
        *(.ARM.exidx*)
        ARM.exidx_region_end = .;
        
        . = ALIGN(4);
        ARM_end = .;
    } > MEMORY_TEXT
   
    



    CODE_RAM_rom_start_not_align = .;
    CODE_RAM_rom_start = (((CODE_RAM_rom_start_not_align + 4 - 1) / 4) * 4);
   
    CODE_RAM_rom_end = CODE_RAM_rom_start + CODE_RAM_ram_end - CODE_RAM_ram_start;




    DATA_RAM_rom_start_not_align = CODE_RAM_rom_end;
    DATA_RAM_rom_start = (((DATA_RAM_rom_start_not_align + 4 - 1) / 4) * 4);
   
    DATA_RAM_rom_end = DATA_RAM_rom_start + DATA_RAM_ram_end - DATA_RAM_ram_start;




    .IVT_RAM  : {
        
        . = ALIGN(1024);
        IVT_RAM_start = .;
        . += 0xC0;
        IVT_RAM_end = .;
    } > MEMORY_IVT_RAM
   
    



    .STACK  : {
        
        . = ALIGN(8);
        STACK_start = .;
        . += 1024;
        STACK_end = .;
    } > MEMORY_STACK
   
    



    .CODE_RAM  : AT(CODE_RAM_rom_start) {
        
        . = ALIGN(4);
        CODE_RAM_ram_start = .;
        CODE_RAM_start = .;
        . = ALIGN(4);
        code_ram_region_start = .;
        *(.code_ram)
        code_ram_region_end = .;
        
        . = ALIGN(4);
        CODE_RAM_end = .;
        CODE_RAM_ram_end = .;
    } > MEMORY_RAM
   
    
    ASSERT((CODE_RAM_ram_end - CODE_RAM_ram_start) == (CODE_RAM_rom_end - CODE_RAM_rom_start), "Copy Section CODE_RAM Size non-aligned")



    .DATA_RAM  : AT(DATA_RAM_rom_start) {
        
        . = ALIGN(4);
        DATA_RAM_ram_start = .;
        DATA_RAM_start = .;
        data_region_start = .;
        *(.data)
        *(.data*)
        data_region_end = .;
        
        . = ALIGN(4);
        DATA_RAM_end = .;
        DATA_RAM_ram_end = .;
    } > MEMORY_RAM
   
    
    ASSERT((DATA_RAM_ram_end - DATA_RAM_ram_start) == (DATA_RAM_rom_end - DATA_RAM_rom_start), "Copy Section DATA_RAM Size non-aligned")



    .BSS  (NOLOAD): {
        
        BSS_start = .;
        bss_region_start = .;
        *(.bss)
        *(.bss*)
        bss_region_end = .;
        
        . = ALIGN(4);
        BSS_end = .;
    } > MEMORY_RAM
   
    


    IVT_memory_start = ORIGIN(MEMORY_IVT);
    IVT_memory_end = ORIGIN(MEMORY_IVT) + LENGTH(MEMORY_IVT);
    IVT_memory_size = LENGTH(MEMORY_IVT);
    TEXT_memory_start = ORIGIN(MEMORY_TEXT);
    TEXT_memory_end = ORIGIN(MEMORY_TEXT) + LENGTH(MEMORY_TEXT);
    TEXT_memory_size = LENGTH(MEMORY_TEXT);
    IVT_RAM_memory_start = ORIGIN(MEMORY_IVT_RAM);
    IVT_RAM_memory_end = ORIGIN(MEMORY_IVT_RAM) + LENGTH(MEMORY_IVT_RAM);
    IVT_RAM_memory_size = LENGTH(MEMORY_IVT_RAM);
    STACK_memory_start = ORIGIN(MEMORY_STACK);
    STACK_memory_end = ORIGIN(MEMORY_STACK) + LENGTH(MEMORY_STACK);
    STACK_memory_size = LENGTH(MEMORY_STACK);
    RAM_memory_start = ORIGIN(MEMORY_RAM);
    RAM_memory_end = ORIGIN(MEMORY_RAM) + LENGTH(MEMORY_RAM);
    RAM_memory_size = LENGTH(MEMORY_RAM);
}