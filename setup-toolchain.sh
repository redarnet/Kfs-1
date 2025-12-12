#!/bin/bash
set -e

echo "=== Installation du compilateur croisé i386-elf ==="

export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $HOME/src
cd $HOME/src

BINUTILS_VERSION=2.40
GCC_VERSION=13.2.0

if [ ! -d binutils-$BINUTILS_VERSION ]; then
  wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz
  tar -xzf binutils-$BINUTILS_VERSION.tar.gz
fi

if [ ! -d gcc-$GCC_VERSION ]; then
  wget https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
  tar -xzf gcc-$GCC_VERSION.tar.gz
fi

mkdir -p build-binutils && cd build-binutils
../binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls --disable-werror
make -j$(nproc)
make install
cd ..

mkdir -p build-gcc && cd build-gcc
../gcc-$GCC_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --without-headers
make all-gcc -j$(nproc)
make install-gcc
cd ..


sudo chmod 777 /root

echo 'export PATH=/root/opt/cross/bin:$PATH' >> ~/.bashrc
source ~/.bashrc


echo "✅ Le compilateur croisé est installé."
echo "➡️ Ferme et rouvre ton terminal ou fais : source ~/.bashrc"
echo "➡️ Test : i386-elf-gcc --version"
