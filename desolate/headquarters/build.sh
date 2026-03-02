nasm -f bin boot.asm -o boot.bin                # 编译引导程序
nasm -f elf32 kernel_start.asm -o kernel_start.o # 编译内核入口汇编
gcc -m32 -ffreestanding -c kernel.c -o kernel.o  # 编译C内核
ld -m elf_i386 -Ttext 0x1000 --oformat binary -o kernel.bin kernel_start.o kernel.o  # 链接成内核二进制
dd if=/dev/zero of=os.img bs=512 count=100
dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc
dd if=kernel.bin of=os.img bs=512 seek=1 conv=notrunc
qemu-system-x86_64 -drive format=raw,file=os.img