#ifndef GDT_H_
#define GDT_H_

#include "types.h"
extern u64 gdt[3];

void setup_registers();
void load_gdt();
void switch_kerneland(u32 addr);

struct gdt_r {
	u16 limit;
	u64 base;
} __attribute__ ((__packed__));
#endif
