#include "io.h"

void win(int (*printf_ptr)(const char *fmt, ...));

int kernel64_entry(void)
{
    win(printf);

    for (;;)
        asm volatile ("hlt");

    return 0;
}
