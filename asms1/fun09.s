	.file	"fun09.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
	pushq	%rcx
	leaq	.LC0(%rip), %rsi
	call	fopen@PLT
	movq	%rax, %rdi
	orl	$-1, %eax
	testq	%rdi, %rdi
	je	.L1
	call	fclose@PLT
	xorl	%eax, %eax
.L1:
	popq	%rdx
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
