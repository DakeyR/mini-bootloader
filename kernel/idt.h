#ifndef KIDT_H_
#define KIDT_H_

#include "types.h"

#define IDT_TYPE_ 31
#define IDT_TASK_ 0xD		// 0b00101
#define IDT_INT_ 0xE		// 0b01110
#define IDT_TRAP_ 0xF		// 0b01111

#define IDT_RING0_ 0
#define IDT_RING1_ 32
#define IDT_RING2_ 64
#define IDT_RING3_ 96

#define IDT_PRESENT_ 128

struct idt_gate {
	u64 offset_lsb:16;
	u64 selector:16;
	u64 reserved:5;
	u64 zeros:3;
	u64 type:5;
	u64 dpl:2;
	u64 p:1;
	u64 offset_msb:16;
} __attribute__ ((__packed__));

struct idt_r {
	u16 limit;
	u32 base;

} __attribute__ ((__packed__));

extern struct idt_gate idt[256];

void set_idt_entry(u32 offset, u16 selector, u8 flags, int index);
void set_idt();
void load_idt();
void set_pic();

void idt_pretty_printer();

#endif
