CC=gcc
LD=ld
CFLAGS = -ffreestanding \
				-Wall \
				-Werror \
				-O0

LDFLAGS = -static \
					-nostdlib \
					-Tmbr.ld

all: disk

disk: mbr.bin
	cat mbr.bin kernel/kernel32.bin kernel64/kernel64.bin > hello.disk

.PHONY: kernel kernel64
mbr.o: kernel kernel64
mbr.o: KSIZE=$(shell echo $$(($$(stat -c%s kernel/kernel32.bin) / 512)))
mbr.o: KSIZE64 =$(shell echo $$(($$(stat -c%s kernel64/kernel64.bin) / 512)))
mbr.o: mbr.S 
	$(CC) $(CFLAGS) -DKSIZE=${KSIZE} -DKSIZE64=${KSIZE64} -c $< -o $@

mbr: mbr.o
	$(LD) $(LDFLAGS) $< -o $@

mbr.bin: mbr
	objcopy -O binary $< $@

kernel:
	$(MAKE) -C kernel

kernel64:
	EXTRA_OBJECT=../${EXTRA_OBJECT} $(MAKE) -C kernel64

debug:
	gdb -ix gdb_init_real_mode.txt mbr

clean:
	$(RM) mbr.bin mbr mbr.o hello.disk
	$(MAKE) clean -C kernel
	$(MAKE) clean -C kernel64
