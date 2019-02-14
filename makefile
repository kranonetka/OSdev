CFLAGS=-m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386

clean:
	rm -f bootblock.bin disk.img start.o cmain.o kernel

build: clean bootblock.bin kernel
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=bootblock.bin of=disk.img bs=512 count=1 conv=notrunc
	dd if=kernel of=disk.img bs=512 count=`python kern_size.py kernel` seek=1 conv=notrunc

kernel: cmain.o start.o
	ld -T linker.ld -o $@ $^

run: build bochs.config
	echo c | bochs -qf bochs.config

bootblock.bin: bootblock.s
	nasm -fbin $^ -o $@

%.o: %.asm
	nasm -felf $^ -o $@

cmain.o: cmain.c
	gcc $(CFLAGS) -c -o $@ $^
