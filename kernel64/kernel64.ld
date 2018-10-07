ENTRY(kernel64_entry);

SECTIONS
{
  . = 0x200000;
  .text :
  {
    * (.text.kernel64_entry);
    * (.text.*);
  }
  .data :
  {
    * (.data*);
  }
}
