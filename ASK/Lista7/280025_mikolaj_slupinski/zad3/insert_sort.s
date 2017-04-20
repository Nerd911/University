.file   "insert_sort.s"
arg0 = %rdi
arg1 = %rsi
pos0 = %r8
pos1 = %rdx
temp = %rbx
val0 = %r8
val1 = %r9
key = %r10
PTR_S = 8

.global insert_sort
.type   insert_sort, @function
.text
insert_sort:
        leaq 8(arg0), pos0
BEGINLOOP1:
        cmpq pos0, arg1
        jb ENDLOOP1
        movq (pos0), key
        leaq -8(pos0), pos1
BEGINLOOP2:
        cmpq pos1, arg0
        ja ENDLOOP2
        cmpq (pos1), key
        jge ENDLOOP2
        movq (pos1), val1
        movq val1, 8(pos1)
        subq $8, pos1
        jmp BEGINLOOP2
ENDLOOP2:
        movq key, 8(pos1)
        addq $8, pos0
        jmp BEGINLOOP1
ENDLOOP1:
        xorq %rax, %rax
        ret
.size   insert_sort, .-insert_sort
