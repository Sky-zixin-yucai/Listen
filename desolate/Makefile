CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra
LDFLAGS = -T linker.ld -m elf_i386

all: kernel.bin

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

kernel.bin: kernel.o
	ld $(LDFLAGS) kernel.o -o kernel.bin

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

clean:
	rm -f kernel.o kernel.bin
