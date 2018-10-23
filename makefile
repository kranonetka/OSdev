build: clear bootblock.s
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin bootblock.s -o bootblock.bin
	nasm -fbin procmode.s -o procmode.bin
	dd if=bootblock.bin of=disk.img bs=512 count=1 conv=notrunc
	dd if=procmode.bin of=disk.img bs=512 count=1 seek=1 conv=notrunc
	
clear:
	rm -f bootblock.bin procmode.bin disk.img

run: build disk.img bochs.config
	echo c | bochs -qf bochs.config
