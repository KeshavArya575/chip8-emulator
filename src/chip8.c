#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

void init_chip8(Chip8 *chip) {
    chip->pc = 0x200;
    chip->I = 0;
    chip->sp = 0;
    chip->running = 1;
    chip->draw_flag = 0;
    for (int i = 0; i < 4096; i++)
        chip->memory[i] = 0;
    for (int i = 0; i < 16; i++)
        chip->V[i] = 0;
}

void load_rom(Chip8 *chip, const char *filename) {
    FILE *f = fopen(filename, "rb");

    if(!f){
        printf("Failed to open ROM\n");
        exit(1);
    }
    fread(&chip->memory[0x200], 1, 3584, f);
    fclose(f);
}

uint16_t fetch_opcode(Chip8 *chip){
    uint16_t opcode = 
            (chip->memory[chip->pc] << 8) |
               chip->memory[chip->pc + 1];

    return opcode;
}
   


void execute_opcode(Chip8 *chip, uint16_t opcode) {

    switch(opcode & 0xF000) {

        case 0x0000:

           if(opcode == 0x00E0) {

    for(int i = 0; i < 64 * 32; i++)
        chip->display[i] = 0;
    chip->draw_flag = 1;

    printf("CLS\n");
}
            break;

        case 0x1000: {

            uint16_t addr = opcode & 0x0FFF;

            chip->pc = addr;

            printf("JP %03X\n", addr);

            return;
        }

        case 0x6000: {

            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t nn = opcode & 0x00FF;

            chip->V[x] = nn;

            printf("LD V%X, %02X\n", x, nn);

            break;
        }

        case 0x7000: {

            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t nn = opcode & 0x00FF;

            chip->V[x] += nn;

            printf("ADD V%X, %02X\n", x, nn);

            break;
        }

        case 0xA000: {

            chip->I = opcode & 0x0FFF;

            printf("LD I, %03X\n", chip->I);

            break;
        }

        case 0xD000: {

    uint8_t x = chip->V[(opcode & 0x0F00) >> 8];
    uint8_t y = chip->V[(opcode & 0x00F0) >> 4];
    uint8_t height = opcode & 0x000F;

    chip->V[0xF] = 0;


    for(int row = 0; row < height; row++) {

        uint8_t sprite_byte = chip->memory[chip->I + row];

        for(int col = 0; col < 8; col++) {

            if((sprite_byte & (0x80 >> col)) != 0) {

                int px = (x + col) % 64;
                int py = (y + row) % 32;

                int index = py * 64 + px;

                if(chip->display[index] == 1)
                    chip->V[0xF] = 1;

                chip->display[index] ^= 1;
                
            }
        }
    }

    printf("DRW V%X, V%X, %X\n",
        (opcode & 0x0F00) >> 8,
        (opcode & 0x00F0) >> 4,
        height);
    chip->draw_flag = 1;

    break;
}

        default:

            printf("Unknown opcode %04X\n", opcode);
    }

    chip->pc += 2;
}

void print_registers(Chip8 *chip) {

    for(int i = 0; i < 16; i++) {
        printf("V%X: %02X ", i, chip->V[i]);
    }

    printf(" I:%03X", chip->I);
    printf("\n");
}

void update_timers(Chip8 *chip) {
    if (chip->delay_timer > 0)
     chip->delay_timer--;

 if (chip->sound_timer > 0)
 {
     chip->sound_timer--;
     printf("BEEP\n");
 }

}




