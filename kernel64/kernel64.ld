ENTRY(kernel64_entry);

SECTIONS
{
  . = 0x200000;
  .text :
  {
    * (.text*);
  }
  .data :
  {
    * (.data*);
  }
}
