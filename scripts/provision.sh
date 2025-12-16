#!/usr/bin/env bash
set -e

echo "==> Update system"
apt-get update -y
apt-get upgrade -y

echo "==> Install packages"
apt-get install -y \
  build-essential nasm grub-pc-bin xorriso qemu-system-x86 \
  bison flex libgmp3-dev libmpfr-dev libmpc-dev texinfo

echo "==> Run cross-toolchain build as vagrant user"
sudo -u vagrant bash /vagrant/download.sh

echo "==> Add cross-compiler to PATH (vagrant)"
echo 'export PATH="$HOME/opt/cross/bin:$PATH"' >> /home/vagrant/.bashrc
chown vagrant:vagrant /home/vagrant/.bashrc

echo "==> Provisioning complete"
