eval:
movq  %rdi, %rax
movq  16(%rsp), %rcx
movq  24(%rsp), %rdx
movq  (%rdx), %rsi
movq  %rcx, %rdx
imulq %rsi, %rdx
movq  %rdx, (%rdi)
movq  8(%rsp), %rdx
movq  %rdx, %rdi
subq  %rsi, %rdi
movq  %rdi, 8(%rax)
subq  %rcx, %rdx
movq  %rdx, 16(%rax)
ret
wrap:
subq  $72, %rsp
movq  %rdx, (%rsp)
movq  %rsp, %rdx
leaq  8(%rsp), %rax
pushq %rdx
pushq %rsi
pushq %rdi
movq  %rax, %rdi
call  eval
movq  40(%rsp), %rax
addq  32(%rsp), %rax
imulq 48(%rsp), %rax
addq  $96, %rsp
ret
