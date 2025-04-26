	.file	"fibonacci.cpp"
	.text
	.globl	_Z9fibonaccii
	.def	_Z9fibonaccii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9fibonaccii
_Z9fibonaccii:
.LFB0:
	.seh_endprologue
	movl	$0, %eax
	testl	%ecx, %ecx
	je	.L1
	movl	$1, %eax
	cmpl	$1, %ecx
	jle	.L1
	addl	$1, %ecx
	movl	$2, %edx
	movl	$0, %r8d
.L3:
	movq	%rax, %r9
	addq	%r8, %rax
	addl	$1, %edx
	movq	%r9, %r8
	cmpl	%ecx, %edx
	jne	.L3
.L1:
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r5) 13.2.0"
