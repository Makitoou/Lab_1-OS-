.file	"fibonacci.cpp"
	.text
	.p2align 4
	.globl	_Z9fibonaccii
	.def	_Z9fibonaccii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9fibonaccii
_Z9fibonaccii:
.LFB0:
	.seh_endprologue
	xorl	%eax, %eax
	testl	%ecx, %ecx
	je	.L1
	movl	$1, %eax
	cmpl	$1, %ecx
	jle	.L1
	addl	$1, %ecx
	movl	$2, %edx
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rax, %r9
	addl	$1, %edx
	addq	%r8, %rax
	movq	%r9, %r8
	cmpl	%ecx, %edx
	jne	.L3
.L1:
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r5) 13.2.0"