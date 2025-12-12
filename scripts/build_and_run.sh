#!/usr/bin/env bash
set -euo pipefail

# Build script for kernel ISO and optional QEMU run

PROJECT_DIR="/vagrant"
cd "$PROJECT_DIR"


# Check for toolchain
if ! command -v i386-elf-gcc >/dev/null 2>&1; then
echo "Error: i386-elf-gcc not found in PATH. Ensure setup-toolchain.sh installed it and reopen shell."
exit 1
fi


echo "==> Assembling and compiling"
make
