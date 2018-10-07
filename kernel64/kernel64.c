#include "io.h"

int kernel64_entry(void)
{
    printf("Hello World\n");

    for (;;)
        asm volatile ("hlt");

    return 0;
}
