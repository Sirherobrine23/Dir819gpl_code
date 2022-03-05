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
	.globl	rst_dev
	.section	.bss
	.align	2
	.type	rst_dev, @object
	.size	rst_dev, 4
rst_dev:
	.space	4
	.text
	.align	2
	.globl	button_pressed
	.ent	button_pressed
	.type	button_pressed, @function
button_pressed:
$LFB2:
	.file 1 "button.c"
	.loc 1 15 0
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI0:
	sw	$31,28($sp)
$LCFI1:
	sw	$16,24($sp)
$LCFI2:
	.cprestore	16
	.loc 1 19 0
	lw	$16,%got(rst_dev)($28)
	.loc 1 23 0
	lw	$25,%call16(gpio_read)($28)
	.loc 1 19 0
	lw	$4,0($16)
	.loc 1 20 0
	.loc 1 19 0
	beq	$4,$0,$L1
	move	$2,$0

	.loc 1 23 0
	jalr	$25
	lw	$4,4($4)

	.loc 1 24 0
	lw	$3,0($16)
	.loc 1 23 0
	lw	$28,16($sp)
	.loc 1 24 0
	lw	$3,8($3)
	.loc 1 25 0
	xor	$3,$3,$2
	sltu	$2,$3,1
$L1:
	.loc 1 29 0
	lw	$31,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE2:
	.end	button_pressed
	.align	2
	.globl	button_init
	.ent	button_init
	.type	button_init, @function
button_init:
$LFB3:
	.loc 1 32 0
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 16, gp= 8
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI3:
	sw	$31,24($sp)
$LCFI4:
	.cprestore	16
	.loc 1 36 0
	lw	$4,%got(mt7620a_btns)($28)
	li	$2,161			# 0xa1
	lw	$3,4($4)
	.loc 1 45 0
	.loc 1 36 0
	beq	$3,$2,$L11
	lw	$31,24($sp)

	move	$5,$4
$L9:
	.loc 1 37 0
	lw	$2,0($5)
	.loc 1 36 0
	.loc 1 37 0
	bne	$2,$0,$L7
	li	$2,161			# 0xa1

	.loc 1 38 0
	lw	$2,%got(rst_dev)($28)
	.loc 1 39 0
	lw	$4,4($5)
	lw	$25,%call16(gpio_config)($28)
	.loc 1 38 0
	sw	$5,0($2)
	.loc 1 39 0
	jalr	$25
	move	$5,$0

	.loc 1 40 0
	b	$L6
	lw	$28,16($sp)

$L7:
	addiu	$5,$5,32
	.loc 1 36 0
	lw	$3,4($5)
	bne	$3,$2,$L9
	nop

$L6:
	.loc 1 45 0
	lw	$31,24($sp)
$L11:
	move	$2,$0
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE3:
	.end	button_init
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
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI2-$LCFI0
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB3
	.4byte	$LFE3-$LFB3
	.byte	0x4
	.4byte	$LCFI3-$LFB3
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI4-$LCFI3
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE2:
	.align	0
	.file 2 "/home/guohongliang/work/819/DIR819/build/include/gpio.h"
	.file 3 "/home/guohongliang/work/819/DIR819/build/include/btn.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x23b
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF39
	.byte	0x1
	.4byte	$LASF40
	.4byte	$LASF41
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
	.4byte	0x9f
	.byte	0x4
	.byte	0x3
	.byte	0x1a
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
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF18
	.byte	0x3
	.byte	0x21
	.4byte	0x72
	.uleb128 0x4
	.4byte	0xc5
	.byte	0x4
	.byte	0x3
	.byte	0x24
	.uleb128 0x5
	.4byte	$LASF15
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF16
	.sleb128 1
	.uleb128 0x5
	.4byte	$LASF17
	.sleb128 2
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF19
	.byte	0x3
	.byte	0x28
	.4byte	0xaa
	.uleb128 0x4
	.4byte	0xe5
	.byte	0x4
	.byte	0x3
	.byte	0x2a
	.uleb128 0x5
	.4byte	$LASF20
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF21
	.sleb128 1
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF22
	.byte	0x3
	.byte	0x2d
	.4byte	0xd0
	.uleb128 0x7
	.4byte	0x16d
	.4byte	$LASF42
	.byte	0x20
	.byte	0x3
	.byte	0x2f
	.uleb128 0x8
	.4byte	$LASF23
	.byte	0x3
	.byte	0x30
	.4byte	0x9f
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF24
	.byte	0x3
	.byte	0x31
	.4byte	0x48
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF25
	.byte	0x3
	.byte	0x32
	.4byte	0xe5
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x8
	.4byte	$LASF26
	.byte	0x3
	.byte	0x33
	.4byte	0x16d
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x8
	.4byte	$LASF27
	.byte	0x3
	.byte	0x34
	.4byte	0xc5
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x8
	.4byte	$LASF28
	.byte	0x3
	.byte	0x35
	.4byte	0x189
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0x8
	.4byte	$LASF29
	.byte	0x3
	.byte	0x36
	.4byte	0x48
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0x8
	.4byte	$LASF30
	.byte	0x3
	.byte	0x37
	.4byte	0x48
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x6b
	.uleb128 0xa
	.4byte	0x183
	.byte	0x1
	.4byte	0xc5
	.uleb128 0xb
	.4byte	0x183
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0xf0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x173
	.uleb128 0x4
	.4byte	0x1a4
	.byte	0x4
	.byte	0x2
	.byte	0x31
	.uleb128 0x5
	.4byte	$LASF31
	.sleb128 0
	.uleb128 0x5
	.4byte	$LASF32
	.sleb128 1
	.byte	0x0
	.uleb128 0x6
	.4byte	$LASF33
	.byte	0x2
	.byte	0x34
	.4byte	0x18f
	.uleb128 0xc
	.4byte	0x1e5
	.byte	0x1
	.4byte	$LASF35
	.byte	0x1
	.byte	0xf
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB2
	.4byte	$LFE2
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0xd
	.4byte	$LASF34
	.byte	0x1
	.byte	0x10
	.4byte	0x48
	.uleb128 0xd
	.4byte	$LASF25
	.byte	0x1
	.byte	0x11
	.4byte	0x1a4
	.byte	0x0
	.uleb128 0xc
	.4byte	0x219
	.byte	0x1
	.4byte	$LASF36
	.byte	0x1
	.byte	0x20
	.byte	0x1
	.4byte	0x48
	.4byte	$LFB3
	.4byte	$LFE3
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0xe
	.ascii	"i\000"
	.byte	0x1
	.byte	0x21
	.4byte	0x48
	.uleb128 0xd
	.4byte	$LASF34
	.byte	0x1
	.byte	0x22
	.4byte	0x48
	.byte	0x0
	.uleb128 0xf
	.byte	0x1
	.4byte	0xf0
	.uleb128 0x10
	.4byte	$LASF37
	.byte	0x1
	.byte	0x6
	.4byte	0x219
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	$LASF38
	.byte	0x1
	.byte	0x7
	.4byte	0x183
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	rst_dev
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
	.uleb128 0xb
	.uleb128 0x5
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
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x1
	.byte	0x0
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x3d
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x23f
	.4byte	0x1af
	.ascii	"button_pressed\000"
	.4byte	0x1e5
	.ascii	"button_init\000"
	.4byte	0x22c
	.ascii	"rst_dev\000"
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
	.ascii	"btn_reset\000"
$LASF8:
	.ascii	"char\000"
$LASF11:
	.ascii	"btn_wps_5g\000"
$LASF38:
	.ascii	"rst_dev\000"
$LASF25:
	.ascii	"level\000"
$LASF35:
	.ascii	"button_pressed\000"
$LASF40:
	.ascii	"button.c\000"
$LASF13:
	.ascii	"btn_wlan\000"
$LASF42:
	.ascii	"btn_dev\000"
$LASF22:
	.ascii	"btn_level\000"
$LASF29:
	.ascii	"ignore\000"
$LASF30:
	.ascii	"index\000"
$LASF21:
	.ascii	"BTN_LEVEL_HIGH\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF32:
	.ascii	"GPIO_LEVEL_HIGH\000"
$LASF17:
	.ascii	"BTN_START\000"
$LASF37:
	.ascii	"mt7620a_btns\000"
$LASF14:
	.ascii	"btn_end\000"
$LASF39:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF12:
	.ascii	"btn_wps_and_reset\000"
$LASF18:
	.ascii	"btn_name\000"
$LASF10:
	.ascii	"btn_wps\000"
$LASF24:
	.ascii	"gpio\000"
$LASF41:
	.ascii	"/home/guohongliang/work/819/DIR819/build.DIR-819/boot/tb"
	.ascii	"sboot/cpu/mt7620a\000"
$LASF33:
	.ascii	"gpio_level\000"
$LASF15:
	.ascii	"BTN_UP\000"
$LASF6:
	.ascii	"long long int\000"
$LASF36:
	.ascii	"button_init\000"
$LASF19:
	.ascii	"btn_status\000"
$LASF27:
	.ascii	"cur_status\000"
$LASF4:
	.ascii	"short int\000"
$LASF31:
	.ascii	"GPIO_LEVEL_LOW\000"
$LASF28:
	.ascii	"get_status\000"
$LASF23:
	.ascii	"name\000"
$LASF16:
	.ascii	"BTN_DOWN\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF20:
	.ascii	"BTN_LEVEL_LOW\000"
$LASF34:
	.ascii	"ret_val\000"
$LASF3:
	.ascii	"signed char\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF26:
	.ascii	"iogroup\000"
	.ident	"GCC: (GNU) 3.4.2"
