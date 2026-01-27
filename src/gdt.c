#include "gdt.h"
#define GDT_ENTRIES 7

static struct gdt_entry gdt[GDT_ENTRIES];
static struct gdt_ptr   gdtp;



extern void gdt_flush(uint32_t);

static void gdt_set_entry(
    int idx,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t gran
) {
    gdt[idx].base_low    = base & 0xFFFF;
    gdt[idx].base_middle = (base >> 16) & 0xFF;
    gdt[idx].base_high   = (base >> 24) & 0xFF;

    gdt[idx].limit_low   = limit & 0xFFFF;
    gdt[idx].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);

    gdt[idx].access      = access;
}

// a revoir 


void gdt_init(void)
{
    gdtp.limit = sizeof(gdt) - 1;
    gdtp.base  = (uint32_t)&gdt;

    // Descripteur nul
    gdt_set_entry(0, 0, 0, 0, 0);

    // Code noyau : base 0, limite 4 Go
    //  base, limite , octed d acces, flags

    // octet d acces :
    //  bit 7 : present (1)
    //  bit 6-5 : privilege level (00 = ring 0)
    //  bit 4 : descriptor type (1 = code/data)
    //  bit 3-0 : segment type (1010 = code exécutable, lecture seule)

    gdt_set_entry(1, LIMIT, KERNEL_CODE, FLAGS);   
    gdt_set_entry(2, LIMIT, KERNEL_DATA, FLAGS);
    gdt_set_entry(3, LIMIT, KERNEL_STACK, FLAGS);
    gdt_set_entry(4, LIMIT, USER_CODE, FLAGS);
    gdt_set_entry(5, LIMIT, USER_DATA, FLAGS);
    gdt_set_entry(6, LIMIT, USER_STACK, FLAGS);
    gdt_flush((uint32_t)&gdtp);
}
