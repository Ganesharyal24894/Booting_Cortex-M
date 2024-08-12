
# **This is a project for learning how ARM Cortex-M CPU boots.**

The goal of this project is to boot an ARM Cortex-M-based CPU, specifically the STM32G0 MCU, from scratch. This project helps you understand the internal workings of a CPU and the magic that happens behind the curtains before you get to the `main()` function.

## Booting Sequence of Cortex-M CPUs

- When the CPU comes out of reset, it first checks the boot pins of the MCU to decide the boot mode (there are various boot modes in which the CPU can boot). Based on this, the 'boot memory' (simply, the memory from where your CPU boots) changes. In simple words, the CPU can select flash memory, system memory, or SRAM as its boot memory. Based on the selected boot memory, the physical remap of the memory changes. For example, the address 0x00000000 can be an alias to 0x08000000 if the boot mode selects internal FLASH memory as the boot memory.
- The first address of the boot memory consists of the stack's start address (RAM's end address) value, which is loaded into the MSP (Main Stack Pointer). The next value is loaded into the PC (Program Counter) register, and this value is the address of the reset handler code.
- The reset handler code generally performs some initialization processes and then calls the `main()` function. This initialization code typically copies the .data section of the program from flash to RAM, and it also places zeroes in the .bss section's address in RAM.

So, this is what I have broadly tried to cover in this project. I have written everything from scratch to perform this booting sequence and then run a simple blinky program inside the `main()` function. Although the booting sequence might sound very simple, the things that you will learn by doing this one simple project will get you started in the right direction.
