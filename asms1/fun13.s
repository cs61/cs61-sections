	.file	"fun13.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	" %d %n"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
	pushq	%r12
	xorl	%r12d, %r12d
	pushq	%rbp
	leaq	.LC0(%rip), %rbp
	pushq	%rbx
	movq	%rdi, %rbx
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
.L2:
	xorl	%eax, %eax
	leaq	4(%rsp), %rcx
	movq	%rsp, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	__isoc99_sscanf@PLT
	decl	%eax
	jne	.L7
	movslq	4(%rsp), %rax
	addl	(%rsp), %r12d
	addq	%rax, %rbx
	jmp	.L2
.L7:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	addq	$16, %rsp
	movl	%r12d, %eax
	popq	%rbx
	popq	%rbp
	popq	%r12
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
