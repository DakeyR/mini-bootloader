.section .text

.macro handler number
.global int_hdl\number
.type int_hdl\number\(), @function
int_hdl\number\():
    pushl $0
    pushl $\number
    jmp isr
.endm

.macro err_handler number
.global err_int_hdl\number
.type err_int_hdl\number\(), @function
err_int_hdl\number\():
    pushl $\number
    jmp isr
.endm

isr:
    pushal
    #pushl %ds
    #pushl %es
    #pushl %fs
    #pushl %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call generic_c_handler

    #popl %gs
    #popl %fs
    #popl %es
    #popl %ds

    popal

    add $8, %esp
    iret


handler 0
handler 1
handler 2
handler 3
handler 4
handler 5
handler 6
handler 7
err_handler 8
handler 9
err_handler 10
err_handler 11
err_handler 12
err_handler 13
err_handler 14
handler 15
handler 16
err_handler 17
handler 18
handler 19
handler 20
handler 21
handler 22
handler 23
handler 24
handler 25
handler 26
handler 27
handler 28
handler 29
err_handler 30
handler 31
handler 32
handler 33
handler 128
