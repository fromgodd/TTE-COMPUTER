# TTE-COMPUTER
Tiny tape based computer emulation in C

This is a simple emulator for a minimal instruction set computer with:

- 20 bytes of total RAM
- A single accumulator register
- A program counter (PC)
- A zero flag
- A basic instruction set with only 6 operations:

```
0x00: HLT - Halt execution
0x01: LDA - Load accumulator from memory
0x02: STA - Store accumulator to memory
0x03: ADD - Add memory value to accumulator
0x04: SUB - Subtract memory value from accumulator
0x05: JMP - Jump to address
```

TTE is good for learning about computer architecture fundamentals, assembly programming, and how CPUs operate at a low level.


![{B6E6FBFE-A801-4B93-B07F-44C205A348B6}](https://github.com/user-attachments/assets/e37006a9-c406-46eb-85b2-b9a3bb81ad6c)
