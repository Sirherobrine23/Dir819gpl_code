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
	.local	gpio_data_grp1
	.comm	gpio_data_grp1,4,4
	.align	2
	.ent	get_gpio_para
	.type	get_gpio_para, @function
get_gpio_para:
$LFB2:
	.file 1 "gpio_boot.c"
	.loc 1 12 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	.loc 1 14 0
	sltu	$2,$4,161
	.loc 1 13 0
	.loc 1 14 0
	beq	$2,$0,$L3
	move	$6,$0

	.loc 1 17 0
	sltu	$2,$4,24
	.loc 1 18 0
	.loc 1 17 0
	beq	$2,$0,$L4
	lw	$6,%got(mt7620a_gpios)($28)

	.loc 1 19 0
	li	$2,1			# 0x1
	b	$L13
	sll	$2,$2,$4

$L4:
	.loc 1 20 0
	sltu	$2,$4,40
	.loc 1 22 0
	.loc 1 20 0
	beq	$2,$0,$L6
	addiu	$2,$4,-24

	.loc 1 22 0
	li	$3,1			# 0x1
	sll	$3,$3,$2
	.loc 1 21 0
	lw	$2,%got(mt7620a_gpios)($28)
	b	$L12
	addiu	$6,$2,24

$L6:
	.loc 1 23 0
	sltu	$2,$4,72
	.loc 1 25 0
	.loc 1 23 0
	beq	$2,$0,$L8
	addiu	$2,$4,-40

	.loc 1 25 0
	li	$3,1			# 0x1
	sll	$3,$3,$2
	.loc 1 24 0
	lw	$2,%got(mt7620a_gpios)($28)
	addiu	$6,$2,48
$L12:
	.loc 1 25 0
	b	$L3
	sw	$3,0($5)

$L8:
	.loc 1 26 0
	sltu	$2,$4,80
	beq	$2,$0,$L10
	lw	$6,%got(mt7620a_gpios)($28)

	.loc 1 28 0
	addiu	$3,$4,-72
	li	$2,1			# 0x1
	sll	$2,$2,$3
	.loc 1 27 0
	addiu	$6,$6,72
$L13:
	.loc 1 28 0
	b	$L3
	sw	$2,0($5)

$L10:
	.loc 1 31 0
	addiu	$3,$4,-80
	li	$2,1			# 0x1
	sll	$2,$2,$3
	sw	$2,0($5)
	.loc 1 30 0
	addiu	$6,$6,96
$L3:
	.loc 1 35 0
	j	$31
	move	$2,$6

	.set	macro
	.set	reorder
$LFE2:
	.end	get_gpio_para
	.align	2
	.globl	gpio_config
	.ent	gpio_config
	.type	gpio_config, @function
gpio_config:
$LFB3:
	.loc 1 39 0
	.frame	$sp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI0:
	sw	$31,36($sp)
$LCFI1:
	sw	$16,32($sp)
$LCFI2:
	.cprestore	16
	.loc 1 44 0
	lw	$25,%got(get_gpio_para)($28)
	.loc 1 39 0
	move	$16,$5
	.loc 1 41 0
	sw	$0,24($sp)
	.loc 1 44 0
	addiu	$25,$25,%lo(get_gpio_para)
	jalr	$25
	addiu	$5,$sp,24

	move	$7,$2
	.loc 1 45 0
	beq	$2,$0,$L14
	lw	$28,16($sp)

	.loc 1 46 0
	lw	$2,0($2)
	sltu	$2,$2,4
	.loc 1 52 0
	.loc 1 46 0
	beq	$2,$0,$L14
	xori	$5,$16,0x1

	.loc 1 47 0
	lw	$4,4($7)
	.loc 1 48 0
	lw	$2,24($sp)
	.loc 1 47 0
	lw	$6,0($4)
	.loc 1 48 0
	nor	$3,$0,$2
	and	$6,$6,$3
	.loc 1 49 0
	sw	$6,0($4)
	.loc 1 50 0
	lw	$4,8($7)
	lw	$6,0($4)
	.loc 1 52 0
	and	$3,$6,$3
	or	$2,$6,$2
	movn	$2,$3,$5
	.loc 1 56 0
	sw	$2,0($4)
$L14:
	.loc 1 59 0
	lw	$31,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE3:
	.end	gpio_config
	.align	2
	.globl	gpio_write
	.ent	gpio_write
	.type	gpio_write, @function
gpio_write:
$LFB4:
	.loc 1 63 0
	.frame	$sp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI3:
	sw	$31,36($sp)
$LCFI4:
	sw	$16,32($sp)
$LCFI5:
	.cprestore	16
	.loc 1 68 0
	lw	$25,%got(get_gpio_para)($28)
	.loc 1 63 0
	move	$16,$5
	.loc 1 65 0
	sw	$0,24($sp)
	.loc 1 68 0
	addiu	$25,$25,%lo(get_gpio_para)
	jalr	$25
	addiu	$5,$sp,24

	move	$5,$2
	.loc 1 69 0
	beq	$2,$0,$L19
	lw	$28,16($sp)

	.loc 1 71 0
	lw	$6,0($2)
	li	$2,1			# 0x1
	.loc 1 79 0
	.loc 1 71 0
	beq	$6,$2,$L25
	lw	$2,%got(gpio_data_grp1)($28)

	beq	$6,$0,$L24
	nop

	sltu	$2,$6,4
	.loc 1 95 0
	.loc 1 71 0
	beq	$2,$0,$L31
	lw	$31,36($sp)

$L24:
	.loc 1 75 0
	lw	$2,12($5)
	lw	$3,0($2)
	.loc 1 85 0
	.loc 1 76 0
	b	$L30
	li	$2,1			# 0x1

$L25:
	.loc 1 79 0
	lw	$3,%lo(gpio_data_grp1)($2)
	.loc 1 85 0
	li	$2,1			# 0x1
$L30:
	bne	$16,$2,$L27
	lw	$4,24($sp)

	.loc 1 86 0
	b	$L28
	or	$3,$3,$4

$L27:
	.loc 1 88 0
	nor	$2,$0,$4
	and	$3,$3,$2
$L28:
	.loc 1 90 0
	lw	$2,12($5)
	sw	$3,0($2)
	.loc 1 91 0
	li	$2,1			# 0x1
	.loc 1 95 0
	.loc 1 91 0
	bne	$6,$2,$L31
	lw	$31,36($sp)

	.loc 1 92 0
	lw	$2,%got(gpio_data_grp1)($28)
	sw	$3,%lo(gpio_data_grp1)($2)
$L19:
	.loc 1 95 0
	lw	$31,36($sp)
$L31:
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE4:
	.end	gpio_write
	.align	2
	.globl	gpio_read
	.ent	gpio_read
	.type	gpio_read, @function
gpio_read:
$LFB5:
	.loc 1 98 0
	.frame	$sp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI6:
	sw	$31,36($sp)
$LCFI7:
	sw	$16,32($sp)
$LCFI8:
	.cprestore	16
	.loc 1 104 0
	lw	$25,%got(get_gpio_para)($28)
	addiu	$5,$sp,24
	addiu	$25,$25,%lo(get_gpio_para)
	.loc 1 99 0
	.loc 1 104 0
	jalr	$25
	li	$16,1			# 0x1

	move	$3,$2
	.loc 1 105 0
	beq	$2,$0,$L33
	lw	$28,16($sp)

	.loc 1 106 0
	lw	$2,0($2)
	sltu	$2,$2,4
	.loc 1 114 0
	.loc 1 106 0
	beq	$2,$0,$L36
	move	$2,$16

	.loc 1 107 0
	lw	$2,12($3)
	.loc 1 108 0
	lw	$3,24($sp)
	.loc 1 107 0
	lw	$2,0($2)
	.loc 1 108 0
	and	$2,$2,$3
	.loc 1 109 0
	sltu	$16,$0,$2
$L33:
	.loc 1 114 0
	move	$2,$16
$L36:
	lw	$31,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE5:
	.end	gpio_read
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
	.align	2
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB3
	.4byte	$LFE3-$LFB3
	.byte	0x4
	.4byte	$LCFI0-$LFB3
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI2-$LCFI0
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB4
	.4byte	$LFE4-$LFB4
	.byte	0x4
	.4byte	$LCFI3-$LFB4
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI5-$LCFI3
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
	.byte	0x4
	.4byte	$LCFI6-$LFB5
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI8-$LCFI6
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE6:
	.align	0
	.file 2 "/home/xieshijing/DIR819-96920/DIR819_1.05/DIR819/build/include/gpio.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x577
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF142
	.byte	0x1
	.4byte	$LASF143
	.4byte	$LASF144
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
	.4byte	0x305
	.byte	0x4
	.byte	0x2
	.byte	0x1e
	.uleb128 0x5
	.4byte	$LASF9
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF10
	.sleb128 1
	.uleb128 0x5
	.4byte	$LASF11
	.sleb128 2
	.uleb128 0x5
	.4byte	$LASF12
	.sleb128 3
	.uleb128 0x5
	.4byte	$LASF13
	.sleb128 4
	.uleb128 0x5
	.4byte	$LASF14
	.sleb128 5
	.uleb128 0x5
	.4byte	$LASF15
	.sleb128 6
	.uleb128 0x5
	.4byte	$LASF16
	.sleb128 7
	.uleb128 0x5
	.4byte	$LASF17
	.sleb128 8
	.uleb128 0x5
	.4byte	$LASF18
	.sleb128 9
	.uleb128 0x5
	.4byte	$LASF19
	.sleb128 10
	.uleb128 0x5
	.4byte	$LASF20
	.sleb128 11
	.uleb128 0x5
	.4byte	$LASF21
	.sleb128 12
	.uleb128 0x5
	.4byte	$LASF22
	.sleb128 13
	.uleb128 0x5
	.4byte	$LASF23
	.sleb128 14
	.uleb128 0x5
	.4byte	$LASF24
	.sleb128 15
	.uleb128 0x5
	.4byte	$LASF25
	.sleb128 16
	.uleb128 0x5
	.4byte	$LASF26
	.sleb128 17
	.uleb128 0x5
	.4byte	$LASF27
	.sleb128 18
	.uleb128 0x5
	.4byte	$LASF28
	.sleb128 19
	.uleb128 0x5
	.4byte	$LASF29
	.sleb128 20
	.uleb128 0x5
	.4byte	$LASF30
	.sleb128 21
	.uleb128 0x5
	.4byte	$LASF31
	.sleb128 22
	.uleb128 0x5
	.4byte	$LASF32
	.sleb128 23
	.uleb128 0x5
	.4byte	$LASF33
	.sleb128 24
	.uleb128 0x5
	.4byte	$LASF34
	.sleb128 25
	.uleb128 0x5
	.4byte	$LASF35
	.sleb128 26
	.uleb128 0x5
	.4byte	$LASF36
	.sleb128 27
	.uleb128 0x5
	.4byte	$LASF37
	.sleb128 28
	.uleb128 0x5
	.4byte	$LASF38
	.sleb128 29
	.uleb128 0x5
	.4byte	$LASF39
	.sleb128 30
	.uleb128 0x5
	.4byte	$LASF40
	.sleb128 31
	.uleb128 0x5
	.4byte	$LASF41
	.sleb128 32
	.uleb128 0x5
	.4byte	$LASF42
	.sleb128 33
	.uleb128 0x5
	.4byte	$LASF43
	.sleb128 34
	.uleb128 0x5
	.4byte	$LASF44
	.sleb128 35
	.uleb128 0x5
	.4byte	$LASF45
	.sleb128 36
	.uleb128 0x5
	.4byte	$LASF46
	.sleb128 37
	.uleb128 0x5
	.4byte	$LASF47
	.sleb128 38
	.uleb128 0x5
	.4byte	$LASF48
	.sleb128 39
	.uleb128 0x5
	.4byte	$LASF49
	.sleb128 40
	.uleb128 0x5
	.4byte	$LASF50
	.sleb128 41
	.uleb128 0x5
	.4byte	$LASF51
	.sleb128 42
	.uleb128 0x5
	.4byte	$LASF52
	.sleb128 43
	.uleb128 0x5
	.4byte	$LASF53
	.sleb128 44
	.uleb128 0x5
	.4byte	$LASF54
	.sleb128 45
	.uleb128 0x5
	.4byte	$LASF55
	.sleb128 46
	.uleb128 0x5
	.4byte	$LASF56
	.sleb128 47
	.uleb128 0x5
	.4byte	$LASF57
	.sleb128 48
	.uleb128 0x5
	.4byte	$LASF58
	.sleb128 49
	.uleb128 0x5
	.4byte	$LASF59
	.sleb128 50
	.uleb128 0x5
	.4byte	$LASF60
	.sleb128 51
	.uleb128 0x5
	.4byte	$LASF61
	.sleb128 52
	.uleb128 0x5
	.4byte	$LASF62
	.sleb128 53
	.uleb128 0x5
	.4byte	$LASF63
	.sleb128 54
	.uleb128 0x5
	.4byte	$LASF64
	.sleb128 55
	.uleb128 0x5
	.4byte	$LASF65
	.sleb128 56
	.uleb128 0x5
	.4byte	$LASF66
	.sleb128 57
	.uleb128 0x5
	.4byte	$LASF67
	.sleb128 58
	.uleb128 0x5
	.4byte	$LASF68
	.sleb128 59
	.uleb128 0x5
	.4byte	$LASF69
	.sleb128 60
	.uleb128 0x5
	.4byte	$LASF70
	.sleb128 61
	.uleb128 0x5
	.4byte	$LASF71
	.sleb128 62
	.uleb128 0x5
	.4byte	$LASF72
	.sleb128 63
	.uleb128 0x5
	.4byte	$LASF73
	.sleb128 64
	.uleb128 0x5
	.4byte	$LASF74
	.sleb128 65
	.uleb128 0x5
	.4byte	$LASF75
	.sleb128 66
	.uleb128 0x5
	.4byte	$LASF76
	.sleb128 67
	.uleb128 0x5
	.4byte	$LASF77
	.sleb128 68
	.uleb128 0x5
	.4byte	$LASF78
	.sleb128 69
	.uleb128 0x5
	.4byte	$LASF79
	.sleb128 70
	.uleb128 0x5
	.4byte	$LASF80
	.sleb128 71
	.uleb128 0x5
	.4byte	$LASF81
	.sleb128 72
	.uleb128 0x5
	.4byte	$LASF82
	.sleb128 73
	.uleb128 0x5
	.4byte	$LASF83
	.sleb128 74
	.uleb128 0x5
	.4byte	$LASF84
	.sleb128 75
	.uleb128 0x5
	.4byte	$LASF85
	.sleb128 76
	.uleb128 0x5
	.4byte	$LASF86
	.sleb128 77
	.uleb128 0x5
	.4byte	$LASF87
	.sleb128 78
	.uleb128 0x5
	.4byte	$LASF88
	.sleb128 79
	.uleb128 0x5
	.4byte	$LASF89
	.sleb128 80
	.uleb128 0x5
	.4byte	$LASF90
	.sleb128 81
	.uleb128 0x5
	.4byte	$LASF91
	.sleb128 82
	.uleb128 0x5
	.4byte	$LASF92
	.sleb128 83
	.uleb128 0x5
	.4byte	$LASF93
	.sleb128 84
	.uleb128 0x5
	.4byte	$LASF94
	.sleb128 85
	.uleb128 0x5
	.4byte	$LASF95
	.sleb128 86
	.uleb128 0x5
	.4byte	$LASF96
	.sleb128 87
	.uleb128 0x5
	.4byte	$LASF97
	.sleb128 88
	.uleb128 0x5
	.4byte	$LASF98
	.sleb128 89
	.uleb128 0x5
	.4byte	$LASF99
	.sleb128 90
	.uleb128 0x5
	.4byte	$LASF100
	.sleb128 91
	.uleb128 0x5
	.4byte	$LASF101
	.sleb128 92
	.uleb128 0x5
	.4byte	$LASF102
	.sleb128 93
	.uleb128 0x5
	.4byte	$LASF103
	.sleb128 94
	.uleb128 0x5
	.4byte	$LASF104
	.sleb128 95
	.uleb128 0x5
	.4byte	$LASF105
	.sleb128 96
	.uleb128 0x5
	.4byte	$LASF106
	.sleb128 97
	.uleb128 0x5
	.4byte	$LASF107
	.sleb128 98
	.uleb128 0x5
	.4byte	$LASF108
	.sleb128 99
	.uleb128 0x5
	.4byte	$LASF109
	.sleb128 160
	.uleb128 0x5
	.4byte	$LASF110
	.sleb128 161
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF113
	.byte	0x2
	.byte	0x2e
	.4byte	0x72
	.uleb128 0x4
	.4byte	0x325
	.byte	0x4
	.byte	0x2
	.byte	0x31
	.uleb128 0x5
	.4byte	$LASF111
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF112
	.sleb128 1
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF114
	.byte	0x2
	.byte	0x34
	.4byte	0x310
	.uleb128 0x4
	.4byte	0x36f
	.byte	0x4
	.byte	0x2
	.byte	0x3e
	.uleb128 0x5
	.4byte	$LASF115
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF116
	.sleb128 1
	.uleb128 0x5
	.4byte	$LASF117
	.sleb128 2
	.uleb128 0x5
	.4byte	$LASF118
	.sleb128 3
	.uleb128 0x5
	.4byte	$LASF119
	.sleb128 4
	.uleb128 0x5
	.4byte	$LASF120
	.sleb128 5
	.uleb128 0x5
	.4byte	$LASF121
	.sleb128 6
	.uleb128 0x5
	.4byte	$LASF122
	.sleb128 7
	.uleb128 0x5
	.4byte	$LASF123
	.sleb128 8
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF124
	.byte	0x2
	.byte	0x48
	.4byte	0x330
	.uleb128 0x7
	.4byte	0x3db
	.4byte	$LASF145
	.byte	0x18
	.byte	0x2
	.byte	0x52
	.uleb128 0x8
	.4byte	$LASF125
	.byte	0x2
	.byte	0x53
	.4byte	0x36f
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF126
	.byte	0x2
	.byte	0x54
	.4byte	0x4f
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF127
	.byte	0x2
	.byte	0x55
	.4byte	0x4f
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x8
	.4byte	$LASF128
	.byte	0x2
	.byte	0x56
	.4byte	0x4f
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x8
	.4byte	$LASF129
	.byte	0x2
	.byte	0x57
	.4byte	0x4f
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x8
	.4byte	$LASF130
	.byte	0x2
	.byte	0x58
	.4byte	0x4f
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.byte	0x0
	.uleb128 0x9
	.4byte	0x42c
	.4byte	$LASF146
	.byte	0x1
	.byte	0xc
	.byte	0x1
	.4byte	0x42c
	.4byte	$LFB2
	.4byte	$LFE2
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0xa
	.4byte	$LASF131
	.byte	0x1
	.byte	0xb
	.4byte	0x305
	.byte	0x1
	.byte	0x54
	.uleb128 0xa
	.4byte	$LASF132
	.byte	0x1
	.byte	0xb
	.4byte	0x432
	.byte	0x1
	.byte	0x55
	.uleb128 0xb
	.ascii	"dev\000"
	.byte	0x1
	.byte	0xd
	.4byte	0x42c
	.byte	0x1
	.byte	0x56
	.uleb128 0xc
	.ascii	"out\000"
	.byte	0x1
	.byte	0x21
	.4byte	$L3
	.byte	0x0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x37a
	.uleb128 0xd
	.byte	0x4
	.4byte	0x2c
	.uleb128 0xe
	.4byte	0x496
	.byte	0x1
	.4byte	$LASF136
	.byte	0x1
	.byte	0x27
	.byte	0x1
	.4byte	$LFB3
	.4byte	$LFE3
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0xa
	.4byte	$LASF133
	.byte	0x1
	.byte	0x26
	.4byte	0x48
	.byte	0x1
	.byte	0x54
	.uleb128 0xa
	.4byte	$LASF134
	.byte	0x1
	.byte	0x26
	.4byte	0x48
	.byte	0x1
	.byte	0x60
	.uleb128 0xb
	.ascii	"dev\000"
	.byte	0x1
	.byte	0x28
	.4byte	0x42c
	.byte	0x1
	.byte	0x57
	.uleb128 0xf
	.4byte	$LASF132
	.byte	0x1
	.byte	0x29
	.4byte	0x2c
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF135
	.byte	0x1
	.byte	0x2a
	.4byte	0x2c
	.byte	0x1
	.byte	0x56
	.byte	0x0
	.uleb128 0xe
	.4byte	0x4f4
	.byte	0x1
	.4byte	$LASF137
	.byte	0x1
	.byte	0x3f
	.byte	0x1
	.4byte	$LFB4
	.4byte	$LFE4
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0xa
	.4byte	$LASF133
	.byte	0x1
	.byte	0x3e
	.4byte	0x48
	.byte	0x1
	.byte	0x54
	.uleb128 0xa
	.4byte	$LASF138
	.byte	0x1
	.byte	0x3e
	.4byte	0x325
	.byte	0x1
	.byte	0x60
	.uleb128 0xb
	.ascii	"dev\000"
	.byte	0x1
	.byte	0x40
	.4byte	0x42c
	.byte	0x1
	.byte	0x55
	.uleb128 0xf
	.4byte	$LASF132
	.byte	0x1
	.byte	0x41
	.4byte	0x2c
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF135
	.byte	0x1
	.byte	0x42
	.4byte	0x2c
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x10
	.4byte	0x556
	.byte	0x1
	.4byte	$LASF139
	.byte	0x1
	.byte	0x62
	.byte	0x1
	.4byte	0x325
	.4byte	$LFB5
	.4byte	$LFE5
	.4byte	$LSFDE6
	.byte	0x1
	.byte	0x6d
	.uleb128 0xa
	.4byte	$LASF133
	.byte	0x1
	.byte	0x61
	.4byte	0x48
	.byte	0x1
	.byte	0x54
	.uleb128 0xf
	.4byte	$LASF138
	.byte	0x1
	.byte	0x63
	.4byte	0x325
	.byte	0x1
	.byte	0x60
	.uleb128 0xb
	.ascii	"dev\000"
	.byte	0x1
	.byte	0x64
	.4byte	0x42c
	.byte	0x1
	.byte	0x53
	.uleb128 0xf
	.4byte	$LASF132
	.byte	0x1
	.byte	0x65
	.4byte	0x2c
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF135
	.byte	0x1
	.byte	0x66
	.4byte	0x2c
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.uleb128 0x11
	.byte	0x1
	.4byte	0x37a
	.uleb128 0x12
	.4byte	$LASF140
	.byte	0x1
	.byte	0xa
	.4byte	0x556
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.4byte	$LASF141
	.byte	0x1
	.byte	0x3d
	.4byte	0x2c
	.byte	0x5
	.byte	0x3
	.4byte	gpio_data_grp1
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
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0xa
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
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
	.uleb128 0x11
	.uleb128 0x1
	.byte	0x0
	.uleb128 0x3c
	.uleb128 0xc
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x3b
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x57b
	.4byte	0x438
	.ascii	"gpio_config\000"
	.4byte	0x496
	.ascii	"gpio_write\000"
	.4byte	0x4f4
	.ascii	"gpio_read\000"
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
$LASF124:
	.ascii	"gpio_group\000"
$LASF8:
	.ascii	"char\000"
$LASF136:
	.ascii	"gpio_config\000"
$LASF68:
	.ascii	"GPIO59\000"
$LASF138:
	.ascii	"level\000"
$LASF115:
	.ascii	"GPIO_GROUP0\000"
$LASF116:
	.ascii	"GPIO_GROUP1\000"
$LASF117:
	.ascii	"GPIO_GROUP2\000"
$LASF121:
	.ascii	"GPIO_GROUP6\000"
$LASF122:
	.ascii	"GPIO_GROUP7\000"
$LASF109:
	.ascii	"GPIO_GROUPS\000"
$LASF42:
	.ascii	"GPIO33\000"
$LASF131:
	.ascii	"index\000"
$LASF73:
	.ascii	"GPIO64\000"
$LASF141:
	.ascii	"gpio_data_grp1\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF9:
	.ascii	"GPIO00\000"
$LASF10:
	.ascii	"GPIO01\000"
$LASF11:
	.ascii	"GPIO02\000"
$LASF12:
	.ascii	"GPIO03\000"
$LASF13:
	.ascii	"GPIO04\000"
$LASF14:
	.ascii	"GPIO05\000"
$LASF15:
	.ascii	"GPIO06\000"
$LASF17:
	.ascii	"GPIO08\000"
$LASF18:
	.ascii	"GPIO09\000"
$LASF112:
	.ascii	"GPIO_LEVEL_HIGH\000"
$LASF113:
	.ascii	"gpio_idx\000"
$LASF135:
	.ascii	"value\000"
$LASF142:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF19:
	.ascii	"GPIO10\000"
$LASF20:
	.ascii	"GPIO11\000"
$LASF21:
	.ascii	"GPIO12\000"
$LASF22:
	.ascii	"GPIO13\000"
$LASF23:
	.ascii	"GPIO14\000"
$LASF24:
	.ascii	"GPIO15\000"
$LASF26:
	.ascii	"GPIO17\000"
$LASF27:
	.ascii	"GPIO18\000"
$LASF28:
	.ascii	"GPIO19\000"
$LASF80:
	.ascii	"GPIO71\000"
$LASF83:
	.ascii	"GPIO74\000"
$LASF84:
	.ascii	"GPIO75\000"
$LASF99:
	.ascii	"GPIO90\000"
$LASF88:
	.ascii	"GPIO79\000"
$LASF145:
	.ascii	"gpio_dev\000"
$LASF133:
	.ascii	"gpio_num\000"
$LASF143:
	.ascii	"gpio_boot.c\000"
$LASF105:
	.ascii	"GPIO96\000"
$LASF30:
	.ascii	"GPIO21\000"
$LASF32:
	.ascii	"GPIO23\000"
$LASF33:
	.ascii	"GPIO24\000"
$LASF34:
	.ascii	"GPIO25\000"
$LASF35:
	.ascii	"GPIO26\000"
$LASF36:
	.ascii	"GPIO27\000"
$LASF37:
	.ascii	"GPIO28\000"
$LASF38:
	.ascii	"GPIO29\000"
$LASF119:
	.ascii	"GPIO_GROUP4\000"
$LASF140:
	.ascii	"mt7620a_gpios\000"
$LASF16:
	.ascii	"GPIO07\000"
$LASF146:
	.ascii	"get_gpio_para\000"
$LASF114:
	.ascii	"gpio_level\000"
$LASF39:
	.ascii	"GPIO30\000"
$LASF40:
	.ascii	"GPIO31\000"
$LASF41:
	.ascii	"GPIO32\000"
$LASF43:
	.ascii	"GPIO34\000"
$LASF44:
	.ascii	"GPIO35\000"
$LASF45:
	.ascii	"GPIO36\000"
$LASF46:
	.ascii	"GPIO37\000"
$LASF47:
	.ascii	"GPIO38\000"
$LASF48:
	.ascii	"GPIO39\000"
$LASF134:
	.ascii	"gpio_func\000"
$LASF90:
	.ascii	"GPIO81\000"
$LASF92:
	.ascii	"GPIO83\000"
$LASF6:
	.ascii	"long long int\000"
$LASF98:
	.ascii	"GPIO89\000"
$LASF139:
	.ascii	"gpio_read\000"
$LASF128:
	.ascii	"data_addr\000"
$LASF49:
	.ascii	"GPIO40\000"
$LASF50:
	.ascii	"GPIO41\000"
$LASF51:
	.ascii	"GPIO42\000"
$LASF52:
	.ascii	"GPIO43\000"
$LASF53:
	.ascii	"GPIO44\000"
$LASF54:
	.ascii	"GPIO45\000"
$LASF55:
	.ascii	"GPIO46\000"
$LASF56:
	.ascii	"GPIO47\000"
$LASF57:
	.ascii	"GPIO48\000"
$LASF58:
	.ascii	"GPIO49\000"
$LASF29:
	.ascii	"GPIO20\000"
$LASF25:
	.ascii	"GPIO16\000"
$LASF60:
	.ascii	"GPIO51\000"
$LASF59:
	.ascii	"GPIO50\000"
$LASF61:
	.ascii	"GPIO52\000"
$LASF62:
	.ascii	"GPIO53\000"
$LASF63:
	.ascii	"GPIO54\000"
$LASF64:
	.ascii	"GPIO55\000"
$LASF65:
	.ascii	"GPIO56\000"
$LASF66:
	.ascii	"GPIO57\000"
$LASF67:
	.ascii	"GPIO58\000"
$LASF102:
	.ascii	"GPIO93\000"
$LASF103:
	.ascii	"GPIO94\000"
$LASF125:
	.ascii	"group\000"
$LASF144:
	.ascii	"/home/xieshijing/DIR819-96920/DIR819_1.05/DIR819/build.D"
	.ascii	"IR-809/boot/tbsboot/cpu/mt7620a\000"
$LASF69:
	.ascii	"GPIO60\000"
$LASF70:
	.ascii	"GPIO61\000"
$LASF71:
	.ascii	"GPIO62\000"
$LASF72:
	.ascii	"GPIO63\000"
$LASF4:
	.ascii	"short int\000"
$LASF74:
	.ascii	"GPIO65\000"
$LASF75:
	.ascii	"GPIO66\000"
$LASF76:
	.ascii	"GPIO67\000"
$LASF77:
	.ascii	"GPIO68\000"
$LASF78:
	.ascii	"GPIO69\000"
$LASF111:
	.ascii	"GPIO_LEVEL_LOW\000"
$LASF31:
	.ascii	"GPIO22\000"
$LASF79:
	.ascii	"GPIO70\000"
$LASF81:
	.ascii	"GPIO72\000"
$LASF82:
	.ascii	"GPIO73\000"
$LASF85:
	.ascii	"GPIO76\000"
$LASF86:
	.ascii	"GPIO77\000"
$LASF87:
	.ascii	"GPIO78\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF126:
	.ascii	"ctrl_addr\000"
$LASF118:
	.ascii	"GPIO_GROUP3\000"
$LASF120:
	.ascii	"GPIO_GROUP5\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF89:
	.ascii	"GPIO80\000"
$LASF91:
	.ascii	"GPIO82\000"
$LASF93:
	.ascii	"GPIO84\000"
$LASF94:
	.ascii	"GPIO85\000"
$LASF95:
	.ascii	"GPIO86\000"
$LASF96:
	.ascii	"GPIO87\000"
$LASF97:
	.ascii	"GPIO88\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF129:
	.ascii	"edge_addr\000"
$LASF132:
	.ascii	"pins\000"
$LASF100:
	.ascii	"GPIO91\000"
$LASF101:
	.ascii	"GPIO92\000"
$LASF104:
	.ascii	"GPIO95\000"
$LASF106:
	.ascii	"GPIO97\000"
$LASF107:
	.ascii	"GPIO98\000"
$LASF108:
	.ascii	"GPIO99\000"
$LASF110:
	.ascii	"GPIO_END\000"
$LASF123:
	.ascii	"GPIO_GROUP_END\000"
$LASF130:
	.ascii	"isr_addr\000"
$LASF3:
	.ascii	"signed char\000"
$LASF127:
	.ascii	"dir_addr\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF137:
	.ascii	"gpio_write\000"
	.ident	"GCC: (GNU) 3.4.2"
