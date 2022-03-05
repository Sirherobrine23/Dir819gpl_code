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
	.globl	_SetLed
	.ent	_SetLed
	.type	_SetLed, @function
_SetLed:
$LFB2:
	.file 1 "led.c"
	.loc 1 9 0
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
	.loc 1 14 0
	lw	$6,%got(mt7620a_leds)($28)
	.loc 1 9 0
	sll	$17,$5,24
	.loc 1 14 0
	li	$2,23			# 0x17
	lw	$3,0($6)
	.loc 1 9 0
	.loc 1 14 0
	beq	$3,$2,$L1
	sra	$17,$17,24

	move	$3,$6
	li	$7,23			# 0x17
	move	$5,$6
$L6:
	.loc 1 15 0
	lw	$2,0($5)
	addiu	$3,$3,28
	beq	$2,$4,$L14
	addiu	$5,$5,28

	.loc 1 14 0
	lw	$2,0($3)
	bne	$2,$7,$L6
	addiu	$6,$6,28

	.loc 1 37 0
	b	$L16
	lw	$31,32($sp)

$L14:
	.loc 1 16 0
	.loc 1 20 0
	beq	$6,$0,$L1
	move	$16,$6

	.loc 1 21 0
	lw	$2,0($6)
	addiu	$4,$2,-18
	sltu	$2,$4,5
	.loc 1 27 0
	.loc 1 21 0
	beq	$2,$0,$L17
	li	$2,1			# 0x1

$LBB2:
	.loc 1 24 0
	lw	$25,%call16(PHY_led_ops)($28)
	jalr	$25
	move	$5,$17

	lw	$28,16($sp)
$LBE2:
	.loc 1 27 0
	li	$2,1			# 0x1
$L17:
	bne	$17,$2,$L9
	lw	$5,8($16)

	.loc 1 28 0
	lw	$4,4($16)
	b	$L15
	lw	$25,%call16(gpio_write)($28)

$L9:
	lw	$4,4($16)
	.loc 1 30 0
	bne	$5,$2,$L11
	lw	$25,%call16(gpio_write)($28)

	.loc 1 31 0
	b	$L15
	move	$5,$0

$L11:
	.loc 1 33 0
	li	$5,1			# 0x1
$L15:
	.loc 1 37 0
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	.loc 1 33 0
	jr	$25
	addiu	$sp,$sp,40

$L1:
	.loc 1 37 0
	lw	$31,32($sp)
$L16:
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE2:
	.end	_SetLed
	.align	2
	.globl	set_all_led_default
	.ent	set_all_led_default
	.type	set_all_led_default, @function
set_all_led_default:
$LFB3:
	.loc 1 40 0
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI4:
	sw	$31,32($sp)
$LCFI5:
	sw	$17,28($sp)
$LCFI6:
	sw	$16,24($sp)
$LCFI7:
	.cprestore	16
	.loc 1 43 0
	lw	$5,%got(mt7620a_leds)($28)
	.loc 1 40 0
	sll	$17,$4,24
	.loc 1 43 0
	li	$2,23			# 0x17
	lw	$3,0($5)
	.loc 1 40 0
	.loc 1 43 0
	beq	$3,$2,$L28
	sra	$17,$17,24

	move	$16,$5
$L26:
	.loc 1 53 0
	lw	$25,%call16(_SetLed)($28)
	.loc 1 44 0
	bgez	$17,$L22
	move	$5,$17

	lw	$6,0($16)
	.loc 1 45 0
	lw	$3,16($16)
	li	$2,1			# 0x1
	.loc 1 46 0
	li	$5,1			# 0x1
	.loc 1 45 0
	beq	$3,$2,$L29
	move	$4,$6

	.loc 1 49 0
	move	$4,$6
	b	$L29
	move	$5,$0

$L22:
	.loc 1 53 0
	lw	$4,0($16)
$L29:
	jalr	$25
	addiu	$16,$16,28

	.loc 1 43 0
	lw	$3,0($16)
	li	$2,23			# 0x17
	.loc 1 53 0
	.loc 1 43 0
	bne	$3,$2,$L26
	lw	$28,16($sp)

$L28:
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE3:
	.end	set_all_led_default
	.align	2
	.globl	_init_led
	.ent	_init_led
	.type	_init_led, @function
_init_led:
$LFB4:
	.loc 1 59 0
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI8:
	sw	$31,28($sp)
$LCFI9:
	sw	$16,24($sp)
$LCFI10:
	.cprestore	16
	.loc 1 62 0
	lw	$4,%got(mt7620a_leds)($28)
	li	$2,23			# 0x17
	lw	$3,0($4)
	beq	$3,$2,$L36
	move	$16,$4

$L34:
	.loc 1 63 0
	lw	$25,%call16(gpio_config)($28)
	lw	$4,4($16)
	li	$5,1			# 0x1
	jalr	$25
	addiu	$16,$16,28

	.loc 1 62 0
	lw	$3,0($16)
	li	$2,23			# 0x17
	.loc 1 63 0
	.loc 1 62 0
	bne	$3,$2,$L34
	lw	$28,16($sp)

$L36:
	.loc 1 65 0
	lw	$3,%got(system_led_state)($28)
	.loc 1 68 0
	lw	$31,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	addiu	$sp,$sp,32
	.loc 1 65 0
	.loc 1 68 0
	j	$31
	sw	$0,%lo(system_led_state)($3)

	.set	macro
	.set	reorder
$LFE4:
	.end	_init_led
	.local	system_led_state
	.comm	system_led_state,4,4
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
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI7-$LCFI4
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
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB4
	.4byte	$LFE4-$LFB4
	.byte	0x4
	.4byte	$LCFI8-$LFB4
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI10-$LCFI8
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE4:
	.align	0
	.file 2 "/home/xieshijing/DIR819-96920/DIR819_1.05/DIR819/build/include/led.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x35e
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF70
	.byte	0x1
	.4byte	$LASF71
	.4byte	$LASF72
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
	.4byte	0x10b
	.byte	0x4
	.byte	0x2
	.byte	0x22
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
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF44
	.byte	0x2
	.byte	0x3b
	.4byte	0x72
	.uleb128 0x4
	.4byte	0x161
	.byte	0x4
	.byte	0x2
	.byte	0x3d
	.uleb128 0x5
	.4byte	$LASF33
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF34
	.sleb128 1
	.uleb128 0x5
	.4byte	$LASF35
	.sleb128 2
	.uleb128 0x5
	.4byte	$LASF36
	.sleb128 3
	.uleb128 0x5
	.4byte	$LASF37
	.sleb128 4
	.uleb128 0x5
	.4byte	$LASF38
	.sleb128 5
	.uleb128 0x5
	.4byte	$LASF39
	.sleb128 6
	.uleb128 0x5
	.4byte	$LASF40
	.sleb128 7
	.uleb128 0x5
	.4byte	$LASF41
	.sleb128 8
	.uleb128 0x5
	.4byte	$LASF42
	.sleb128 9
	.uleb128 0x5
	.4byte	$LASF43
	.sleb128 10
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF45
	.byte	0x2
	.byte	0x49
	.4byte	0x116
	.uleb128 0x4
	.4byte	0x181
	.byte	0x4
	.byte	0x2
	.byte	0x4b
	.uleb128 0x5
	.4byte	$LASF46
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF47
	.sleb128 1
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF48
	.byte	0x2
	.byte	0x4e
	.4byte	0x16c
	.uleb128 0x4
	.4byte	0x1a1
	.byte	0x4
	.byte	0x2
	.byte	0x51
	.uleb128 0x5
	.4byte	$LASF49
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF50
	.sleb128 1
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF51
	.byte	0x2
	.byte	0x54
	.4byte	0x18c
	.uleb128 0x7
	.4byte	0x252
	.4byte	$LASF57
	.byte	0x1c
	.byte	0x2
	.byte	0x64
	.uleb128 0x8
	.4byte	$LASF52
	.byte	0x2
	.byte	0x65
	.4byte	0x10b
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF53
	.byte	0x2
	.byte	0x66
	.4byte	0x48
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF54
	.byte	0x2
	.byte	0x67
	.4byte	0x181
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x8
	.4byte	$LASF55
	.byte	0x2
	.byte	0x68
	.4byte	0x161
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x8
	.4byte	$LASF56
	.byte	0x2
	.byte	0x69
	.4byte	0x1a1
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x7
	.4byte	0x235
	.4byte	$LASF58
	.byte	0xc
	.byte	0x2
	.byte	0x6a
	.uleb128 0x8
	.4byte	$LASF52
	.byte	0x2
	.byte	0x6f
	.4byte	0x161
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF59
	.byte	0x2
	.byte	0x70
	.4byte	0x26c
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF60
	.byte	0x2
	.byte	0x71
	.4byte	0x26c
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x8
	.4byte	$LASF61
	.byte	0x2
	.byte	0x6a
	.4byte	0x252
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0x8
	.4byte	$LASF62
	.byte	0x2
	.byte	0x6b
	.4byte	0x258
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x1fe
	.uleb128 0xa
	.byte	0x4
	.uleb128 0xb
	.4byte	0x266
	.byte	0x1
	.uleb128 0xc
	.4byte	0x266
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x1ac
	.uleb128 0x9
	.byte	0x4
	.4byte	0x25a
	.uleb128 0xd
	.4byte	0x2e2
	.byte	0x1
	.4byte	$LASF65
	.byte	0x1
	.byte	0x9
	.byte	0x1
	.4byte	$LFB2
	.4byte	$LFE2
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0xe
	.ascii	"led\000"
	.byte	0x1
	.byte	0x8
	.4byte	0x10b
	.byte	0x1
	.byte	0x54
	.uleb128 0xf
	.4byte	$LASF63
	.byte	0x1
	.byte	0x8
	.4byte	0x6b
	.byte	0x1
	.byte	0x61
	.uleb128 0x10
	.ascii	"dev\000"
	.byte	0x1
	.byte	0xa
	.4byte	0x266
	.byte	0x1
	.byte	0x60
	.uleb128 0x11
	.ascii	"i\000"
	.byte	0x1
	.byte	0xb
	.4byte	0x48
	.uleb128 0x12
	.4byte	$LASF64
	.byte	0x1
	.byte	0xc
	.4byte	0x4f
	.uleb128 0x13
	.4byte	$LBB2
	.4byte	$LBE2
	.uleb128 0x14
	.byte	0x1
	.4byte	$LASF73
	.byte	0x1
	.byte	0x18
	.4byte	0x48
	.byte	0x1
	.uleb128 0x15
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.4byte	0x314
	.byte	0x1
	.4byte	$LASF66
	.byte	0x1
	.byte	0x28
	.byte	0x1
	.4byte	$LFB3
	.4byte	$LFE3
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0xf
	.4byte	$LASF63
	.byte	0x1
	.byte	0x27
	.4byte	0x6b
	.byte	0x1
	.byte	0x61
	.uleb128 0x11
	.ascii	"i\000"
	.byte	0x1
	.byte	0x29
	.4byte	0x48
	.byte	0x0
	.uleb128 0x16
	.4byte	0x33d
	.byte	0x1
	.4byte	$LASF67
	.byte	0x1
	.byte	0x3b
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB4
	.4byte	$LFE4
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0x11
	.ascii	"i\000"
	.byte	0x1
	.byte	0x3c
	.4byte	0x48
	.byte	0x0
	.uleb128 0x17
	.byte	0x1
	.4byte	0x1ac
	.uleb128 0x18
	.4byte	$LASF68
	.byte	0x1
	.byte	0x5
	.4byte	0x33d
	.byte	0x1
	.byte	0x1
	.uleb128 0x19
	.4byte	$LASF69
	.byte	0x1
	.byte	0x6
	.4byte	0x4f
	.byte	0x5
	.byte	0x3
	.4byte	system_led_state
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
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x27
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x11
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.uleb128 0x18
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0x1
	.byte	0x0
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
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
	.uleb128 0x19
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
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x40
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x362
	.4byte	0x272
	.ascii	"_SetLed\000"
	.4byte	0x2e2
	.ascii	"set_all_led_default\000"
	.4byte	0x314
	.ascii	"_init_led\000"
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
$LASF42:
	.ascii	"led_blinking_trig\000"
$LASF47:
	.ascii	"LED_GPIO_HIGH\000"
$LASF13:
	.ascii	"led_internet_green\000"
$LASF45:
	.ascii	"trig_name\000"
$LASF8:
	.ascii	"char\000"
$LASF10:
	.ascii	"led_power_green\000"
$LASF40:
	.ascii	"led_wps_overlap_trig\000"
$LASF19:
	.ascii	"led_wps_red\000"
$LASF48:
	.ascii	"led_level\000"
$LASF62:
	.ascii	"trigger_data\000"
$LASF54:
	.ascii	"level\000"
$LASF43:
	.ascii	"led_end_trig\000"
$LASF12:
	.ascii	"led_internet\000"
$LASF29:
	.ascii	"led_lan_3\000"
$LASF30:
	.ascii	"led_lan_4\000"
$LASF31:
	.ascii	"led_lan_5\000"
$LASF20:
	.ascii	"led_wps_yellow\000"
$LASF58:
	.ascii	"led_trigger\000"
$LASF41:
	.ascii	"led_wps_success_trig\000"
$LASF21:
	.ascii	"led_dsl\000"
$LASF27:
	.ascii	"led_lan_1\000"
$LASF32:
	.ascii	"led_end\000"
$LASF60:
	.ascii	"deactivate\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF57:
	.ascii	"led_dev\000"
$LASF39:
	.ascii	"led_wps_error_trig\000"
$LASF65:
	.ascii	"_SetLed\000"
$LASF11:
	.ascii	"led_power_red\000"
$LASF70:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF26:
	.ascii	"led_prov_alm\000"
$LASF71:
	.ascii	"led.c\000"
$LASF16:
	.ascii	"led_wlan\000"
$LASF64:
	.ascii	"port\000"
$LASF56:
	.ascii	"boot_default\000"
$LASF28:
	.ascii	"led_lan_2\000"
$LASF18:
	.ascii	"led_wps_green\000"
$LASF53:
	.ascii	"gpio\000"
$LASF14:
	.ascii	"led_internet_red\000"
$LASF35:
	.ascii	"led_flash_trig\000"
$LASF68:
	.ascii	"mt7620a_leds\000"
$LASF6:
	.ascii	"long long int\000"
$LASF17:
	.ascii	"led_wps\000"
$LASF22:
	.ascii	"led_register\000"
$LASF36:
	.ascii	"led_flash_4hz_trig\000"
$LASF33:
	.ascii	"led_off_trig\000"
$LASF66:
	.ascii	"set_all_led_default\000"
$LASF50:
	.ascii	"LED_BOOT_ON\000"
$LASF44:
	.ascii	"led_name\000"
$LASF67:
	.ascii	"_init_led\000"
$LASF55:
	.ascii	"kernel_default\000"
$LASF51:
	.ascii	"led_boot_default\000"
$LASF72:
	.ascii	"/home/xieshijing/DIR819-96920/DIR819_1.05/DIR819/build.D"
	.ascii	"IR-809/boot/tbsboot/cpu/mt7620a\000"
$LASF4:
	.ascii	"short int\000"
$LASF46:
	.ascii	"LED_GPIO_LOW\000"
$LASF25:
	.ascii	"led_line\000"
$LASF49:
	.ascii	"LED_BOOT_OFF\000"
$LASF61:
	.ascii	"cur_trig\000"
$LASF37:
	.ascii	"led_dataflash_trig\000"
$LASF69:
	.ascii	"system_led_state\000"
$LASF59:
	.ascii	"activate\000"
$LASF34:
	.ascii	"led_on_trig\000"
$LASF52:
	.ascii	"name\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF23:
	.ascii	"led_phone_1\000"
$LASF24:
	.ascii	"led_phone_2\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF38:
	.ascii	"led_wps_inprogress_trig\000"
$LASF9:
	.ascii	"led_power\000"
$LASF63:
	.ascii	"state\000"
$LASF15:
	.ascii	"led_usb\000"
$LASF3:
	.ascii	"signed char\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF73:
	.ascii	"PHY_led_ops\000"
	.ident	"GCC: (GNU) 3.4.2"
