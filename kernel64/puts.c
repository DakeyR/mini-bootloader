#include "io.h"

void setBaudRate(u16 rate)
{
	char divLatch = DIVLATCH_CONST_ / rate;
	outb(COM1_BASE_ + LCR_OFFSET, inb(COM1_BASE_ + LCR_OFFSET) | 0x80);
	outb(COM1_BASE_ + LATCH_HIGH, divLatch >> 8);
	outb(COM1_BASE_ + LATCH_LOW, divLatch & 0xFF);
	outb(COM1_BASE_ + LCR_OFFSET, inb(COM1_BASE_ + LCR_OFFSET) & 0x7F);
}

size_t strnlen(const char *s, size_t maxlen)
{
    size_t l = 0;
    for (;l < maxlen && s[l]; l++)
        ;
    return l;
}

int puts(const char *s)
{
    setBaudRate(38400);
    int count = 0;

    for (int i = 0; s[i]; i++, count++)
        outb(COM1_BASE_, s[i]);

    return count;
}
