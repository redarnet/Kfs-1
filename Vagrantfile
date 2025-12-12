# Vagrantfile for KFS1 (Debian 13 / bookworm)
Vagrant.configure("2") do |config|
  config.vm.box = "bento/debian-12"
  config.vm.box_version = "202407.22.0"
  config.vm.hostname = "Kfs-1"
  config.vm.network "private_network", ip: "192.168.56.110"
  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.name = "p3"
    vb.memory = "4096"
    vb.cpus = 4
  end

# Resources
config.vm.provider "virtualbox" do |vb|
vb.name = "kfs1-vm"
vb.memory = 4096
vb.cpus = 2
# Enable nested VT-x/AMD-V if VirtualBox supports it on the host
vb.customize ["modifyvm", :id, "--nested-hw-virt", "on"]
end

# Shared folder: project root -> /vagrant
config.vm.synced_folder ".", "/vagrant/"

# Forward SSH agent so the VM can use host keys if needed
config.ssh.forward_agent = true

# Provision with the shell script
config.vm.provision "shell", path: "scripts/provision.sh"

# Optional: keep the VM up after provisioning to allow manual work
config.vm.post_up_message = "vagrant up finished — connect with 'vagrant ssh'"
end