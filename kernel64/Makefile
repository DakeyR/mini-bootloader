CC=gcc
LD=ld
CFLAGS = -ffreestanding \
				-fno-stack-protector \
				-Wall \
				-Werror \
				-O0 \
				-iquote ../kernel/ \
				-g

LDFLAGS = -static \
					-nostdlib \
					-Tkernel64.ld

ELF=kernel64

KOBJS=kernel64.o \
			printf.o \
			puts.o


all: ${ELF}.bin

${ELF}: $(KOBJS)
	$(LD) $(LDFLAGS) $^ -o $@

${ELF}.bin: ${ELF}
	objcopy -O binary $< $@

clean:
	$(RM) ${ELF} ${ELF}.bin ${KOBJS}
