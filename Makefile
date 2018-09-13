CC=gcc
LD=ld
CFLAGS = -ffreestanding \
				-Wall \
				-Werror \
				-O0

LDFLAGS = -static \
					-nostdlib \
					-Tmbr.ld

all: mbr.bin

mbr.o: mbr.S
	$(CC) $(CFLAGS) -DKSIZE=0 -c $< -o $@

mbr: mbr.o
	$(LD) $(LDFLAGS) $< -o $@

mbr.bin: mbr
	objcopy -O binary $< $@

debug:
	gdb -ix gdb_init_real_mode.txt mbr

clean:
	$(RM) mbr.bin mbr mbr.o
