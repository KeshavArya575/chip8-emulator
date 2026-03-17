#include <SDL2/SDL.h>
#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

#define SCALE 10

void init_display() {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "CHIP-8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        64 * SCALE,
        32 * SCALE,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void draw_display(Chip8 *chip) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int y = 0; y < 32; y++) {
        for(int x = 0; x < 64; x++) {

            if(chip->display[y * 64 + x]) {

                SDL_Rect rect = {
                    x * SCALE,
                    y * SCALE,
                    SCALE,
                    SCALE
                };

                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void cleanup_display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}