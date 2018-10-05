#include "idt.h"
#include "io.h"

int main(void)
{
    char star[4] = "|/-\\";
    char *fb = (void *)0xb8000;

    printf("Hello World\n");

    for (unsigned i = 0; ; )
    {
        *fb = star[i++ % 4];
    }

    asm volatile ("hlt");

    return 0;
}
