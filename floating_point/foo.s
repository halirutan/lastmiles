	.text
	.file	"foo.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3               # -- Begin function main
.LCPI0_0:
	.quad	-4607182418800017408    # double -4
.LCPI0_1:
	.quad	4611686018427387904     # double 2
.LCPI0_2:
	.quad	4621469175726033948     # double 9.3783783783783789
.LCPI0_3:
	.quad	4658815484840378368     # double 3000
.LCPI0_4:
	.quad	4637511347540590592     # double 111
.LCPI0_5:
	.quad	4652684608003899392     # double 1130
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
.Lfunc_begin0:
	.file	1 "/usr/home/dclarke/pgm/lastmiles/floating_point" "foo.c"
	.loc	1 11 0                  # foo.c:11:0
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$176, %rsp
	movl	$0, -4(%rbp)
.Ltmp0:
	.loc	1 18 5 prologue_end     # foo.c:18:5
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movb	%al, %cl
	movl	%eax, %esi
	movb	%cl, %al
	movb	%cl, -53(%rbp)          # 1-byte Spill
	callq	printf
	movl	%eax, -60(%rbp)         # 4-byte Spill
	.loc	1 21 21                 # foo.c:21:21
	callq	fegetround
	.loc	1 21 19 is_stmt 0       # foo.c:21:19
	movl	%eax, -48(%rbp)
	.loc	1 22 5 is_stmt 1        # foo.c:22:5
	movl	$.L.str.1, %edi
	movb	-53(%rbp), %al          # 1-byte Reload
	callq	printf
	.loc	1 23 12                 # foo.c:23:12
	movl	-48(%rbp), %esi
	.loc	1 23 5 is_stmt 0        # foo.c:23:5
	testl	%esi, %esi
	movl	%eax, -64(%rbp)         # 4-byte Spill
	movl	%esi, -68(%rbp)         # 4-byte Spill
	je	.LBB0_1
	jmp	.LBB0_26
.LBB0_26:
	.loc	1 0 5                   # foo.c:0:5
	movl	-68(%rbp), %eax         # 4-byte Reload
	.loc	1 23 5                  # foo.c:23:5
	subl	$1024, %eax             # imm = 0x400
	movl	%eax, -72(%rbp)         # 4-byte Spill
	je	.LBB0_4
	jmp	.LBB0_27
.LBB0_27:
	.loc	1 0 5                   # foo.c:0:5
	movl	-68(%rbp), %eax         # 4-byte Reload
	.loc	1 23 5                  # foo.c:23:5
	subl	$2048, %eax             # imm = 0x800
	movl	%eax, -76(%rbp)         # 4-byte Spill
	je	.LBB0_3
	jmp	.LBB0_28
.LBB0_28:
	.loc	1 0 5                   # foo.c:0:5
	movl	-68(%rbp), %eax         # 4-byte Reload
	.loc	1 23 5                  # foo.c:23:5
	subl	$3072, %eax             # imm = 0xC00
	movl	%eax, -80(%rbp)         # 4-byte Spill
	je	.LBB0_2
	jmp	.LBB0_5
.LBB0_1:
.Ltmp1:
	.loc	1 25 13 is_stmt 1       # foo.c:25:13
	movabsq	$.L.str.2, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -84(%rbp)         # 4-byte Spill
	.loc	1 26 13                 # foo.c:26:13
	jmp	.LBB0_6
.LBB0_2:
	.loc	1 28 13                 # foo.c:28:13
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -88(%rbp)         # 4-byte Spill
	.loc	1 29 13                 # foo.c:29:13
	jmp	.LBB0_6
.LBB0_3:
	.loc	1 31 13                 # foo.c:31:13
	movabsq	$.L.str.4, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -92(%rbp)         # 4-byte Spill
	.loc	1 32 13                 # foo.c:32:13
	jmp	.LBB0_6
.LBB0_4:
	.loc	1 34 13                 # foo.c:34:13
	movabsq	$.L.str.5, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -96(%rbp)         # 4-byte Spill
	.loc	1 35 13                 # foo.c:35:13
	jmp	.LBB0_6
.LBB0_5:
	.loc	1 37 13                 # foo.c:37:13
	movabsq	$.L.str.6, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -100(%rbp)        # 4-byte Spill
.Ltmp2:
.LBB0_6:
	.loc	1 0 13 is_stmt 0        # foo.c:0:13
	movsd	.LCPI0_0(%rip), %xmm0   # xmm0 = mem[0],zero
	movsd	.LCPI0_1(%rip), %xmm1   # xmm1 = mem[0],zero
	.loc	1 41 8 is_stmt 1        # foo.c:41:8
	movsd	%xmm1, -16(%rbp)
	.loc	1 42 8                  # foo.c:42:8
	movsd	%xmm0, -24(%rbp)
	.loc	1 47 5                  # foo.c:47:5
	movabsq	$.L.str.7, %rdi
	movb	$0, %al
	callq	printf
	.loc	1 48 5                  # foo.c:48:5
	movabsq	$.L.str.8, %rdi
	movl	%eax, -104(%rbp)        # 4-byte Spill
	movb	$0, %al
	callq	printf
	.loc	1 49 5                  # foo.c:49:5
	movabsq	$.L.str.9, %rdi
	movl	%eax, -108(%rbp)        # 4-byte Spill
	movb	$0, %al
	callq	printf
	.loc	1 50 5                  # foo.c:50:5
	movabsq	$.L.str.10, %rdi
	movl	%eax, -112(%rbp)        # 4-byte Spill
	movb	$0, %al
	callq	printf
.Ltmp3:
	.loc	1 52 10                 # foo.c:52:10
	movl	$63, %edi
	movl	%eax, -116(%rbp)        # 4-byte Spill
	callq	feclearexcept
	.loc	1 52 39 is_stmt 0       # foo.c:52:39
	cmpl	$0, %eax
.Ltmp4:
	.loc	1 52 10                 # foo.c:52:10
	jne	.LBB0_8
# %bb.7:
.Ltmp5:
	.loc	1 53 9 is_stmt 1        # foo.c:53:9
	movabsq	$.L.str.11, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -120(%rbp)        # 4-byte Spill
	.loc	1 54 5                  # foo.c:54:5
	jmp	.LBB0_9
.Ltmp6:
.LBB0_8:
	.loc	1 55 9                  # foo.c:55:9
	movabsq	$.L.str.12, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -124(%rbp)        # 4-byte Spill
.Ltmp7:
.LBB0_9:
	.loc	1 57 5                  # foo.c:57:5
	movabsq	$.L.str.13, %rdi
	movb	$0, %al
	callq	printf
	movsd	.LCPI0_2(%rip), %xmm0   # xmm0 = mem[0],zero
	.loc	1 59 8                  # foo.c:59:8
	movsd	%xmm0, -40(%rbp)
	.loc	1 61 18                 # foo.c:61:18
	movl	$63, %edi
	movl	%eax, -128(%rbp)        # 4-byte Spill
	callq	fetestexcept
	.loc	1 61 16 is_stmt 0       # foo.c:61:16
	movl	%eax, -52(%rbp)
.Ltmp8:
	.loc	1 62 19 is_stmt 1       # foo.c:62:19
	cmpl	$0, -52(%rbp)
.Ltmp9:
	.loc	1 62 9 is_stmt 0        # foo.c:62:9
	je	.LBB0_21
# %bb.10:
.Ltmp10:
	.loc	1 63 9 is_stmt 1        # foo.c:63:9
	movabsq	$.L.str.14, %rdi
	movb	$0, %al
	callq	printf
.Ltmp11:
	.loc	1 64 12                 # foo.c:64:12
	movl	-52(%rbp), %ecx
	.loc	1 64 23 is_stmt 0       # foo.c:64:23
	andl	$32, %ecx
	cmpl	$0, %ecx
	movl	%eax, -132(%rbp)        # 4-byte Spill
.Ltmp12:
	.loc	1 64 12                 # foo.c:64:12
	je	.LBB0_12
# %bb.11:
.Ltmp13:
	.loc	1 64 37                 # foo.c:64:37
	movabsq	$.L.str.15, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -136(%rbp)        # 4-byte Spill
.Ltmp14:
.LBB0_12:
	.loc	1 65 12 is_stmt 1       # foo.c:65:12
	movl	-52(%rbp), %eax
	.loc	1 65 23 is_stmt 0       # foo.c:65:23
	andl	$4, %eax
	cmpl	$0, %eax
.Ltmp15:
	.loc	1 65 12                 # foo.c:65:12
	je	.LBB0_14
# %bb.13:
.Ltmp16:
	.loc	1 65 39                 # foo.c:65:39
	movabsq	$.L.str.16, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -140(%rbp)        # 4-byte Spill
.Ltmp17:
.LBB0_14:
	.loc	1 66 12 is_stmt 1       # foo.c:66:12
	movl	-52(%rbp), %eax
	.loc	1 66 23 is_stmt 0       # foo.c:66:23
	andl	$16, %eax
	cmpl	$0, %eax
.Ltmp18:
	.loc	1 66 12                 # foo.c:66:12
	je	.LBB0_16
# %bb.15:
.Ltmp19:
	.loc	1 66 39                 # foo.c:66:39
	movabsq	$.L.str.17, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -144(%rbp)        # 4-byte Spill
.Ltmp20:
.LBB0_16:
	.loc	1 67 12 is_stmt 1       # foo.c:67:12
	movl	-52(%rbp), %eax
	.loc	1 67 23 is_stmt 0       # foo.c:67:23
	andl	$8, %eax
	cmpl	$0, %eax
.Ltmp21:
	.loc	1 67 12                 # foo.c:67:12
	je	.LBB0_18
# %bb.17:
.Ltmp22:
	.loc	1 67 38                 # foo.c:67:38
	movabsq	$.L.str.18, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -148(%rbp)        # 4-byte Spill
.Ltmp23:
.LBB0_18:
	.loc	1 68 12 is_stmt 1       # foo.c:68:12
	movl	-52(%rbp), %eax
	.loc	1 68 23 is_stmt 0       # foo.c:68:23
	andl	$1, %eax
	cmpl	$0, %eax
.Ltmp24:
	.loc	1 68 12                 # foo.c:68:12
	je	.LBB0_20
# %bb.19:
.Ltmp25:
	.loc	1 68 37                 # foo.c:68:37
	movabsq	$.L.str.19, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -152(%rbp)        # 4-byte Spill
.Ltmp26:
.LBB0_20:
	.loc	1 69 9 is_stmt 1        # foo.c:69:9
	movabsq	$.L.str.13, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -156(%rbp)        # 4-byte Spill
.Ltmp27:
.LBB0_21:
	.loc	1 72 50                 # foo.c:72:50
	movsd	-40(%rbp), %xmm0        # xmm0 = mem[0],zero
	.loc	1 72 5 is_stmt 0        # foo.c:72:5
	movabsq	$.L.str.20, %rdi
	movb	$1, %al
	callq	printf
	.loc	1 73 5 is_stmt 1        # foo.c:73:5
	movabsq	$.L.str.21, %rdi
	movl	%eax, -160(%rbp)        # 4-byte Spill
	movb	$0, %al
	callq	printf
	xorl	%esi, %esi
	.loc	1 75 41                 # foo.c:75:41
	movsd	-16(%rbp), %xmm0        # xmm0 = mem[0],zero
	.loc	1 75 5 is_stmt 0        # foo.c:75:5
	movabsq	$.L.str.22, %rdi
	movl	%eax, -164(%rbp)        # 4-byte Spill
	movb	$1, %al
	callq	printf
	.loc	1 76 41 is_stmt 1       # foo.c:76:41
	movsd	-24(%rbp), %xmm0        # xmm0 = mem[0],zero
	.loc	1 76 5 is_stmt 0        # foo.c:76:5
	movabsq	$.L.str.22, %rdi
	movl	$1, %esi
	movl	%eax, -168(%rbp)        # 4-byte Spill
	movb	$1, %al
	callq	printf
.Ltmp28:
	.loc	1 78 12 is_stmt 1       # foo.c:78:12
	movl	$2, -44(%rbp)
	movl	%eax, -172(%rbp)        # 4-byte Spill
.LBB0_22:                               # =>This Inner Loop Header: Depth=1
.Ltmp29:
	.loc	1 78 17 is_stmt 0       # foo.c:78:17
	cmpl	$32, -44(%rbp)
.Ltmp30:
	.loc	1 78 5                  # foo.c:78:5
	jge	.LBB0_25
# %bb.23:                               #   in Loop: Header=BB0_22 Depth=1
	.loc	1 0 5                   # foo.c:0:5
	movsd	.LCPI0_3(%rip), %xmm0   # xmm0 = mem[0],zero
	movsd	.LCPI0_4(%rip), %xmm1   # xmm1 = mem[0],zero
	movsd	.LCPI0_5(%rip), %xmm2   # xmm2 = mem[0],zero
.Ltmp31:
	.loc	1 80 28 is_stmt 1       # foo.c:80:28
	divsd	-24(%rbp), %xmm2
	.loc	1 80 20 is_stmt 0       # foo.c:80:20
	subsd	%xmm2, %xmm1
	.loc	1 80 45                 # foo.c:80:45
	movsd	-24(%rbp), %xmm2        # xmm2 = mem[0],zero
	.loc	1 80 48                 # foo.c:80:48
	mulsd	-16(%rbp), %xmm2
	.loc	1 80 41                 # foo.c:80:41
	divsd	%xmm2, %xmm0
	.loc	1 80 32                 # foo.c:80:32
	addsd	%xmm0, %xmm1
	.loc	1 80 12                 # foo.c:80:12
	movsd	%xmm1, -32(%rbp)
	.loc	1 82 42 is_stmt 1       # foo.c:82:42
	movl	-44(%rbp), %esi
	.loc	1 82 46 is_stmt 0       # foo.c:82:46
	movsd	-32(%rbp), %xmm0        # xmm0 = mem[0],zero
	.loc	1 82 9                  # foo.c:82:9
	movabsq	$.L.str.22, %rdi
	movb	$1, %al
	callq	printf
	.loc	1 84 14 is_stmt 1       # foo.c:84:14
	movsd	-24(%rbp), %xmm0        # xmm0 = mem[0],zero
	.loc	1 84 12 is_stmt 0       # foo.c:84:12
	movsd	%xmm0, -16(%rbp)
	.loc	1 85 14 is_stmt 1       # foo.c:85:14
	movsd	-32(%rbp), %xmm0        # xmm0 = mem[0],zero
	.loc	1 85 12 is_stmt 0       # foo.c:85:12
	movsd	%xmm0, -24(%rbp)
	movl	%eax, -176(%rbp)        # 4-byte Spill
.Ltmp32:
# %bb.24:                               #   in Loop: Header=BB0_22 Depth=1
	.loc	1 78 23 is_stmt 1       # foo.c:78:23
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	.loc	1 78 5 is_stmt 0        # foo.c:78:5
	jmp	.LBB0_22
.Ltmp33:
.LBB0_25:
	.loc	1 0 5                   # foo.c:0:5
	xorl	%eax, %eax
	.loc	1 89 5 is_stmt 1        # foo.c:89:5
	addq	$176, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Ltmp34:
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function fegetround
	.type	fegetround,@function
fegetround:                             # @fegetround
.Lfunc_begin1:
	.file	2 "/usr" "include/fenv.h"
	.loc	2 114 0                 # include/fenv.h:114:0
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
.Ltmp35:
	.loc	2 123 2 prologue_end    # include/fenv.h:123:2
	#APP
	fnstcw	-2(%rbp)
	#NO_APP
	.loc	2 124 10                # include/fenv.h:124:10
	movzwl	-2(%rbp), %eax
	.loc	2 124 20 is_stmt 0      # include/fenv.h:124:20
	andl	$3072, %eax             # imm = 0xC00
	.loc	2 124 2                 # include/fenv.h:124:2
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Ltmp36:
.Lfunc_end1:
	.size	fegetround, .Lfunc_end1-fegetround
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function feclearexcept
	.type	feclearexcept,@function
feclearexcept:                          # @feclearexcept
.Lfunc_begin2:
	.loc	2 268 0 is_stmt 1       # include/fenv.h:268:0
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
.Ltmp37:
	.loc	2 271 16 prologue_end   # include/fenv.h:271:16
	cmpl	$63, -4(%rbp)
.Ltmp38:
	.loc	2 271 6 is_stmt 0       # include/fenv.h:271:6
	jne	.LBB2_2
# %bb.1:
.Ltmp39:
	.loc	2 272 3 is_stmt 1       # include/fenv.h:272:3
	#APP
	fnclex
	#NO_APP
	.loc	2 273 2                 # include/fenv.h:273:2
	jmp	.LBB2_3
.Ltmp40:
.LBB2_2:
	.loc	2 0 2 is_stmt 0         # include/fenv.h:0:2
	leaq	-40(%rbp), %rax
.Ltmp41:
	.loc	2 274 3 is_stmt 1       # include/fenv.h:274:3
	#APP
	fnstenv	(%rax)
	#NO_APP
	leaq	-40(%rbp), %rax
	.loc	2 275 28                # include/fenv.h:275:28
	movl	-4(%rbp), %ecx
	.loc	2 275 27 is_stmt 0      # include/fenv.h:275:27
	xorl	$-1, %ecx
	.loc	2 275 24                # include/fenv.h:275:24
	andl	-36(%rbp), %ecx
	movl	%ecx, -36(%rbp)
	.loc	2 276 3 is_stmt 1       # include/fenv.h:276:3
	#APP
	fldenv	(%rax)
	#NO_APP
.Ltmp42:
.LBB2_3:
	.loc	2 278 2                 # include/fenv.h:278:2
	leaq	-40(%rbp), %rax
	addq	$28, %rax
	#APP
	stmxcsr	(%rax)
	#NO_APP
	.loc	2 279 20                # include/fenv.h:279:20
	movl	-4(%rbp), %ecx
	.loc	2 279 19 is_stmt 0      # include/fenv.h:279:19
	xorl	$-1, %ecx
	.loc	2 279 16                # include/fenv.h:279:16
	andl	-12(%rbp), %ecx
	movl	%ecx, -12(%rbp)
	.loc	2 280 2 is_stmt 1       # include/fenv.h:280:2
	leaq	-40(%rbp), %rax
	addq	$28, %rax
	#APP
	ldmxcsr	(%rax)
	#NO_APP
	xorl	%eax, %eax
	.loc	2 281 2                 # include/fenv.h:281:2
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Ltmp43:
.Lfunc_end2:
	.size	feclearexcept, .Lfunc_end2-feclearexcept
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function fetestexcept
	.type	fetestexcept,@function
fetestexcept:                           # @fetestexcept
.Lfunc_begin3:
	.loc	2 298 0                 # include/fenv.h:298:0
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
.Ltmp44:
	.loc	2 302 2 prologue_end    # include/fenv.h:302:2
	#APP
	stmxcsr	-8(%rbp)
	#NO_APP
	.loc	2 303 2                 # include/fenv.h:303:2
	#APP
	fnstsw	-10(%rbp)
	#NO_APP
	.loc	2 304 11                # include/fenv.h:304:11
	movzwl	-10(%rbp), %edi
	.loc	2 304 20 is_stmt 0      # include/fenv.h:304:20
	orl	-8(%rbp), %edi
	.loc	2 304 31                # include/fenv.h:304:31
	andl	-4(%rbp), %edi
	.loc	2 304 2                 # include/fenv.h:304:2
	movl	%edi, %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Ltmp45:
.Lfunc_end3:
	.size	fetestexcept, .Lfunc_end3-fetestexcept
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"INFO : FLT_EVAL_METHOD == %d\n"
	.size	.L.str, 30

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"INFO : fp rounding mode is "
	.size	.L.str.1, 28

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"FE_TONEAREST\n"
	.size	.L.str.2, 14

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"FE_TOWARDZERO\n"
	.size	.L.str.3, 15

	.type	.L.str.4,@object        # @.str.4
.L.str.4:
	.asciz	"FE_UPWARD\n"
	.size	.L.str.4, 11

	.type	.L.str.5,@object        # @.str.5
.L.str.5:
	.asciz	"FE_DOWNWARD\n"
	.size	.L.str.5, 13

	.type	.L.str.6,@object        # @.str.6
.L.str.6:
	.asciz	"bloody unknown!\n"
	.size	.L.str.6, 17

	.type	.L.str.7,@object        # @.str.7
.L.str.7:
	.asciz	"\n---------------------------------------\n"
	.size	.L.str.7, 42

	.type	.L.str.8,@object        # @.str.8
.L.str.8:
	.asciz	" We know that u2 = 37/2 which is 18.5\n"
	.size	.L.str.8, 39

	.type	.L.str.9,@object        # @.str.9
.L.str.9:
	.asciz	" We also know that u3 = 347/37 and that\n"
	.size	.L.str.9, 41

	.type	.L.str.10,@object       # @.str.10
.L.str.10:
	.asciz	" can not be represented by any computer.\n"
	.size	.L.str.10, 42

	.type	.L.str.11,@object       # @.str.11
.L.str.11:
	.asciz	"\n    feclearexcept(FE_ALL_EXCEPT) works!\n"
	.size	.L.str.11, 42

	.type	.L.str.12,@object       # @.str.12
.L.str.12:
	.asciz	"\n    feclearexcept(FE_ALL_EXCEPT) fails!\n"
	.size	.L.str.12, 42

	.type	.L.str.13,@object       # @.str.13
.L.str.13:
	.asciz	"\n"
	.size	.L.str.13, 2

	.type	.L.str.14,@object       # @.str.14
.L.str.14:
	.asciz	"INFO : FP Exception raised is"
	.size	.L.str.14, 30

	.type	.L.str.15,@object       # @.str.15
.L.str.15:
	.asciz	" FE_INEXACT"
	.size	.L.str.15, 12

	.type	.L.str.16,@object       # @.str.16
.L.str.16:
	.asciz	" FE_DIVBYZERO"
	.size	.L.str.16, 14

	.type	.L.str.17,@object       # @.str.17
.L.str.17:
	.asciz	" FE_UNDERFLOW"
	.size	.L.str.17, 14

	.type	.L.str.18,@object       # @.str.18
.L.str.18:
	.asciz	" FE_OVERFLOW"
	.size	.L.str.18, 13

	.type	.L.str.19,@object       # @.str.19
.L.str.19:
	.asciz	" FE_INVALID"
	.size	.L.str.19, 12

	.type	.L.str.20,@object       # @.str.20
.L.str.20:
	.asciz	" In fact u3 sort of is %-+32.28e\n"
	.size	.L.str.20, 34

	.type	.L.str.21,@object       # @.str.21
.L.str.21:
	.asciz	"---------------------------------------\n"
	.size	.L.str.21, 41

	.type	.L.str.22,@object       # @.str.22
.L.str.22:
	.asciz	" u[%2i] = %-+32.28e\n"
	.size	.L.str.22, 21

	.file	3 "/usr" "include/x86/_types.h"
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"FreeBSD clang version 8.0.1 (tags/RELEASE_801/final 366581) (based on LLVM 8.0.1)" # string offset=0
.Linfo_string1:
	.asciz	"foo.c"                 # string offset=82
.Linfo_string2:
	.asciz	"/usr/home/dclarke/pgm/lastmiles/floating_point" # string offset=88
.Linfo_string3:
	.asciz	"main"                  # string offset=135
.Linfo_string4:
	.asciz	"int"                   # string offset=140
.Linfo_string5:
	.asciz	"fegetround"            # string offset=144
.Linfo_string6:
	.asciz	"feclearexcept"         # string offset=155
.Linfo_string7:
	.asciz	"fetestexcept"          # string offset=169
.Linfo_string8:
	.asciz	"u0"                    # string offset=182
.Linfo_string9:
	.asciz	"double"                # string offset=185
.Linfo_string10:
	.asciz	"u1"                    # string offset=192
.Linfo_string11:
	.asciz	"un"                    # string offset=195
.Linfo_string12:
	.asciz	"u3"                    # string offset=198
.Linfo_string13:
	.asciz	"k"                     # string offset=201
.Linfo_string14:
	.asciz	"fp_round_mode"         # string offset=203
.Linfo_string15:
	.asciz	"fpe_raised"            # string offset=217
.Linfo_string16:
	.asciz	"__control"             # string offset=228
.Linfo_string17:
	.asciz	"unsigned short"        # string offset=238
.Linfo_string18:
	.asciz	"__uint16_t"            # string offset=253
.Linfo_string19:
	.asciz	"__excepts"             # string offset=264
.Linfo_string20:
	.asciz	"__env"                 # string offset=274
.Linfo_string21:
	.asciz	"__x87"                 # string offset=280
.Linfo_string22:
	.asciz	"unsigned int"          # string offset=286
.Linfo_string23:
	.asciz	"__uint32_t"            # string offset=299
.Linfo_string24:
	.asciz	"__status"              # string offset=310
.Linfo_string25:
	.asciz	"__tag"                 # string offset=319
.Linfo_string26:
	.asciz	"__other"               # string offset=325
.Linfo_string27:
	.asciz	"char"                  # string offset=333
.Linfo_string28:
	.asciz	"__ARRAY_SIZE_TYPE__"   # string offset=338
.Linfo_string29:
	.asciz	"__mxcsr"               # string offset=358
.Linfo_string30:
	.asciz	"fenv_t"                # string offset=366
	.section	.debug_abbrev,"",@progbits
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	14                      # DW_FORM_strp
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	16                      # DW_AT_stmt_list
	.byte	6                       # DW_FORM_data4
	.byte	27                      # DW_AT_comp_dir
	.byte	14                      # DW_FORM_strp
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	12                      # DW_FORM_flag
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	12                      # DW_FORM_flag
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	39                      # DW_AT_prototyped
	.byte	12                      # DW_FORM_flag
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	10                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	12                      # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
	.byte	33                      # DW_TAG_subrange_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	34                      # DW_AT_lower_bound
	.byte	11                      # DW_FORM_data1
	.byte	55                      # DW_AT_count
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	14                      # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
	.section	.debug_info,"",@progbits
.Lcu_begin0:
	.long	.Ldebug_info_end0-.Ldebug_info_start0 # Length of Unit
.Ldebug_info_start0:
	.short	2                       # DWARF version number
	.long	.debug_abbrev           # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x213 DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	12                      # DW_AT_language
	.long	.Linfo_string1          # DW_AT_name
	.long	.Lline_table_start0     # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
	.quad	.Lfunc_begin0           # DW_AT_low_pc
	.quad	.Lfunc_end3             # DW_AT_high_pc
	.byte	2                       # Abbrev [2] 0x2e:0x81 DW_TAG_subprogram
	.quad	.Lfunc_begin0           # DW_AT_low_pc
	.quad	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.long	.Linfo_string3          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	10                      # DW_AT_decl_line
	.long	359                     # DW_AT_type
	.byte	1                       # DW_AT_external
	.byte	3                       # Abbrev [3] 0x4c:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.long	.Linfo_string8          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.long	366                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0x5a:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	104
	.long	.Linfo_string10         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.long	366                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0x68:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.long	.Linfo_string11         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
	.long	366                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0x76:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	88
	.long	.Linfo_string12         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	14                      # DW_AT_decl_line
	.long	366                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0x84:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	84
	.long	.Linfo_string13         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	15                      # DW_AT_decl_line
	.long	359                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0x92:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	80
	.long	.Linfo_string14         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	15                      # DW_AT_decl_line
	.long	359                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0xa0:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	76
	.long	.Linfo_string15         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	15                      # DW_AT_decl_line
	.long	359                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0xaf:0x2d DW_TAG_subprogram
	.quad	.Lfunc_begin1           # DW_AT_low_pc
	.quad	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.long	.Linfo_string5          # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	113                     # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	359                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0xcd:0xe DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	126
	.long	.Linfo_string16         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	115                     # DW_AT_decl_line
	.long	373                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0xdc:0x3e DW_TAG_subprogram
	.quad	.Lfunc_begin2           # DW_AT_low_pc
	.quad	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.long	.Linfo_string6          # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	267                     # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	359                     # DW_AT_type
	.byte	6                       # Abbrev [6] 0xfb:0xf DW_TAG_formal_parameter
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	124
	.long	.Linfo_string19         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	267                     # DW_AT_decl_line
	.long	359                     # DW_AT_type
	.byte	7                       # Abbrev [7] 0x10a:0xf DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	88
	.long	.Linfo_string20         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	269                     # DW_AT_decl_line
	.long	391                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x11a:0x4d DW_TAG_subprogram
	.quad	.Lfunc_begin3           # DW_AT_low_pc
	.quad	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.long	.Linfo_string7          # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	297                     # DW_AT_decl_line
	.byte	1                       # DW_AT_prototyped
	.long	359                     # DW_AT_type
	.byte	6                       # Abbrev [6] 0x139:0xf DW_TAG_formal_parameter
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	124
	.long	.Linfo_string19         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	297                     # DW_AT_decl_line
	.long	359                     # DW_AT_type
	.byte	7                       # Abbrev [7] 0x148:0xf DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	120
	.long	.Linfo_string29         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	299                     # DW_AT_decl_line
	.long	496                     # DW_AT_type
	.byte	7                       # Abbrev [7] 0x157:0xf DW_TAG_variable
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	118
	.long	.Linfo_string24         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.short	300                     # DW_AT_decl_line
	.long	373                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x167:0x7 DW_TAG_base_type
	.long	.Linfo_string4          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	8                       # Abbrev [8] 0x16e:0x7 DW_TAG_base_type
	.long	.Linfo_string9          # DW_AT_name
	.byte	4                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	9                       # Abbrev [9] 0x175:0xb DW_TAG_typedef
	.long	384                     # DW_AT_type
	.long	.Linfo_string18         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.byte	8                       # Abbrev [8] 0x180:0x7 DW_TAG_base_type
	.long	.Linfo_string17         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	2                       # DW_AT_byte_size
	.byte	9                       # Abbrev [9] 0x187:0xb DW_TAG_typedef
	.long	402                     # DW_AT_type
	.long	.Linfo_string30         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.byte	10                      # Abbrev [10] 0x192:0x5e DW_TAG_structure_type
	.byte	32                      # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	84                      # DW_AT_decl_line
	.byte	11                      # Abbrev [11] 0x196:0xe DW_TAG_member
	.long	.Linfo_string21         # DW_AT_name
	.long	420                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	10                      # Abbrev [10] 0x1a4:0x3d DW_TAG_structure_type
	.byte	28                      # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	85                      # DW_AT_decl_line
	.byte	11                      # Abbrev [11] 0x1a8:0xe DW_TAG_member
	.long	.Linfo_string16         # DW_AT_name
	.long	496                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	11                      # Abbrev [11] 0x1b6:0xe DW_TAG_member
	.long	.Linfo_string24         # DW_AT_name
	.long	496                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	11                      # Abbrev [11] 0x1c4:0xe DW_TAG_member
	.long	.Linfo_string25         # DW_AT_name
	.long	496                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	88                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	11                      # Abbrev [11] 0x1d2:0xe DW_TAG_member
	.long	.Linfo_string26         # DW_AT_name
	.long	514                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	89                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	12
	.byte	0                       # End Of Children Mark
	.byte	11                      # Abbrev [11] 0x1e1:0xe DW_TAG_member
	.long	.Linfo_string29         # DW_AT_name
	.long	496                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	91                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	35
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x1f0:0xb DW_TAG_typedef
	.long	507                     # DW_AT_type
	.long	.Linfo_string23         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.byte	8                       # Abbrev [8] 0x1fb:0x7 DW_TAG_base_type
	.long	.Linfo_string22         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	12                      # Abbrev [12] 0x202:0xd DW_TAG_array_type
	.long	527                     # DW_AT_type
	.byte	13                      # Abbrev [13] 0x207:0x7 DW_TAG_subrange_type
	.long	534                     # DW_AT_type
	.byte	0                       # DW_AT_lower_bound
	.byte	16                      # DW_AT_count
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x20f:0x7 DW_TAG_base_type
	.long	.Linfo_string27         # DW_AT_name
	.byte	6                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	14                      # Abbrev [14] 0x216:0x7 DW_TAG_base_type
	.long	.Linfo_string28         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	7                       # DW_AT_encoding
	.byte	0                       # End Of Children Mark
.Ldebug_info_end0:
	.section	.debug_macinfo,"",@progbits
	.byte	0                       # End Of Macro List Mark

	.ident	"FreeBSD clang version 8.0.1 (tags/RELEASE_801/final 366581) (based on LLVM 8.0.1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
	.addrsig_sym fegetround
	.addrsig_sym feclearexcept
	.addrsig_sym fetestexcept
	.section	.debug_line,"",@progbits
.Lline_table_start0:
