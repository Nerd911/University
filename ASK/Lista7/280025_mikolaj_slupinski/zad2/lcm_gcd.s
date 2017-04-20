.file   "lcm_gcd.s"
temp = %rcx
arg0 = %rdi
arg1 = %rsi
remainder = %rdx
quotient = %rax
result_gcd = %rdx
result_lcm = %rax
gcd = %r9
lcm = %r10

.global lcm_gcd
.type   lcm_gcd, @function
.text
lcm_gcd:
        movq arg0, %rax
        mulq arg1
        movq %rax, lcm
        cmp arg0, arg1
        ja EXCHANGE
GCD:
        movq arg0, %rax
        test arg1, arg1
        jz ENDLOOP
BEGINLOOP:
        xorq %rdx, %rdx
        divq arg1
        movq arg1, %rax
        movq %rdx, arg1
        test arg1, arg1
        jnz BEGINLOOP
ENDLOOP:
        movq %rax, arg0
        movq lcm, %rax
        divq arg0
        movq arg0, %rdx

        ret

EXCHANGE:
        xchg arg0, arg1
        jmp GCD
.size   lcm_gcd, .-lcm_gcd
