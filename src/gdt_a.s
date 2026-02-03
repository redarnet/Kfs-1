.global gdt_flush
.extern gdtp

gdt_flush:
    movl 4(%esp), %eax      # eax = &gdtp
    lgdt (%eax)             # charge GDTR

    # Far jump pour recharger CS
    ljmp $0x08, $flush_cs

flush_cs:
    movw $0x10, %ax         # data segment
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    ret