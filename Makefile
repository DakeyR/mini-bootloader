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

disk: mbr.bin kernel64
	cat mbr.bin kernel/kernel32.bin > hello.disk

.PHONY: kernel
mbr.o: kernel
mbr.o: KSIZE=$(shell $$(stat -c%s kernel/kernel32.bin)
mbr.o: mbr.S 
	$(CC) $(CFLAGS) -DKSIZE=50 -c $< -o $@

mbr: mbr.o
	$(LD) $(LDFLAGS) $< -o $@

mbr.bin: mbr
	objcopy -O binary $< $@

kernel:
	$(MAKE) -C kernel

kernel64:
	$(MAKE) -C kernel64

debug:
	gdb -ix gdb_init_real_mode.txt mbr

clean:
	$(RM) mbr.bin mbr mbr.o
	$(MAKE) clean -C kernel
	$(MAKE) clean -C kernel64
