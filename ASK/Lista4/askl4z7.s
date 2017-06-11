.section .text
.globl add128
.type add128, @function

add128:
  movq %rdi, %rax
  movq %rsi, %rbx
  addq %rdx, %rax
  addq %rcx, %rbx
  movq %rbx, %rdx
  subq %rsi, %rbx
  shrq $63, %rbx
  addq %rbx, %rax
  ret
