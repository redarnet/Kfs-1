#include "kernel.h"
#include "gdt.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


void cursor_enable(uint8_t start, uint8_t end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

void cursor_update(size_t row, size_t col)
{
    uint16_t pos = row * VGA_WIDTH + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}


void vga_scroll(void) {
    for (int row = 1; row < VGA_HEIGHT; ++row)
	{
        for (int col = 0; col < VGA_WIDTH; ++col)
		{
            terminal_buffer[(row-1) * VGA_WIDTH + col] =
					terminal_buffer[row * VGA_WIDTH + col];
		}
	}
	uint16_t blank = vga_entry(' ', terminal_color);
    for (int col = 0; col < VGA_WIDTH; ++col)
	{
        terminal_buffer[(VGA_HEIGHT-1) * VGA_WIDTH + col] = blank;
	}
	terminal_row = VGA_HEIGHT - 1;
	cursor_update(terminal_row, terminal_column);

}

void terminal_putchar(char c)
{
    uint16_t blank = vga_entry(' ', terminal_color);

    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    }
    else if (c == '\b') {
        if (terminal_column > 0) {
            terminal_column--;
        }
        else if (terminal_row > 0) {
            terminal_row--;
            terminal_column = VGA_WIDTH - 1;
			while (terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] == blank)
			{
				if (terminal_column == 0)
					break;
				terminal_column--;
			}
        }
        terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = blank;
    }
    else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
    }

    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
    }

    if (terminal_row >= VGA_HEIGHT) {
        vga_scroll();
        terminal_row = VGA_HEIGHT - 1;
    }
    cursor_update(terminal_row, terminal_column);
}


void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	cursor_enable(0, 15);
	cursor_update(0, 0);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_clear(void) 
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	cursor_update(0, 0);
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}


void keyboard_handle_input(void)
{
    static uint8_t last_scancode = 0;

    uint8_t scancode = inb(0x60);

    if (scancode == last_scancode)
        return;

    last_scancode = scancode;

    if (scancode & 0x80)
        return;

    char c = scancode_table[scancode];
    if (c)
        terminal_putchar(c);
}


void kernel_main(void) 
{
	terminal_initialize();
	draw_42(5);
    gdt_init();
	while (1)
        keyboard_handle_input();
}