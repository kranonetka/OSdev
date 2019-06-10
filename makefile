CFLAGS=-m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -masm=intel

build: clean bootblock.bin kernel
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=bootblock.bin of=disk.img bs=512 count=1 conv=notrunc
	dd if=kernel of=disk.img bs=512 count=`python kern_size.py kernel` seek=1 conv=notrunc

clean:
	rm -f bootblock.bin kernel disk.img *.o

kernel: cmain.o common.o video.o panic.o string.o idt.o isr.o interrupt.o time.o keyboard.o task.o switch.o
	ld -T linker.ld -o $@ $^

run: build bochs.config
	echo c | bochs -qf bochs.config

bootblock.bin: bootblock.asm
	nasm -fbin $^ -o $@

%.o: %.asm
	nasm -felf $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^
