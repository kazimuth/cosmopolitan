.include "o/libc/nt/codegen.inc"
.imp	KernelBase,__imp_SetFilePointer,SetFilePointer,1511

	.text.windows
SetFilePointer:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	__imp_SetFilePointer(%rip),%rax
	jmp	__sysv2nt
	.endfn	SetFilePointer,globl
	.previous
