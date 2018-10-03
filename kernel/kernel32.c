int main(void)
{
    /*  
    char star[4] = "|/-\\";
    char *fb = (void *)0xb8000;
    for (unsigned i = 0; ; )
    {
        *fb = star[i++ % 4];
    }

    */
    asm volatile ("hlt");

    return 0;
}
