#ifndef IO_H_
#define IO_H_

#include "types.h"

#define COM1_BASE_ 0x3F8
#define COM2_BASE_ 0x2F8
#define COM3_BASE_ 0x3E8
#define COM4_BASE_ 0x2F8

#define BAUDRATE_ 38400
#define DIVLATCH_CONST_ 115200
#define LCR_OFFSET 0x03
#define LATCH_LOW 0x0
#define LATCH_HIGH 0x1

int printf(const char *fmt, ...);

static inline void outb(u16 port, u8 val)
{
	asm volatile ("outb %0, %1\n\t":	/* No output */
		      :"a" (val), "d"(port));
}

static inline u8 inb(u16 port)
{
	u8 res;
	asm volatile ("inb %1, %0\n\t":"=&a" (res)
		      :"d"(port));

	return res;
}

size_t strnlen(const char *s, size_t maxlen);
int puts(const char *s);

void setBaudRate(u16 rate);

#endif				/* !IO_H_ */
