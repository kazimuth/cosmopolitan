.include "o/libc/nt/codegen.inc"
.imp	KernelBase,__imp_ReadConsoleInputW,ReadConsoleInputW,1302

	.text.windows
ReadConsoleInput:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	__imp_ReadConsoleInputW(%rip),%rax
	jmp	__sysv2nt
	.endfn	ReadConsoleInput,globl
	.previous
