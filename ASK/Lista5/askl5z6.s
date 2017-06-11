proc:
    movq 8(%rdi),%rax   ; rax  = *(arg + 8) // arg->next
    movq (%rax),%rdx    ; rdx  = *rax // arg->next->p
    movq (%rdx),%rdx    ; rdx  = *rdx // *(arg->next->p)
    subq 8(%rax),%rdx   ; rdx -= *(rax + 8) // arg->next->y
    movq %rdx,(%rdi)    ; *arg = rdx
    ret
