# PeachOS
Hello World

# Install
```
sudo apt update
sudo apt install nasm
nasm -v
sudo apt install qemu-system-x86
```

# Compile
```
nasm -f bin ./boot.asm -o ./boot.bin
ndisasm boot.bin
```

# Run
```
qemu-system-x86_64 -hda ./boot.bin
```

# Burn to usb
sudo dd if=./boot.bin of=/dev/sdb