.file   "clz.s"
MASK32 = 0xFFFFFFFF00000000
arg0 = %rdi
temp = %rbx
mask = %rdx
result = %rax
result8 = %al
base = %cl

        .global clz
        .type   clz, @function
        .text
clz:
        xorq result, result
        test arg0, arg0
        jz ZERO
        movq $MASK32, mask
        mov $32, base
LOOP_START:
        cmp $0,base
        je ENDLOOP
        movq arg0, temp
        andq mask, temp
        cmp $0, temp
        jne NOTEQUAL
        addb base, result8
        shr $1, base
        shr base, mask
        jmp LOOP_START
ENDLOOP:
        ret
NOTEQUAL:
        shr base, arg0
        shr $1, base
        sar base, mask
        jmp LOOP_START
ZERO:
        movq $64, result
        ret
.size   clz, .-clz
