CC=gcc
LD=ld
CFLAGS = -ffreestanding \
				-Wall \
				-Werror \
				-O0 \
				-m32 \
				-march=i686

LDFLAGS = -static \
					-nostdlib \
					-Tkernel32.ld \
					-melf_i386

KOBJS=kernel32.o

all: kernel32.bin

kernel32: $(KOBJS)
	$(LD) $(LDFLAGS) $< -o $@

kernel32.bin: kernel32
	objcopy -O binary $< $@

clean:
	$(RM) kernel32 kernel32.bin kernel32.o
