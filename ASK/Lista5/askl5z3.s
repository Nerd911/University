
set_val:
    movslq 8(%rsi), %rax    // r = *(q + 8)
    addq 32(%rsi), %rax     // r += *(q + 32)
    movq %rax, 184(%rdi)    // *(p + 184) = r
    ret
