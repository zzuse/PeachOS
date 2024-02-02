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

# Look the Bin
```
bless ./boot.bin
```

# Run
```
qemu-system-x86_64 -hda ./boot.bin
```

# gdb
```
(gdb) target remote | qemu-system-x86_64 -hda ./boot.bin -S -gdb stdio
(gdb) c
(gdb) layout asm
(gdb) info registers
```

# Burn to usb
sudo dd if=./boot.bin of=/dev/sdb

# Resource
```
wiki.osdev.org/Protected_Mode
www.ctyme.com/intr/int.htm
yjdoc2.github.io/8086-emulator-web/
falstad.com/circuit/
```