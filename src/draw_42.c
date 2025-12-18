#include <stdint.h>
#include <stddef.h>
#include "kernel.h"

extern void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

static const char *big42[] = {
    "    #        ####### ",
    "  # #             ## ",
    " #  #             ## ",
    "########     ####### ",
    "    #        ##      ",
    "    #        ##      ",
    "    #        ####### ",
};

#define BIG42_HEIGHT 7
#define BIG42_WIDTH  20

void draw_42(uint8_t color)
{
    size_t start_x  = 30;
    size_t start_y = 8;
    for (size_t y = 0; y < BIG42_HEIGHT; y++)
    {
        for (size_t x = 0; x < BIG42_WIDTH; x++)
        {
            char c = big42[y][x];
            if (c != ' ')
                terminal_putentryat(c, color, start_x + x, start_y + y);
        }
    }
}
