#ifndef GENERIC_HDL_
#define GENERIC_HDL_

#include "types.h"

struct general_registers
{
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
} __attribute__ ((__packed__));
//Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and ED
void generic_c_handler(struct general_registers regs, u32 interrupt, u32 err_code);

void devide_zero_hdl();

#endif
