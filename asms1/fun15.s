	.file	"fun15.cc"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
.L2:
	movb	(%rdi), %al
	testb	%al, %al
	je	.L7
	cmpb	1(%rdi), %al
	jb	.L5
	incq	%rdi
	jmp	.L2
.L7:
	xorl	%eax, %eax
	ret
.L5:
	orl	$-1, %eax
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
