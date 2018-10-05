#include "io.h"
#include "idt.h"
#include "handlers.h"

struct idt_gate idt[256];

void set_idt_entry(u32 offset, u16 selector, u8 flags, int index)
{
	idt[index].offset_lsb = offset & 0xFFFF;
	idt[index].offset_msb = (offset >> 16) & 0xFFFF;

	idt[index].selector = selector;

	idt[index].type = flags & IDT_TYPE_;
	idt[index].dpl = (flags & IDT_RING3_) >> 5;
	idt[index].p = (flags & IDT_PRESENT_) >> 7;

}

void set_idt()
{
	set_idt_entry((u32) int_hdl0, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      0);
	set_idt_entry((u32) int_hdl1, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      1);
	set_idt_entry((u32) int_hdl2, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      2);
	set_idt_entry((u32) int_hdl3, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      3);
	set_idt_entry((u32) int_hdl4, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      4);
	set_idt_entry((u32) int_hdl5, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      5);
	set_idt_entry((u32) int_hdl6, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      6);
	set_idt_entry((u32) int_hdl7, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      7);
	set_idt_entry((u32) err_int_hdl8, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 8);
	set_idt_entry((u32) int_hdl9, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      9);
	set_idt_entry((u32) err_int_hdl10, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 10);
	set_idt_entry((u32) err_int_hdl11, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 11);
	set_idt_entry((u32) err_int_hdl12, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 12);
	set_idt_entry((u32) err_int_hdl13, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 13);
	set_idt_entry((u32) err_int_hdl14, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 14);
	set_idt_entry((u32) int_hdl15, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      15);
	set_idt_entry((u32) int_hdl16, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      16);
	set_idt_entry((u32) err_int_hdl17, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 17);
	set_idt_entry((u32) int_hdl18, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      18);
	set_idt_entry((u32) int_hdl19, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      19);
	set_idt_entry((u32) int_hdl20, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      20);
	set_idt_entry((u32) int_hdl21, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      21);
	set_idt_entry((u32) int_hdl22, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      22);
	set_idt_entry((u32) int_hdl23, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      23);
	set_idt_entry((u32) int_hdl24, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      24);
	set_idt_entry((u32) int_hdl25, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      25);
	set_idt_entry((u32) int_hdl26, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      26);
	set_idt_entry((u32) int_hdl27, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      27);
	set_idt_entry((u32) int_hdl28, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      28);
	set_idt_entry((u32) int_hdl29, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      29);
	set_idt_entry((u32) err_int_hdl30, 8,
		      IDT_INT_ | IDT_RING0_ | IDT_PRESENT_, 30);
	set_idt_entry((u32) int_hdl31, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      31);
	set_idt_entry((u32) int_hdl32, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      32);
	set_idt_entry((u32) int_hdl33, 8, IDT_INT_ | IDT_RING0_ | IDT_PRESENT_,
		      33);
	set_idt_entry((u32) int_hdl128, 8, IDT_INT_ | IDT_RING3_ | IDT_PRESENT_,
		      128);
}


void load_idt()
{
	struct idt_r idtr;
	idtr.base = (u32) idt;
	idtr.limit = sizeof(idt) - 1;

	//Loading the iDTR
	asm volatile ("lidt %0\n" "sti"::"m" (idtr)
		      :"memory");

  outb(0x21, 0xFC);

}

void set_pic()
{
    //ICW1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    //ICW2
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    //ICW3
    outb(0x21, 0x04);//0x03
    outb(0xA1, 0x02);

    //ICW4
    outb(0x21, 0x01);//0x02
    outb(0xA1, 0x01);//0x02

    //OCW1
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);



    int divider = 1193182/100;

    //timer setup
    outb(0x43, 0x34);
    outb(0x40, divider & 0xFF);
    outb(0x40, (divider >> 8) & 0xFF);
}
void idt_pretty_printer()
{
  for (int i = 0; i < 33; i++)
  {
    printf ("----- Segment %d -----\n", i);
    printf ("offset lsb: %d, selector: %d, type: %d, reserved: %d, dpl: %d\n",
            idt[i].offset_lsb, idt[i].selector, idt[i].type, idt[i].reserved, idt[i].dpl);
    printf ("p: %d, offset msb: %d, zeros: %d\n",
            idt[i].p, idt[i].offset_msb, idt[i].zeros);
    printf ("----------------------\n");
  }
  int i = 128;
  printf ("----- Segment %d -----\n", i);
    printf ("offset lsb: %d, selector: %d, type: %d, reserved: %d, dpl: %d\n",
            idt[i].offset_lsb, idt[i].selector, idt[i].type, idt[i].reserved, idt[i].dpl);
    printf ("p: %d, offset msb: %d, zeros: %d\n",
            idt[i].p, idt[i].offset_msb, idt[i].zeros);
    printf ("----------------------\n");

}
