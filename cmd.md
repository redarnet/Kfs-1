```bash
sudo apt update
sudo apt install build-essential nasm grub-pc-bin xorriso qemu-system-x86 make -y
```
installation des dependence
>  installation du compilateur croise 

binutils : assembleur + editeur de liens pour i686
gcc-cross-compiler   compile du C vers i686


repertoire ou stocker le compilateur croise 

```
mkdir -p $HOME/opt/cross
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

telecharger binutils

```bash
cd /tmp
wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz
tar -xvf binutils-2.41.tar.gz
mkdir build-binutils && cd build-binutils

../binutils-2.41/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install
```

telechager gcc

``` bash
cd /tmp
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz
tar -xvf gcc-13.2.0.tar.gz
mkdir build-gcc && cd build-gcc

../gcc-13.2.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --without-headers
make all-gcc -j$(nproc)
make install-gcc
```




	À quoi ça sert
Installer dépendances	Permet de compiler des outils
Compiler binutils	Crée l’assembleur et le linker pour i686-elf
Compiler gcc minimal	Crée un compilateur C pour i686-elf, sans OS
Ajouter au PATH	Permet d’utiliser i686-elf-gcc partou





