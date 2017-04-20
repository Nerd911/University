.file   "fibonacci.s"
arg = %rdi

.global fibonacci
.type   fibonacci, @function
.text
fibonacci:
        cmpq $1, %rdi
				jnbe L1
				movq $1, %rax
				ret
L1:
				decq %rdi
				pushq %rdi
				call fibonacci
				popq %rdi
				pushq %rax
				decq %rdi
				call fibonacci
				popq %rdx
				addq %rdx, %rax
				ret
.size   fibonacci, .-fibonacci
