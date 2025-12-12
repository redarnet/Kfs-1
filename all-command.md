iso : debian-13.1.0-amd64-netinst.iso

```
su -
usermod -aG sudo vboxuser
```

Reboot vm

```
sudo apt update
sudo apt install build-essential nasm grub-pc-bin xorriso qemu-system-x86 make -y

sudo apt install -y build-essential bison flex libgmp3-dev libmpfr-dev libmpc-dev texinfo

```

```
chmod +x download.sh
./download.sh
chmod +x setup-toolchain.sh
cp  setup-toolchain.sh $HOME/src
./setup-toolchain.sh
```

️ Ferme et rouvre ton terminal 
Test : i386-elf-gcc --version

Dans src du projet
```
i386-elf-as boot.s -o boot.o
i386-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding
i386-elf-ld -T linker.ld -o kernel.bin boot.o kernel.o
```


```
mkdir -p isodir/boot/grub
cp kernel.bin isodir/boot/kernel.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o kernel.iso isodir
qemu-system-i386 -cdrom kernel.iso
``
== make + make run 
