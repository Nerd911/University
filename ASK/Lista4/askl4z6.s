.section .text
.globl convert
.type convert, @function

convert:
  movq %rdi, %rax
   ror $0x08, %ax
   ror $0x10, %eax
   ror $0x08, %ax
   ror $0x20, %rax
   ror $0x08, %ax
   ror $0x10, %eax
   ror $0x08, %ax
  ret
