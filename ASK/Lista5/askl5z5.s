test:
movl   0x120(%rsi),%ecx
addl   (%rsi),%ecx
leaq   (%rdi,%rdi,4),%rax
leaq   (%rsi,%rax,8),%rax
movq   0x8(%rax),%rdx
movslq %ecx,%rcx
movq   %rcx,0x10(%rax,%rdx,8)
retq
