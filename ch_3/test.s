	.file	"test.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Static variable value: %d\12\0"
	.text
	.globl	demoFunction
	.def	demoFunction;	.scl	2;	.type	32;	.endef
	.seh_proc	demoFunction
demoFunction:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	staticVariable.3221(%rip), %eax
	addl	$1, %eax
	movl	%eax, staticVariable.3221(%rip)
	movl	staticVariable.3221(%rip), %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$0, -4(%rbp)
	jmp	.L3
.L4:
	call	demoFunction
	addl	$1, -4(%rbp)
.L3:
	cmpl	$4, -4(%rbp)
	jle	.L4
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
.lcomm staticVariable.3221,4,4
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	printf;	.scl	2;	.type	32;	.endef
