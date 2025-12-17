#include "kernel.h"

void print_int(int n)
{
    if (n < 0) {
        terminal_putchar('-');
        n = -n;
    }

    if (n >= 10)
        print_int(n / 10);

    terminal_putchar('0' + (n % 10));
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

