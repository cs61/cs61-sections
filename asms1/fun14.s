	.file	"fun14.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	" %d %n"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
	pushq	%r13
	leaq	.LC0(%rip), %r13
	pushq	%r12
	xorl	%r12d, %r12d
	pushq	%rbp
	xorl	%ebp, %ebp
	pushq	%rbx
	movq	%rdi, %rbx
	subq	$24, %rsp
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
.L2:
	xorl	%eax, %eax
	leaq	4(%rsp), %rcx
	movq	%rsp, %rdx
	movq	%r13, %rsi
	movq	%rbx, %rdi
	call	__isoc99_sscanf@PLT
	decl	%eax
	jne	.L8
	movl	(%rsp), %eax
	addl	%eax, %r12d
	testl	%eax, %eax
	setne	%al
	orl	%eax, %ebp
	movslq	4(%rsp), %rax
	addq	%rax, %rbx
	jmp	.L2
.L8:
	testb	%bpl, %bpl
	movl	$-1, %eax
	cmove	%eax, %r12d
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	addq	$24, %rsp
	movl	%r12d, %eax
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
