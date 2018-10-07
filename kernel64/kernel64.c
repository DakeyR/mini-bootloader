#include "io.h"

int kernel64_entry(void)
{
    for (;;)
        asm volatile ("hlt");

    printf("Hello World\n");

    return 0;
}
