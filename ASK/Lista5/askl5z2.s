# long puzzle2(char *s, char *d)
# input: %rdi, %rsi
# output: %rax

puzzle2:
movq  %rdi, %rax # %rax = %rdi
.L3:
leaq  1(%rax), %r8 # %r8 = %rax + 1
movb  -1(%r8), %r9b #
movq  %rsi, %rdx
.L2:
incq  %rdx
movb  -1(%rdx), %cl
testb %cl, %cl
je    .L7
cmpb  %cl, %r9b
jne   .L2
movq  %r8, %rax
jmp   .L3
.L7:
subq  %rdi, %rax
ret
