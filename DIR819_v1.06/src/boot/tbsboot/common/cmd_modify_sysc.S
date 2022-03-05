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
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"modify_sysc    - sysc modify \n\000"
	.align	2
$LC1:
	.ascii	"-mac xx.xx.xx.xx.xx.xx -ip x.x.x.x\n\000"
	.globl	__u_boot_cmd_modify_sysc
	.section	.u_boot_cmd,"aw",@progbits
	.align	2
	.type	__u_boot_cmd_modify_sysc, @object
	.size	__u_boot_cmd_modify_sysc, 120
__u_boot_cmd_modify_sysc:
	.ascii	"modify_sysc\000"
	.space	88
	.word	5
	.word	1
	.word	do_modify_sysc
	.word	$LC0
	.word	$LC1
	.globl	stSysConfig
	.data
	.align	2
	.type	stSysConfig, @object
	.size	stSysConfig, 4
stSysConfig:
	.word	-2082869248
	.section	.rodata.str1.4
	.align	2
$LC2:
	.ascii	"your ip is not suitability\n\000"
	.text
	.align	2
	.globl	deal_ip
	.ent	deal_ip
	.type	deal_ip, @function
deal_ip:
$LFB2:
	.file 1 "cmd_modify_sysc.c"
	.loc 1 34 0
	.frame	$sp,64,$31		# vars= 16, regs= 6/0, args= 16, gp= 8
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-64
$LCFI0:
	sw	$31,60($sp)
$LCFI1:
	sw	$20,56($sp)
$LCFI2:
	sw	$19,52($sp)
$LCFI3:
	sw	$18,48($sp)
$LCFI4:
	sw	$17,44($sp)
$LCFI5:
	sw	$16,40($sp)
$LCFI6:
	.cprestore	16
	.loc 1 34 0
	move	$17,$4
	move	$20,$5
	.loc 1 36 0
	move	$19,$0
	.loc 1 40 0
	move	$16,$0
	addiu	$18,$sp,24
	sll	$2,$16,1
$L47:
	addu	$2,$2,$16
	addu	$4,$2,$18
	.loc 1 42 0
	move	$5,$0
$L8:
	addiu	$2,$5,1
	.loc 1 43 0
	addu	$3,$4,$5
	.loc 1 42 0
	andi	$5,$2,0x00ff
	sltu	$2,$5,3
	.loc 1 43 0
	.loc 1 42 0
	bne	$2,$0,$L8
	sb	$0,0($3)

	.loc 1 40 0
	addiu	$2,$16,1
	andi	$16,$2,0x00ff
	sltu	$2,$16,4
	bne	$2,$0,$L47
	sll	$2,$16,1

	.loc 1 50 0
	lw	$25,%call16(strlen)($28)
	move	$4,$17
	.loc 1 46 0
	.loc 1 50 0
	jalr	$25
	li	$16,4			# 0x4

	lw	$28,16($sp)
	li	$3,46
	addu	$2,$17,$2
	.loc 1 51 0
	lw	$25,%call16(strlen)($28)
	.loc 1 50 0
	sb	$3,0($2)
	.loc 1 51 0
	jalr	$25
	move	$4,$17

	lw	$28,16($sp)
	addu	$2,$17,$2
	.loc 1 52 0
	move	$4,$17
	lw	$25,%call16(strlen)($28)
	.loc 1 51 0
	.loc 1 52 0
	jalr	$25
	sb	$0,1($2)

	addiu	$4,$2,-1
	lw	$28,16($sp)
	.loc 1 48 0
	.loc 1 52 0
	bltz	$4,$L40
	li	$5,2			# 0x2

	li	$9,46			# 0x2e
	.loc 1 54 0
	addu	$2,$17,$4
$L48:
	lbu	$7,0($2)
	.loc 1 60 0
	sll	$2,$16,1
	addu	$2,$2,$16
	addu	$2,$2,$18
	addu	$6,$2,$5
	.loc 1 54 0
	sll	$2,$7,24
	.loc 1 61 0
	addiu	$3,$5,-1
	.loc 1 54 0
	sra	$2,$2,24
	.loc 1 56 0
	addiu	$8,$16,-1
	.loc 1 61 0
	.loc 1 54 0
	bne	$2,$9,$L13
	andi	$5,$3,0x00ff

	.loc 1 56 0
	andi	$16,$8,0x00ff
	.loc 1 57 0
	.loc 1 58 0
	b	$L12
	li	$5,2			# 0x2

$L13:
	.loc 1 60 0
	sb	$7,0($6)
$L12:
	.loc 1 52 0
	addiu	$4,$4,-1
	.loc 1 54 0
	.loc 1 52 0
	bgez	$4,$L48
	addu	$2,$17,$4

$L40:
	.loc 1 63 0
	move	$16,$0
$L18:
	addiu	$2,$16,1
	.loc 1 64 0
	addu	$3,$17,$16
	.loc 1 63 0
	andi	$16,$2,0x00ff
	sltu	$2,$16,15
	.loc 1 64 0
	.loc 1 63 0
	bne	$2,$0,$L18
	sb	$0,0($3)

	.loc 1 65 0
	move	$16,$0
$L29:
	.loc 1 67 0
	move	$5,$0
	.loc 1 69 0
	sll	$2,$16,1
$L49:
	addu	$2,$2,$16
	addiu	$17,$sp,24
	addu	$2,$2,$17
	addu	$6,$2,$5
	lbu	$3,0($6)
	.loc 1 67 0
	addiu	$2,$5,1
	andi	$5,$2,0x00ff
	.loc 1 75 0
	addiu	$4,$3,-48
	andi	$2,$4,0x00ff
	.loc 1 69 0
	sltu	$3,$3,58
	.loc 1 67 0
	sltu	$7,$5,3
	.loc 1 75 0
	.loc 1 69 0
	bne	$3,$0,$L25
	sltu	$2,$2,10

	.loc 1 71 0
	lw	$4,%got($LC2)($28)
	lw	$25,%call16(printf)($28)
	.loc 1 72 0
	li	$19,1			# 0x1
	.loc 1 71 0
	jalr	$25
	addiu	$4,$4,%lo($LC2)

	.loc 1 73 0
	b	$L23
	lw	$28,16($sp)

$L25:
	.loc 1 75 0
	beq	$2,$0,$L24
	nop

	.loc 1 76 0
	sb	$4,0($6)
$L24:
	.loc 1 69 0
	.loc 1 67 0
	bne	$7,$0,$L49
	sll	$2,$16,1

$L23:
	.loc 1 65 0
	addiu	$2,$16,1
	andi	$16,$2,0x00ff
	sltu	$2,$16,4
	bne	$2,$0,$L29
	nop

	.loc 1 79 0
	li	$2,1			# 0x1
	.loc 1 81 0
	.loc 1 79 0
	beq	$19,$2,$L1
	move	$16,$0

$L34:
	.loc 1 83 0
	sll	$2,$16,1
	addu	$2,$2,$16
	addu	$2,$2,$17
	lbu	$4,0($2)
	lbu	$5,1($2)
	lbu	$6,2($2)
	sll	$2,$4,1
	addu	$2,$2,$4
	sll	$3,$5,2
	sll	$2,$2,3
	addu	$2,$2,$4
	addu	$3,$3,$5
	sll	$3,$3,1
	sll	$2,$2,2
	.loc 1 81 0
	addiu	$4,$16,1
	.loc 1 83 0
	addu	$2,$2,$3
	addu	$5,$20,$16
	.loc 1 81 0
	andi	$16,$4,0x00ff
	.loc 1 83 0
	addu	$2,$2,$6
	.loc 1 81 0
	sltu	$3,$16,4
	.loc 1 83 0
	.loc 1 81 0
	bne	$3,$0,$L34
	sb	$2,0($5)

$L1:
	.loc 1 86 0
	lw	$31,60($sp)
	lw	$20,56($sp)
	lw	$19,52($sp)
	lw	$18,48($sp)
	lw	$17,44($sp)
	lw	$16,40($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
$LFE2:
	.end	deal_ip
	.section	.rodata.str1.4
	.align	2
$LC3:
	.ascii	"your mac is not suitability\n\000"
	.text
	.align	2
	.globl	deal_mac
	.ent	deal_mac
	.type	deal_mac, @function
deal_mac:
$LFB3:
	.loc 1 89 0
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI7:
	sw	$31,32($sp)
$LCFI8:
	sw	$17,28($sp)
$LCFI9:
	sw	$16,24($sp)
$LCFI10:
	.cprestore	16
	.loc 1 89 0
	move	$16,$4
	move	$17,$5
	.loc 1 91 0
	move	$10,$0
	.loc 1 93 0
	move	$7,$0
	.loc 1 95 0
	addu	$6,$16,$7
$L71:
	lbu	$4,0($6)
	.loc 1 103 0
	addiu	$2,$4,-65
	andi	$2,$2,0x00ff
	.loc 1 95 0
	sll	$3,$4,24
	.loc 1 103 0
	sltu	$9,$2,26
	.loc 1 95 0
	sra	$3,$3,24
	li	$2,58			# 0x3a
	.loc 1 97 0
	.loc 1 95 0
	beq	$3,$2,$L53
	slt	$5,$3,103

	.loc 1 105 0
	addiu	$2,$4,-97
	andi	$2,$2,0x00ff
	.loc 1 104 0
	addiu	$3,$4,-55
	.loc 1 105 0
	.loc 1 97 0
	bne	$5,$0,$L55
	sltu	$8,$2,26

	.loc 1 99 0
	lw	$4,%got($LC3)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC3)

	lw	$28,16($sp)
	.loc 1 100 0
	.loc 1 101 0
	b	$L52
	li	$10,1			# 0x1

$L55:
	.loc 1 103 0
	bne	$9,$0,$L69
	nop

	.loc 1 107 0
	addiu	$5,$4,-48
	andi	$2,$5,0x00ff
	.loc 1 106 0
	addiu	$3,$4,-87
	.loc 1 107 0
	.loc 1 105 0
	beq	$8,$0,$L59
	sltu	$2,$2,10

$L69:
	.loc 1 106 0
	b	$L53
	sb	$3,0($6)

$L59:
	.loc 1 93 0
	.loc 1 107 0
	beq	$2,$0,$L70
	addiu	$2,$7,1

	.loc 1 108 0
	sb	$5,0($6)
$L53:
	.loc 1 93 0
	addiu	$2,$7,1
$L70:
	andi	$7,$2,0x00ff
	sltu	$2,$7,17
	.loc 1 95 0
	.loc 1 93 0
	bne	$2,$0,$L71
	addu	$6,$16,$7

$L52:
	.loc 1 110 0
	li	$2,1			# 0x1
	.loc 1 119 0
	.loc 1 110 0
	beq	$10,$2,$L72
	lw	$31,32($sp)

	.loc 1 112 0
	move	$7,$0
	move	$6,$0
$L66:
	.loc 1 114 0
	addu	$2,$16,$7
	lb	$3,0($2)
	lbu	$4,1($2)
	.loc 1 116 0
	addiu	$2,$7,3
	andi	$7,$2,0x00ff
	.loc 1 114 0
	sll	$3,$3,4
	addu	$3,$3,$4
	addu	$2,$17,$6
	.loc 1 115 0
	addiu	$5,$6,1
	.loc 1 112 0
	sltu	$4,$7,17
	.loc 1 114 0
	sb	$3,0($2)
	.loc 1 115 0
	.loc 1 112 0
	bne	$4,$0,$L66
	andi	$6,$5,0x00ff

	.loc 1 119 0
	lw	$31,32($sp)
$L72:
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE3:
	.end	deal_mac
	.section	.rodata.str1.4
	.align	2
$LC4:
	.ascii	"-mac\000"
	.align	2
$LC5:
	.ascii	"The -mac parameter is wrong.\n\000"
	.align	2
$LC6:
	.ascii	"-ip\000"
	.align	2
$LC7:
	.ascii	"The -ip parameter is wrong.\n\000"
	.text
	.align	2
	.globl	do_modify_sysc
	.ent	do_modify_sysc
	.type	do_modify_sysc, @function
do_modify_sysc:
$LFB4:
	.loc 1 124 0
	.frame	$sp,72,$31		# vars= 24, regs= 6/0, args= 16, gp= 8
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-72
$LCFI11:
	sw	$31,68($sp)
$LCFI12:
	sw	$20,64($sp)
$LCFI13:
	sw	$19,60($sp)
$LCFI14:
	sw	$18,56($sp)
$LCFI15:
	sw	$17,52($sp)
$LCFI16:
	sw	$16,48($sp)
$LCFI17:
	.cprestore	16
	.loc 1 134 0
	li	$17,1			# 0x1
	.loc 1 124 0
	move	$19,$6
	.loc 1 134 0
	slt	$2,$17,$6
	.loc 1 124 0
	move	$20,$7
	.loc 1 132 0
	sw	$0,40($sp)
	.loc 1 133 0
	move	$18,$0
$L116:
	.loc 1 136 0
	.loc 1 134 0
	beq	$2,$0,$L107
	sll	$2,$17,2

	.loc 1 136 0
	lw	$5,%got($LC4)($28)
	addu	$16,$2,$20
	lw	$25,%call16(strcmp)($28)
	lw	$4,0($16)
	jalr	$25
	addiu	$5,$5,%lo($LC4)

	bne	$2,$0,$L77
	lw	$28,16($sp)

	.loc 1 138 0
	addiu	$2,$17,1
	andi	$17,$2,0x00ff
	.loc 1 139 0
	slt	$2,$17,$19
	beq	$2,$0,$L79
	sll	$2,$17,2

	addu	$2,$2,$20
	lw	$4,0($2)
	li	$2,45			# 0x2d
	lb	$3,0($4)
	bne	$3,$2,$L78
	nop

$L79:
	.loc 1 141 0
	lw	$4,%got($LC5)($28)
	lw	$25,%call16(printf)($28)
	b	$L118
	addiu	$4,$4,%lo($LC5)

$L78:
	.loc 1 144 0
	lw	$25,%call16(deal_mac)($28)
	jalr	$25
	addiu	$5,$sp,32

	lw	$28,16($sp)
	.loc 1 145 0
	move	$5,$0
	addiu	$7,$sp,24
	lw	$8,%got(stSysConfig)($28)
	lw	$6,0($8)
$L84:
	.loc 1 147 0
	addu	$2,$5,$6
	addu	$4,$7,$5
	lbu	$3,44($2)
	lbu	$4,8($4)
	.loc 1 145 0
	addiu	$2,$5,1
	andi	$5,$2,0x00ff
	.loc 1 148 0
	xor	$3,$3,$4
	.loc 1 145 0
	sltu	$2,$5,6
	.loc 1 148 0
	li	$4,1			# 0x1
	.loc 1 145 0
	bne	$2,$0,$L84
	movn	$18,$4,$3

	.loc 1 134 0
	.loc 1 150 0
	bne	$18,$4,$L119
	addiu	$2,$17,1

	.loc 1 152 0
	move	$5,$0
$L89:
	.loc 1 154 0
	lw	$3,0($8)
	addu	$2,$7,$5
	lbu	$4,8($2)
	.loc 1 152 0
	addiu	$2,$5,1
	.loc 1 154 0
	addu	$3,$5,$3
	.loc 1 152 0
	andi	$5,$2,0x00ff
	sltu	$2,$5,6
	.loc 1 154 0
	.loc 1 152 0
	bne	$2,$0,$L89
	sb	$4,44($3)

	.loc 1 134 0
	.loc 1 152 0
	b	$L119
	addiu	$2,$17,1

$L77:
	.loc 1 159 0
	lw	$5,%got($LC6)($28)
	lw	$25,%call16(strcmp)($28)
	lw	$4,0($16)
	jalr	$25
	addiu	$5,$5,%lo($LC6)

	bne	$2,$0,$L76
	lw	$28,16($sp)

	.loc 1 161 0
	addiu	$2,$17,1
	andi	$17,$2,0x00ff
	.loc 1 162 0
	slt	$2,$17,$19
	beq	$2,$0,$L93
	sll	$2,$17,2

	addu	$2,$2,$20
	lw	$4,0($2)
	li	$2,45			# 0x2d
	lb	$3,0($4)
	.loc 1 167 0
	.loc 1 162 0
	bne	$3,$2,$L92
	lw	$25,%call16(deal_ip)($28)

$L93:
	.loc 1 164 0
	lw	$4,%got($LC7)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC7)
$L118:
	jalr	$25
	nop

	.loc 1 186 0
	b	$L73
	lw	$28,16($sp)

$L92:
	.loc 1 167 0
	jalr	$25
	addiu	$5,$sp,24

	lw	$28,16($sp)
	.loc 1 168 0
	move	$5,$0
	addiu	$7,$sp,40
	addiu	$6,$sp,24
$L98:
	.loc 1 170 0
	addu	$2,$5,$7
	addu	$4,$6,$5
	lb	$3,0($2)
	lbu	$4,0($4)
	.loc 1 168 0
	addiu	$2,$5,1
	andi	$5,$2,0x00ff
	.loc 1 171 0
	xor	$3,$3,$4
	.loc 1 168 0
	sltu	$2,$5,4
	.loc 1 171 0
	li	$4,1			# 0x1
	.loc 1 168 0
	bne	$2,$0,$L98
	movn	$18,$4,$3

	.loc 1 134 0
	.loc 1 173 0
	bne	$18,$4,$L119
	addiu	$2,$17,1

	.loc 1 175 0
	move	$5,$0
$L103:
	.loc 1 177 0
	addu	$2,$6,$5
	lbu	$4,0($2)
	.loc 1 175 0
	addiu	$2,$5,1
	.loc 1 177 0
	addu	$3,$5,$7
	.loc 1 175 0
	andi	$5,$2,0x00ff
	sltu	$2,$5,4
	.loc 1 177 0
	.loc 1 175 0
	bne	$2,$0,$L103
	sb	$4,0($3)

	.loc 1 179 0
	lw	$2,%got(stSysConfig)($28)
	lw	$3,0($2)
	lw	$2,40($sp)
	sw	$2,24($3)
$L76:
	.loc 1 134 0
	addiu	$2,$17,1
$L119:
	andi	$17,$2,0x00ff
	b	$L116
	slt	$2,$17,$19

$L107:
	.loc 1 184 0
	li	$2,1			# 0x1
	.loc 1 190 0
	.loc 1 184 0
	bne	$18,$2,$L120
	lw	$31,68($sp)

	.loc 1 186 0
	lw	$2,%got(stSysConfig)($28)
	lw	$25,%call16(sysdata_save)($28)
	lw	$4,0($2)
	lw	$2,%got(info)($28)
	jalr	$25
	lw	$5,0($2)

	lw	$28,16($sp)
$L73:
	.loc 1 190 0
	lw	$31,68($sp)
$L120:
	lw	$20,64($sp)
	lw	$19,60($sp)
	lw	$18,56($sp)
	lw	$17,52($sp)
	lw	$16,48($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,72

	.set	macro
	.set	reorder
$LFE4:
	.end	do_modify_sysc
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
	.uleb128 0x40
	.byte	0x4
	.4byte	$LCFI6-$LCFI0
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
	.uleb128 0x14
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
	.4byte	$LCFI7-$LFB3
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI10-$LCFI7
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
	.4byte	$LCFI11-$LFB4
	.byte	0xe
	.uleb128 0x48
	.byte	0x4
	.4byte	$LCFI17-$LCFI11
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
	.uleb128 0x14
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE4:
	.align	0
	.file 2 "/home/xieshijing/DIR819-97597/DIR819/build.DIR-809/boot/tbsboot/include/command.h"
	.file 3 "/home/xieshijing/DIR819-97597/DIR819/build.DIR-809/boot/tbsboot/include/common.h"
	.file 4 "/home/xieshijing/DIR819-97597/DIR819/build.DIR-809/boot/tbsboot/include/flash.h"
	.file 5 "/home/xieshijing/DIR819-97597/DIR819/build.DIR-809/boot/tbsboot/include/types.h"
	.file 6 "/home/xieshijing/DIR819-97597/DIR819/build/include/flash_layout.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x55b
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF58
	.byte	0x1
	.4byte	$LASF59
	.4byte	$LASF60
	.uleb128 0x2
	.4byte	$LASF8
	.byte	0x3
	.byte	0x4
	.4byte	0x30
	.uleb128 0x3
	.4byte	$LASF0
	.byte	0x1
	.byte	0x8
	.uleb128 0x3
	.4byte	$LASF1
	.byte	0x4
	.byte	0x7
	.uleb128 0x3
	.4byte	$LASF2
	.byte	0x2
	.byte	0x7
	.uleb128 0x3
	.4byte	$LASF3
	.byte	0x1
	.byte	0x6
	.uleb128 0x3
	.4byte	$LASF4
	.byte	0x2
	.byte	0x5
	.uleb128 0x4
	.ascii	"int\000"
	.byte	0x4
	.byte	0x5
	.uleb128 0x3
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x3
	.4byte	$LASF6
	.byte	0x8
	.byte	0x5
	.uleb128 0x3
	.4byte	$LASF7
	.byte	0x8
	.byte	0x7
	.uleb128 0x2
	.4byte	$LASF9
	.byte	0x5
	.byte	0x14
	.4byte	0x3e
	.uleb128 0x2
	.4byte	$LASF10
	.byte	0x5
	.byte	0x16
	.4byte	0x37
	.uleb128 0x3
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x5
	.4byte	0xdd
	.2byte	0x530
	.byte	0x4
	.byte	0x32
	.uleb128 0x6
	.4byte	$LASF11
	.byte	0x4
	.byte	0x21
	.4byte	0x7a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x6
	.4byte	$LASF12
	.byte	0x4
	.byte	0x22
	.4byte	0x6f
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x6
	.4byte	$LASF13
	.byte	0x4
	.byte	0x23
	.4byte	0x7a
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x6
	.4byte	$LASF14
	.byte	0x4
	.byte	0x24
	.4byte	0xdd
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x6
	.4byte	$LASF15
	.byte	0x4
	.byte	0x25
	.4byte	0xee
	.byte	0x3
	.byte	0x10
	.uleb128 0x428
	.byte	0x0
	.uleb128 0x7
	.4byte	0xee
	.4byte	0x7a
	.uleb128 0x8
	.4byte	0x85
	.2byte	0x106
	.byte	0x0
	.uleb128 0x7
	.4byte	0xff
	.4byte	0x25
	.uleb128 0x8
	.4byte	0x85
	.2byte	0x106
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF16
	.byte	0x4
	.byte	0x32
	.4byte	0x8c
	.uleb128 0x7
	.4byte	0x11a
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0xb
	.byte	0x0
	.uleb128 0x7
	.4byte	0x12a
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0x5
	.byte	0x0
	.uleb128 0x7
	.4byte	0x13a
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0xf
	.byte	0x0
	.uleb128 0x7
	.4byte	0x14a
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0x1f
	.byte	0x0
	.uleb128 0x7
	.4byte	0x15a
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0x3
	.byte	0x0
	.uleb128 0x7
	.4byte	0x16a
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0x13
	.byte	0x0
	.uleb128 0x3
	.4byte	$LASF17
	.byte	0x1
	.byte	0x6
	.uleb128 0xa
	.4byte	0x188
	.byte	0x18
	.byte	0x6
	.byte	0x85
	.uleb128 0x6
	.4byte	$LASF18
	.byte	0x6
	.byte	0x84
	.4byte	0x188
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.4byte	0x198
	.4byte	0x5a
	.uleb128 0x9
	.4byte	0x85
	.byte	0x5
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF19
	.byte	0x6
	.byte	0x85
	.4byte	0x171
	.uleb128 0xa
	.4byte	0x29d
	.byte	0xbc
	.byte	0x6
	.byte	0xa1
	.uleb128 0x6
	.4byte	$LASF20
	.byte	0x6
	.byte	0x89
	.4byte	0x198
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.ascii	"ip\000"
	.byte	0x6
	.byte	0x8a
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0x6
	.4byte	$LASF21
	.byte	0x6
	.byte	0x8b
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.uleb128 0x6
	.4byte	$LASF22
	.byte	0x6
	.byte	0x8c
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0x6
	.4byte	$LASF23
	.byte	0x6
	.byte	0x8d
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0x6
	.4byte	$LASF24
	.byte	0x6
	.byte	0x8e
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.uleb128 0xb
	.ascii	"mac\000"
	.byte	0x6
	.byte	0x8f
	.4byte	0x11a
	.byte	0x2
	.byte	0x10
	.uleb128 0x2c
	.uleb128 0x6
	.4byte	$LASF25
	.byte	0x6
	.byte	0x90
	.4byte	0x30
	.byte	0x2
	.byte	0x10
	.uleb128 0x32
	.uleb128 0x6
	.4byte	$LASF26
	.byte	0x6
	.byte	0x91
	.4byte	0x30
	.byte	0x2
	.byte	0x10
	.uleb128 0x33
	.uleb128 0x6
	.4byte	$LASF27
	.byte	0x6
	.byte	0x92
	.4byte	0x12a
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.uleb128 0x6
	.4byte	$LASF28
	.byte	0x6
	.byte	0x93
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x44
	.uleb128 0x6
	.4byte	$LASF29
	.byte	0x6
	.byte	0x94
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x64
	.uleb128 0x6
	.4byte	$LASF30
	.byte	0x6
	.byte	0x97
	.4byte	0x12a
	.byte	0x3
	.byte	0x10
	.uleb128 0x84
	.uleb128 0x6
	.4byte	$LASF31
	.byte	0x6
	.byte	0x98
	.4byte	0x14a
	.byte	0x3
	.byte	0x10
	.uleb128 0x94
	.uleb128 0x6
	.4byte	$LASF32
	.byte	0x6
	.byte	0x9a
	.4byte	0x10a
	.byte	0x3
	.byte	0x10
	.uleb128 0x98
	.uleb128 0xb
	.ascii	"sn\000"
	.byte	0x6
	.byte	0x9b
	.4byte	0x15a
	.byte	0x3
	.byte	0x10
	.uleb128 0xa4
	.uleb128 0xb
	.ascii	"tag\000"
	.byte	0x6
	.byte	0xa0
	.4byte	0x14a
	.byte	0x3
	.byte	0x10
	.uleb128 0xb8
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF33
	.byte	0x6
	.byte	0xa1
	.4byte	0x1a3
	.uleb128 0xc
	.byte	0x4
	.4byte	0x30
	.uleb128 0xc
	.byte	0x4
	.4byte	0x16a
	.uleb128 0xd
	.4byte	0x315
	.4byte	$LASF61
	.byte	0x78
	.byte	0x2
	.byte	0x27
	.uleb128 0x6
	.4byte	$LASF34
	.byte	0x2
	.byte	0x28
	.4byte	0x315
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x6
	.4byte	$LASF35
	.byte	0x2
	.byte	0x29
	.4byte	0x53
	.byte	0x2
	.byte	0x10
	.uleb128 0x64
	.uleb128 0x6
	.4byte	$LASF36
	.byte	0x2
	.byte	0x2a
	.4byte	0x53
	.byte	0x2
	.byte	0x10
	.uleb128 0x68
	.uleb128 0xb
	.ascii	"cmd\000"
	.byte	0x2
	.byte	0x2c
	.4byte	0x350
	.byte	0x2
	.byte	0x10
	.uleb128 0x6c
	.uleb128 0x6
	.4byte	$LASF37
	.byte	0x2
	.byte	0x2d
	.4byte	0x2ae
	.byte	0x2
	.byte	0x10
	.uleb128 0x70
	.uleb128 0x6
	.4byte	$LASF38
	.byte	0x2
	.byte	0x2f
	.4byte	0x2ae
	.byte	0x2
	.byte	0x10
	.uleb128 0x74
	.byte	0x0
	.uleb128 0x7
	.4byte	0x325
	.4byte	0x16a
	.uleb128 0x9
	.4byte	0x85
	.byte	0x63
	.byte	0x0
	.uleb128 0xe
	.4byte	0x344
	.byte	0x1
	.4byte	0x53
	.uleb128 0xf
	.4byte	0x344
	.uleb128 0xf
	.4byte	0x53
	.uleb128 0xf
	.4byte	0x53
	.uleb128 0xf
	.4byte	0x34a
	.byte	0x0
	.uleb128 0xc
	.byte	0x4
	.4byte	0x2b4
	.uleb128 0xc
	.byte	0x4
	.4byte	0x2ae
	.uleb128 0xc
	.byte	0x4
	.4byte	0x325
	.uleb128 0x2
	.4byte	$LASF39
	.byte	0x2
	.byte	0x37
	.4byte	0x2b4
	.uleb128 0xc
	.byte	0x4
	.4byte	0x356
	.uleb128 0x10
	.4byte	0x3d9
	.byte	0x1
	.4byte	$LASF44
	.byte	0x1
	.byte	0x22
	.byte	0x1
	.4byte	$LFB2
	.4byte	$LFE2
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0x11
	.4byte	$LASF40
	.byte	0x1
	.byte	0x21
	.4byte	0x2ae
	.byte	0x1
	.byte	0x61
	.uleb128 0x11
	.4byte	$LASF41
	.byte	0x1
	.byte	0x21
	.4byte	0x2a8
	.byte	0x1
	.byte	0x64
	.uleb128 0x12
	.ascii	"i\000"
	.byte	0x1
	.byte	0x23
	.4byte	0x30
	.byte	0x1
	.byte	0x60
	.uleb128 0x12
	.ascii	"k\000"
	.byte	0x1
	.byte	0x23
	.4byte	0x30
	.byte	0x1
	.byte	0x55
	.uleb128 0x13
	.4byte	$LASF42
	.byte	0x1
	.byte	0x24
	.4byte	0x30
	.byte	0x1
	.byte	0x63
	.uleb128 0x13
	.4byte	$LASF43
	.byte	0x1
	.byte	0x25
	.4byte	0x3e9
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x12
	.ascii	"j\000"
	.byte	0x1
	.byte	0x26
	.4byte	0x53
	.byte	0x1
	.byte	0x54
	.byte	0x0
	.uleb128 0x7
	.4byte	0x3e9
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0x2
	.byte	0x0
	.uleb128 0x7
	.4byte	0x3f9
	.4byte	0x3d9
	.uleb128 0x9
	.4byte	0x85
	.byte	0x3
	.byte	0x0
	.uleb128 0x10
	.4byte	0x452
	.byte	0x1
	.4byte	$LASF45
	.byte	0x1
	.byte	0x59
	.byte	0x1
	.4byte	$LFB3
	.4byte	$LFE3
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0x11
	.4byte	$LASF40
	.byte	0x1
	.byte	0x58
	.4byte	0x2ae
	.byte	0x1
	.byte	0x60
	.uleb128 0x11
	.4byte	$LASF46
	.byte	0x1
	.byte	0x58
	.4byte	0x2a8
	.byte	0x1
	.byte	0x61
	.uleb128 0x12
	.ascii	"j\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x30
	.byte	0x1
	.byte	0x57
	.uleb128 0x12
	.ascii	"k\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x30
	.byte	0x1
	.byte	0x56
	.uleb128 0x13
	.4byte	$LASF47
	.byte	0x1
	.byte	0x5b
	.4byte	0x30
	.byte	0x1
	.byte	0x5a
	.byte	0x0
	.uleb128 0x14
	.4byte	0x511
	.byte	0x1
	.4byte	$LASF48
	.byte	0x1
	.byte	0x7c
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB4
	.4byte	$LFE4
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0x11
	.4byte	$LASF49
	.byte	0x1
	.byte	0x7b
	.4byte	0x361
	.byte	0x1
	.byte	0x54
	.uleb128 0x11
	.4byte	$LASF50
	.byte	0x1
	.byte	0x7b
	.4byte	0x53
	.byte	0x1
	.byte	0x55
	.uleb128 0x11
	.4byte	$LASF51
	.byte	0x1
	.byte	0x7b
	.4byte	0x53
	.byte	0x1
	.byte	0x63
	.uleb128 0x11
	.4byte	$LASF40
	.byte	0x1
	.byte	0x7b
	.4byte	0x34a
	.byte	0x1
	.byte	0x64
	.uleb128 0x12
	.ascii	"i\000"
	.byte	0x1
	.byte	0x7d
	.4byte	0x30
	.byte	0x1
	.byte	0x61
	.uleb128 0x12
	.ascii	"j\000"
	.byte	0x1
	.byte	0x7d
	.4byte	0x30
	.byte	0x1
	.byte	0x55
	.uleb128 0x13
	.4byte	$LASF52
	.byte	0x1
	.byte	0x7d
	.4byte	0x30
	.byte	0x1
	.byte	0x62
	.uleb128 0x13
	.4byte	$LASF41
	.byte	0x1
	.byte	0x7e
	.4byte	0x14a
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x13
	.4byte	$LASF46
	.byte	0x1
	.byte	0x7f
	.4byte	0x11a
	.byte	0x2
	.byte	0x91
	.sleb128 32
	.uleb128 0x15
	.4byte	0x502
	.byte	0x4
	.byte	0x1
	.byte	0x84
	.uleb128 0x16
	.4byte	$LASF53
	.byte	0x1
	.byte	0x82
	.4byte	0x5a
	.uleb128 0x17
	.ascii	"ch\000"
	.byte	0x1
	.byte	0x83
	.4byte	0x511
	.byte	0x0
	.uleb128 0x13
	.4byte	$LASF54
	.byte	0x1
	.byte	0x84
	.4byte	0x4e4
	.byte	0x2
	.byte	0x91
	.sleb128 40
	.byte	0x0
	.uleb128 0x7
	.4byte	0x521
	.4byte	0x16a
	.uleb128 0x9
	.4byte	0x85
	.byte	0x3
	.byte	0x0
	.uleb128 0x18
	.4byte	$LASF55
	.byte	0x3
	.byte	0xe0
	.4byte	0x52e
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.byte	0x4
	.4byte	0xff
	.uleb128 0x19
	.4byte	$LASF56
	.byte	0x1
	.byte	0x1c
	.4byte	0x546
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	stSysConfig
	.uleb128 0xc
	.byte	0x4
	.4byte	0x29d
	.uleb128 0x19
	.4byte	$LASF57
	.byte	0x1
	.byte	0xc0
	.4byte	0x356
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__u_boot_cmd_modify_sysc
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
	.uleb128 0x3
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
	.uleb128 0x4
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
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x13
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
	.uleb128 0x17
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
	.uleb128 0x16
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
	.byte	0x0
	.byte	0x0
	.uleb128 0x17
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x67
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x55f
	.4byte	0x367
	.ascii	"deal_ip\000"
	.4byte	0x3f9
	.ascii	"deal_mac\000"
	.4byte	0x452
	.ascii	"do_modify_sysc\000"
	.4byte	0x534
	.ascii	"stSysConfig\000"
	.4byte	0x54c
	.ascii	"__u_boot_cmd_modify_sysc\000"
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
$LASF47:
	.ascii	"mac_right\000"
$LASF36:
	.ascii	"repeatable\000"
$LASF35:
	.ascii	"maxargs\000"
$LASF3:
	.ascii	"signed char\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF49:
	.ascii	"cmdtp\000"
$LASF38:
	.ascii	"help\000"
$LASF59:
	.ascii	"cmd_modify_sysc.c\000"
$LASF39:
	.ascii	"cmd_tbl_t\000"
$LASF25:
	.ascii	"endian\000"
$LASF45:
	.ascii	"deal_mac\000"
$LASF28:
	.ascii	"product\000"
$LASF6:
	.ascii	"long long int\000"
$LASF23:
	.ascii	"second_image_len\000"
$LASF19:
	.ascii	"flash_layout_t\000"
$LASF12:
	.ascii	"sector_count\000"
$LASF32:
	.ascii	"swversion\000"
$LASF61:
	.ascii	"cmd_tbl_s\000"
$LASF24:
	.ascii	"second_image_checksum\000"
$LASF15:
	.ascii	"protect\000"
$LASF34:
	.ascii	"name\000"
$LASF18:
	.ascii	"zone_offset\000"
$LASF11:
	.ascii	"size\000"
$LASF41:
	.ascii	"iTempIP\000"
$LASF60:
	.ascii	"/home/xieshijing/DIR819-97597/DIR819/build.DIR-809/boot/"
	.ascii	"tbsboot/common\000"
$LASF29:
	.ascii	"version\000"
$LASF56:
	.ascii	"stSysConfig\000"
$LASF44:
	.ascii	"deal_ip\000"
$LASF21:
	.ascii	"first_image_len\000"
$LASF13:
	.ascii	"flash_id\000"
$LASF9:
	.ascii	"ushort\000"
$LASF33:
	.ascii	"sys_config_t\000"
$LASF46:
	.ascii	"iTempMAC\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF4:
	.ascii	"short int\000"
$LASF55:
	.ascii	"info\000"
$LASF27:
	.ascii	"board_id\000"
$LASF48:
	.ascii	"do_modify_sysc\000"
$LASF14:
	.ascii	"start\000"
$LASF54:
	.ascii	"iptmp\000"
$LASF42:
	.ascii	"ip_right\000"
$LASF20:
	.ascii	"layout\000"
$LASF50:
	.ascii	"flag\000"
$LASF17:
	.ascii	"char\000"
$LASF40:
	.ascii	"argv\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF43:
	.ascii	"ip_data\000"
$LASF57:
	.ascii	"__u_boot_cmd_modify_sysc\000"
$LASF52:
	.ascii	"temp\000"
$LASF37:
	.ascii	"usage\000"
$LASF31:
	.ascii	"region\000"
$LASF22:
	.ascii	"first_image_checksum\000"
$LASF58:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF16:
	.ascii	"flash_info_t\000"
$LASF53:
	.ascii	"iIpVal\000"
$LASF8:
	.ascii	"uchar\000"
$LASF26:
	.ascii	"image_mark\000"
$LASF51:
	.ascii	"argc\000"
$LASF30:
	.ascii	"model_name\000"
$LASF10:
	.ascii	"ulong\000"
	.ident	"GCC: (GNU) 3.4.2"
