.include "o/libc/nt/codegen.inc"
.imp	KernelBase,__imp_LoadLibraryW,LoadLibraryW,978

	.text.windows
LoadLibrary:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	%rdi,%rcx
	sub	$32,%rsp
	call	*__imp_LoadLibraryW(%rip)
	leave
	ret
	.endfn	LoadLibrary,globl
	.previous
