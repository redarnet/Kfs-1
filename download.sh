#!/usr/bin/env bash
set -e

BINUTILS_VERSION=2.45
GCC_VERSION=15.2.0

PREFIX="$HOME/opt/cross"
TARGET=i386-elf

export PATH="$PREFIX/bin:$PATH"

mkdir -p "$HOME/src"
cd "$HOME/src"

# BINUTILS
if [ ! -d "binutils-$BINUTILS_VERSION" ]; then
  wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz
  tar -xzf binutils-$BINUTILS_VERSION.tar.gz
fi

mkdir -p build-binutils
cd build-binutils
../binutils-$BINUTILS_VERSION/configure \
  --target=$TARGET \
  --prefix=$PREFIX \
  --disable-nls \
  --disable-werror

make -j$(nproc)
make install
cd ..

# GCC
if [ ! -d "gcc-$GCC_VERSION" ]; then
  wget https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
  tar -xzf gcc-$GCC_VERSION.tar.gz
fi

mkdir -p build-gcc
cd build-gcc
../gcc-$GCC_VERSION/configure \
  --target=$TARGET \
  --prefix=$PREFIX \
  --disable-nls \
  --enable-languages=c \
  --without-headers

make all-gcc -j$(nproc)
make install-gcc


#  latest version binutils :  binutils-2.45.tar.gz
#latest version gcc        : gcc-15.2.0.tar.gz
