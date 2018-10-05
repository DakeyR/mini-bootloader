#include "general_handler.h"
#include "io.h"

void devide_zero_hdl()
{
  printf("Exception: Division By Zero\n");
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
      printf("Interrupt #%d, error: %d\n", interrupt, err_code);
	    for (;;)
		    asm volatile ("hlt");
      break;
  }

}
