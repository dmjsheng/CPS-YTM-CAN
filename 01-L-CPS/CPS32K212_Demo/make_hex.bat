@echo off
arm-none-eabi-objcopy -Oihex CPS32K212_Demo.elf CPS32K212_Demo.hex
arm-none-eabi-objcopy -Obinary CPS32K212_Demo.elf CPS32K212_Demo.bin
echo [SUCCESS] Generated CPS32K212_Demo.hex and CPS32K212_Demo.bin
