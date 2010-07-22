	.file	"list.c"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$52, %esp
	movl	$20, (%esp)
	call	malloc
	movl	%eax, -28(%ebp)
	cmpl	$0, -28(%ebp)
	jne	.L2
	movl	$-1, (%esp)
	call	exit
.L2:
	movl	$20, -24(%ebp)
	call	getchar
	movb	%al, -5(%ebp)
	movl	$0, -20(%ebp)
	jmp	.L3
.L4:
	movl	-20(%ebp), %ecx
	movl	%ecx, %eax
	movl	%eax, %edx
	addl	-28(%ebp), %edx
	movzbl	-5(%ebp), %eax
	movb	%al, (%edx)
	leal	1(%ecx), %eax
	movl	%eax, -20(%ebp)
	call	getchar
	movb	%al, -5(%ebp)
	movl	-24(%ebp), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	cmpl	%eax, %edx
	jg	.L3
	addl	$10, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -28(%ebp)
	cmpl	$0, -28(%ebp)
	jne	.L3
	movl	$-1, (%esp)
	call	exit
.L3:
	cmpb	$10, -5(%ebp)
	jne	.L4
	movl	-20(%ebp), %eax
	addl	-28(%ebp), %eax
	movb	$0, (%eax)
	leal	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	initList
	movl	$0, -20(%ebp)
	jmp	.L5
.L6:
	movl	-16(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	insertToListTail
.L5:
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	getNextNumber
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	je	.L6
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	cmpl	$1, -12(%ebp)
	jne	.L7
	movl	$-1, (%esp)
	call	exit
.L7:
	movl	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	printList
	movl	$0, %eax
	addl	$52, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
