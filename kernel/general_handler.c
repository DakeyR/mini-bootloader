#include "general_handler.h"

void devide_zero_hdl()
{
	for (;;)
		asm volatile ("hlt");
}

//Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and ED
void generic_c_handler(struct general_registers regs, u32 interrupt, u32 err_code)
{
  switch (interrupt)
  {
    case 0:
        devide_zero_hdl();
        break;
    default:
	    for (;;)
		    asm volatile ("hlt");
      break;
  }

}
