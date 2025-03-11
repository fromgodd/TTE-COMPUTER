#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define MEM_SIZE 20
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

// Global variables
uint8_t ram[MEM_SIZE]; // 20 bytes of RAM
uint8_t accumulator;   // Accumulator register
uint8_t pc;            // Program counter
int zero_flag;         // Zero flag (1 if result is zero, else 0)
int running;           // Emulator running state

// Function prototypes
void load_program(uint8_t program[], int size);
void execute_instruction();
void print_memory();
void shell();
void parse_program(char *input);

// Main function
int main() {
    printf(GREEN "TTE COMPUTER - 20 Bytes RAM\n" RESET);
    printf("Type 'help' for instructions.\n");
    shell(); // Start the interactive shell
    return 0;
}

// Load a program into memory
void load_program(uint8_t program[], int size) {
    if (size > MEM_SIZE) {
        printf("Error: Program too large for memory.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        ram[i] = program[i];
    }
    printf("Program loaded into memory.\n");
}

// Execute instructions
void execute_instruction() {
    uint8_t opcode = ram[pc++]; // Fetch opcode
    uint8_t operand;

    switch (opcode) {
        case 0x00: // HLT: Halt execution
            running = 0;
            printf("Program halted.\n");
            break;

        case 0x01: // LDA: Load accumulator
            operand = ram[pc++];
            accumulator = ram[operand];
            zero_flag = (accumulator == 0);
            break;

        case 0x02: // STA: Store accumulator
            operand = ram[pc++];
            ram[operand] = accumulator;
            break;

        case 0x03: // ADD: Add to accumulator
            operand = ram[pc++];
            accumulator += ram[operand];
            zero_flag = (accumulator == 0);
            break;

        case 0x04: // SUB: Subtract from accumulator
            operand = ram[pc++];
            accumulator -= ram[operand];
            zero_flag = (accumulator == 0);
            break;

        case 0x05: // JMP: Jump to address
            operand = ram[pc++];
            pc = operand;
            break;

        default:
            printf("Unknown opcode: %02X\n", opcode);
            running = 0;
            break;
    }
}

// Print memory contents
void print_memory() {
    printf("Memory Dump:\n");
    for (int i = 0; i < MEM_SIZE; i++) {
        printf("%02X ", ram[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

// Parse and load a custom program
void parse_program(char *input) {
    uint8_t program[MEM_SIZE];
    int program_size = 0;
    char *token = strtok(input, " ");

    while (token != NULL && program_size < MEM_SIZE) {
        program[program_size++] = (uint8_t)strtol(token, NULL, 16);
        token = strtok(NULL, " ");
    }

    load_program(program, program_size);
}

// Interactive shell
void shell() {
    char input[64];
    while (1) {
        printf(GREEN "$ " RESET); // Green prompt
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strncmp(input, "run", 3) == 0) {
            // Run the loaded program
            running = 1;
            pc = 0;
            while (running) {
                execute_instruction();
            }
            print_memory();
        } else if (strncmp(input, "mem", 3) == 0) {
            // Print memory
            print_memory();
        } else if (strncmp(input, "program", 7) == 0) {
            // Load a custom program
            printf("Enter your program as space-separated hex bytes (e.g., 01 0A 03 0B 02 0C 00):\n");
            printf(GREEN "> " RESET);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0; // Remove newline
            parse_program(input);
        } else if (strncmp(input, "help", 4) == 0) {
            // Show help
            printf("Commands:\n");
            printf("  run      - Run the loaded program\n");
            printf("  program  - Load a custom program\n");
            printf("  mem      - Print memory contents\n");
            printf("  help     - Show this help message\n");
            printf("  exit     - Exit the emulator\n");
        } else if (strncmp(input, "exit", 4) == 0) {
            // Exit the shell
            printf("Exiting...\n");
            break;
        } else {
            printf("Unknown command. Type 'help' for instructions.\n");
        }
    }
}
