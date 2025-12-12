#!/usr/bin/env bash
set -euo pipefail

# Provision script for KFS1

echo "==> Provision: update & install packages"
sudo apt-get update -y
sudo apt-get upgrade -y


sudo apt-get install -y \
build-essential nasm grub-pc-bin xorriso qemu-system-x86 make \
bison flex libgmp3-dev libmpfr-dev libmpc-dev texinfo


mkdir -p "$HOME/src"

if [ -f /vagrant/download.sh ]; then
echo "==> Running /vagrant/download.sh"
chmod +x /vagrant/download.sh
/vagrant/download.sh
else
echo "==> Warning: /vagrant/download.sh not found — skip"
fi


if [ -f /vagrant/setup-toolchain.sh ]; then
echo "==> Running /vagrant/setup-toolchain.sh"
chmod +x /vagrant/setup-toolchain.sh
cp /vagrant/setup-toolchain.sh "$HOME/src/"
bash "$HOME/src/setup-toolchain.sh"
echo "==> Toolchain script executed"
else
echo "==> Warning: /vagrant/setup-toolchain.sh not found — skip"
fi


sudo chmod 777 /root
echo 'export PATH=/root/opt/cross/bin:$PATH' >> ~/.bashrc
source ~/.bashrc


echo "==> Provisioning complete. Close and reopen the shell (or 'vagrant ssh') to get PATH changes."