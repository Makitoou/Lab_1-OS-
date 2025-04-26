	.file	"fibonacci.cpp"
	.text
	.globl	_Z9fibonaccii
	.def	_Z9fibonaccii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9fibonaccii
_Z9fibonaccii:
.LFB0:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$0, 16(%rbp)
	jne	.L2
	movl	$0, %eax
	jmp	.L3
.L2:
	cmpl	$1, 16(%rbp)
	jne	.L4
	movl	$1, %eax
	jmp	.L3
.L4:
	movq	$0, -8(%rbp)
	movq	$1, -16(%rbp)
	movl	$2, -20(%rbp)
	jmp	.L5
.L6:
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	addl	$1, -20(%rbp)
.L5:
	movl	-20(%rbp), %eax
	cmpl	16(%rbp), %eax
	jle	.L6
	movq	-16(%rbp), %rax
.L3:
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r5) 13.2.0"
