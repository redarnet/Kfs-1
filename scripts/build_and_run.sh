#!/usr/bin/env bash
set -euo pipefail


# Build script for kernel ISO and optional QEMU run
# Run this from /vagrant (project root)


PROJECT_DIR="/vagrant"
cd "$PROJECT_DIR"


# Check for toolchain
if ! command -v i386-elf-gcc >/dev/null 2>&1; then
echo "Error: i386-elf-gcc not found in PATH. Ensure setup-toolchain.sh installed it and reopen shell."
exit 1
fi


echo "==> Assembling and compiling"
# i386-elf-as boot.s -o boot.o


# i386-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2


# i386-elf-ld -T linker.ld -o kernel.bin boot.o kernel.o


# mkdir -p isodir/boot/grub
# cp kernel.bin isodir/boot/kernel.bin
# cp grub.cfg isodir/boot/grub/grub.cfg


# echo "==> Creating ISO (kernel.iso)"
# grub-mkrescue -o kernel.iso isodir || {
# echo "grub-mkrescue failed — ensure grub-pc-bin and xorriso are installed." ; exit 1
# }


# echo "==> kernel.iso created in $PROJECT_DIR/kernel.iso"


# # Attempt to run qemu
# if qemu-system-i386 --version >/dev/null 2>&1; then
# echo "==> Launching qemu-system-i386... (press Ctrl-A X or Ctrl-C to quit depending on qemu)"
# qemu-system-i386 -cdrom kernel.iso
# else
# echo "==> qemu-system-i386 not available or cannot run here — skip running QEMU"
# fi