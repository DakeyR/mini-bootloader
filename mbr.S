.code16

#define S_FLAG_ 1
#define SYSSEG 0
#define CODE_OR_DATA 1

#define DPL_FLAG_ 6
#define RING0 0
#define RING1 2
#define RING2 4
#define RING3 6

#define PRESENT_FLAG_ 8

#define AVAILABLE_FLAG_ 16
#define L_FLAG_ 32

#define DB_FLAG_ 64

#define G_FLAG_ 128

.section .data

gdt:
    .quad 0x0000000000000000
    .quad 0x00cf9a000000ffff
    .quad 0x00cf93000000ffff

#    .long 0x0000ffff # code
#    .long 0xcfb300
#    .long 0x0000ffff # data
#    .long 0xcf9300
gdt_end:

gdtr:
    .word gdt_end - gdt - 1
    .long gdt

.section .text
.global __start

# edx contains the drive index (should not be touched)
__start:
    call loadk

loadk:
# Read drive parameters
    push %dx
#    mov $0x2401, %ax
#    int $0x15
    mov $0x08, %ah
    mov $0x00, %edi
    mov %di, %es
    int $0x13
    setc %bl
    mov $0x0, %di
    mov %di, %es
    test %ah, %ah
    jne error
    test %bl, %bl
    jne error

    xor %bx, %bx
    mov %bx, %es

    and $0x3f, %cl
    mov %dh, %ch
    pop %dx
    push %dx
    mov %ch, %dh
    #cyl (ch) = lba (1) / (heads(dh) * spt(cl))
    mov %cl, %al
    mul %ch
    mov %al, %ch
    mov $0x1, %ax
    div %ch # 1 / ch
    mov %al, %ch
    #head(dh) = (lba / spt(cl)) % heads (dh)
    mov $0x1, %ax
    div %cl
    movsx %al, %ax
    div %dh
    mov %ah, %dh
    #sector (cl) = (lba (1) % spt (cl)) + 1
    mov $0x1, %ax
    div %cl
    mov %ah, %cl
    add $0x1, %cl

    mov $0xffff, %ax # Physical address = Segment Selector * 16 + Offset (ES:BX)
    mov %ax, %es
    mov $0x10, %bx

    mov $KSIZE, %al
    mov $0x2, %ah

    int $0x13
    setc %bl
    mov $0x0, %dx
    mov %dx, %es
    test %ah, %ah
    jne error
    test %bl, %bl
    jne error

    pop %dx

    mov $0xffff, %ax # Physical address = Segment Selector * 16 + Offset (ES:BX)
    mov $0x8, %cl
    mov %ax, %es
    mov $0xc10, %bx
    mov $KSIZE64, %al
    mov $0x2, %ah

    int $0x13

    setc %bl
    mov $0x0, %dx
    mov %dx, %es
    test %ah, %ah
    jne error
    test %bl, %bl
    jne error

    lgdt (gdtr)

    mov %cr0, %ebx
    or $0x1, %ebx
    mov %ebx, %cr0
    cli

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    mov %ax, %es

    #pushl $0x8
    #pushl $0x100000
    #lretl
    ljmp $0x8, $protected_mode


error:
    hlt

.code32
protected_mode:
    mov $0x100000, %eax
    jmp *%eax
