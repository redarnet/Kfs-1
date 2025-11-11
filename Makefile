CROSS = i386-elf
CC = $(CROSS)-gcc
AS = $(CROSS)-as
LD = $(CROSS)-ld

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T src/linker.ld -nostdlib
# faut les flags : -fno-builtin
# • -fno-exception
# • -fno-stack-protector
# • -fno-rtti
# • -nostdlib
# • -nodefaultlibs

ISO_DIR = iso
KERNEL_BIN = kernel.bin
ISO = mon_os.iso

all: $(ISO)

$(KERNEL_BIN): src/boot.o src/kernel.o
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) src/boot.o src/kernel.o

src/boot.o: src/boot.s
	$(AS) src/boot.s -o src/boot.o

src/kernel.o: src/kernel.c
	$(CC) $(CFLAGS) -c src/kernel.c -o src/kernel.o

$(ISO): $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/
	cp src/grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue -o $(ISO) $(ISO_DIR)

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f src/*.o $(KERNEL_BIN) $(ISO)

re: clean all

