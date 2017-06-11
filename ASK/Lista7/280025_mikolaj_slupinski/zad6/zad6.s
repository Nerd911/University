.file   "zad6.s"
argc = %rdi
argv = %rsi
size = %r9
index = %r10
temp = %r11
array = %r8
PTR_S = 8
min = %r12
max = %r13
.global main
.type   main, @function
        .text
main:
        cmp     $1, argc
        jbe     ERROR
        dec     argc
        add     $PTR_S, argv
        mov     argc, size
        xor     index, index
        mov     $PTR_S, temp
        imul    size, temp
        sub     temp, %rsp
        mov     %rsp, array
        mov     $1, temp
        and     size, temp
        imul    $PTR_S, temp
        sub     temp, %rsp

ADDELEMS:
        push    argc
        push    argv
        push    size
        push    index
        push    array

        mov     (argv), argc
        call    atol

        pop     array
        pop     index
        pop     size
        pop     argv
        pop     argc

        mov     %rax, (array, index, PTR_S)
        inc     index

        add     $PTR_S, argv                # point to next argument
        dec     argc                    # count down
        jnz     ADDELEMS                    # if not done counting keep going

        mov     (array), min
        mov     (array), max

        mov     $1, index

BEGINLOOP:
        cmp     index, size
        jle     ENDLOOP
        mov     (array, index, PTR_S), temp
        cmp     min, temp
        jl      SET_MIN
        cmp     max, temp
        jg      SET_MAX
        inc     index
        jmp     BEGINLOOP
SET_MIN:
        mov     temp, min
        inc     index
        jmp     BEGINLOOP
SET_MAX:
        mov     temp, max
        inc     index
        jmp     BEGINLOOP
ENDLOOP:
        mov     $1, temp
        and     size, temp
        add     size, temp
        lea     (%rsp, temp, PTR_S), %rsp
        mov     $format, %rdi
        mov     min, %rsi
        mov     max, %rdx
        xor     %rax, %rax
        call    printf
        xor     %rax, %rax
        ret

ERROR:
        mov $-1, %rax
        ret
.size   main, .-main
format:
        .asciz  "Min: %d\tMax: %d\n"
