#include "gdt.h"
#include "kernel.h"


void dump_gdt(int i, struct gdt_entry *gdt)
{
    uint8_t *p = (uint8_t *)&gdt[i];

    kprintf("GDT[%d] = ", i);
    for (int j = 0; j < 8; j++)
    {
        kprintf("%x ", p[j]);
    }
    kprintf("\n");
}

void print_gdt(struct gdt_entry *gdt, struct gdt_ptr *gdtp)
{
    terminal_clear();
    kprintf("GDT initialized\n");
    kprintf("gdt   @ %x\n", gdt);
    kprintf("gdtp  @ %x\n", &gdtp);
    kprintf("base  = %x\n", gdtp->base);
    kprintf("limit = %d\n", gdtp->limit);
    kprintf("sizeof(gdt) = %d\n", sizeof(struct gdt_entry) * GDT_ENTRIES);
    kprintf("sizeof(gdt_entry) = %d\n", sizeof(struct gdt_entry));

    for (int i = 0; i < GDT_ENTRIES; i++)
        dump_gdt(i, gdt);
}


    // attendu gdtp base == gdt
    // attendu gdtp limit == sizeof (gdt) -1
    // attendu sizeof (gdt_entry) == 8

    // ff ff   -> limit low = 0xFFFF
    // 00 00   -> base low
    // 00      -> base mid
    // 9a      -> access
    // cf      -> granularity
    // 00      -> base high

    // access = 1001 1010 = 0x9A
    // granularity = 1100 1111 = 0xCF