.file   "zad7.s"
argc = %rdi
argv = %rsi
index = %r15
BUFF_S = 200
PTR_S = 8
array = %r8
.global _start
.type   _start, @function
				.text
_start:
				mov $0, %rax
				mov $0, %rdi
				mov $buffer, %rsi
				mov $BUFF_S, %rdx
				syscall

				mov $0, index
				mov $buffer, array

BEGINLOOP:
				cmpb $0, (array, index, 1)
				je ENDLOOP
				cmp $BUFF_S, index
				je ERROR
				cmpb $0x61, (array, index, 1)
				jae CHECK_SMALL
				cmpb $0x41, (array, index, 1)
				jae CHECK_BIG
INCINDEX:
				inc index
				jmp BEGINLOOP
ENDLOOP:
				mov $1, %rax
				mov $1, %rdi
				mov $buffer, %rsi
				mov $BUFF_S, %rdx
				syscall

				mov $60, %rax
				mov $0, %rdi
				syscall
CHECK_BIG:
				cmpb $0x5a, (array, index, 1)
				ja INCINDEX
				xorb $0x20, (array, index, 1)
				jmp INCINDEX
CHECK_SMALL:
				cmpb $0x7a, (array, index, 1)
				ja INCINDEX
				xorb $0x20, (array, index, 1)
				jmp INCINDEX
ERROR:
        mov $60, %rax
				mov $-1, %rdi
				syscall
.size   _start, .-_start
				.bss
.comm	buffer,200,32
