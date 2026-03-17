#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"

void init_display();
void draw_display(Chip8 *chip);
void cleanup_display();

#endif