#include "kernel.h"
#include <stdarg.h>
#include <stdint.h>

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
void print_hex(uint32_t n)
{
    char hex[] = "0123456789abcdef";

    terminal_writestring("0x");

    for (int i = 28; i >= 0; i -= 4)
        terminal_putchar(hex[(n >> i) & 0xF]);
}

#include "kernel.h"
#include <stdarg.h>
#include <stdint.h>

void print_hex(uint32_t n);
void print_int(int n);

void kprintf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            terminal_putchar(*fmt++);
            continue;
        }

        fmt++;  // saute %

        switch (*fmt) {
            case 's':
                terminal_writestring(va_arg(ap, char *));
                break;

            case 'c':
                terminal_putchar((char)va_arg(ap, int));
                break;

            case 'd':
                print_int(va_arg(ap, int));
                break;

            case 'x':
                print_hex(va_arg(ap, uint32_t));
                break;

            case '%':
                terminal_putchar('%');
                break;

            default:
                terminal_putchar('?');
                break;
        }

        fmt++;
    }

    va_end(ap);
}
