.section .text
.globl add128
.type add128, @function

add128:
  movq %rdi, %rax
  movq %rsi, %rbx
  addq %rdx, %rax
  addq %rcx, %rbx
  # trzeba jeszcze dorobic reszte, odejmujemy od dolnych bitów z sumy dolne bity z jednej z liczbm, shuftujemy w prawo logicznie o 63, dodajemy do gornych bitow sumy, cieszymy sie,
  movq %rbx, %rdx
  subq %rsi, %rbx
  shrq $63, %rbx
  addq %rbx, %rax
  ret
