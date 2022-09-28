	.file	"fun12.cc"
	.text
	.globl	_Z3funPKc
	.type	_Z3funPKc, @function
_Z3funPKc:
	endbr64
	pushq	%rbx
	movq	%rdi, %rbx
	call	strlen@PLT
	xorl	%edx, %edx
	movq	%rax, %rcx
	cltq
	addq	%rbx, %rax
.L3:
	movb	(%rbx,%rdx), %sil
	movl	%edx, %edi
	testb	%sil, %sil
	je	.L4
	leaq	1(%rdx), %r8
	notq	%rdx
	cmpb	(%rax,%rdx), %sil
	jne	.L4
	movq	%r8, %rdx
	jmp	.L3
.L4:
	cmpl	$4, %ecx
	popq	%rbx
	setle	%al
	cmpl	%ecx, %edi
	setne	%dl
	orl	%edx, %eax
	movzbl	%al, %eax
	ret
	.size	_Z3funPKc, .-_Z3funPKc
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
