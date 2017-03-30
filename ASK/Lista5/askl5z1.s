puzzle:
    testl %esi, %esi    # n & n ; ZF = (n&n == 0)
    je .L4              # skok do L4 gdy n == 0
    xorl %edx, %edx     # edx = 0
    xorl %eax, %eax     # eax = 0
.L3:
    movl %edi, %ecx     # ecx = x & 0xFFFFFFFF
    andl $1, %ecx       # ecx &= 1
    addl %ecx, %eax     # eax += ecx
    sarq %rdi           # x >>= 1
    incl %edx           # edx++
    cmpl %edx, %esi     # n - edx;
    jne .L3             # skok do L3 gdy n != edx
    ret
.L4:
    movl %esi, %eax     # eax = n
    ret
