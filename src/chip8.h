#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

typedef struct 
{
    uint8_t memory[4096];
    uint8_t V[16];
    
    uint16_t I;
    uint16_t pc;
    uint16_t stack[16];
    uint8_t sp;
    uint8_t display[64 * 32];
    int running;
   
    uint8_t delay_timer;
    uint8_t sound_timer;
    int draw_flag;
} Chip8;

void init_chip8(Chip8 *chip);
void load_rom(Chip8 *chip, const char *filename);
uint16_t fetch_opcode(Chip8 *chip);
void execute_opcode(Chip8 *chip, uint16_t opcode);
void print_registers(Chip8 *chip);
void draw_display(Chip8 *chip);
void update_timers(Chip8 *chip);

#endif