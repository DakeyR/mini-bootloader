ENTRY(main);

SECTIONS
{
  . = 0x100000;
  .text :
  {
    * (.text.main);
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
