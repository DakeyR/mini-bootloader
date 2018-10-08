CC=gcc
LD=ld
CFLAGS = -ffreestanding \
				-fno-stack-protector \
				-ffunction-sections \
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
	$(LD) $(LDFLAGS) $^ ${EXTRA_OBJECT} -o $@

${ELF}.bin: ${ELF}
	objcopy -O binary $< $@

clean:
	$(RM) ${ELF} ${ELF}.bin ${KOBJS}
