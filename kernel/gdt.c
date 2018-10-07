#include "gdt.h"

void load_gdt()
{
	struct gdt_r gdtr;
	gdtr.base = (u32) gdt;
	gdtr.limit = sizeof(gdt) - 1;

	//Loading the GDTR
	asm volatile ("lgdt %0\n"::"m" (gdtr)
		      :"memory");

}

void setup_registers()
{

    //Setting Segment Selectors Registers
    asm volatile ("mov $0x10, %%ax\n"
              "mov %%ax, %%ds\n"
              "mov %%ax, %%es\n"
              "mov %%ax, %%fs\n"
              "mov %%ax, %%gs\n" "mov %%ax, %%ss\n":::"memory");

	asm volatile ("pushl $0x8\n" "pushl $0x100c00\n" "lret\n":::"memory");
}
