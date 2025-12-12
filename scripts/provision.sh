#!/usr/bin/env bash
set -euo pipefail


# Provision script for KFS1
# Run as vagrant user by default

echo "==> Provision: update & install packages"
sudo apt-get update -y
sudo apt-get upgrade -y


sudo apt-get install -y \
build-essential nasm grub-pc-bin xorriso qemu-system-x86 make \
bison flex libgmp3-dev libmpfr-dev libmpc-dev texinfo


# Ensure /home/vagrant/src exists
mkdir -p "$HOME/src"


# If the user provided download.sh and setup-toolchain.sh in the project root, run them
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


chmod 777 root
sudo ln -sf /root/opt/cross/bin/i386-elf-gcc /usr/local/bin/i386-elf-gcc



echo "==> Provisioning complete. Close and reopen the shell (or 'vagrant ssh') to get PATH changes."