CROSS   = i386-elf
CC      = $(CROSS)-gcc
LD      = $(CROSS)-ld
AS      = $(CC)

CFLAGS  = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
ASFLAGS = -c -ffreestanding
LDFLAGS = -T src/linker.ld -nostdlib

SRC_DIR   = src
BUILD_DIR = build
ISO_DIR   = iso

KERNEL_BIN = $(BUILD_DIR)/kernel.bin
ISO        = kernel.iso

OBJS = \
	$(BUILD_DIR)/boot.o \
	$(BUILD_DIR)/gdt_a.o \
	$(BUILD_DIR)/kernel.o \
	$(BUILD_DIR)/draw_42.o \
	$(BUILD_DIR)/printk.o \
	$(BUILD_DIR)/gdt.o \
	$(BUILD_DIR)/printgdt.o \

all: $(ISO)

$(KERNEL_BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@


$(BUILD_DIR)/gdt_a.o: $(SRC_DIR)/gdt_a.s | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/draw_42.o: $(SRC_DIR)/draw_42.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/printk.o: $(SRC_DIR)/printk.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/gdt.o: $(SRC_DIR)/gdt.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/printgdt.o: $(SRC_DIR)/printgdt.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ISO): $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/
	cp $(SRC_DIR)/grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue -o $@ $(ISO_DIR)

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR) $(ISO)

re: clean all

.PHONY: all clean run re
