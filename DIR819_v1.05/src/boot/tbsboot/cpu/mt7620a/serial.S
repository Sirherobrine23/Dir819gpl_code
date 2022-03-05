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
	.globl	serial_setbrg
	.ent	serial_setbrg
	.type	serial_setbrg, @function
serial_setbrg:
$LFB8:
	.file 1 "serial.c"
	.loc 1 40 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	.loc 1 45 0
	li	$2,-1342177280			# 0xffffffffb0000000
	ori	$2,$2,0x10
	lw	$3,0($2)
	.loc 1 50 0
	lw	$3,0($2)
	.loc 1 51 0
	srl	$2,$3,4
	andi	$2,$2,0x3
	bne	$2,$0,$L2
	lw	$3,%got(mips_bus_feq)($28)

	.loc 1 57 0
	li	$2,149946368			# 0x8f00000
	b	$L4
	ori	$2,$2,0xd180

$L2:
	.loc 1 61 0
	li	$2,199950336			# 0xbeb0000
	ori	$2,$2,0xc200
$L4:
	sw	$2,0($3)
	.loc 1 65 0
	li	$2,-1342177280			# 0xffffffffb0000000
	.loc 1 72 0
	ori	$3,$2,0xc08
	sw	$0,0($3)
	.loc 1 76 0
	ori	$6,$2,0xc14
	.loc 1 73 0
	ori	$4,$2,0xc10
	.loc 1 76 0
	li	$3,131			# 0x83
	.loc 1 73 0
	sw	$0,0($4)
	.loc 1 78 0
	ori	$7,$2,0xc30
	.loc 1 76 0
	sw	$3,0($6)
	.loc 1 65 0
	ori	$5,$2,0x34
	.loc 1 77 0
	li	$3,21			# 0x15
	ori	$2,$2,0xc2c
	sw	$3,0($2)
	.loc 1 79 0
	li	$2,3			# 0x3
	.loc 1 78 0
	sw	$0,0($7)
	.loc 1 67 0
	sw	$0,0($5)
	.loc 1 79 0
	sw	$2,0($6)
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE8:
	.end	serial_setbrg
	.align	2
	.globl	serial_init
	.ent	serial_init
	.type	serial_init, @function
serial_init:
$LFB9:
	.loc 1 88 0
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 16, gp= 8
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI0:
	sw	$31,24($sp)
$LCFI1:
	.cprestore	16
	.loc 1 89 0
	lw	$25,%call16(serial_setbrg)($28)
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 91 0
	lw	$31,24($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE9:
	.end	serial_init
	.align	2
	.globl	serial_putc
	.ent	serial_putc
	.type	serial_putc, @function
serial_putc:
$LFB10:
	.loc 1 97 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	li	$5,-1342177280			# 0xffffffffb0000000
	.loc 1 97 0
	sll	$4,$4,24
	sra	$4,$4,24
	ori	$3,$5,0xc1c
$L7:
	.loc 1 99 0
	lw	$2,0($3)
	srl	$2,$2,6
	xori	$2,$2,0x1
	andi	$2,$2,0x1
	.loc 1 101 0
	.loc 1 99 0
	bne	$2,$0,$L7
	ori	$2,$5,0xc04

	.loc 1 101 0
	sw	$4,0($2)
	.loc 1 104 0
	li	$2,10			# 0xa
	.loc 1 105 0
	.loc 1 104 0
	bne	$4,$2,$L10
	lw	$25,%call16(serial_putc)($28)

	.loc 1 105 0
	jr	$25
	li	$4,13			# 0xd

$L10:
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE10:
	.end	serial_putc
	.align	2
	.globl	serial_tstc
	.ent	serial_tstc
	.type	serial_tstc, @function
serial_tstc:
$LFB11:
	.loc 1 114 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 115 0
	li	$2,-1342177280			# 0xffffffffb0000000
	ori	$2,$2,0xc1c
	lw	$2,0($2)
	.loc 1 116 0
	j	$31
	andi	$2,$2,0x1

	.set	macro
	.set	reorder
$LFE11:
	.end	serial_tstc
	.align	2
	.globl	serial_getc
	.ent	serial_getc
	.type	serial_getc, @function
serial_getc:
$LFB12:
	.loc 1 124 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 126 0
	li	$2,-1342177280			# 0xffffffffb0000000
	ori	$3,$2,0xc1c
	lw	$3,0($3)
	.loc 1 130 0
	ori	$4,$2,0xc00
	.loc 1 126 0
	andi	$3,$3,0x1
	.loc 1 128 0
	.loc 1 127 0
	beq	$3,$0,$L15
	move	$2,$0

	.loc 1 130 0
	lw	$2,0($4)
	andi	$2,$2,0x00ff
$L15:
	.loc 1 137 0
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE12:
	.end	serial_getc
	.align	2
	.globl	serial_puts
	.ent	serial_puts
	.type	serial_puts, @function
serial_puts:
$LFB13:
	.loc 1 141 0
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI2:
	sw	$31,28($sp)
$LCFI3:
	sw	$16,24($sp)
$LCFI4:
	.cprestore	16
	.loc 1 141 0
	move	$16,$4
$L22:
	.loc 1 143 0
	lbu	$4,0($16)
	beq	$4,$0,$L21
	lw	$25,%call16(serial_putc)($28)

	sll	$4,$4,24
	jalr	$25
	sra	$4,$4,24

	lw	$28,16($sp)
	b	$L22
	addiu	$16,$16,1

$L21:
	lw	$31,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE13:
	.end	serial_puts

	.comm	mips_bus_feq,4,4
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
	.4byte	$LFB8
	.4byte	$LFE8-$LFB8
	.align	2
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB9
	.4byte	$LFE9-$LFB9
	.byte	0x4
	.4byte	$LCFI0-$LFB9
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI1-$LCFI0
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB10
	.4byte	$LFE10-$LFB10
	.align	2
$LEFDE4:
$LSFDE6:
	.4byte	$LEFDE6-$LASFDE6
$LASFDE6:
	.4byte	$Lframe0
	.4byte	$LFB11
	.4byte	$LFE11-$LFB11
	.align	2
$LEFDE6:
$LSFDE8:
	.4byte	$LEFDE8-$LASFDE8
$LASFDE8:
	.4byte	$Lframe0
	.4byte	$LFB12
	.4byte	$LFE12-$LFB12
	.align	2
$LEFDE8:
$LSFDE10:
	.4byte	$LEFDE10-$LASFDE10
$LASFDE10:
	.4byte	$Lframe0
	.4byte	$LFB13
	.4byte	$LFE13-$LFB13
	.byte	0x4
	.4byte	$LCFI2-$LFB13
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI4-$LCFI2
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE10:
	.align	0
	.file 2 "/home/xieshijing/DIR819-96920/DIR819_1.05/DIR819/build.DIR-809/boot/build/include2/asm/types.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x189
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF19
	.byte	0x1
	.4byte	$LASF20
	.4byte	$LASF21
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
	.byte	0x2
	.byte	0x37
	.4byte	0x4f
	.uleb128 0x2
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF8
	.byte	0x1
	.byte	0x6
	.uleb128 0x5
	.4byte	0xbe
	.byte	0x1
	.4byte	$LASF11
	.byte	0x1
	.byte	0x28
	.byte	0x1
	.4byte	$LFB8
	.4byte	$LFE8
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0x6
	.4byte	$LASF9
	.byte	0x1
	.byte	0x2a
	.4byte	0x4f
	.byte	0x1
	.byte	0x53
	.uleb128 0x7
	.ascii	"reg\000"
	.byte	0x1
	.byte	0x2c
	.4byte	0x64
	.byte	0x1
	.byte	0x53
	.uleb128 0x8
	.4byte	$LASF10
	.byte	0x1
	.byte	0x2c
	.4byte	0x64
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.4byte	$LASF13
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB9
	.4byte	$LFE9
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0x5
	.4byte	0x100
	.byte	0x1
	.4byte	$LASF12
	.byte	0x1
	.byte	0x61
	.byte	0x1
	.4byte	$LFB10
	.4byte	$LFE10
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0xa
	.ascii	"c\000"
	.byte	0x1
	.byte	0x60
	.4byte	0x100
	.byte	0x1
	.byte	0x54
	.byte	0x0
	.uleb128 0xb
	.4byte	0x76
	.uleb128 0x9
	.byte	0x1
	.4byte	$LASF14
	.byte	0x1
	.byte	0x72
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB11
	.4byte	$LFE11
	.4byte	$LSFDE6
	.byte	0x1
	.byte	0x6d
	.uleb128 0xc
	.4byte	0x14d
	.byte	0x1
	.4byte	$LASF15
	.byte	0x1
	.byte	0x7c
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB12
	.4byte	$LFE12
	.4byte	$LSFDE8
	.byte	0x1
	.byte	0x6d
	.uleb128 0x6
	.4byte	$LASF16
	.byte	0x1
	.byte	0x7d
	.4byte	0x4f
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x5
	.4byte	0x174
	.byte	0x1
	.4byte	$LASF17
	.byte	0x1
	.byte	0x8d
	.byte	0x1
	.4byte	$LFB13
	.4byte	$LFE13
	.4byte	$LSFDE10
	.byte	0x1
	.byte	0x6d
	.uleb128 0xa
	.ascii	"s\000"
	.byte	0x1
	.byte	0x8c
	.4byte	0x174
	.byte	0x1
	.byte	0x60
	.byte	0x0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x100
	.uleb128 0xe
	.4byte	$LASF18
	.byte	0x1
	.byte	0x24
	.4byte	0x2c
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	mips_bus_feq
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x0
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
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x81
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x18d
	.4byte	0x7d
	.ascii	"serial_setbrg\000"
	.4byte	0xbe
	.ascii	"serial_init\000"
	.4byte	0xd9
	.ascii	"serial_putc\000"
	.4byte	0x105
	.ascii	"serial_tstc\000"
	.4byte	0x120
	.ascii	"serial_getc\000"
	.4byte	0x14d
	.ascii	"serial_puts\000"
	.4byte	0x17a
	.ascii	"mips_bus_feq\000"
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
$LASF8:
	.ascii	"char\000"
$LASF18:
	.ascii	"mips_bus_feq\000"
$LASF13:
	.ascii	"serial_init\000"
$LASF11:
	.ascii	"serial_setbrg\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF19:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF9:
	.ascii	"clock_divisor\000"
$LASF12:
	.ascii	"serial_putc\000"
$LASF6:
	.ascii	"long long int\000"
$LASF21:
	.ascii	"/home/xieshijing/DIR819-96920/DIR819_1.05/DIR819/build.D"
	.ascii	"IR-809/boot/tbsboot/cpu/mt7620a\000"
$LASF4:
	.ascii	"short int\000"
$LASF16:
	.ascii	"status\000"
$LASF14:
	.ascii	"serial_tstc\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF10:
	.ascii	"cpu_clock\000"
$LASF15:
	.ascii	"serial_getc\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF17:
	.ascii	"serial_puts\000"
$LASF20:
	.ascii	"serial.c\000"
$LASF3:
	.ascii	"signed char\000"
$LASF2:
	.ascii	"short unsigned int\000"
	.ident	"GCC: (GNU) 3.4.2"
