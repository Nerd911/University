store_elem:
    leaq (%rsi,%rsi,2),%rax ; r = 3j
    leaq (%rsi,%rax,4),%rax ; r = j + 4r // r = 13j
    movq %rdi,%rsi          ; j = i;
    salq $6,%rsi            ; j <<= 6; // j = i << 6
    addq %rsi,%rdi          ; i += j // i = i + (i << 6)
    addq %rax,%rdi          ; i += r // i = i + (i << 6) + 13j
    addq %rdi,%rdx          ; k += i // k = k + i + (i << 6) + 13j
    movq A(,%rdx,8),%rax    ; r = *(8k + A)
    movq %rax,(%rcx)        ; *dest = r;
    movq $3640,%rax         ; r = 3640
    ret
