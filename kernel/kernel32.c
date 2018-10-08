#include "gdt.h"
#include "idt.h"
#include "types.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(*A))

#define PAGE_SIZE (1 << 7)
#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITEABLE (1 << 1)
#define MEGABYTE (1 << 20)

#define GDT_L_FLAG ((u64)1 << 53)
#define GDT_DB_FLAG ((u64)1 << 54)

u64 pml4e[512] __attribute__((aligned(0x1000)));
u64 pdpe[512] __attribute__((aligned(0x1000)));
u64 pde[512] __attribute__((aligned(0x1000)));



u64 gdt[3] = {
    0x0000000000000000,
    0x00af9a000000ffff,
    0x00af93000000ffff
};

void setup_paging()
{
    pml4e[0] = ((unsigned long)pdpe) | PAGE_PRESENT | PAGE_WRITEABLE;
    pdpe[0] = ((unsigned long)pde) | PAGE_PRESENT | PAGE_WRITEABLE;

    u64 page_addr = 0x0;
    for (u64 i = 0; i <= 2; i += 2, page_addr += 2 * MEGABYTE)
        pde[i] = page_addr | PAGE_PRESENT | PAGE_SIZE | PAGE_WRITEABLE;

    //Moving pml level-4 table into cr3
    asm volatile ("mov %0, %%eax\n"
                  "mov %%eax, %%cr3\n"::"r" (pml4e)
                  :"memory");

    //Activating LME with EFER_MSR
    asm volatile ("mov $0xC0000080, %%ecx\n"
                  "rdmsr\n"
                  "or $0x100, %%eax\n"
                  "wrmsr\n":::"memory");

    //Activating PAE with cr4
    asm volatile ("mov %%cr4, %%eax\n"
                  "or $0x20, %%eax\n"
                  "mov %%eax, %%cr4\n":::"memory");

    //Activating Paging (PG=1 in cr0)
    u64 cr0;
    asm volatile ("mov %%cr0, %0":"=r" (cr0));
    asm volatile ("mov %0, %%cr0"::"r" (cr0 | (1 << 31)));


}

int main(void)
{
    setup_paging();
    load_gdt();
    setup_registers();

	asm volatile ("pushl $0x8\n" "pushl $0x100c00\n" "lret\n":::"memory");

    asm volatile ("hlt");

    return 0;
}
