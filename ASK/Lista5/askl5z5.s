test:
    movl 0x120(%rsi),%ecx       ; ecx  = *(bp + 288)
    addl (%rsi),%ecx            ; ecx += *bp
    leaq (%rdi,%rdi,4),%rax     ; rax  = 5i
    leaq (%rsi,%rax,8),%rax     ; rax  = bp + 40i
    movq 0x8(%rax),%rdx         ; rdx  = *(bp + 8 + 40i)
    movslq %ecx,%rcx            ; rcx  = *(bp + 288) + *bp
    movq %rcx,0x10(%rax,%rdx,8) ; *(rax + 8 rdx + 16) = rcx
    retq
