.code16

.section .data

gdt:
    .long 0x00000000
    .long 0xAAAAAAAA
    .long 0xBBBBBBBB

.section .text
.global __start

# edx contains the drive index (should not be touched)
__start:
    call loadk

loadk:
# Read drive parameters
    push %dx
    mov $0x08, %ah
    mov $0x00, %edi
    mov %di, %es
    int $0x13
    setc %bl
    test %ah, %ah
    jne error
    test %bl, %bl
    jne error

    xor %bx, %bx
    mov %bx, %es

    and $0x3f, %cl
    mov %dh, %ch
    pop %dx
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

    mov KSIZE, %al
    mov $0x2, %ah

    int $0x13
    setc %bl
    test %ah, %ah
    jne error
    test %bl, %bl
    jne error

error:
    hlt
