#include <stdio.h>
#include <i86.h>

#pragma pack( __push, 1 )
typedef struct vgachar {
    char c;
    unsigned char fg : 4;
    unsigned char bg : 3;
    unsigned char blink : 1;
} vgachar_t;
#pragma pack(_pop)

enum {
    VGA_COLOR_BLACK = 0x0,
    VGA_COLOR_BLUE = 0x1,
    VGA_COLOR_GREEN = 0x2,
    VGA_COLOR_CYAN = 0x3,
    VGA_COLOR_RED = 0x4,
    VGA_COLOR_MAGENTA = 0x5,
    VGA_COLOR_BROWN = 0x6,
    VGA_COLOR_LIGHTGREY = 0x7,
    VGA_COLOR_DARKGREY = 0x8,
    VGA_COLOR_LIGHTBLUE = 0x9,
    VGA_COLOR_LIGHTGREEN = 0xa,
    VGA_COLOR_LIGHTCYAN = 0xb,
    VGA_COLOR_LIGHTRED = 0xc,
    VGA_COLOR_LIGHTMAGENTA = 0xd,
    VGA_COLOR_YELLOW = 0xe,
    VGA_COLOR_WHITE = 0xf
};

#define TEXT_MODE_LOCATION (0xB8000)
#define VGAMEM ((vgachar_t*)TEXT_MODE_LOCATION)

int main(int argc, char** argv) {
    
    union REGS regIn, regOut;

    regIn.h.ah = 0x0f; // get video mode 
    regIn.h.al = 0; // regOut.al is the return location

    int386(0x10, &regIn, &regOut);

    printf("Mode: %02xh\n", regOut.h.al);

    for (int i = 80; i < 80*2; ++i) {

        vgachar_t c = {0};
        c.c = '#';
        c.fg = VGA_COLOR_LIGHTGREY;
        c.bg = VGA_COLOR_BLUE;

        VGAMEM[i] = c;
    }

    return 0;
}
