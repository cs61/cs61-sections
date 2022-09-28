	.file	"fun07.cc"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
	pushq	%rcx
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movl	$2, %edx
	movl	%eax, %esi
.L2:
	cmpl	%esi, %edx
	jge	.L5
	movl	%edx, %ecx
	imull	%edx, %ecx
.L6:
	cmpl	%esi, %ecx
	jge	.L10
	addl	%edx, %ecx
	jmp	.L6
.L10:
	je	.L7
	incl	%edx
	jmp	.L2
.L5:
	decl	%eax
	setle	%al
	movzbl	%al, %eax
	jmp	.L1
.L7:
	movl	$1, %eax
.L1:
	popq	%rdx
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
