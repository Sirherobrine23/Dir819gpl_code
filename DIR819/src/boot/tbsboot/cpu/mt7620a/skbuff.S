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
	.local	skb_cur
	.comm	skb_cur,4,4
	.align	2
	.ent	skb_headerinit
	.type	skb_headerinit, @function
skb_headerinit:
$LFB2:
	.file 1 "skbuff.c"
	.loc 1 10 0
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
	.loc 1 11 0
	li	$2,536805376			# 0x1fff0000
	ori	$2,$2,0xffff
	and	$2,$4,$2
	.loc 1 12 0
	lw	$25,%call16(memset)($28)
	.loc 1 11 0
	li	$3,-1610612736			# 0xffffffffa0000000
	or	$2,$2,$3
	.loc 1 10 0
	move	$16,$4
	andi	$17,$5,0x00ff
	.loc 1 11 0
	sw	$2,1600($4)
	.loc 1 12 0
	li	$6,1600			# 0x640
	jalr	$25
	move	$5,$0

	.loc 1 14 0
	sh	$17,1606($16)
	.loc 1 12 0
	lw	$28,16($sp)
	.loc 1 13 0
	sh	$0,1604($16)
	.loc 1 14 0
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE2:
	.end	skb_headerinit
	.align	2
	.globl	skb_init
	.ent	skb_init
	.type	skb_init, @function
skb_init:
$LFB3:
	.loc 1 18 0
	.frame	$sp,48,$31		# vars= 0, regs= 5/0, args= 16, gp= 8
	.mask	0x800f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-48
$LCFI4:
	sw	$31,40($sp)
$LCFI5:
	sw	$19,36($sp)
$LCFI6:
	sw	$18,32($sp)
$LCFI7:
	sw	$17,28($sp)
$LCFI8:
	sw	$16,24($sp)
$LCFI9:
	.cprestore	16
	.loc 1 24 0
	lw	$19,%got(skbuff)($28)
	.loc 1 21 0
	li	$2,-12			# 0xfffffffffffffff4
	.loc 1 24 0
	.loc 1 25 0
	beq	$4,$0,$L3
	sw	$4,%lo(skbuff)($19)

	move	$18,$0
	li	$17,255			# 0xff
$L7:
	.loc 1 27 0
	lw	$16,%lo(skbuff)($19)
	.loc 1 28 0
	lw	$25,%call16(memset)($28)
	move	$5,$0
	.loc 1 27 0
	addu	$16,$16,$18
	.loc 1 28 0
	move	$4,$16
	jalr	$25
	li	$6,1608			# 0x648

	lw	$28,16($sp)
	.loc 1 29 0
	move	$4,$16
	move	$5,$0
	lw	$25,%got(skb_headerinit)($28)
	.loc 1 26 0
	addiu	$17,$17,-1
	.loc 1 29 0
	addiu	$25,$25,%lo(skb_headerinit)
	jalr	$25
	addiu	$18,$18,1608

	bgez	$17,$L7
	lw	$28,16($sp)

	.loc 1 31 0
	move	$2,$0
$L3:
	.loc 1 35 0
	lw	$31,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
$LFE3:
	.end	skb_init
	.align	2
	.globl	alloc_skb
	.ent	alloc_skb
	.type	alloc_skb, @function
alloc_skb:
$LFB4:
	.loc 1 38 0
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI10:
	sw	$31,28($sp)
$LCFI11:
	sw	$16,24($sp)
$LCFI12:
	.cprestore	16
	lw	$7,%got(skb_cur)($28)
	lw	$2,%got(skbuff)($28)
	.loc 1 42 0
	move	$4,$0
	lw	$5,%lo(skb_cur)($7)
	lw	$6,%lo(skbuff)($2)
	li	$8,1			# 0x1
	.loc 1 43 0
	sll	$2,$5,1
$L20:
	addu	$2,$2,$5
	sll	$2,$2,3
	addu	$2,$2,$5
	sll	$2,$2,3
	addu	$2,$2,$5
	sll	$2,$2,3
	addu	$16,$6,$2
	.loc 1 45 0
	lhu	$3,1606($16)
	.loc 1 44 0
	addiu	$2,$5,1
	.loc 1 45 0
	bne	$3,$8,$L19
	andi	$5,$2,0xff

	.loc 1 42 0
	addiu	$4,$4,1
	slt	$2,$4,256
	.loc 1 43 0
	.loc 1 42 0
	bne	$2,$0,$L20
	sll	$2,$5,1

$L19:
	.loc 1 49 0
	li	$2,256			# 0x100
	bne	$4,$2,$L16
	sw	$5,%lo(skb_cur)($7)

	.loc 1 50 0
	b	$L17
	move	$16,$0

$L16:
	.loc 1 52 0
	lw	$25,%got(skb_headerinit)($28)
	move	$4,$16
	addiu	$25,$25,%lo(skb_headerinit)
	jalr	$25
	li	$5,1			# 0x1

	lw	$28,16($sp)
$L17:
	.loc 1 56 0
	move	$2,$16
	lw	$31,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE4:
	.end	alloc_skb
	.align	2
	.globl	free_skb
	.ent	free_skb
	.type	free_skb, @function
free_skb:
$LFB5:
	.loc 1 59 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	.loc 1 60 0
	lw	$25,%got(skb_headerinit)($28)
	addiu	$25,$25,%lo(skb_headerinit)
	jr	$25
	move	$5,$0

	.set	macro
	.set	reorder
$LFE5:
	.end	free_skb
	.align	2
	.globl	skb_put
	.ent	skb_put
	.type	skb_put, @function
skb_put:
$LFB6:
	.loc 1 64 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 65 0
	lhu	$3,1604($4)
	.loc 1 67 0
	lw	$2,1600($4)
	.loc 1 65 0
	addu	$5,$5,$3
	.loc 1 67 0
	j	$31
	sh	$5,1604($4)

	.set	macro
	.set	reorder
$LFE6:
	.end	skb_put
	.align	2
	.globl	skb_pull
	.ent	skb_pull
	.type	skb_pull, @function
skb_pull:
$LFB7:
	.loc 1 70 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 71 0
	lw	$2,1600($4)
	.loc 1 72 0
	lhu	$3,1604($4)
	.loc 1 71 0
	addu	$2,$2,$5
	.loc 1 72 0
	subu	$3,$3,$5
	sh	$3,1604($4)
	.loc 1 71 0
	.loc 1 74 0
	j	$31
	sw	$2,1600($4)

	.set	macro
	.set	reorder
$LFE7:
	.end	skb_pull
	.align	2
	.globl	skb_push
	.ent	skb_push
	.type	skb_push, @function
skb_push:
$LFB8:
	.loc 1 77 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 78 0
	lw	$2,1600($4)
	.loc 1 79 0
	lhu	$3,1604($4)
	.loc 1 78 0
	subu	$2,$2,$5
	.loc 1 79 0
	addu	$5,$5,$3
	sh	$5,1604($4)
	.loc 1 78 0
	.loc 1 81 0
	j	$31
	sw	$2,1600($4)

	.set	macro
	.set	reorder
$LFE8:
	.end	skb_push
	.align	2
	.globl	skb_reserve
	.ent	skb_reserve
	.type	skb_reserve, @function
skb_reserve:
$LFB9:
	.loc 1 84 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 85 0
	lw	$2,1600($4)
	addu	$2,$2,$5
	j	$31
	sw	$2,1600($4)

	.set	macro
	.set	reorder
$LFE9:
	.end	skb_reserve
	.local	skbuff
	.comm	skbuff,4,4
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
	.4byte	$LFB2
	.4byte	$LFE2-$LFB2
	.byte	0x4
	.4byte	$LCFI0-$LFB2
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
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB3
	.4byte	$LFE3-$LFB3
	.byte	0x4
	.4byte	$LCFI4-$LFB3
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.4byte	$LCFI9-$LCFI4
	.byte	0x11
	.uleb128 0x10
	.sleb128 -6
	.byte	0x11
	.uleb128 0x11
	.sleb128 -5
	.byte	0x11
	.uleb128 0x12
	.sleb128 -4
	.byte	0x11
	.uleb128 0x13
	.sleb128 -3
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB4
	.4byte	$LFE4-$LFB4
	.byte	0x4
	.4byte	$LCFI10-$LFB4
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI12-$LCFI10
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE4:
$LSFDE6:
	.4byte	$LEFDE6-$LASFDE6
$LASFDE6:
	.4byte	$Lframe0
	.4byte	$LFB5
	.4byte	$LFE5-$LFB5
	.align	2
$LEFDE6:
$LSFDE8:
	.4byte	$LEFDE8-$LASFDE8
$LASFDE8:
	.4byte	$Lframe0
	.4byte	$LFB6
	.4byte	$LFE6-$LFB6
	.align	2
$LEFDE8:
$LSFDE10:
	.4byte	$LEFDE10-$LASFDE10
$LASFDE10:
	.4byte	$Lframe0
	.4byte	$LFB7
	.4byte	$LFE7-$LFB7
	.align	2
$LEFDE10:
$LSFDE12:
	.4byte	$LEFDE12-$LASFDE12
$LASFDE12:
	.4byte	$Lframe0
	.4byte	$LFB8
	.4byte	$LFE8-$LFB8
	.align	2
$LEFDE12:
$LSFDE14:
	.4byte	$LEFDE14-$LASFDE14
$LASFDE14:
	.4byte	$Lframe0
	.4byte	$LFB9
	.4byte	$LFE9-$LFB9
	.align	2
$LEFDE14:
	.align	0
	.file 2 "skbuff.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x2d0
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF24
	.byte	0x1
	.4byte	$LASF25
	.4byte	$LASF26
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
	.uleb128 0x2
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF8
	.byte	0x1
	.byte	0x6
	.uleb128 0x4
	.byte	0x4
	.4byte	0x25
	.uleb128 0x5
	.4byte	0xc1
	.4byte	$LASF27
	.2byte	0x648
	.byte	0x2
	.byte	0x5
	.uleb128 0x6
	.ascii	"buf\000"
	.byte	0x2
	.byte	0x6
	.4byte	0xc1
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x7
	.4byte	$LASF9
	.byte	0x2
	.byte	0x7
	.4byte	0x72
	.byte	0x3
	.byte	0x10
	.uleb128 0x640
	.uleb128 0x6
	.ascii	"len\000"
	.byte	0x2
	.byte	0x8
	.4byte	0x33
	.byte	0x3
	.byte	0x10
	.uleb128 0x644
	.uleb128 0x7
	.4byte	$LASF10
	.byte	0x2
	.byte	0x9
	.4byte	0x33
	.byte	0x3
	.byte	0x10
	.uleb128 0x646
	.byte	0x0
	.uleb128 0x8
	.4byte	0xd2
	.4byte	0x25
	.uleb128 0x9
	.4byte	0x64
	.2byte	0x63f
	.byte	0x0
	.uleb128 0xa
	.4byte	0x107
	.4byte	$LASF28
	.byte	0x1
	.byte	0xa
	.byte	0x1
	.4byte	$LFB2
	.4byte	$LFE2
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0xb
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x9
	.4byte	0x107
	.byte	0x1
	.byte	0x60
	.uleb128 0xc
	.4byte	$LASF11
	.byte	0x1
	.byte	0x9
	.4byte	0x25
	.byte	0x1
	.byte	0x61
	.byte	0x0
	.uleb128 0x4
	.byte	0x4
	.4byte	0x78
	.uleb128 0xd
	.4byte	0x15f
	.byte	0x1
	.4byte	$LASF14
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB3
	.4byte	$LFE3
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0xc
	.4byte	$LASF12
	.byte	0x1
	.byte	0x11
	.4byte	0x72
	.byte	0x1
	.byte	0x54
	.uleb128 0xe
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x13
	.4byte	0x107
	.byte	0x1
	.byte	0x60
	.uleb128 0xe
	.ascii	"i\000"
	.byte	0x1
	.byte	0x14
	.4byte	0x48
	.byte	0x1
	.byte	0x61
	.uleb128 0xf
	.4byte	$LASF13
	.byte	0x1
	.byte	0x15
	.4byte	0x48
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.uleb128 0xd
	.4byte	0x1a4
	.byte	0x1
	.4byte	$LASF15
	.byte	0x1
	.byte	0x26
	.byte	0x1
	.4byte	0x107
	.4byte	$LFB4
	.4byte	$LFE4
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0xc
	.4byte	$LASF16
	.byte	0x1
	.byte	0x25
	.4byte	0x4f
	.byte	0x1
	.byte	0x54
	.uleb128 0xe
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x27
	.4byte	0x107
	.byte	0x1
	.byte	0x60
	.uleb128 0xe
	.ascii	"i\000"
	.byte	0x1
	.byte	0x28
	.4byte	0x48
	.byte	0x1
	.byte	0x54
	.byte	0x0
	.uleb128 0x10
	.4byte	0x1cd
	.byte	0x1
	.4byte	$LASF17
	.byte	0x1
	.byte	0x3b
	.byte	0x1
	.4byte	$LFB5
	.4byte	$LFE5
	.4byte	$LSFDE6
	.byte	0x1
	.byte	0x6d
	.uleb128 0xb
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x3a
	.4byte	0x107
	.byte	0x1
	.byte	0x54
	.byte	0x0
	.uleb128 0xd
	.4byte	0x207
	.byte	0x1
	.4byte	$LASF18
	.byte	0x1
	.byte	0x40
	.byte	0x1
	.4byte	0x72
	.4byte	$LFB6
	.4byte	$LFE6
	.4byte	$LSFDE8
	.byte	0x1
	.byte	0x6d
	.uleb128 0xb
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x3f
	.4byte	0x107
	.byte	0x1
	.byte	0x54
	.uleb128 0xb
	.ascii	"len\000"
	.byte	0x1
	.byte	0x3f
	.4byte	0x4f
	.byte	0x1
	.byte	0x55
	.byte	0x0
	.uleb128 0xd
	.4byte	0x241
	.byte	0x1
	.4byte	$LASF19
	.byte	0x1
	.byte	0x46
	.byte	0x1
	.4byte	0x72
	.4byte	$LFB7
	.4byte	$LFE7
	.4byte	$LSFDE10
	.byte	0x1
	.byte	0x6d
	.uleb128 0xb
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x45
	.4byte	0x107
	.byte	0x1
	.byte	0x54
	.uleb128 0xb
	.ascii	"len\000"
	.byte	0x1
	.byte	0x45
	.4byte	0x4f
	.byte	0x1
	.byte	0x55
	.byte	0x0
	.uleb128 0xd
	.4byte	0x27b
	.byte	0x1
	.4byte	$LASF20
	.byte	0x1
	.byte	0x4d
	.byte	0x1
	.4byte	0x72
	.4byte	$LFB8
	.4byte	$LFE8
	.4byte	$LSFDE12
	.byte	0x1
	.byte	0x6d
	.uleb128 0xb
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x4c
	.4byte	0x107
	.byte	0x1
	.byte	0x54
	.uleb128 0xb
	.ascii	"len\000"
	.byte	0x1
	.byte	0x4c
	.4byte	0x4f
	.byte	0x1
	.byte	0x55
	.byte	0x0
	.uleb128 0x10
	.4byte	0x2b1
	.byte	0x1
	.4byte	$LASF21
	.byte	0x1
	.byte	0x54
	.byte	0x1
	.4byte	$LFB9
	.4byte	$LFE9
	.4byte	$LSFDE14
	.byte	0x1
	.byte	0x6d
	.uleb128 0xb
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x53
	.4byte	0x107
	.byte	0x1
	.byte	0x54
	.uleb128 0xb
	.ascii	"len\000"
	.byte	0x1
	.byte	0x53
	.4byte	0x4f
	.byte	0x1
	.byte	0x55
	.byte	0x0
	.uleb128 0xf
	.4byte	$LASF22
	.byte	0x1
	.byte	0x6
	.4byte	0x107
	.byte	0x5
	.byte	0x3
	.4byte	skbuff
	.uleb128 0xf
	.4byte	$LASF23
	.byte	0x1
	.byte	0x7
	.4byte	0x4f
	.byte	0x5
	.byte	0x3
	.4byte	skb_cur
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
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
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
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x6c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x2d4
	.4byte	0x10d
	.ascii	"skb_init\000"
	.4byte	0x15f
	.ascii	"alloc_skb\000"
	.4byte	0x1a4
	.ascii	"free_skb\000"
	.4byte	0x1cd
	.ascii	"skb_put\000"
	.4byte	0x207
	.ascii	"skb_pull\000"
	.4byte	0x241
	.ascii	"skb_push\000"
	.4byte	0x27b
	.ascii	"skb_reserve\000"
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
$LASF21:
	.ascii	"skb_reserve\000"
$LASF3:
	.ascii	"signed char\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF6:
	.ascii	"long long int\000"
$LASF28:
	.ascii	"skb_headerinit\000"
$LASF20:
	.ascii	"skb_push\000"
$LASF9:
	.ascii	"data\000"
$LASF16:
	.ascii	"size\000"
$LASF13:
	.ascii	"ret_val\000"
$LASF23:
	.ascii	"skb_cur\000"
$LASF17:
	.ascii	"free_skb\000"
$LASF27:
	.ascii	"sk_buff_s\000"
$LASF26:
	.ascii	"/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tb"
	.ascii	"sboot/cpu/mt7620a\000"
$LASF25:
	.ascii	"skbuff.c\000"
$LASF12:
	.ascii	"sk_pool\000"
$LASF10:
	.ascii	"used\000"
$LASF14:
	.ascii	"skb_init\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF18:
	.ascii	"skb_put\000"
$LASF4:
	.ascii	"short int\000"
$LASF15:
	.ascii	"alloc_skb\000"
$LASF11:
	.ascii	"flag\000"
$LASF8:
	.ascii	"char\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF19:
	.ascii	"skb_pull\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF24:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF22:
	.ascii	"skbuff\000"
	.ident	"GCC: (GNU) 3.4.2"
