ENTRY(kernel64_entry);

SECTIONS
{
  . = 0x100c00;
  .text :
  {
    * (.text.kernel64_entry);
    * (.text.*);
  }
  .data :
  {
    * (.data*);
  }
  .end :
  {
    BYTE(0x0);
    . = ALIGN(512) - 1;
    BYTE(0x0);
  }
}
