#!/bin/bash
nasm -f bin boot.asm -o boot.bin
gcc -m32 -ffreestanding -c kernel.c -o kernel.o
ld -m elf_i386 -Ttext 0x1000 --oformat binary -o kernel.bin kernel.o
dd if=/dev/zero of=os.img bs=512 count=100
dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc
dd if=kernel.bin of=os.img bs=512 seek=1 conv=notrunc
qemu-system-x86_64 -drive format=raw,file=os.img
