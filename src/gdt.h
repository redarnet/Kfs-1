#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>


#define GDT_ENTRIES 7
#define LIMIT 0xFFFFF
#define BASE 0x00000000
#define KERNEL_CODE 0x9A
#define KERNEL_DATA 0x92
#define KERNEL_STACK 0x96
#define USER_CODE 0xFA
#define USER_DATA 0xF2
#define USER_STACK 0xF6  

#define FLAGS 0xCF


struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

void gdt_init(void);
void print_gdt(struct gdt_entry *gdt, struct gdt_ptr *gdtp);

extern struct gdt_entry *gdt;
extern struct gdt_ptr gdtp;

#endif