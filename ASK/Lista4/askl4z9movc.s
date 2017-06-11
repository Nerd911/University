.section .text
.globl adds
.type adds, @function

adds:
  movq %rdi, %rax
  addq %rsi, %rax
  mov $0x7FFFFFFFFFFFFFFF, %rsi
  sarq $63, %rdi
  xorq %rdi, %rsi
  cmovo %rsi, %rax
  ret
