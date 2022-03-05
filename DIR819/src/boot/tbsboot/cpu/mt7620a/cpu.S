	.section .mdebug.abi32
	.previous
	.abicalls
	.section	.debug_abbrev,"",@progbits
$Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.text
$Ltext0:
	.align	2
	.globl	flush_icache_range
	.ent	flush_icache_range
	.type	flush_icache_range, @function
flush_icache_range:
$LFB11:
	.file 1 "cpu.c"
	.loc 1 93 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.loc 1 95 0
	li	$2,-32			# 0xffffffffffffffe0
	.loc 1 96 0
	addiu	$5,$5,-1
	and	$5,$5,$2
	.loc 1 95 0
	and	$4,$4,$2
$L2:
	.loc 1 99 0
#APP
		.set	push			
	.set	noreorder		
	.set	mips3			
1:	cache	21, ($4)		
2:	.set	pop			
	.section __ex_table,"a"	
	.dword 1b, 2b		
	.previous
	.loc 1 100 0
	sync
	.loc 1 101 0
		.set	push			
	.set	noreorder		
	.set	mips3			
1:	cache	16, ($4)		
2:	.set	pop			
	.section __ex_table,"a"	
	.dword 1b, 2b		
	.previous
#NO_APP
	.loc 1 102 0
	.set	noreorder
	.set	nomacro
	bne	$4,$5,$L2
	addiu	$4,$4,32
	.set	macro
	.set	reorder

$LBB2:
	.loc 1 107 0
#APP
		.set	mips64r2				
	dla	$2, 1f					
	jr.hb	$2					
	.set	mips0					
1:							

#NO_APP
$LBE2:
	j	$31
$LFE11:
	.end	flush_icache_range
	.align	2
	.globl	flush_dcache_range
	.ent	flush_dcache_range
	.type	flush_dcache_range, @function
flush_dcache_range:
$LFB12:
	.loc 1 111 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.loc 1 113 0
	li	$2,-32			# 0xffffffffffffffe0
	.loc 1 114 0
	addiu	$5,$5,-1
	and	$5,$5,$2
	.loc 1 113 0
	and	$4,$4,$2
$L7:
	.loc 1 117 0
#APP
		.set	push			
	.set	noreorder		
	.set	mips3			
1:	cache	17, ($4)		
2:	.set	pop			
	.section __ex_table,"a"	
	.dword 1b, 2b		
	.previous
#NO_APP
	.loc 1 118 0
	.set	noreorder
	.set	nomacro
	bne	$4,$5,$L7
	addiu	$4,$4,32
	.set	macro
	.set	reorder

$LBB3:
	.loc 1 123 0
#APP
		.set	mips64r2				
	dla	$2, 1f					
	jr.hb	$2					
	.set	mips0					
1:							

#NO_APP
$LBE3:
	j	$31
$LFE12:
	.end	flush_dcache_range
	.align	2
	.globl	do_reset
	.ent	do_reset
	.type	do_reset, @function
do_reset:
$LFB13:
	.loc 1 127 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 130 0
	li	$5,-1342177280			# 0xffffffffb0000000
	ori	$3,$5,0x120
	li	$2,16			# 0x10
	sw	$2,0($3)
	.loc 1 131 0
	ori	$5,$5,0x128
	lw	$3,0($5)
	.loc 1 132 0
	li	$4,-65			# 0xffffffffffffffbf
	.loc 1 137 0
	move	$2,$0
	.loc 1 132 0
	and	$3,$3,$4
	.loc 1 133 0
	ori	$3,$3,0xb0
	.loc 1 134 0
	sw	$3,0($5)
	.loc 1 137 0
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE13:
	.end	do_reset
	.align	2
	.globl	flush_icache
	.ent	flush_icache
	.type	flush_icache, @function
flush_icache:
$LFB14:
	.loc 1 140 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
$LBB4:
	.loc 1 143 0
#APP
	.set	push
	.set	reorder
	mfc0	$2,$20
	.set	pop
#NO_APP
$LBE4:
	.loc 1 145 0
	li	$3,-3			# 0xfffffffffffffffd
	and	$3,$2,$3
#APP
	mtc0	$3,$20
	nop
	.loc 1 146 0
#NO_APP
	ori	$3,$2,0x2
#APP
	mtc0	$3,$20
	nop
	.loc 1 149 0
	.set	noreorder
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	.set	reorder
	
	.loc 1 159 0
	mtc0	$2,$20
	nop
#NO_APP
	j	$31
$LFE14:
	.end	flush_icache
	.align	2
	.globl	flush_dcache
	.ent	flush_dcache
	.type	flush_dcache, @function
flush_dcache:
$LFB15:
	.loc 1 163 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
$LBB5:
	.loc 1 166 0
#APP
	.set	push
	.set	reorder
	mfc0	$2,$20
	.set	pop
#NO_APP
$LBE5:
	.loc 1 168 0
	li	$3,-2			# 0xfffffffffffffffe
	and	$3,$2,$3
#APP
	mtc0	$3,$20
	nop
	.loc 1 169 0
#NO_APP
	ori	$3,$2,0x1
#APP
	mtc0	$3,$20
	nop
	.loc 1 172 0
	.set	noreorder
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	.set	reorder
	
	.loc 1 182 0
	mtc0	$2,$20
	nop
#NO_APP
	j	$31
$LFE15:
	.end	flush_dcache
	.align	2
	.globl	flush_cache
	.ent	flush_cache
	.type	flush_cache, @function
flush_cache:
$LFB16:
	.loc 1 187 0
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI0:
	sw	$31,32($sp)
$LCFI1:
	sw	$17,28($sp)
$LCFI2:
	sw	$16,24($sp)
$LCFI3:
	.cprestore	16
	.loc 1 190 0
	lw	$25,%call16(flush_icache_range)($28)
	.loc 1 188 0
	addu	$17,$4,$5
	.loc 1 190 0
	move	$5,$17
	.loc 1 187 0
	.loc 1 190 0
	jalr	$25
	move	$16,$4

	lw	$28,16($sp)
	.loc 1 191 0
	move	$4,$16
	move	$5,$17
	lw	$25,%call16(flush_dcache_range)($28)
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	jr	$25
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE16:
	.end	flush_cache
	.align	2
	.globl	write_one_tlb
	.ent	write_one_tlb
	.type	write_one_tlb, @function
write_one_tlb:
$LFB17:
	.loc 1 194 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.loc 1 194 0
	lw	$2,16($sp)
	.loc 1 195 0
#APP
	mtc0	$7,$2
	nop
	.loc 1 196 0
	mtc0	$5,$5
	nop
	.loc 1 197 0
	mtc0	$2,$3
	nop
	.loc 1 198 0
	mtc0	$6,$10
	nop
	.loc 1 199 0
	mtc0	$4,$0
	nop
	.loc 1 200 0
	.set noreorder
	tlbwi
	.set reorder
#NO_APP
	j	$31
$LFE17:
	.end	write_one_tlb
	.section	.debug_frame,"",@progbits
$Lframe0:
	.4byte	$LECIE0-$LSCIE0
$LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 4
	.byte	0x1f
	.byte	0xc
	.uleb128 0x1d
	.uleb128 0x0
	.align	2
$LECIE0:
$LSFDE0:
	.4byte	$LEFDE0-$LASFDE0
$LASFDE0:
	.4byte	$Lframe0
	.4byte	$LFB11
	.4byte	$LFE11-$LFB11
	.align	2
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB12
	.4byte	$LFE12-$LFB12
	.align	2
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB13
	.4byte	$LFE13-$LFB13
	.align	2
$LEFDE4:
$LSFDE6:
	.4byte	$LEFDE6-$LASFDE6
$LASFDE6:
	.4byte	$Lframe0
	.4byte	$LFB14
	.4byte	$LFE14-$LFB14
	.align	2
$LEFDE6:
$LSFDE8:
	.4byte	$LEFDE8-$LASFDE8
$LASFDE8:
	.4byte	$Lframe0
	.4byte	$LFB15
	.4byte	$LFE15-$LFB15
	.align	2
$LEFDE8:
$LSFDE10:
	.4byte	$LEFDE10-$LASFDE10
$LASFDE10:
	.4byte	$Lframe0
	.4byte	$LFB16
	.4byte	$LFE16-$LFB16
	.byte	0x4
	.4byte	$LCFI0-$LFB16
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI3-$LCFI0
	.byte	0x11
	.uleb128 0x10
	.sleb128 -4
	.byte	0x11
	.uleb128 0x11
	.sleb128 -3
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE10:
$LSFDE12:
	.4byte	$LEFDE12-$LASFDE12
$LASFDE12:
	.4byte	$Lframe0
	.4byte	$LFB17
	.4byte	$LFE17-$LFB17
	.align	2
$LEFDE12:
	.align	0
	.file 2 "/home/guohongliang/work/819/DIR819/build.DIR-819/boot/tbsboot/include/command.h"
	.file 3 "/home/guohongliang/work/819/DIR819/build.DIR-819/boot/tbsboot/include/types.h"
	.file 4 "/home/guohongliang/work/819/DIR819/build.DIR-819/boot/build/include2/asm/types.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x39e
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF38
	.byte	0x1
	.4byte	$LASF39
	.4byte	$LASF40
	.uleb128 0x2
	.4byte	$LASF0
	.byte	0x1
	.byte	0x8
	.uleb128 0x2
	.4byte	$LASF1
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF2
	.byte	0x2
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF3
	.byte	0x1
	.byte	0x6
	.uleb128 0x2
	.4byte	$LASF4
	.byte	0x2
	.byte	0x5
	.uleb128 0x3
	.ascii	"int\000"
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF6
	.byte	0x8
	.byte	0x5
	.uleb128 0x2
	.4byte	$LASF7
	.byte	0x8
	.byte	0x7
	.uleb128 0x4
	.ascii	"u32\000"
	.byte	0x4
	.byte	0x37
	.4byte	0x4f
	.uleb128 0x5
	.4byte	$LASF8
	.byte	0x3
	.byte	0x16
	.4byte	0x2c
	.uleb128 0x2
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF9
	.byte	0x1
	.byte	0x6
	.uleb128 0x6
	.byte	0x4
	.4byte	0x81
	.uleb128 0x7
	.4byte	0xef
	.4byte	$LASF41
	.byte	0x78
	.byte	0x2
	.byte	0x27
	.uleb128 0x8
	.4byte	$LASF10
	.byte	0x2
	.byte	0x28
	.4byte	0xef
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF11
	.byte	0x2
	.byte	0x29
	.4byte	0x48
	.byte	0x2
	.byte	0x10
	.uleb128 0x64
	.uleb128 0x8
	.4byte	$LASF12
	.byte	0x2
	.byte	0x2a
	.4byte	0x48
	.byte	0x2
	.byte	0x10
	.uleb128 0x68
	.uleb128 0x9
	.ascii	"cmd\000"
	.byte	0x2
	.byte	0x2c
	.4byte	0x12a
	.byte	0x2
	.byte	0x10
	.uleb128 0x6c
	.uleb128 0x8
	.4byte	$LASF13
	.byte	0x2
	.byte	0x2d
	.4byte	0x88
	.byte	0x2
	.byte	0x10
	.uleb128 0x70
	.uleb128 0x8
	.4byte	$LASF14
	.byte	0x2
	.byte	0x2f
	.4byte	0x88
	.byte	0x2
	.byte	0x10
	.uleb128 0x74
	.byte	0x0
	.uleb128 0xa
	.4byte	0xff
	.4byte	0x81
	.uleb128 0xb
	.4byte	0x7a
	.byte	0x63
	.byte	0x0
	.uleb128 0xc
	.4byte	0x11e
	.byte	0x1
	.4byte	0x48
	.uleb128 0xd
	.4byte	0x11e
	.uleb128 0xd
	.4byte	0x48
	.uleb128 0xd
	.4byte	0x48
	.uleb128 0xd
	.4byte	0x124
	.byte	0x0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x8e
	.uleb128 0x6
	.byte	0x4
	.4byte	0x88
	.uleb128 0x6
	.byte	0x4
	.4byte	0xff
	.uleb128 0x5
	.4byte	$LASF15
	.byte	0x2
	.byte	0x37
	.4byte	0x8e
	.uleb128 0x6
	.byte	0x4
	.4byte	0x130
	.uleb128 0xe
	.4byte	0x1b3
	.byte	0x1
	.4byte	$LASF20
	.byte	0x1
	.byte	0x5d
	.byte	0x1
	.4byte	$LFB11
	.4byte	$LFE11
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0xf
	.4byte	$LASF16
	.byte	0x1
	.byte	0x5c
	.4byte	0x2c
	.byte	0x1
	.byte	0x54
	.uleb128 0x10
	.ascii	"end\000"
	.byte	0x1
	.byte	0x5c
	.4byte	0x2c
	.byte	0x1
	.byte	0x55
	.uleb128 0x11
	.4byte	$LASF17
	.byte	0x1
	.byte	0x5e
	.4byte	0x2c
	.uleb128 0x12
	.4byte	$LASF18
	.byte	0x1
	.byte	0x5f
	.4byte	0x2c
	.byte	0x1
	.byte	0x54
	.uleb128 0x12
	.4byte	$LASF19
	.byte	0x1
	.byte	0x60
	.4byte	0x2c
	.byte	0x1
	.byte	0x55
	.uleb128 0x13
	.4byte	$LBB2
	.4byte	$LBE2
	.uleb128 0x14
	.ascii	"tmp\000"
	.byte	0x1
	.byte	0x6b
	.4byte	0x2c
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.4byte	0x225
	.byte	0x1
	.4byte	$LASF21
	.byte	0x1
	.byte	0x6f
	.byte	0x1
	.4byte	$LFB12
	.4byte	$LFE12
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0xf
	.4byte	$LASF16
	.byte	0x1
	.byte	0x6e
	.4byte	0x2c
	.byte	0x1
	.byte	0x54
	.uleb128 0x10
	.ascii	"end\000"
	.byte	0x1
	.byte	0x6e
	.4byte	0x2c
	.byte	0x1
	.byte	0x55
	.uleb128 0x11
	.4byte	$LASF17
	.byte	0x1
	.byte	0x70
	.4byte	0x2c
	.uleb128 0x12
	.4byte	$LASF18
	.byte	0x1
	.byte	0x71
	.4byte	0x2c
	.byte	0x1
	.byte	0x54
	.uleb128 0x12
	.4byte	$LASF19
	.byte	0x1
	.byte	0x72
	.4byte	0x2c
	.byte	0x1
	.byte	0x55
	.uleb128 0x13
	.4byte	$LBB3
	.4byte	$LBE3
	.uleb128 0x14
	.ascii	"tmp\000"
	.byte	0x1
	.byte	0x7b
	.4byte	0x2c
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.4byte	0x286
	.byte	0x1
	.4byte	$LASF22
	.byte	0x1
	.byte	0x7f
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB13
	.4byte	$LFE13
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0xf
	.4byte	$LASF23
	.byte	0x1
	.byte	0x7e
	.4byte	0x13b
	.byte	0x1
	.byte	0x54
	.uleb128 0xf
	.4byte	$LASF24
	.byte	0x1
	.byte	0x7e
	.4byte	0x48
	.byte	0x1
	.byte	0x55
	.uleb128 0xf
	.4byte	$LASF25
	.byte	0x1
	.byte	0x7e
	.4byte	0x48
	.byte	0x1
	.byte	0x56
	.uleb128 0xf
	.4byte	$LASF26
	.byte	0x1
	.byte	0x7e
	.4byte	0x124
	.byte	0x1
	.byte	0x57
	.uleb128 0x12
	.4byte	$LASF27
	.byte	0x1
	.byte	0x80
	.4byte	0x4f
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0xe
	.4byte	0x2c6
	.byte	0x1
	.4byte	$LASF28
	.byte	0x1
	.byte	0x8c
	.byte	0x1
	.4byte	$LFB14
	.4byte	$LFE14
	.4byte	$LSFDE6
	.byte	0x1
	.byte	0x6d
	.uleb128 0x12
	.4byte	$LASF29
	.byte	0x1
	.byte	0x8d
	.4byte	0x4f
	.byte	0x1
	.byte	0x52
	.uleb128 0x13
	.4byte	$LBB4
	.4byte	$LBE4
	.uleb128 0x12
	.4byte	$LASF30
	.byte	0x1
	.byte	0x8f
	.4byte	0x48
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.4byte	0x306
	.byte	0x1
	.4byte	$LASF31
	.byte	0x1
	.byte	0xa3
	.byte	0x1
	.4byte	$LFB15
	.4byte	$LFE15
	.4byte	$LSFDE8
	.byte	0x1
	.byte	0x6d
	.uleb128 0x12
	.4byte	$LASF29
	.byte	0x1
	.byte	0xa4
	.4byte	0x4f
	.byte	0x1
	.byte	0x52
	.uleb128 0x13
	.4byte	$LBB5
	.4byte	$LBE5
	.uleb128 0x12
	.4byte	$LASF30
	.byte	0x1
	.byte	0xa6
	.4byte	0x48
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.4byte	0x349
	.byte	0x1
	.4byte	$LASF32
	.byte	0x1
	.byte	0xbb
	.byte	0x1
	.4byte	$LFB16
	.4byte	$LFE16
	.4byte	$LSFDE10
	.byte	0x1
	.byte	0x6d
	.uleb128 0xf
	.4byte	$LASF16
	.byte	0x1
	.byte	0xba
	.4byte	0x6f
	.byte	0x1
	.byte	0x60
	.uleb128 0xf
	.4byte	$LASF33
	.byte	0x1
	.byte	0xba
	.4byte	0x6f
	.byte	0x1
	.byte	0x55
	.uleb128 0x14
	.ascii	"end\000"
	.byte	0x1
	.byte	0xbc
	.4byte	0x2c
	.byte	0x1
	.byte	0x61
	.byte	0x0
	.uleb128 0x16
	.byte	0x1
	.4byte	$LASF42
	.byte	0x1
	.byte	0xc2
	.byte	0x1
	.4byte	$LFB17
	.4byte	$LFE17
	.4byte	$LSFDE12
	.byte	0x1
	.byte	0x6d
	.uleb128 0xf
	.4byte	$LASF34
	.byte	0x1
	.byte	0xc2
	.4byte	0x48
	.byte	0x1
	.byte	0x54
	.uleb128 0xf
	.4byte	$LASF35
	.byte	0x1
	.byte	0xc2
	.4byte	0x64
	.byte	0x1
	.byte	0x55
	.uleb128 0x10
	.ascii	"hi\000"
	.byte	0x1
	.byte	0xc2
	.4byte	0x64
	.byte	0x1
	.byte	0x56
	.uleb128 0xf
	.4byte	$LASF36
	.byte	0x1
	.byte	0xc2
	.4byte	0x64
	.byte	0x1
	.byte	0x57
	.uleb128 0xf
	.4byte	$LASF37
	.byte	0x1
	.byte	0xc2
	.4byte	0x64
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x2001
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x2001
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x2001
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x8d
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x3a2
	.4byte	0x141
	.ascii	"flush_icache_range\000"
	.4byte	0x1b3
	.ascii	"flush_dcache_range\000"
	.4byte	0x225
	.ascii	"do_reset\000"
	.4byte	0x286
	.ascii	"flush_icache\000"
	.4byte	0x2c6
	.ascii	"flush_dcache\000"
	.4byte	0x306
	.ascii	"flush_cache\000"
	.4byte	0x349
	.ascii	"write_one_tlb\000"
	.4byte	0x0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",@progbits,1
$LASF9:
	.ascii	"char\000"
$LASF32:
	.ascii	"flush_cache\000"
$LASF29:
	.ascii	"controlReg\000"
$LASF22:
	.ascii	"do_reset\000"
$LASF34:
	.ascii	"index\000"
$LASF11:
	.ascii	"maxargs\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF27:
	.ascii	"value\000"
$LASF28:
	.ascii	"flush_icache\000"
$LASF38:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF20:
	.ascii	"flush_icache_range\000"
$LASF35:
	.ascii	"pagemask\000"
$LASF40:
	.ascii	"/home/guohongliang/work/819/DIR819/build.DIR-819/boot/tb"
	.ascii	"sboot/cpu/mt7620a\000"
$LASF12:
	.ascii	"repeatable\000"
$LASF6:
	.ascii	"long long int\000"
$LASF42:
	.ascii	"write_one_tlb\000"
$LASF31:
	.ascii	"flush_dcache\000"
$LASF41:
	.ascii	"cmd_tbl_s\000"
$LASF15:
	.ascii	"cmd_tbl_t\000"
$LASF33:
	.ascii	"size\000"
$LASF39:
	.ascii	"cpu.c\000"
$LASF25:
	.ascii	"argc\000"
$LASF26:
	.ascii	"argv\000"
$LASF4:
	.ascii	"short int\000"
$LASF24:
	.ascii	"flag\000"
$LASF23:
	.ascii	"cmdtp\000"
$LASF8:
	.ascii	"ulong\000"
$LASF13:
	.ascii	"usage\000"
$LASF18:
	.ascii	"addr\000"
$LASF10:
	.ascii	"name\000"
$LASF16:
	.ascii	"start\000"
$LASF36:
	.ascii	"low0\000"
$LASF37:
	.ascii	"low1\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF14:
	.ascii	"help\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF21:
	.ascii	"flush_dcache_range\000"
$LASF19:
	.ascii	"aend\000"
$LASF3:
	.ascii	"signed char\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF30:
	.ascii	"__res\000"
$LASF17:
	.ascii	"lsize\000"
	.ident	"GCC: (GNU) 3.4.2"
