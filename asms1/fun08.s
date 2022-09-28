	.file	"fun08.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d %d %d"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
	subq	$40, %rsp
	leaq	.LC0(%rip), %rsi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	20(%rsp), %r8
	leaq	16(%rsp), %rcx
	leaq	12(%rsp), %rdx
	call	__isoc99_sscanf@PLT
	movl	%eax, %r8d
	orl	$-1, %eax
	cmpl	$3, %r8d
	jne	.L1
	movl	16(%rsp), %eax
	addl	12(%rsp), %eax
	subl	20(%rsp), %eax
.L1:
	movq	24(%rsp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	addq	$40, %rsp
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
