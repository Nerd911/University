.file "approx_sqrt.s"
arg0 = %xmm0
arg1 = %xmm1
result = %xmm0
temp1 = %xmm2
a = %xmm3
temp2 = %xmm4

.global approx_sqrt

.text
approx_sqrt:
        movq arg0, a
LOOPBEGIN:
        movq a, temp1
        movq result, temp2
        divsd result, temp1
        addsd temp1, result
        mulsd half, result
        subsd result, temp2
        comisd zero, temp2
        jbe NEGATIVE
CHECK:
        comisd temp2, arg1
        jbe LOOPBEGIN
        ret
NEGATIVE:
        mulsd minusone, temp2
        jmp CHECK
.size   approx_sqrt, .-approx_sqrt
.section  .rodata
        half: .double 0.5
        zero: .double 0.0
        minusone: .double -1.0
