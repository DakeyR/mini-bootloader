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
  . = ALIGN(512);
}
