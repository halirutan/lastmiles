
	.section	".text",#alloc,#execinstr,#progbits
	.file	"pi_fp128.c"

	.section	".data",#alloc,#write,#progbits

Ddata.data:

	.section	".rodata",#alloc,#progbits
!
! CONSTANT POOL
!

Drodata.rodata:

	.section	".picdata",#alloc,#write

Dpicdata.picdata:

	.section	".bss",#alloc,#write,#nobits

Bbss.bss:

	.section	".rodata1",#alloc,#progbits
	.align	8
!
! CONSTANT POOL
!

.L18:
	.ascii	"pi could be %42.36Le\n\000"
	.size	.L18,22
	.type	.L18,#object

	.section	".text",#alloc,#execinstr,#progbits
/* 000000	   0 */		.align	16
!
! CONSTANT POOL
!
                       

			.L___const_seg_900000101:
/* 000000	   0 */		.word	1073779231,-1253817647,-2073458292,-988347976
/* 0x0010	   0 */		.type	.L___const_seg_900000101,#object
/* 0x0010	   0 */		.size	.L___const_seg_900000101,(.-.L___const_seg_900000101)
/* 0x0010	   0 */		.align	8
/* 0x0010	     */		.word	65536,65536,65536,65536,65536,65536,65536,65536
/* 0x0030	     */		.align	16
! FILE pi_fp128.c

!    2		      !#include <stdio.h>
!    3		      !#include <stdlib.h>
!    5		      !int main(int argc, char *argv[])
!    6		      !{

!
! SUBROUTINE main
!
! OFFSET    SOURCE LINE	LABEL	INSTRUCTION

                       	.global main
                       

			main:
                       
! predecessor blocks: main

			.L900000108:
/* 000000	   6 */		save	%sp,-256,%sp
                       

			.L900000104:
/* 0x0004	   6 */		rd	%pc,%l0
/* 0x0008	     */		sethi	%pc22(_GLOBAL_OFFSET_TABLE_-(.L900000104-.)),%g1
/* 0x000c	     */		add	%g1,%pc10(_GLOBAL_OFFSET_TABLE_-(.L900000104-.)),%g1
/* 0x0010	     */		add	%g1,%l0,%l0

!    8		      !    long double pi = 3.1415926535897932384626433832795028841971693993751058209749
!    8		      >445923078164062862089986280L;

/* 0x0014	   8 */		sethi	%gdop_hix22(.L___const_seg_900000101),%o0
/* 0x0018	     */		xor	%o0,%gdop_lox10(.L___const_seg_900000101),%o0
/* 0x001c	     */		ldx	[%l0+%o0],%o0,%gdop(.L___const_seg_900000101)
/* 0x0020	     */		ldx	[%o0],%o1
/* 0x0024	     */		ldx	[%o0+8],%o0
/* 0x0028	     */		stx	%o1,[%fp+1999]
/* 0x002c	     */		stx	%o0,[%fp+2007]

!   10		      !    printf("pi could be %42.36Le\n", pi);

/* 0x0030	  10 */		stx	%o1,[%fp+1983]
/* 0x0034	     */		stx	%o0,[%fp+1991]
/* 0x0038	     */		sethi	%gdop_hix22(.L18),%o2
/* 0x003c	     */		xor	%o2,%gdop_lox10(.L18),%o2
/* 0x0040	     */		ldx	[%l0+%o2],%o2,%gdop(.L18)
/* 0x0044	     */		stx	%o2,[%fp+1975]
/* 0x0048	     */		mov	%o1,%o2
/* 0x004c	     */		mov	%o0,%o3
/* 0x0050	     */		ldx	[%fp+1975],%o0
/* 0x0054	     */		call	printf	!params=  %o0 %o2 %o3	!result= 
/* 0x0058	     */		nop

!   11		      !    return ( EXIT_SUCCESS );

/* 0x005c	  11 */		sra	%g0,0,%i0
/* 0x0060	     */		ret	! Result =  %i0
/* 0x0064	     */		restore	%g0,%g0,%g0
/* 0x0068	   0 */		.type	main,#function
/* 0x0068	   0 */		.size	main,(.-main)
/* 0x0068	   0 */		.global	__fsr_init_value
/* 0x0068	     */		 __fsr_init_value=0
                       

			.L900000109:

	.section	".text",#alloc,#execinstr,#progbits
                       

			.L900000114:

	.section	".annotate",#exclude,#progbits
/* 000000	   0 */		.asciz	"anotate"
/* 0x0008	   0 */		.word	6,0
/* 0x0010	   0 */		.xword	160
/* 0x0018	   0 */		.word	0,16
/* 0x0020	   0 */		.xword	(.L900000114-0x98)
/* 0x0028	   0 */		.xword	152
/* 0x0030	   0 */		.word	2,32
/* 0x0038	   0 */		.xword	.L900000108
/* 0x0040	   0 */		.xword	(.L900000109-.L900000108)
/* 0x0048	   0 */		.xword	.L___const_seg_900000101
/* 0x0050	   0 */		.word	-2145857408,0
/* 0x0058	   0 */		.word	5,24
/* 0x0060	   0 */		.xword	(.L900000104+0x4)
/* 0x0068	   0 */		.xword	_GLOBAL_OFFSET_TABLE_
/* 0x0070	   0 */		.xword	.L900000104
/* 0x0078	   0 */		.word	6,24
/* 0x0080	   0 */		.xword	(.L900000104+0x8)
/* 0x0088	   0 */		.xword	_GLOBAL_OFFSET_TABLE_
/* 0x0090	   0 */		.xword	.L900000104
/* 0x0098	   0 */		.word	7,24
/* 0x00a0	   0 */		.xword	.L___const_seg_900000101
/* 0x00a8	   0 */		.xword	16
/* 0x00b0	   0 */		.xword	16

! Begin Disassembling Debug Info

! Begin sdCreateSection
	.section ".debug_info"
	.byte 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00
	.byte 0x00,0x00,0x01,0xf3,0x00,0x02
!	<reloc> off=14 kind=2 l1=.debug_abbrev loff=0
	.uaxword %section_symbol(".debug_abbrev")
	.byte 0x08,0x01
	.ascii "pi_fp128.c\0"
	.byte 0x0c
	.ascii "DBG_GEN 5.7.6\0"
	.ascii "/export/home/dclarke/pgm/lastmiles/floating_point/\0"
	.ascii "/opt/developerstudio12.6/bin/cc -std=iso9899:1999 -errfmt=error -erroff=%none -xmemalign=8s -errshort=full -xstrconst -xildoff -m64 -xnolibmil -xcode=pic32 -xregs=no%appl -xlibmieee -ftrap=%none -xarch=sparc -mc -xs -xbuiltin=%none -xdebugformat=dwarf -xunroll=1 -D_POSIX_PTHREAD_SEMANTICS -D_LARGEFILE64_SOURCE -D_TS_ERRNO -S  pi_fp128.c\0"
	.ascii "Xa;P;R=5.15<<Studio 12.6 Sun C 5.15 SunOS_sparc 2017/05/30>>;\0"
!	<reloc> off=502 kind=2 l1=.debug_line loff=0
	.uaxword %section_symbol(".debug_line")
	.byte 0x00
! End sdCreateSection

! Begin sdCreateSection
	.section ".debug_line"
	.byte 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00
	.byte 0x00,0x00,0x00,0x28,0x00,0x02,0x00,0x00
	.byte 0x00,0x00,0x00,0x00,0x00,0x1e,0x04,0x00
	.byte 0xff,0x04,0x0a,0x00,0x01,0x01,0x01,0x01
	.byte 0x00,0x00,0x00,0x01,0x00,0x70,0x69,0x5f
	.byte 0x66,0x70,0x31,0x32,0x38,0x2e,0x63,0x00
	.byte 0x00,0x00,0x00,0x00
! End sdCreateSection

! Begin sdCreateSection
	.section ".debug_abbrev"
	.byte 0x01,0x11,0x00,0x03,0x08,0x13,0x0b,0x25
	.byte 0x08,0x1b,0x08,0x85,0x44,0x08,0x87,0x44
	.byte 0x08,0x10,0x07,0x00,0x00,0x00
! End sdCreateSection
	.xstabs ".stab.index","V=10.0;DBG_GEN=5.7.6;Xa;P;R=5.15<<Studio 12.6 Sun C 5.15 SunOS_sparc 2017/05/30>>",60,0,0,0
	.xstabs ".stab.index","/export/home/dclarke/pgm/lastmiles/floating_point; /opt/developerstudio12.6/bin/cc -std=iso9899:1999 -errfmt=error -erroff=%none -xmemalign=8s -errshort=full -xstrconst -xildoff -m64 -xnolibmil -xcode=pic32 -xregs=no%appl -xlibmieee -ftrap=%none -xarch=sparc -mc -xs -xbuiltin=%none -xdebugformat=dwarf -xunroll=1 -D_POSIX_PTHREAD_SEMANTICS -D_LARGEFILE64_SOURCE -D_TS_ERRNO -S  pi_fp128.c",52,0,0,0
	.xstabs ".stab.index","main",42,0,0,6

! End Disassembling Debug Info

! Begin Disassembling Ident
	.ident	"cg: Studio 12.6 Compiler Common 12.6 SunOS_sparc 2017-05-30"	! (NO SOURCE LINE)
	.ident	"@(#)stdio.h\t1.86\t13/09/11 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)feature_tests.h\t1.26\t11/04/12 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)ccompile.h\t1.2\t04/11/08 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)isa_defs.h\t1.30\t11/03/31 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdio_iso.h\t1.8\t05/08/16 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)va_list.h\t1.15\t04/11/19 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdio_tag.h\t1.4\t04/09/28 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdio_impl.h\t1.15\t07/03/05 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdio_c99.h\t1.2\t04/03/29 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdlib.h\t1.52\t12/08/01 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdlib_iso.h\t1.9\t04/09/28 SMI"	! (NO SOURCE LINE)
	.ident	"@(#)stdlib_c99.h\t1.2\t04/03/29 SMI"	! (NO SOURCE LINE)
	.ident	"acomp: Studio 12.6 Sun C 5.15 SunOS_sparc 2017/05/30"	! (NO SOURCE LINE)
	.ident	"cg: Studio 12.6 Compiler Common 12.6 SunOS_sparc 2017-05-30"	! (NO SOURCE LINE)
! End Disassembling Ident
