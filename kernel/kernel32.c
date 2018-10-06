#include "idt.h"
#include "types.h"
#include "io.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(*A))

#define PAGE_SIZE (1 << 7)
#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITEABLE (1 << 1)
#define MEGABYTE (1 << 20)

u64 pml4e[1] __attribute__((aligned(0x1000)));
u64 pdpe[1] __attribute__((aligned(0x1000)));
u64 pde[512] __attribute__((aligned(0x1000)));


void setup_paging()
{
    pml4e[0] = ((unsigned long)pdpe) | PAGE_PRESENT | PAGE_WRITEABLE;
    pdpe[0] = ((unsigned long)pde) | PAGE_PRESENT | PAGE_WRITEABLE;

    u64 page_addr = 0x0;
    for (u64 i = 0; i < ARRAY_SIZE(pde); i++, page_addr += 2 * MEGABYTE)
        pde[i] = page_addr | PAGE_PRESENT | PAGE_SIZE | PAGE_WRITEABLE;
}


int main(void)
{
    char star[4] = "|/-\\";
    char *fb = (void *)0xb8000;

    setup_paging();

    printf("Hello World\n");

    for (unsigned i = 0; ; )
    {
        *fb = star[i++ % 4];
    }

    asm volatile ("hlt");

    return 0;
}
