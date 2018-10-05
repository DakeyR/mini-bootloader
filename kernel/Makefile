CC=gcc
LD=ld
CFLAGS = -ffreestanding \
				-fno-stack-protector \
				-Wall \
				-Werror \
				-O0 \
				-m32 \
				-march=i686 \
				-g

ASFLAGS = -m32

LDFLAGS = -static \
					-nostdlib \
					-Tkernel32.ld \
					-melf_i386

KOBJS=kernel32.o \
			printf.o \
			puts.o \
			idt.o \
			handlers.o \
			general_handler.o


all: kernel32.bin

kernel32: $(KOBJS)
	$(LD) $(LDFLAGS) $^ -o $@

kernel32.bin: kernel32
	objcopy -O binary $< $@

clean:
	$(RM) kernel32 kernel32.bin ${KOBJS}
