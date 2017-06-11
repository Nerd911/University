add128:
        movq    %rdi, %r9       # a, a
        movq    %rsi, %r10      # a, a
        addq    %rdx, %r9       # b, a
        adcq    %rcx, %r10      # b, a
        movq    %r9, %rax       # a, tmp93
        movq    %r10, %rdx      # a,
        ret
