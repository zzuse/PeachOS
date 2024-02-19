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
qemu-system-i386 -hda ./boot.bin
```

# gdb
```
(gdb) add-symbol-file ../build/kernelfull.o 0x100000
(gdb) target remote | qemu-system-i386 -hda ./os.bin -S -gdb stdio
(gdb) break kernel_main
(gdb) c
(gdb) layout asm
(gdb) stepi
(gdb) info registers
```

# Burn to usb
```
sudo dd if=./boot.bin of=/dev/sdb
```

# Resource
```
wiki.osdev.org/Protected_Mode
www.ctyme.com/intr/int.htm
yjdoc2.github.io/8086-emulator-web/
falstad.com/circuit/
```

# Cross-Compiler build
https://wiki.osdev.org/GCC_Cross-Compiler
*   Installing Dependencies
*   Download packages
https://www.gnu.org/software/binutils/ -> https://ftp.gnu.org/gnu/binutils/ -> binutils-2.42.tar.xz
https://www.gnu.org/software/gcc/ -> Mirros -> US, Michigan -> releases -> gcc-10.2.0
*   Build
```
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
cd $HOME/src
mkdir build-binutils
cd build-binutils/
../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
$HOME/opt/cross/bin/$TARGET-gcc --version
```
