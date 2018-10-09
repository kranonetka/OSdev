build: bootblock.s
	rm -f disk.img
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin bootblock.s -o bootblock.bin
	nasm -fbin sector1.s -o sector1.bin
	dd if=bootblock.bin of=disk.img bs=512 count=1 conv=notrunc
	dd if=sector1.bin of=disk.img bs=512 count=1 seek=1 conv=notrunc
	dd if=sec2 of=disk.img bs=512 count=1 seek=2 conv=notrunc
	dd if=sec3 of=disk.img bs=512 count=1 seek=3 conv=notrunc
	dd if=sec4 of=disk.img bs=512 count=1 seek=4 conv=notrunc
	
clear:
	rm -f bootblock.bin disk.img

run: build disk.img bochs.config
	echo c | bochs -qf bochs.config
