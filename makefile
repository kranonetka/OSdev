build: bootblock.s
	rm -f disk.img
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin bootblock.s -o bootblock.bin
	dd if=bootblock.bin of=disk.img bs=1 count=512 conv=notrunc

clear:
	rm -f bootblock.bin
	rm -f disk.img

run: build disk.img bochs.config
	bochs -qf bochs.config
