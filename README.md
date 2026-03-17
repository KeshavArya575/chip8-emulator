# CHIP-8 Emulator (C + SDL2)

A simple CHIP-8 emulator written in C with SDL2 for graphics.

## Features

* 4096-byte memory
* 16 registers (V0–VF)
* Index register (I)
* Program counter (PC)
* Stack
* Basic instruction set:

  * JP, LD, ADD
  * CLS
  * DRW (sprite rendering)
* 64×32 monochrome display
* XOR-based rendering with collision detection
* SDL2-based graphical output

## Demo

Runs the classic IBM Logo ROM.

## Build

### Windows (MSYS2 MinGW64)

```bash
gcc src/main.c src/chip8.c src/display.c -o chip8 \
    -lmingw32 -lSDL2main -lSDL2
```

## Run

```bash
./chip8 roms/IBM_logo.ch8
```
## Screenshot

![CHIP-8 Screenshot](assets/screenshot.png)

## TODO

* Keyboard input
* More opcode support
* Sound
* Better timing accuracy
