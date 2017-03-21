.section .text
.globl mul128
.type mul128, @function

mul128: # to poprostu zdesasemblowane mnozenie 128 bitowcow z biblioteki standardowej
  imulq     %rdx, %rsi
  movq     %rdi, %rax
  imulq     %rdi, %rcx
  mulq     %rdx
  addq     %rsi, %rcx
  addq     %rcx, %rdx
  ret
