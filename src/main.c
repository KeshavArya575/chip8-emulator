#include <stdio.h>
#include "chip8.h"
#include "display.h"
#include <SDL2/SDL.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: %s rom\n", argv[0]);
        return 1;
    }

    Chip8 chip;
    init_chip8(&chip);
    load_rom(&chip, argv[1]);
   int cycles = 0;
   init_display();
SDL_Event event;


while(chip.running) {

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            chip.running = 0;
    }

    uint16_t opcode = fetch_opcode(&chip);

    execute_opcode(&chip, opcode);

    if(chip.draw_flag) {
        draw_display(&chip);
        chip.draw_flag = 0;
    }

    update_timers(&chip);

    SDL_Delay(16);
}
 return 0;
     }