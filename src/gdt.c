#include "gdt.h"
#include "kernel.h"

__attribute__((section(".gdt"))) 

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

void dump_gdt(int i)
{
    uint8_t *p = (uint8_t *)&gdt[i];

    kprintf("GDT[%d] = ", i);
    for (int j = 0; j < 8; j++)
    {
        kprintf("%x ", p[j]);
    }
    kprintf("\n");
}


// a revoir 


void gdt_init(void)
{
    gdtp.limit = sizeof(gdt) - 1;
    // gdtp.base  = (uint32_t)&gdt;
    gdtp.base  = (uint32_t)&gdt;

    // Descripteur nul/
    gdt_set_entry(0, 0, 0, 0, 0);

    // Code noyau : base 0, limite 4 Go
    //  base, limite , octed d acces, flags

    // octet d acces :
    //  bit 7 : present (1)
    //  bit 6-5 : privilege level (00 = ring 0)
    //  bit 4 : descriptor type (1 = code/data)
    //  bit 3-0 : segment type (1010 = code exécutable, lecture seule)


    gdt_set_entry(1, BASE, LIMIT, KERNEL_CODE, FLAGS);   
    gdt_set_entry(2, BASE, LIMIT, KERNEL_DATA, FLAGS);
    gdt_set_entry(3, BASE, LIMIT, KERNEL_STACK, FLAGS);
    gdt_set_entry(4, BASE, LIMIT, USER_CODE, FLAGS);
    gdt_set_entry(5, BASE, LIMIT, USER_DATA, FLAGS);
    gdt_set_entry(6, BASE, LIMIT, USER_STACK, FLAGS);
    // gdt_set_entry(1, BASE, LIMIT, 0x00, FLAGS); // P = 0

    kprintf("GDT initialized\n");
    kprintf("GDT pointer at %x\n", &gdtp);
    gdt_flush((uint32_t)&gdtp);
    kprintf("GDT pointer at %x\n", &gdtp);
    kprintf("gdt   @ %x\n", &gdt);
    kprintf("gdtp  @ %x\n", &gdtp);
    kprintf("base  = %x\n", gdtp.base);
    kprintf("limit = %d\n", gdtp.limit);
    kprintf("sizeof(gdt) = %d\n", sizeof(gdt));
    kprintf("sizeof(gdt_entry) = %d\n", sizeof(struct gdt_entry));

    // for (int i = 0; i < GDT_ENTRIES; i++)
        dump_gdt(1);
    // attendu gdtp base == & gdt
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

}
