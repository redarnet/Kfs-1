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


# Add typical toolchain bin path to .profile if the toolchain installs to /usr/local or $HOME/.local
# We avoid forcing a path — adjust if your setup-toolchain.sh prints where i386-elf-gcc is installed.


cat <<'EOF' >> "$HOME/.profile"
# KFS1 toolchain path (example)
export PATH="$HOME/src/bin:$HOME/.local/bin:/usr/local/bin:$PATH"
EOF

# Ajouter le chemin du compilateur croisé au PATH de l'utilisateur vagrant
CROSS_PATH="/root/opt/cross/bin"
PROFILE_FILE="/home/vagrant/.bashrc"

if ! grep -q "$CROSS_PATH" "$PROFILE_FILE"; then
    echo "export PATH=$CROSS_PATH:\$PATH" >> "$PROFILE_FILE"
fi



echo "==> Provisioning complete. Close and reopen the shell (or 'vagrant ssh') to get PATH changes."