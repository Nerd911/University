.section .text
.globl adds
.type adds, @function

adds:
  movq %rdi, %rax
  addq %rsi, %rax
  movq %rdi, %rbx
  sarq $63, %rbx
  movq %rsi, %rdx
  sarq $63, %rdx
  andq %rdx, %rbx
  movq %rax, %rdx
  notq %rdx
  sarq $63, %rdx
  andq %rdx, %rbx
  movq $0x8000000000000000, %rdx
  andq %rbx, %rdx
  notq %rbx
  andq %rbx, %rax
  orq %rdx, %rax
  movq %rdi, %rbx
  notq %rbx
  sarq $63, %rbx
  movq %rsi, %rdx
  notq %rdx
  sarq $63, %rdx
  andq %rdx, %rbx
  movq %rax, %rdx
  sarq $63, %rdx
  andq %rdx, %rbx
  movq $0x7FFFFFFFFFFFFFFF, %rdx
  andq %rbx, %rdx
  notq %rbx
  andq %rbx, %rax
  orq %rdx, %rax
  ret
