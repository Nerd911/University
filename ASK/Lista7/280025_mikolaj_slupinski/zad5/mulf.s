.file   "mulf.s"
arg0 = %edi
arg1 = %esi
result = %eax
temp0 = %ebx
temp1 = %edx
exp = %ecx


EXPMASK = 0x7F800000
SGNMASK = 0x80000000
MTSMASK = 0x007FFFFF
EXPPOS = 23

.global mulf
.type   mulf, @function
.text
mulf:
        mov arg0, temp0
        mov arg1, temp1
        and $EXPMASK, temp0
        and $EXPMASK, temp1
        shr $EXPPOS, temp0
        shr $EXPPOS, temp1
        sub $127, temp0
        lea (temp0, temp1, 1), exp
        mov arg0, temp0
        mov arg1, result
        and $MTSMASK, temp0
        and $MTSMASK, result
        or  $0x00800000, temp0
        or  $0x00800000, result
        xor %edx, %edx
        mul temp0
        mov $0x00008000, temp0
        and temp1, temp0
        test temp0, temp0
        jnz NORMALIZE
L1:
        and $0x00003FFF, temp1
        shrd $23, temp1, result
        shl $EXPPOS, exp
        and $EXPMASK, exp
        or exp, result
        xor arg0, arg1
        and $SGNMASK, arg1
        or arg1, result
        ret
NORMALIZE:
        inc exp
        shrd $1, %edx, %eax
        shr $1, %edx
        jmp L1
.size   mulf, .-mulf
