ENTRY(__start);

SECTIONS
{
  . = 0x7C00;
  .text :
  {
    * (.text*);
  }
  .data :
  {
    * (.data*);
  }

  . = 0x7DFE;
  .sig :
  {
    SHORT(0xaa55);
  }
}
