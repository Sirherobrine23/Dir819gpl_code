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
	.rdata
	.align	2
	.type	__func__.3, @object
	.size	__func__.3, 13
__func__.3:
	.ascii	"mii_mgr_read\000"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"%s: Error, timeout!\n\000"
	.text
	.align	2
	.globl	mii_mgr_read
	.ent	mii_mgr_read
	.type	mii_mgr_read, @function
mii_mgr_read:
$LFB16:
	.file 1 "mt7620_eth.c"
	.loc 1 275 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	li	$2,-1341063168			# 0xffffffffb0110000
	ori	$8,$2,0x7004
	.loc 1 279 0
	move	$7,$0
$L6:
	.loc 1 280 0
	lw	$3,0($8)
	.loc 1 285 0
	.loc 1 281 0
	bgez	$3,$L15
	sll	$3,$5,25

	.loc 1 279 0
	addiu	$7,$7,1
	sltu	$2,$7,1000
	bne	$2,$0,$L6
	nop

$L15:
	.loc 1 285 0
	sll	$2,$4,20
	or	$2,$2,$3
	li	$3,-2146893824			# 0xffffffff80090000
	or	$3,$2,$3
	.loc 1 287 0
	sltu	$2,$7,2000
	.loc 1 286 0
	sw	$3,0($8)
	.loc 1 287 0
	beq	$2,$0,$L8
	li	$2,-1341063168			# 0xffffffffb0110000

	ori	$4,$2,0x7004
$L11:
	.loc 1 288 0
	lw	$3,0($4)
	.loc 1 293 0
	.loc 1 289 0
	bgez	$3,$L16
	andi	$2,$3,0xffff

	.loc 1 287 0
	addiu	$7,$7,1
	sltu	$2,$7,2000
	bne	$2,$0,$L11
	nop

$L8:
	.loc 1 293 0
	andi	$2,$3,0xffff
$L16:
	.loc 1 294 0
	sltu	$3,$7,2001
	.loc 1 293 0
	.loc 1 294 0
	bne	$3,$0,$L17
	sw	$2,0($6)

	.loc 1 295 0
	lw	$4,%got($LC0)($28)
	lw	$5,%got(__func__.3)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC0)
	jr	$25
	addiu	$5,$5,%lo(__func__.3)

$L17:
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE16:
	.end	mii_mgr_read
	.rdata
	.align	2
	.type	__func__.2, @object
	.size	__func__.2, 14
__func__.2:
	.ascii	"mii_mgr_write\000"
	.section	.rodata.str1.4
	.align	2
$LC1:
	.ascii	"%s timed out!\n\000"
	.text
	.align	2
	.globl	mii_mgr_write
	.ent	mii_mgr_write
	.type	mii_mgr_write, @function
mii_mgr_write:
$LFB17:
	.loc 1 300 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	li	$2,-1341063168			# 0xffffffffb0110000
	ori	$8,$2,0x7004
	.loc 1 304 0
	move	$7,$0
$L23:
	.loc 1 305 0
	lw	$3,0($8)
	.loc 1 310 0
	.loc 1 306 0
	bgez	$3,$L32
	sll	$3,$5,25

	.loc 1 304 0
	addiu	$7,$7,1
	sltu	$2,$7,1000
	bne	$2,$0,$L23
	nop

$L32:
	.loc 1 310 0
	sll	$2,$4,20
	or	$2,$2,$3
	or	$2,$2,$6
	li	$3,-2147155968			# 0xffffffff80050000
	or	$3,$2,$3
	.loc 1 312 0
	sltu	$2,$7,2000
	.loc 1 311 0
	sw	$3,0($8)
	.loc 1 312 0
	beq	$2,$0,$L25
	li	$2,-1341063168			# 0xffffffffb0110000

	ori	$4,$2,0x7004
$L28:
	.loc 1 313 0
	lw	$3,0($4)
	.loc 1 318 0
	.loc 1 314 0
	bgez	$3,$L33
	sltu	$2,$7,2001

	.loc 1 312 0
	addiu	$7,$7,1
	sltu	$2,$7,2000
	bne	$2,$0,$L28
	nop

$L25:
	.loc 1 318 0
	sltu	$2,$7,2001
$L33:
	.loc 1 319 0
	.loc 1 318 0
	bne	$2,$0,$L34
	lw	$4,%got($LC1)($28)

	.loc 1 319 0
	lw	$5,%got(__func__.2)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC1)
	jr	$25
	addiu	$5,$5,%lo(__func__.2)

$L34:
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE17:
	.end	mii_mgr_write
	.section	.rodata.str1.4
	.align	2
$LC3:
	.ascii	"Warning: still busy\n\000"
	.align	2
$LC4:
	.ascii	"Error: rw register failed\n\000"
	.align	2
$LC2:
	.ascii	"Warning: Abort rw rf register: too busy\n\000"
	.text
	.align	2
	.globl	rw_rf_reg
	.ent	rw_rf_reg
	.type	rw_rf_reg, @function
rw_rf_reg:
$LFB19:
	.loc 1 393 0
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
	li	$2,-1340604416			# 0xffffffffb0180000
	ori	$9,$2,0x500
	.loc 1 397 0
	move	$3,$0
$L36:
	.loc 1 398 0
	lw	$7,0($9)
	.loc 1 402 0
	sltu	$8,$3,10001
	.loc 1 399 0
	andi	$2,$7,0x1
	.loc 1 397 0
	.loc 1 399 0
	beq	$2,$0,$L37
	addiu	$3,$3,1

	.loc 1 403 0
	.loc 1 402 0
	beq	$8,$0,$L48
	lw	$25,%call16(printf)($28)

	.loc 1 397 0
	b	$L36
	nop

$L37:
	.loc 1 407 0
	lbu	$3,0($6)
	andi	$5,$5,0x3f
	sll	$2,$5,16
	sll	$3,$3,8
	or	$2,$2,$3
	.loc 1 409 0
	ori	$3,$2,0x11
	.loc 1 407 0
	ori	$7,$2,0x1
	.loc 1 411 0
	li	$2,-1340604416			# 0xffffffffb0180000
	.loc 1 409 0
	movn	$7,$3,$4
	.loc 1 411 0
	ori	$2,$2,0x500
	sw	$7,0($2)
	move	$8,$2
	.loc 1 412 0
	move	$3,$0
$L42:
	.loc 1 413 0
	lw	$7,0($8)
	.loc 1 417 0
	sltu	$4,$3,10001
	.loc 1 414 0
	andi	$2,$7,0x1
	.loc 1 412 0
	.loc 1 414 0
	beq	$2,$0,$L43
	addiu	$3,$3,1

	.loc 1 418 0
	.loc 1 417 0
	beq	$4,$0,$L49
	lw	$4,%got($LC3)($28)

	.loc 1 412 0
	b	$L42
	nop

$L43:
	.loc 1 422 0
	li	$2,-1340604416			# 0xffffffffb0180000
	ori	$2,$2,0x500
	lw	$7,0($2)
	.loc 1 423 0
	srl	$2,$7,16
	andi	$2,$2,0x3f
	.loc 1 424 0
	.loc 1 423 0
	beq	$2,$5,$L47
	lw	$4,%got($LC4)($28)

	.loc 1 424 0
	lw	$25,%call16(printf)($28)
	b	$L50
	addiu	$4,$4,%lo($LC4)

$L48:
	.loc 1 403 0
	lw	$4,%got($LC2)($28)
	b	$L50
	addiu	$4,$4,%lo($LC2)

$L49:
	.loc 1 418 0
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC3)
$L50:
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 419 0
	b	$L35
	li	$2,-1			# 0xffffffffffffffff

$L47:
	.loc 1 427 0
	andi	$2,$7,0xff00
	srl	$2,$2,8
	sw	$2,0($6)
	.loc 1 429 0
	move	$2,$0
$L35:
	.loc 1 430 0
	lw	$31,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE19:
	.end	rw_rf_reg
	.section	.rodata.str1.4
	.align	2
$LC5:
	.ascii	"set vlan timeout.\n\000"
	.text
	.align	2
	.ent	IsSwitchVlanTableBusy
	.type	IsSwitchVlanTableBusy, @function
IsSwitchVlanTableBusy:
$LFB21:
	.loc 1 517 0
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
	.loc 1 518 0
	move	$16,$0
$L56:
	.loc 1 522 0
	li	$2,-1341063168			# 0xffffffffb0110000
	ori	$2,$2,0x90
	lw	$2,0($2)
	.loc 1 526 0
	lw	$25,%call16(udelay)($28)
	.loc 1 523 0
	bgez	$2,$L53
	li	$4,1000			# 0x3e8

	.loc 1 521 0
	.loc 1 526 0
	jalr	$25
	addiu	$16,$16,1

	.loc 1 521 0
	slt	$2,$16,20
	.loc 1 526 0
	.loc 1 521 0
	bne	$2,$0,$L56
	lw	$28,16($sp)

$L53:
	.loc 1 528 0
	li	$2,20			# 0x14
	.loc 1 530 0
	.loc 1 528 0
	bne	$16,$2,$L51
	lw	$31,28($sp)

	.loc 1 529 0
	lw	$4,%got($LC5)($28)
	lw	$25,%call16(printf)($28)
	.loc 1 530 0
	lw	$16,24($sp)
	.loc 1 529 0
	addiu	$4,$4,%lo($LC5)
	.loc 1 530 0
	.loc 1 529 0
	jr	$25
	addiu	$sp,$sp,32

$L51:
	.loc 1 530 0
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE21:
	.end	IsSwitchVlanTableBusy
	.rdata
	.align	2
	.type	__func__.1, @object
	.size	__func__.1, 20
__func__.1:
	.ascii	"dma_descriptor_init\000"
	.section	.rodata.str1.4
	.align	2
$LC6:
	.ascii	"%s: NULL skb!\n\000"
	.text
	.align	2
	.globl	mt7620_eth_probe
	.ent	mt7620_eth_probe
	.type	mt7620_eth_probe, @function
mt7620_eth_probe:
$LFB24:
	.loc 1 621 0
	.frame	$sp,72,$31		# vars= 8, regs= 9/0, args= 16, gp= 8
	.mask	0x80ff0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-72
$LCFI5:
	sw	$31,64($sp)
$LCFI6:
	sw	$23,60($sp)
$LCFI7:
	sw	$22,56($sp)
$LCFI8:
	sw	$21,52($sp)
$LCFI9:
	sw	$20,48($sp)
$LCFI10:
	sw	$19,44($sp)
$LCFI11:
	sw	$18,40($sp)
$LCFI12:
	sw	$17,36($sp)
$LCFI13:
	sw	$16,32($sp)
$LCFI14:
	.cprestore	16
	.loc 1 627 0
	lw	$25,%call16(rw_rf_reg)($28)
	.loc 1 622 0
	li	$2,5			# 0x5
	.loc 1 627 0
	li	$5,29			# 0x1d
	addiu	$6,$sp,24
	.loc 1 622 0
	sw	$2,24($sp)
	.loc 1 621 0
	move	$17,$4
	.loc 1 627 0
	jalr	$25
	li	$4,1			# 0x1

	lw	$28,16($sp)
	.loc 1 628 0
	move	$4,$0
	li	$5,29			# 0x1d
	lw	$25,%call16(rw_rf_reg)($28)
	jalr	$25
	addiu	$6,$sp,24

	lw	$28,16($sp)
	li	$2,-1341128704			# 0xffffffffb0100000
	ori	$3,$2,0xa04
$L60:
	.loc 1 630 0
	lw	$24,0($3)
	.loc 1 631 0
	andi	$2,$24,0x1
	.loc 1 632 0
	.loc 1 631 0
	bne	$2,$0,$L60
	lw	$25,%call16(udelay)($28)

	.loc 1 632 0
	jalr	$25
	li	$4,10000			# 0x2710

$LBB2:
$LBB3:
	.loc 1 332 0
	li	$2,-1342177280			# 0xffffffffb0000000
	ori	$2,$2,0xc
$LBE3:
$LBE2:
	.loc 1 632 0
	lw	$28,16($sp)
$LBB4:
$LBB5:
	.loc 1 332 0
	lw	$2,0($2)
	.loc 1 334 0
	li	$4,1			# 0x1
	lw	$25,%call16(mii_mgr_write)($28)
	.loc 1 332 0
	srl	$2,$2,16
	andi	$2,$2,0x1
	sw	$2,28($sp)
	.loc 1 334 0
	li	$5,31			# 0x1f
	jalr	$25
	li	$6,16384			# 0x4000

	lw	$28,16($sp)
	.loc 1 335 0
	li	$4,1			# 0x1
	li	$5,17			# 0x11
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,29764			# 0x7444

	lw	$28,16($sp)
	.loc 1 336 0
	lw	$2,28($sp)
	beq	$2,$0,$L63
	lw	$25,%call16(mii_mgr_write)($28)

	.loc 1 337 0
	li	$4,1			# 0x1
	li	$5,19			# 0x13
	b	$L105
	li	$6,276			# 0x114

$L63:
	.loc 1 339 0
	li	$4,1			# 0x1
	li	$5,19			# 0x13
	li	$6,279			# 0x117
$L105:
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 341 0
	li	$4,1			# 0x1
	li	$5,22			# 0x16
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,4303			# 0x10cf

	lw	$28,16($sp)
	.loc 1 342 0
	li	$4,1			# 0x1
	li	$5,25			# 0x19
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,25106			# 0x6212

	lw	$28,16($sp)
	.loc 1 343 0
	li	$4,1			# 0x1
	li	$5,26			# 0x1a
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,1911			# 0x777

	lw	$28,16($sp)
	.loc 1 344 0
	li	$4,1			# 0x1
	li	$5,29			# 0x1d
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,16384			# 0x4000

	lw	$28,16($sp)
	.loc 1 345 0
	li	$4,1			# 0x1
	li	$5,28			# 0x1c
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,49271			# 0xc077

	lw	$28,16($sp)
	.loc 1 346 0
	li	$4,1			# 0x1
	li	$5,24			# 0x18
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	move	$6,$0

	lw	$28,16($sp)
	.loc 1 347 0
	li	$4,1			# 0x1
	li	$5,31			# 0x1f
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,12288			# 0x3000

	lw	$28,16($sp)
	.loc 1 348 0
	li	$4,1			# 0x1
	li	$5,17			# 0x11
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,18488			# 0x4838

	lw	$28,16($sp)
	.loc 1 349 0
	li	$4,1			# 0x1
	li	$5,31			# 0x1f
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,8192			# 0x2000

	lw	$28,16($sp)
	.loc 1 350 0
	lw	$2,28($sp)
	beq	$2,$0,$L65
	lw	$25,%call16(mii_mgr_write)($28)

	.loc 1 351 0
	li	$4,1			# 0x1
	li	$5,21			# 0x15
	jalr	$25
	li	$6,1301			# 0x515

	lw	$28,16($sp)
	.loc 1 352 0
	li	$4,1			# 0x1
	li	$5,22			# 0x16
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,83			# 0x53

	lw	$28,16($sp)
	.loc 1 353 0
	li	$4,1			# 0x1
	li	$5,23			# 0x17
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,191			# 0xbf

	lw	$28,16($sp)
	.loc 1 354 0
	li	$4,1			# 0x1
	li	$5,24			# 0x18
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,2735			# 0xaaf

	lw	$28,16($sp)
	.loc 1 355 0
	li	$4,1			# 0x1
	li	$5,25			# 0x19
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,4013			# 0xfad

	lw	$28,16($sp)
	.loc 1 356 0
	li	$4,1			# 0x1
	li	$5,26			# 0x1a
	lw	$25,%call16(mii_mgr_write)($28)
	b	$L106
	li	$6,4033			# 0xfc1

$L65:
	.loc 1 358 0
	li	$4,1			# 0x1
	li	$5,21			# 0x15
	jalr	$25
	li	$6,1303			# 0x517

	lw	$28,16($sp)
	.loc 1 359 0
	li	$4,1			# 0x1
	li	$5,22			# 0x16
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,4050			# 0xfd2

	lw	$28,16($sp)
	.loc 1 360 0
	li	$4,1			# 0x1
	li	$5,23			# 0x17
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,191			# 0xbf

	lw	$28,16($sp)
	.loc 1 361 0
	li	$4,1			# 0x1
	li	$5,24			# 0x18
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,2731			# 0xaab

	lw	$28,16($sp)
	.loc 1 362 0
	li	$4,1			# 0x1
	li	$5,25			# 0x19
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,174			# 0xae

	lw	$28,16($sp)
	.loc 1 363 0
	li	$4,1			# 0x1
	li	$5,26			# 0x1a
	lw	$25,%call16(mii_mgr_write)($28)
	li	$6,4095			# 0xfff
$L106:
	.loc 1 368 0
	.loc 1 363 0
	jalr	$25
	move	$16,$0

	lw	$28,16($sp)
	.loc 1 365 0
	li	$4,1			# 0x1
	li	$5,31			# 0x1f
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,4096			# 0x1000

	lw	$28,16($sp)
	.loc 1 366 0
	li	$4,1			# 0x1
	li	$5,17			# 0x11
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,59384			# 0xe7f8

	lw	$28,16($sp)
	.loc 1 367 0
	li	$4,1			# 0x1
	li	$5,31			# 0x1f
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,32768			# 0x8000

	lw	$28,16($sp)
$L70:
	.loc 1 369 0
	lw	$25,%call16(mii_mgr_write)($28)
	move	$4,$16
	li	$5,30			# 0x1e
	jalr	$25
	li	$6,40960			# 0xa000

	lw	$28,16($sp)
	.loc 1 370 0
	move	$4,$16
	li	$5,4			# 0x4
	lw	$25,%call16(mii_mgr_write)($28)
	.loc 1 368 0
	addiu	$16,$16,1
	.loc 1 370 0
	jalr	$25
	li	$6,1505			# 0x5e1

	.loc 1 368 0
	sltu	$2,$16,5
	.loc 1 370 0
	.loc 1 368 0
	bne	$2,$0,$L70
	lw	$28,16($sp)

	.loc 1 372 0
	lw	$25,%call16(mii_mgr_write)($28)
	li	$4,1			# 0x1
	li	$5,31			# 0x1f
	jalr	$25
	li	$6,40960			# 0xa000

	lw	$28,16($sp)
	.loc 1 373 0
	move	$4,$0
	li	$5,16			# 0x10
	lw	$25,%call16(mii_mgr_write)($28)
	li	$6,4369			# 0x1111
	.loc 1 378 0
	.loc 1 373 0
	jalr	$25
	move	$16,$0

	lw	$28,16($sp)
	.loc 1 374 0
	li	$4,1			# 0x1
	li	$5,16			# 0x10
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,4112			# 0x1010

	lw	$28,16($sp)
	.loc 1 375 0
	li	$4,2			# 0x2
	li	$5,16			# 0x10
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,5397			# 0x1515

	lw	$28,16($sp)
	.loc 1 376 0
	li	$4,3			# 0x3
	li	$5,16			# 0x10
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,3855			# 0xf0f

	lw	$28,16($sp)
	.loc 1 377 0
	li	$4,4			# 0x4
	li	$5,16			# 0x10
	lw	$25,%call16(mii_mgr_write)($28)
	jalr	$25
	li	$6,4883			# 0x1313

	lw	$28,16($sp)
$L74:
	.loc 1 379 0
	lw	$25,%call16(mii_mgr_read)($28)
	move	$4,$16
	move	$5,$0
	jalr	$25
	addiu	$6,$sp,28

	lw	$28,16($sp)
	.loc 1 380 0
	lw	$6,28($sp)
	.loc 1 381 0
	move	$4,$16
	lw	$25,%call16(mii_mgr_write)($28)
	.loc 1 380 0
	ori	$6,$6,0x1200
	sw	$6,28($sp)
	.loc 1 378 0
	addiu	$16,$16,1
	.loc 1 381 0
	jalr	$25
	move	$5,$0

	.loc 1 378 0
	sltu	$2,$16,5
	.loc 1 381 0
	.loc 1 378 0
	bne	$2,$0,$L74
	lw	$28,16($sp)

	.loc 1 383 0
	li	$5,-1342177280			# 0xffffffffb0000000
	ori	$5,$5,0x14
	lw	$3,0($5)
	.loc 1 385 0
	li	$2,-65536			# 0xffffffffffff0000
	ori	$2,$2,0x3fff
	.loc 1 384 0
	ori	$3,$3,0x100
	.loc 1 385 0
	and	$3,$3,$2
	.loc 1 387 0
	li	$4,-1341063168			# 0xffffffffb0110000
	li	$2,327680			# 0x50000
	ori	$6,$4,0x3600
	ori	$2,$2,0xe33b
	.loc 1 385 0
	sw	$3,28($sp)
	.loc 1 386 0
	sw	$3,0($5)
	.loc 1 387 0
	sw	$2,0($6)
	.loc 1 388 0
	li	$2,2139029504			# 0x7f7f0000
	.loc 1 389 0
	ori	$7,$4,0x3500
	.loc 1 388 0
	ori	$2,$2,0x7fe0
	ori	$4,$4,0x10
	sw	$2,0($4)
	.loc 1 389 0
	li	$2,32768			# 0x8000
	sw	$2,0($7)
$LBE5:
$LBE4:
	.loc 1 635 0
	lbu	$2,16($17)
	lbu	$3,17($17)
	.loc 1 636 0
	li	$6,-1341128704			# 0xffffffffb0100000
	.loc 1 635 0
	sll	$2,$2,8
	or	$24,$2,$3
	.loc 1 636 0
	ori	$2,$6,0x60c
	sw	$24,0($2)
	.loc 1 637 0
	lbu	$3,18($17)
	lbu	$2,19($17)
$LBB6:
$LBB7:
	.loc 1 458 0
	li	$4,536805376			# 0x1fff0000
$LBE7:
$LBE6:
	.loc 1 637 0
	sll	$3,$3,24
	sll	$2,$2,16
	or	$24,$3,$2
$LBB8:
$LBB9:
	.loc 1 459 0
	lw	$3,%got(tx_ring_cache)($28)
	.loc 1 458 0
	lw	$2,%got(rx_ring_cache)($28)
$LBE9:
$LBE8:
	.loc 1 638 0
	lbu	$5,20($17)
$LBB10:
$LBB11:
	.loc 1 458 0
	ori	$4,$4,0xffff
	lw	$21,%got(rx_ring)($28)
	.loc 1 459 0
	addiu	$3,$3,%lo(tx_ring_cache)
	.loc 1 458 0
	addiu	$2,$2,%lo(rx_ring_cache)
$LBE11:
$LBE10:
	.loc 1 638 0
	lbu	$7,21($17)
$LBB12:
$LBB13:
	.loc 1 459 0
	and	$3,$3,$4
	.loc 1 458 0
	and	$2,$2,$4
	li	$4,-1610612736			# 0xffffffffa0000000
	or	$2,$2,$4
$LBE13:
$LBE12:
	.loc 1 638 0
	sll	$5,$5,8
$LBB14:
$LBB15:
	.loc 1 459 0
	lw	$22,%got(tx_ring)($28)
	.loc 1 458 0
	sw	$2,%lo(rx_ring)($21)
	lw	$2,%got(txskbs)($28)
$LBE15:
$LBE14:
	.loc 1 638 0
	or	$5,$5,$7
	.loc 1 639 0
	ori	$6,$6,0x608
	.loc 1 638 0
	or	$24,$24,$5
$LBB16:
$LBB17:
	.loc 1 459 0
	or	$3,$3,$4
$LBE17:
$LBE16:
	.loc 1 639 0
	sw	$24,0($6)
$LBB18:
$LBB19:
	.loc 1 459 0
	sw	$3,%lo(tx_ring)($22)
	addiu	$6,$2,%lo(txskbs)
	.loc 1 462 0
	move	$17,$0
	li	$7,-128			# 0xffffffffffffff80
$L79:
	.loc 1 463 0
	lw	$3,%lo(tx_ring)($22)
	sll	$4,$17,4
	.loc 1 462 0
	addiu	$17,$17,1
	.loc 1 463 0
	addu	$3,$4,$3
	lbu	$2,7($3)
	.loc 1 462 0
	slt	$5,$17,64
	.loc 1 463 0
	ori	$2,$2,0x40
	sb	$2,7($3)
	.loc 1 464 0
	lw	$2,%lo(tx_ring)($22)
	addu	$4,$4,$2
	lbu	$2,7($4)
	or	$2,$7,$2
	sb	$2,7($4)
	.loc 1 465 0
	sw	$0,0($6)
	.loc 1 462 0
	bne	$5,$0,$L79
	addiu	$6,$6,4

	.loc 1 467 0
	move	$17,$0
$L86:
	.loc 1 468 0
	lw	$3,%lo(rx_ring)($21)
	sll	$18,$17,4
	.loc 1 470 0
	lw	$25,%call16(alloc_skb)($28)
	.loc 1 468 0
	addu	$3,$18,$3
	lbu	$2,7($3)
	sb	$0,6($3)
	.loc 1 470 0
	li	$4,1600			# 0x640
	.loc 1 468 0
	andi	$2,$2,0xc0
	ori	$2,$2,0x6
	sb	$2,7($3)
	.loc 1 469 0
	lw	$3,%lo(rx_ring)($21)
	addu	$3,$18,$3
	lbu	$2,7($3)
	andi	$2,$2,0x7f
	.loc 1 470 0
	jalr	$25
	sb	$2,7($3)

	lw	$28,16($sp)
	move	$16,$2
	.loc 1 475 0
	move	$4,$2
	lw	$25,%call16(skb_reserve)($28)
	.loc 1 471 0
	beq	$2,$0,$L104
	li	$5,2			# 0x2

	.loc 1 475 0
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 476 0
	li	$2,536805376			# 0x1fff0000
	lw	$3,%lo(rx_ring)($21)
	lw	$5,1600($16)
	ori	$20,$2,0xffff
	.loc 1 477 0
	lw	$2,%got(rxskbs)($28)
	.loc 1 476 0
	addu	$3,$18,$3
	and	$5,$5,$20
	.loc 1 477 0
	sll	$4,$17,2
	addiu	$2,$2,%lo(rxskbs)
	.loc 1 467 0
	addiu	$17,$17,1
	.loc 1 477 0
	addu	$4,$4,$2
	.loc 1 476 0
	swl	$5,3($3)
	.loc 1 467 0
	slt	$2,$17,64
	.loc 1 476 0
	swr	$5,0($3)
	.loc 1 477 0
	.loc 1 467 0
	bne	$2,$0,$L86
	sw	$16,0($4)

	.loc 1 481 0
	lw	$18,%got(cur_txd_idx)($28)
	.loc 1 480 0
	lw	$2,%got(cur_rxd_idx)($28)
	.loc 1 482 0
	li	$16,-1341128704			# 0xffffffffb0100000
	.loc 1 483 0
	lw	$25,%call16(udelay)($28)
	.loc 1 482 0
	ori	$17,$16,0xa04
	lw	$19,0($17)
	.loc 1 483 0
	li	$4,100			# 0x64
	.loc 1 480 0
	sw	$0,%lo(cur_rxd_idx)($2)
	.loc 1 481 0
	.loc 1 483 0
	jalr	$25
	sw	$0,%lo(cur_txd_idx)($18)

	lw	$28,16($sp)
	.loc 1 485 0
	li	$2,-2147483648			# 0xffffffff80000000
	.loc 1 484 0
	andi	$19,$19,0xffff
	.loc 1 487 0
	lw	$25,%call16(udelay)($28)
	.loc 1 485 0
	or	$19,$19,$2
	.loc 1 486 0
	sw	$19,0($17)
	.loc 1 487 0
	jalr	$25
	li	$4,500			# 0x1f4

	.loc 1 489 0
	lw	$2,%lo(rx_ring)($21)
	.loc 1 487 0
	lw	$28,16($sp)
	.loc 1 489 0
	ori	$4,$16,0x900
	and	$2,$2,$20
	.loc 1 492 0
	lw	$3,%lo(tx_ring)($22)
	.loc 1 494 0
	lw	$11,%lo(cur_txd_idx)($18)
	.loc 1 488 0
	lw	$19,0($17)
	.loc 1 490 0
	li	$9,64			# 0x40
	.loc 1 489 0
	sw	$2,0($4)
	.loc 1 490 0
	ori	$5,$16,0x904
	.loc 1 491 0
	ori	$6,$16,0x908
	li	$2,63			# 0x3f
	.loc 1 496 0
	lw	$25,%call16(udelay)($28)
	.loc 1 490 0
	sw	$9,0($5)
	.loc 1 491 0
	sw	$2,0($6)
	.loc 1 495 0
	li	$2,65536			# 0x10000
	ori	$10,$16,0xa08
	.loc 1 492 0
	ori	$7,$16,0x800
	.loc 1 493 0
	ori	$8,$16,0x804
	.loc 1 492 0
	and	$3,$3,$20
	.loc 1 494 0
	ori	$16,$16,0x808
	.loc 1 495 0
	ori	$2,$2,0x1
	.loc 1 496 0
	li	$4,500			# 0x1f4
	.loc 1 492 0
	sw	$3,0($7)
	.loc 1 493 0
	sw	$9,0($8)
	.loc 1 494 0
	sw	$11,0($16)
	.loc 1 495 0
	sw	$2,0($10)
	b	$L108
	nop

$L104:
$L84:
	.loc 1 472 0
	lw	$4,%got($LC6)($28)
	lw	$5,%got(__func__.1)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC6)
	jalr	$25
	addiu	$5,$5,%lo(__func__.1)

$L107:
	.loc 1 499 0
	bltz	$17,$L103
	lw	$28,16($sp)

	.loc 1 500 0
	lw	$3,%lo(rx_ring)($21)
	sll	$2,$17,4
	.loc 1 501 0
	lw	$25,%call16(free_skb)($28)
	.loc 1 500 0
	addu	$2,$2,$3
	lwl	$3,3($2)
	.loc 1 501 0
	li	$4,-2147483648			# 0xffffffff80000000
	.loc 1 499 0
	addiu	$17,$17,-1
	.loc 1 500 0
	lwr	$3,0($2)
	li	$2,536805376			# 0x1fff0000
	ori	$2,$2,0xffff
	and	$3,$3,$2
	.loc 1 501 0
	jalr	$25
	or	$4,$3,$4

	b	$L107
	nop

$L103:
	.loc 1 503 0
	lw	$25,%call16(free)($28)
	move	$4,$0
$L108:
$L87:
	.loc 1 641 0
	.loc 1 503 0
	jalr	$25
	li	$17,-1341128704			# 0xffffffffb0100000

$LBE19:
$LBE18:
	.loc 1 641 0
	lw	$24,0($17)
	.loc 1 644 0
	ori	$16,$17,0x600
$LBB20:
$LBB21:
	.loc 1 503 0
	lw	$28,16($sp)
$LBE21:
$LBE20:
	.loc 1 642 0
	ori	$24,$24,0xc800
	.loc 1 643 0
	sw	$24,0($17)
	.loc 1 644 0
	lw	$24,0($16)
	.loc 1 647 0
	lw	$25,%call16(udelay)($28)
	.loc 1 645 0
	li	$2,-8			# 0xfffffffffffffff8
	and	$24,$24,$2
	.loc 1 646 0
	sw	$24,0($16)
	.loc 1 647 0
	jalr	$25
	li	$4,500			# 0x1f4

	lw	$28,16($sp)
	.loc 1 649 0
	li	$2,-2142240768			# 0xffffffff80500000
	.loc 1 648 0
	lw	$24,0($16)
	.loc 1 649 0
	ori	$24,$2,0x4000
$LBB22:
$LBB23:
	.loc 1 583 0
	lw	$2,%got(IsSwitchVlanTableBusy)($28)
	.loc 1 564 0
	li	$3,-1341063168			# 0xffffffffb0110000
	li	$4,16711680			# 0xff0000
	ori	$4,$4,0x3
	.loc 1 583 0
	addiu	$23,$2,%lo(IsSwitchVlanTableBusy)
$LBE23:
$LBE22:
	.loc 1 650 0
	ori	$17,$17,0x500
$LBB24:
$LBB25:
	.loc 1 564 0
	ori	$2,$3,0x2004
$LBE25:
$LBE24:
	.loc 1 650 0
	sw	$24,0($17)
$LBB26:
$LBB27:
	.loc 1 565 0
	ori	$7,$3,0x2104
	.loc 1 564 0
	sw	$4,0($2)
	.loc 1 566 0
	ori	$8,$3,0x2204
	.loc 1 567 0
	ori	$9,$3,0x2304
	.loc 1 568 0
	ori	$10,$3,0x2404
	.loc 1 569 0
	ori	$11,$3,0x2504
	.loc 1 572 0
	ori	$16,$3,0x2610
	li	$2,-2130706432			# 0xffffffff81000000
	.loc 1 565 0
	sw	$4,0($7)
	.loc 1 573 0
	li	$6,65536			# 0x10000
	.loc 1 566 0
	sw	$4,0($8)
	.loc 1 582 0
	li	$18,-2147483648			# 0xffffffff80000000
	.loc 1 567 0
	sw	$4,0($9)
	.loc 1 568 0
	sw	$4,0($10)
	.loc 1 569 0
	sw	$4,0($11)
	.loc 1 572 0
	sw	$2,0($16)
	.loc 1 581 0
	li	$2,1090387968			# 0x40fe0000
	.loc 1 574 0
	ori	$5,$6,0x1
	.loc 1 582 0
	ori	$22,$3,0x90
	.loc 1 581 0
	ori	$21,$3,0x94
	.loc 1 574 0
	ori	$12,$3,0x2114
	.loc 1 575 0
	ori	$13,$3,0x2214
	.loc 1 576 0
	ori	$14,$3,0x2314
	.loc 1 577 0
	ori	$15,$3,0x2414
	.loc 1 573 0
	ori	$19,$3,0x2014
	ori	$6,$6,0x2
	.loc 1 578 0
	ori	$3,$3,0x2514
	.loc 1 582 0
	ori	$20,$18,0x1000
	.loc 1 581 0
	ori	$2,$2,0x1
	.loc 1 573 0
	sw	$6,0($19)
	.loc 1 583 0
	move	$25,$23
	.loc 1 574 0
	sw	$5,0($12)
	.loc 1 575 0
	sw	$5,0($13)
	.loc 1 576 0
	sw	$5,0($14)
	.loc 1 577 0
	sw	$5,0($15)
	.loc 1 578 0
	sw	$5,0($3)
	.loc 1 581 0
	sw	$2,0($21)
	.loc 1 582 0
	sw	$20,0($22)
	.loc 1 586 0
	.loc 1 583 0
	jalr	$25
	ori	$18,$18,0x1001

	.loc 1 585 0
	li	$2,1086390272			# 0x40c10000
	ori	$2,$2,0x1
	sw	$2,0($21)
	.loc 1 587 0
	move	$25,$23
	.loc 1 586 0
	sw	$18,0($22)
	.loc 1 587 0
	jalr	$25
	nop

	lw	$28,16($sp)
$LBE27:
$LBE26:
	lw	$31,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,72

	.set	macro
	.set	reorder
$LFE24:
	.end	mt7620_eth_probe
	.align	2
	.globl	mt7620_eth_link_change
	.ent	mt7620_eth_link_change
	.type	mt7620_eth_link_change, @function
mt7620_eth_link_change:
$LFB26:
	.loc 1 676 0
	.frame	$sp,48,$31		# vars= 8, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-48
$LCFI15:
	sw	$31,40($sp)
$LCFI16:
	sw	$17,36($sp)
$LCFI17:
	sw	$16,32($sp)
$LCFI18:
	.cprestore	16
$LBB28:
$LBB29:
	.loc 1 664 0
	move	$17,$0
	.loc 1 667 0
	move	$16,$0
$L113:
	.loc 1 668 0
	lw	$25,%call16(mii_mgr_read)($28)
	move	$4,$16
	li	$5,1			# 0x1
	jalr	$25
	addiu	$6,$sp,28

	.loc 1 669 0
	lw	$2,28($sp)
	.loc 1 667 0
	addiu	$3,$16,1
	.loc 1 668 0
	lw	$28,16($sp)
	.loc 1 669 0
	srl	$2,$2,2
	andi	$2,$2,0x1
	.loc 1 670 0
	sll	$2,$2,$16
	.loc 1 667 0
	andi	$16,$3,0x00ff
	sltu	$3,$16,5
	.loc 1 670 0
	.loc 1 667 0
	bne	$3,$0,$L113
	or	$17,$17,$2

	.loc 1 672 0
	sw	$17,24($sp)
$LBE29:
$LBE28:
	.loc 1 682 0
	move	$16,$0
$L120:
	.loc 1 683 0
	lw	$3,24($sp)
	li	$2,1			# 0x1
	sll	$2,$2,$16
	and	$3,$3,$2
	addiu	$2,$16,18
	.loc 1 685 0
	li	$5,1			# 0x1
	lw	$25,%call16(SetLed)($28)
	.loc 1 683 0
	bne	$3,$0,$L125
	move	$4,$2

	.loc 1 689 0
	move	$4,$2
	move	$5,$0
$L125:
	.loc 1 682 0
	.loc 1 689 0
	jalr	$25
	addiu	$16,$16,1

	.loc 1 682 0
	slt	$2,$16,5
	.loc 1 689 0
	.loc 1 682 0
	bne	$2,$0,$L120
	lw	$28,16($sp)

	lw	$31,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
$LFE26:
	.end	mt7620_eth_link_change
	.section	.rodata.str1.4
	.align	2
$LC7:
	.ascii	"Packet Length has error In normal mode!\n\000"
	.align	2
$LC8:
	.ascii	"Packet received from CPU port, len=%d\n\000"
	.text
	.align	2
	.ent	mt7620_eth_recv
	.type	mt7620_eth_recv, @function
mt7620_eth_recv:
$LFB27:
	.loc 1 695 0
	.frame	$sp,56,$31		# vars= 0, regs= 7/0, args= 16, gp= 8
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-56
$LCFI19:
	sw	$31,48($sp)
$LCFI20:
	sw	$21,44($sp)
$LCFI21:
	sw	$20,40($sp)
$LCFI22:
	sw	$19,36($sp)
$LCFI23:
	sw	$18,32($sp)
$LCFI24:
	sw	$17,28($sp)
$LCFI25:
	sw	$16,24($sp)
$LCFI26:
	.cprestore	16
	.loc 1 702 0
	li	$2,-1341128704			# 0xffffffffb0100000
	ori	$3,$2,0x8
	lw	$5,0($3)
	.loc 1 706 0
	lw	$18,%got(cur_rxd_idx)($28)
	lw	$20,%got(rx_ring)($28)
	.loc 1 703 0
	sw	$5,0($3)
	.loc 1 704 0
	ori	$2,$2,0xa20
	.loc 1 706 0
	lw	$7,%lo(cur_rxd_idx)($18)
	.loc 1 704 0
	lw	$5,0($2)
	.loc 1 706 0
	lw	$4,%lo(rx_ring)($20)
	sll	$3,$7,4
	.loc 1 705 0
	sw	$5,0($2)
	.loc 1 706 0
	addu	$6,$3,$4
	lbu	$4,7($6)
	srl	$2,$4,7
	.loc 1 698 0
	.loc 1 706 0
	beq	$2,$0,$L127
	move	$19,$0

	.loc 1 708 0
	lw	$21,%got(rxskbs)($28)
	.loc 1 707 0
	lbu	$5,6($6)
	andi	$4,$4,0x3f
	sll	$4,$4,8
	.loc 1 708 0
	sll	$2,$7,2
	addiu	$3,$21,%lo(rxskbs)
	addu	$2,$2,$3
	.loc 1 707 0
	or	$19,$4,$5
	.loc 1 708 0
	.loc 1 709 0
	bne	$19,$0,$L128
	lw	$16,0($2)

	.loc 1 710 0
	lw	$4,%got($LC7)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC7)

	.loc 1 719 0
	b	$L135
	lw	$28,16($sp)

$L128:
	.loc 1 713 0
	lbu	$2,14($6)
	li	$3,6			# 0x6
	srl	$2,$2,3
	andi	$2,$2,0x7
	.loc 1 716 0
	.loc 1 713 0
	beq	$2,$3,$L130
	li	$2,536805376			# 0x1fff0000

	.loc 1 716 0
	lw	$3,1600($16)
	lw	$25,%call16(NetReceive)($28)
	ori	$2,$2,0xffff
	and	$3,$3,$2
	li	$4,-1610612736			# 0xffffffffa0000000
	or	$4,$3,$4
	move	$5,$19
	.loc 1 714 0
	.loc 1 716 0
	jalr	$25
	sh	$19,1604($16)

	lw	$28,16($sp)
	.loc 1 717 0
	move	$4,$16
	lw	$25,%call16(skb_pull)($28)
	jalr	$25
	li	$5,14			# 0xe

	.loc 1 719 0
	b	$L135
	lw	$28,16($sp)

$L130:
	lw	$4,%got($LC8)($28)
	lw	$25,%call16(printf)($28)
	move	$5,$19
	jalr	$25
	addiu	$4,$4,%lo($LC8)

$L129:
	lw	$28,16($sp)
$L135:
	.loc 1 722 0
	lw	$25,%call16(alloc_skb)($28)
	jalr	$25
	li	$4,1600			# 0x640

	move	$17,$2
	.loc 1 723 0
	bne	$2,$0,$L132
	lw	$28,16($sp)

	.loc 1 724 0
	b	$L133
	move	$17,$16

$L132:
	.loc 1 726 0
	lw	$25,%call16(free_skb)($28)
	jalr	$25
	move	$4,$16

	lw	$28,16($sp)
	.loc 1 727 0
	move	$4,$17
	lw	$25,%call16(skb_reserve)($28)
	jalr	$25
	li	$5,2			# 0x2

	lw	$28,16($sp)
$L133:
	.loc 1 729 0
	lw	$3,%lo(cur_rxd_idx)($18)
	lw	$2,%lo(rx_ring)($20)
	.loc 1 733 0
	addiu	$5,$21,%lo(rxskbs)
	.loc 1 729 0
	sll	$3,$3,4
	addu	$3,$3,$2
	lbu	$2,7($3)
	andi	$2,$2,0x7f
	sb	$2,7($3)
	.loc 1 730 0
	lw	$3,%lo(cur_rxd_idx)($18)
	lw	$2,%lo(rx_ring)($20)
	sll	$3,$3,4
	addu	$3,$3,$2
	lbu	$2,7($3)
	andi	$2,$2,0xbf
	sb	$2,7($3)
	.loc 1 731 0
	lw	$2,%lo(cur_rxd_idx)($18)
	lw	$3,%lo(rx_ring)($20)
	sll	$2,$2,4
	addu	$2,$2,$3
	lbu	$3,7($2)
	sb	$0,6($2)
	andi	$3,$3,0xc0
	ori	$3,$3,0x6
	sb	$3,7($2)
	.loc 1 732 0
	lw	$3,%lo(cur_rxd_idx)($18)
	lw	$2,%lo(rx_ring)($20)
	lw	$4,1600($17)
	sll	$3,$3,4
	addu	$3,$3,$2
	li	$2,536805376			# 0x1fff0000
	ori	$2,$2,0xffff
	and	$4,$4,$2
	swl	$4,3($3)
	swr	$4,0($3)
	.loc 1 733 0
	lw	$4,%lo(cur_rxd_idx)($18)
	sll	$2,$4,2
	addu	$2,$2,$5
	.loc 1 735 0
	addiu	$3,$4,1
	.loc 1 733 0
	sw	$17,0($2)
	.loc 1 734 0
	li	$2,-1341128704			# 0xffffffffb0100000
	.loc 1 735 0
	andi	$3,$3,0x3f
	.loc 1 734 0
	ori	$2,$2,0x908
	.loc 1 735 0
	sw	$3,%lo(cur_rxd_idx)($18)
	.loc 1 734 0
	sw	$4,0($2)
$L127:
	.loc 1 739 0
	move	$2,$19
	lw	$31,48($sp)
	lw	$21,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,56

	.set	macro
	.set	reorder
$LFE27:
	.end	mt7620_eth_recv
	.rdata
	.align	2
	.type	__func__.0, @object
	.size	__func__.0, 16
__func__.0:
	.ascii	"mt7620_eth_send\000"
	.section	.rodata.str1.4
	.align	2
$LC9:
	.ascii	"%s: bad packet size: %d\n\000"
	.align	2
$LC10:
	.ascii	"%s: Fail to alloc skbuff\n\000"
	.align	2
$LC11:
	.ascii	"%s: Frame engine TXD[%d] is busy, drop packet!\n\000"
	.align	2
$LC12:
	.ascii	"TXD[%02d] @ %#x, DDONE=%d, SDP0=%#x\n\000"
	.text
	.align	2
	.ent	mt7620_eth_send
	.type	mt7620_eth_send, @function
mt7620_eth_send:
$LFB28:
	.loc 1 742 0
	.frame	$sp,56,$31		# vars= 0, regs= 6/0, args= 24, gp= 8
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-56
$LCFI27:
	sw	$31,52($sp)
$LCFI28:
	sw	$20,48($sp)
$LCFI29:
	sw	$19,44($sp)
$LCFI30:
	sw	$18,40($sp)
$LCFI31:
	sw	$17,36($sp)
$LCFI32:
	sw	$16,32($sp)
$LCFI33:
	.cprestore	24
	.loc 1 748 0
	addiu	$2,$6,-1
	sltu	$2,$2,1500
	.loc 1 742 0
	move	$17,$6
	move	$18,$5
	.loc 1 746 0
	.loc 1 748 0
	bne	$2,$0,$L137
	li	$20,-1			# 0xffffffffffffffff

	.loc 1 749 0
	move	$5,$4
	lw	$4,%got($LC9)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC9)

	.loc 1 773 0
	b	$L138
	lw	$28,24($sp)

$L137:
	.loc 1 753 0
	lw	$25,%call16(alloc_skb)($28)
	jalr	$25
	li	$4,1600			# 0x640

	move	$16,$2
	.loc 1 754 0
	bne	$2,$0,$L139
	lw	$28,24($sp)

	.loc 1 755 0
	lw	$4,%got($LC10)($28)
	lw	$5,%got(__func__.0)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC10)
	jalr	$25
	addiu	$5,$5,%lo(__func__.0)

	.loc 1 773 0
	b	$L138
	lw	$28,24($sp)

$L139:
	.loc 1 757 0
	slt	$2,$17,60
	.loc 1 758 0
	.loc 1 757 0
	beq	$2,$0,$L141
	li	$2,60

	.loc 1 758 0
	b	$L140
	sh	$2,1604($16)

$L141:
	.loc 1 760 0
	sh	$17,1604($16)
$L140:
	.loc 1 762 0
	lw	$25,%call16(memcpy)($28)
	lw	$4,1600($16)
	move	$6,$17
	jalr	$25
	move	$5,$18

	lw	$28,24($sp)
	.loc 1 764 0
	move	$17,$0
$L153:
	.loc 1 765 0
	lw	$5,%got(cur_txd_idx)($28)
	lw	$19,%got(tx_ring)($28)
	.loc 1 767 0
	li	$2,536805376			# 0x1fff0000
	.loc 1 765 0
	lw	$6,%lo(cur_txd_idx)($5)
	lw	$3,%lo(tx_ring)($19)
	.loc 1 767 0
	ori	$4,$2,0xffff
	.loc 1 765 0
	sll	$2,$6,4
	addu	$2,$2,$3
	lbu	$2,7($2)
	srl	$2,$2,7
	.loc 1 777 0
	.loc 1 765 0
	bne	$2,$0,$L159
	lw	$2,%lo(cur_txd_idx)($5)

	.loc 1 764 0
	.loc 1 767 0
	bne	$17,$4,$L145
	addiu	$17,$17,1

	addiu	$17,$17,-1
	.loc 1 768 0
	lw	$4,%got($LC11)($28)
	lw	$5,%got(__func__.0)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC11)
	jalr	$25
	addiu	$5,$5,%lo(__func__.0)

	lw	$28,24($sp)
	.loc 1 769 0
	move	$17,$0
$L152:
	.loc 1 770 0
	lw	$6,%lo(tx_ring)($19)
	sll	$2,$17,4
	lw	$4,%got($LC12)($28)
	addu	$6,$6,$2
	lwl	$2,3($6)
	lbu	$7,7($6)
	lw	$25,%call16(printf)($28)
	lwr	$2,0($6)
	move	$5,$17
	addiu	$4,$4,%lo($LC12)
	sw	$2,16($sp)
	srl	$7,$7,7
	.loc 1 769 0
	.loc 1 770 0
	jalr	$25
	addiu	$17,$17,1

	.loc 1 769 0
	sltu	$2,$17,64
	.loc 1 770 0
	.loc 1 769 0
	bne	$2,$0,$L152
	lw	$28,24($sp)

	.loc 1 773 0
	lw	$25,%call16(free_skb)($28)
	jalr	$25
	move	$4,$16

	.loc 1 774 0
	b	$L138
	lw	$28,24($sp)

$L145:
	.loc 1 764 0
	sltu	$2,$4,$17
	.loc 1 777 0
	.loc 1 764 0
	beq	$2,$0,$L153
	lw	$2,%lo(cur_txd_idx)($5)

$L159:
	.loc 1 777 0
	lw	$3,%got(txskbs)($28)
	sll	$2,$2,2
	addiu	$18,$3,%lo(txskbs)
	addu	$2,$2,$18
	lw	$4,0($2)
	.loc 1 778 0
	beq	$4,$0,$L154
	lw	$17,%got(cur_txd_idx)($28)

	.loc 1 779 0
	lw	$25,%call16(free_skb)($28)
	jalr	$25
	nop

	lw	$28,24($sp)
$L154:
	.loc 1 782 0
	lw	$3,%lo(cur_txd_idx)($17)
	.loc 1 783 0
	lw	$5,%lo(tx_ring)($19)
	lw	$4,1600($16)
	.loc 1 782 0
	sll	$2,$3,2
	addu	$2,$2,$18
	sw	$16,0($2)
	.loc 1 783 0
	li	$2,536805376			# 0x1fff0000
	ori	$2,$2,0xffff
	sll	$3,$3,4
	addu	$3,$3,$5
	and	$4,$4,$2
	.loc 1 781 0
	lhu	$20,1604($16)
	.loc 1 783 0
	swl	$4,3($3)
	swr	$4,0($3)
	.loc 1 784 0
	lw	$4,%lo(cur_txd_idx)($17)
	lw	$2,%lo(tx_ring)($19)
	lhu	$5,1604($16)
	sll	$4,$4,4
	addu	$4,$4,$2
	lbu	$3,7($4)
	srl	$2,$5,8
	andi	$2,$2,0x3f
	andi	$3,$3,0xc0
	or	$3,$3,$2
	sb	$3,7($4)
	sb	$5,6($4)
	.loc 1 785 0
	lw	$3,%lo(cur_txd_idx)($17)
	lw	$2,%lo(tx_ring)($19)
	sll	$3,$3,4
	addu	$3,$3,$2
	lbu	$2,7($3)
	andi	$2,$2,0x7f
	sb	$2,7($3)
	.loc 1 786 0
	lw	$3,%lo(cur_txd_idx)($17)
	.loc 1 787 0
	li	$2,-1341128704			# 0xffffffffb0100000
	ori	$2,$2,0x808
	.loc 1 786 0
	addiu	$3,$3,1
	andi	$3,$3,0x3f
	.loc 1 787 0
	sw	$3,0($2)
	.loc 1 786 0
	sw	$3,%lo(cur_txd_idx)($17)
$L138:
	.loc 1 790 0
	move	$2,$20
	lw	$31,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,56

	.set	macro
	.set	reorder
$LFE28:
	.end	mt7620_eth_send
	.align	2
	.globl	PHY_power_ops
	.ent	PHY_power_ops
	.type	PHY_power_ops, @function
PHY_power_ops:
$LFB29:
	.loc 1 793 0
	.frame	$sp,48,$31		# vars= 8, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-48
$LCFI34:
	sw	$31,40($sp)
$LCFI35:
	sw	$17,36($sp)
$LCFI36:
	sw	$16,32($sp)
$LCFI37:
	.cprestore	16
	.loc 1 796 0
	sltu	$2,$4,5
	.loc 1 793 0
	move	$16,$5
	.loc 1 797 0
	lw	$25,%call16(mii_mgr_read)($28)
	addiu	$6,$sp,24
	.loc 1 793 0
	move	$17,$4
	.loc 1 797 0
	move	$5,$0
	.loc 1 794 0
	.loc 1 796 0
	beq	$2,$0,$L160
	sw	$0,24($sp)

	.loc 1 797 0
	jalr	$25
	nop

	.loc 1 798 0
	lw	$3,24($sp)
	andi	$2,$3,0x800
	srl	$2,$2,11
	.loc 1 797 0
	.loc 1 798 0
	bne	$16,$2,$L160
	lw	$28,16($sp)

	.loc 1 802 0
	li	$2,-2049			# 0xfffffffffffff7ff
	and	$2,$3,$2
	.loc 1 803 0
	ori	$2,$2,0x1200
	.loc 1 800 0
	.loc 1 799 0
	bne	$16,$0,$L163
	ori	$3,$3,0x800

	.loc 1 800 0
	b	$L164
	sw	$3,24($sp)

$L163:
	.loc 1 803 0
	sw	$2,24($sp)
$L164:
	.loc 1 806 0
	lw	$25,%call16(mii_mgr_write)($28)
	lw	$6,24($sp)
	move	$4,$17
	jalr	$25
	move	$5,$0

	lw	$28,16($sp)
$L160:
	.loc 1 809 0
	lw	$31,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
$LFE29:
	.end	PHY_power_ops
	.align	2
	.globl	PHY_led_ops
	.ent	PHY_led_ops
	.type	PHY_led_ops, @function
PHY_led_ops:
$LFB30:
	.loc 1 812 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	.loc 1 817 0
	sltu	$4,$4,5
	.loc 1 820 0
	.loc 1 817 0
	beq	$4,$0,$L169
	sltu	$5,$5,2

	.loc 1 819 0
	li	$2,-1342177280			# 0xffffffffb0000000
	ori	$2,$2,0x60
	lw	$3,0($2)
	.loc 1 821 0
	.loc 1 820 0
	bne	$5,$0,$L167
	li	$2,32768			# 0x8000

	.loc 1 821 0
	nor	$2,$0,$2
	b	$L168
	and	$3,$3,$2

$L167:
	.loc 1 823 0
	ori	$3,$3,0x8000
$L168:
	.loc 1 825 0
	li	$2,-1342177280			# 0xffffffffb0000000
	ori	$2,$2,0x60
	sw	$3,0($2)
$L169:
	j	$31
	nop

	.set	macro
	.set	reorder
$LFE30:
	.end	PHY_led_ops
	.align	2
	.globl	mt7620_start_eth
	.ent	mt7620_start_eth
	.type	mt7620_start_eth, @function
mt7620_start_eth:
$LFB31:
	.loc 1 830 0
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI38:
	sw	$31,32($sp)
$LCFI39:
	sw	$17,28($sp)
$LCFI40:
	sw	$16,24($sp)
$LCFI41:
	.cprestore	16
	.loc 1 833 0
	lw	$25,%call16(udelay)($28)
	.loc 1 832 0
	li	$17,-1341128704			# 0xffffffffb0100000
	ori	$17,$17,0xa04
	.loc 1 833 0
	li	$4,100			# 0x64
	.loc 1 832 0
	lw	$16,0($17)
	.loc 1 834 0
	.loc 1 833 0
	jalr	$25
	ori	$16,$16,0x45

	lw	$28,16($sp)
	.loc 1 835 0
	sw	$16,0($17)
	.loc 1 836 0
	lw	$25,%call16(udelay)($28)
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	li	$4,500			# 0x1f4
	jr	$25
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE31:
	.end	mt7620_start_eth
	.align	2
	.globl	mt7620_stop_eth
	.ent	mt7620_stop_eth
	.type	mt7620_stop_eth, @function
mt7620_stop_eth:
$LFB32:
	.loc 1 840 0
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI42:
	sw	$31,32($sp)
$LCFI43:
	sw	$17,28($sp)
$LCFI44:
	sw	$16,24($sp)
$LCFI45:
	.cprestore	16
	.loc 1 843 0
	lw	$25,%call16(udelay)($28)
	.loc 1 842 0
	li	$17,-1341128704			# 0xffffffffb0100000
	ori	$17,$17,0xa04
	.loc 1 843 0
	li	$4,100			# 0x64
	.loc 1 842 0
	lw	$16,0($17)
	.loc 1 843 0
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 844 0
	li	$2,-70			# 0xffffffffffffffba
	and	$16,$16,$2
	.loc 1 846 0
	lw	$25,%call16(udelay)($28)
	.loc 1 845 0
	sw	$16,0($17)
	.loc 1 846 0
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	li	$4,500			# 0x1f4
	jr	$25
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE32:
	.end	mt7620_stop_eth
	.align	2
	.globl	mt7620_eth_init
	.ent	mt7620_eth_init
	.type	mt7620_eth_init, @function
mt7620_eth_init:
$LFB33:
	.loc 1 850 0
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI46:
	sw	$31,32($sp)
$LCFI47:
	sw	$17,28($sp)
$LCFI48:
	sw	$16,24($sp)
$LCFI49:
	.cprestore	16
	.loc 1 850 0
	move	$17,$4
	.loc 1 853 0
	move	$16,$0
$L176:
	.loc 1 854 0
	lw	$25,%call16(PHY_power_ops)($28)
	move	$4,$16
	jalr	$25
	li	$5,1			# 0x1

	lw	$28,16($sp)
	.loc 1 855 0
	move	$4,$16
	li	$5,9			# 0x9
	lw	$25,%call16(PHY_led_ops)($28)
	.loc 1 853 0
	.loc 1 855 0
	jalr	$25
	addiu	$16,$16,1

	.loc 1 853 0
	slt	$2,$16,5
	.loc 1 855 0
	.loc 1 853 0
	bne	$2,$0,$L176
	lw	$28,16($sp)

	.loc 1 857 0
	lw	$25,%call16(mt7620_start_eth)($28)
	jalr	$25
	move	$4,$17

	lw	$28,16($sp)
	.loc 1 859 0
	lw	$31,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE33:
	.end	mt7620_eth_init
	.align	2
	.globl	mt7620_eth_halt
	.ent	mt7620_eth_halt
	.type	mt7620_eth_halt, @function
mt7620_eth_halt:
$LFB34:
	.loc 1 862 0
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	.loc 1 870 0
	lw	$25,%call16(mt7620_stop_eth)($28)
	jr	$25
	nop

	.set	macro
	.set	reorder
$LFE34:
	.end	mt7620_eth_halt
	.section	.rodata.str1.4
	.align	2
$LC13:
	.ascii	"Failed to allocate memory\n\000"
	.align	2
$LC14:
	.ascii	"eth0\000"
	.text
	.align	2
	.globl	rt2880_eth_initialize
	.ent	rt2880_eth_initialize
	.type	rt2880_eth_initialize, @function
rt2880_eth_initialize:
$LFB35:
	.loc 1 874 0
	.frame	$sp,40,$31		# vars= 0, regs= 4/0, args= 16, gp= 8
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI50:
	sw	$31,36($sp)
$LCFI51:
	sw	$18,32($sp)
$LCFI52:
	sw	$17,28($sp)
$LCFI53:
	sw	$16,24($sp)
$LCFI54:
	.cprestore	16
	.loc 1 874 0
	move	$18,$4
	.loc 1 879 0
	lw	$4,%got(sk_buf_pool)($28)
	lw	$25,%call16(skb_init)($28)
	jalr	$25
	addiu	$4,$4,%lo(sk_buf_pool)

	lw	$28,16($sp)
	move	$17,$2
	.loc 1 884 0
	li	$4,56			# 0x38
	.loc 1 881 0
	bne	$2,$0,$L182
	lw	$25,%call16(malloc)($28)

	.loc 1 884 0
	jalr	$25
	nop

	lw	$28,16($sp)
	move	$16,$2
	.loc 1 890 0
	move	$4,$16
	lw	$25,%call16(memset)($28)
	move	$5,$0
	li	$6,56			# 0x38
	move	$2,$25
	.loc 1 887 0
	.loc 1 886 0
	bne	$16,$0,$L183
	lw	$25,%call16(printf)($28)

	.loc 1 887 0
	lw	$4,%got($LC13)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC13)

	.loc 1 888 0
	b	$L182
	lw	$28,16($sp)

$L183:
	.loc 1 890 0
	move	$25,$2
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 891 0
	li	$6,6			# 0x6
	addiu	$5,$18,8
	lw	$25,%call16(memcpy)($28)
	jalr	$25
	addiu	$4,$16,16

	lw	$28,16($sp)
	.loc 1 893 0
	move	$4,$16
	lw	$5,%got($LC14)($28)
	lw	$25,%call16(sprintf)($28)
	jalr	$25
	addiu	$5,$5,%lo($LC14)

	lw	$28,16($sp)
	.loc 1 894 0
	lw	$25,%call16(mt7620_eth_probe)($28)
	jalr	$25
	move	$4,$16

	lw	$28,16($sp)
	.loc 1 895 0
	li	$2,-1341128704			# 0xffffffffb0100000
	sw	$2,24($16)
	.loc 1 896 0
	lw	$2,%got(mt7620_eth_init)($28)
	.loc 1 900 0
	lw	$25,%call16(eth_register)($28)
	move	$4,$16
	.loc 1 896 0
	sw	$2,32($16)
	.loc 1 897 0
	lw	$2,%got(mt7620_eth_halt)($28)
	sw	$2,44($16)
	.loc 1 898 0
	lw	$2,%got(mt7620_eth_send)($28)
	addiu	$2,$2,%lo(mt7620_eth_send)
	sw	$2,36($16)
	.loc 1 899 0
	lw	$2,%got(mt7620_eth_recv)($28)
	addiu	$2,$2,%lo(mt7620_eth_recv)
	.loc 1 900 0
	jalr	$25
	sw	$2,40($16)

	lw	$28,16($sp)
	move	$17,$2
$L182:
	.loc 1 904 0
	move	$2,$17
	lw	$31,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE35:
	.end	rt2880_eth_initialize
	.local	cur_rxd_idx
	.comm	cur_rxd_idx,4,4
	.local	cur_txd_idx
	.comm	cur_txd_idx,4,4
	.local	rx_ring
	.comm	rx_ring,4,4
	.local	tx_ring
	.comm	tx_ring,4,4
	.local	rxskbs
	.comm	rxskbs,256,4
	.local	txskbs
	.comm	txskbs,256,4
	.local	tx_ring_cache
	.comm	tx_ring_cache,1024,32
	.local	rx_ring_cache
	.comm	rx_ring_cache,1024,32
	.local	sk_buf_pool
	.comm	sk_buf_pool,411648,4
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
	.4byte	$LFB16
	.4byte	$LFE16-$LFB16
	.align	2
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB17
	.4byte	$LFE17-$LFB17
	.align	2
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB19
	.4byte	$LFE19-$LFB19
	.byte	0x4
	.4byte	$LCFI0-$LFB19
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI1-$LCFI0
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE4:
$LSFDE6:
	.4byte	$LEFDE6-$LASFDE6
$LASFDE6:
	.4byte	$Lframe0
	.4byte	$LFB21
	.4byte	$LFE21-$LFB21
	.byte	0x4
	.4byte	$LCFI2-$LFB21
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
$LEFDE6:
$LSFDE8:
	.4byte	$LEFDE8-$LASFDE8
$LASFDE8:
	.4byte	$Lframe0
	.4byte	$LFB24
	.4byte	$LFE24-$LFB24
	.byte	0x4
	.4byte	$LCFI5-$LFB24
	.byte	0xe
	.uleb128 0x48
	.byte	0x4
	.4byte	$LCFI14-$LCFI5
	.byte	0x11
	.uleb128 0x10
	.sleb128 -10
	.byte	0x11
	.uleb128 0x11
	.sleb128 -9
	.byte	0x11
	.uleb128 0x12
	.sleb128 -8
	.byte	0x11
	.uleb128 0x13
	.sleb128 -7
	.byte	0x11
	.uleb128 0x14
	.sleb128 -6
	.byte	0x11
	.uleb128 0x15
	.sleb128 -5
	.byte	0x11
	.uleb128 0x16
	.sleb128 -4
	.byte	0x11
	.uleb128 0x17
	.sleb128 -3
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE8:
$LSFDE10:
	.4byte	$LEFDE10-$LASFDE10
$LASFDE10:
	.4byte	$Lframe0
	.4byte	$LFB26
	.4byte	$LFE26-$LFB26
	.byte	0x4
	.4byte	$LCFI15-$LFB26
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.4byte	$LCFI18-$LCFI15
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
	.4byte	$LFB27
	.4byte	$LFE27-$LFB27
	.byte	0x4
	.4byte	$LCFI19-$LFB27
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.4byte	$LCFI26-$LCFI19
	.byte	0x11
	.uleb128 0x10
	.sleb128 -8
	.byte	0x11
	.uleb128 0x11
	.sleb128 -7
	.byte	0x11
	.uleb128 0x12
	.sleb128 -6
	.byte	0x11
	.uleb128 0x13
	.sleb128 -5
	.byte	0x11
	.uleb128 0x14
	.sleb128 -4
	.byte	0x11
	.uleb128 0x15
	.sleb128 -3
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE12:
$LSFDE14:
	.4byte	$LEFDE14-$LASFDE14
$LASFDE14:
	.4byte	$Lframe0
	.4byte	$LFB28
	.4byte	$LFE28-$LFB28
	.byte	0x4
	.4byte	$LCFI27-$LFB28
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.4byte	$LCFI33-$LCFI27
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
$LEFDE14:
$LSFDE16:
	.4byte	$LEFDE16-$LASFDE16
$LASFDE16:
	.4byte	$Lframe0
	.4byte	$LFB29
	.4byte	$LFE29-$LFB29
	.byte	0x4
	.4byte	$LCFI34-$LFB29
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.4byte	$LCFI37-$LCFI34
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
$LEFDE16:
$LSFDE18:
	.4byte	$LEFDE18-$LASFDE18
$LASFDE18:
	.4byte	$Lframe0
	.4byte	$LFB30
	.4byte	$LFE30-$LFB30
	.align	2
$LEFDE18:
$LSFDE20:
	.4byte	$LEFDE20-$LASFDE20
$LASFDE20:
	.4byte	$Lframe0
	.4byte	$LFB31
	.4byte	$LFE31-$LFB31
	.byte	0x4
	.4byte	$LCFI38-$LFB31
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI41-$LCFI38
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
$LEFDE20:
$LSFDE22:
	.4byte	$LEFDE22-$LASFDE22
$LASFDE22:
	.4byte	$Lframe0
	.4byte	$LFB32
	.4byte	$LFE32-$LFB32
	.byte	0x4
	.4byte	$LCFI42-$LFB32
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI45-$LCFI42
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
$LEFDE22:
$LSFDE24:
	.4byte	$LEFDE24-$LASFDE24
$LASFDE24:
	.4byte	$Lframe0
	.4byte	$LFB33
	.4byte	$LFE33-$LFB33
	.byte	0x4
	.4byte	$LCFI46-$LFB33
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI49-$LCFI46
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
$LEFDE24:
$LSFDE26:
	.4byte	$LEFDE26-$LASFDE26
$LASFDE26:
	.4byte	$Lframe0
	.4byte	$LFB34
	.4byte	$LFE34-$LFB34
	.align	2
$LEFDE26:
$LSFDE28:
	.4byte	$LEFDE28-$LASFDE28
$LASFDE28:
	.4byte	$Lframe0
	.4byte	$LFB35
	.4byte	$LFE35-$LFB35
	.byte	0x4
	.4byte	$LCFI50-$LFB35
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI54-$LCFI50
	.byte	0x11
	.uleb128 0x10
	.sleb128 -4
	.byte	0x11
	.uleb128 0x11
	.sleb128 -3
	.byte	0x11
	.uleb128 0x12
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE28:
	.align	0
	.file 2 "/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tbsboot/include/net.h"
	.file 3 "/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/build/include2/asm/global_data.h"
	.file 4 "skbuff.h"
	.file 5 "/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tbsboot/include/common.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0xe3b
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF131
	.byte	0x1
	.4byte	$LASF132
	.4byte	$LASF133
	.uleb128 0x2
	.4byte	$LASF19
	.byte	0x5
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
	.uleb128 0x3
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x5
	.4byte	0x86
	.4byte	0x30
	.uleb128 0x6
	.4byte	0x6f
	.byte	0x5
	.byte	0x0
	.uleb128 0x3
	.4byte	$LASF8
	.byte	0x1
	.byte	0x6
	.uleb128 0x7
	.byte	0x4
	.4byte	0x30
	.uleb128 0x8
	.byte	0x4
	.uleb128 0x9
	.4byte	0x12e
	.4byte	$LASF21
	.byte	0x2c
	.byte	0x3
	.byte	0x15
	.uleb128 0xa
	.4byte	$LASF9
	.byte	0x3
	.byte	0x16
	.4byte	0x53
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xa
	.4byte	$LASF10
	.byte	0x3
	.byte	0x17
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0xa
	.4byte	$LASF11
	.byte	0x3
	.byte	0x18
	.4byte	0x76
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xa
	.4byte	$LASF12
	.byte	0x3
	.byte	0x19
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0xa
	.4byte	$LASF13
	.byte	0x3
	.byte	0x1a
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0xa
	.4byte	$LASF14
	.byte	0x3
	.byte	0x1b
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0xa
	.4byte	$LASF15
	.byte	0x3
	.byte	0x1c
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.uleb128 0xa
	.4byte	$LASF16
	.byte	0x3
	.byte	0x1d
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0xa
	.4byte	$LASF17
	.byte	0x3
	.byte	0x1e
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0xa
	.4byte	$LASF18
	.byte	0x3
	.byte	0x1f
	.4byte	0x37
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF20
	.byte	0x3
	.byte	0x20
	.4byte	0x95
	.uleb128 0x7
	.byte	0x4
	.4byte	0x12e
	.uleb128 0x9
	.4byte	0x1d8
	.4byte	$LASF22
	.byte	0x38
	.byte	0x2
	.byte	0x41
	.uleb128 0xa
	.4byte	$LASF23
	.byte	0x2
	.byte	0x42
	.4byte	0x1d8
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xa
	.4byte	$LASF24
	.byte	0x2
	.byte	0x43
	.4byte	0x76
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0xa
	.4byte	$LASF25
	.byte	0x2
	.byte	0x44
	.4byte	0x53
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0xa
	.4byte	$LASF26
	.byte	0x2
	.byte	0x45
	.4byte	0x53
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.uleb128 0xa
	.4byte	$LASF27
	.byte	0x2
	.byte	0x47
	.4byte	0x203
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0xa
	.4byte	$LASF28
	.byte	0x2
	.byte	0x48
	.4byte	0x22a
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0xa
	.4byte	$LASF29
	.byte	0x2
	.byte	0x49
	.4byte	0x240
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.uleb128 0xa
	.4byte	$LASF30
	.byte	0x2
	.byte	0x4a
	.4byte	0x252
	.byte	0x2
	.byte	0x10
	.uleb128 0x2c
	.uleb128 0xa
	.4byte	$LASF31
	.byte	0x2
	.byte	0x4c
	.4byte	0x1fd
	.byte	0x2
	.byte	0x10
	.uleb128 0x30
	.uleb128 0xa
	.4byte	$LASF32
	.byte	0x2
	.byte	0x4d
	.4byte	0x93
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x5
	.4byte	0x1e8
	.4byte	0x86
	.uleb128 0x6
	.4byte	0x6f
	.byte	0xf
	.byte	0x0
	.uleb128 0xb
	.4byte	0x1fd
	.byte	0x1
	.4byte	0x53
	.uleb128 0xc
	.4byte	0x1fd
	.uleb128 0xc
	.4byte	0x139
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x13f
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1e8
	.uleb128 0xb
	.4byte	0x223
	.byte	0x1
	.4byte	0x53
	.uleb128 0xc
	.4byte	0x1fd
	.uleb128 0xc
	.4byte	0x223
	.uleb128 0xc
	.4byte	0x53
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x229
	.uleb128 0xd
	.uleb128 0x7
	.byte	0x4
	.4byte	0x209
	.uleb128 0xb
	.4byte	0x240
	.byte	0x1
	.4byte	0x53
	.uleb128 0xc
	.4byte	0x1fd
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x230
	.uleb128 0xe
	.4byte	0x252
	.byte	0x1
	.uleb128 0xc
	.4byte	0x1fd
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x246
	.uleb128 0xf
	.4byte	0x2a1
	.4byte	$LASF33
	.2byte	0x648
	.byte	0x4
	.byte	0x5
	.uleb128 0x10
	.ascii	"buf\000"
	.byte	0x4
	.byte	0x6
	.4byte	0x2a1
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xa
	.4byte	$LASF34
	.byte	0x4
	.byte	0x7
	.4byte	0x8d
	.byte	0x3
	.byte	0x10
	.uleb128 0x640
	.uleb128 0x10
	.ascii	"len\000"
	.byte	0x4
	.byte	0x8
	.4byte	0x3e
	.byte	0x3
	.byte	0x10
	.uleb128 0x644
	.uleb128 0xa
	.4byte	$LASF35
	.byte	0x4
	.byte	0x9
	.4byte	0x3e
	.byte	0x3
	.byte	0x10
	.uleb128 0x646
	.byte	0x0
	.uleb128 0x5
	.4byte	0x2b2
	.4byte	0x30
	.uleb128 0x11
	.4byte	0x6f
	.2byte	0x63f
	.byte	0x0
	.uleb128 0x12
	.4byte	0x2c7
	.byte	0x4
	.byte	0x1
	.byte	0xa1
	.uleb128 0x13
	.4byte	$LASF36
	.sleb128 0
	.uleb128 0x13
	.4byte	$LASF37
	.sleb128 1
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF38
	.byte	0x1
	.byte	0xa4
	.4byte	0x2b2
	.uleb128 0x9
	.4byte	0x2ed
	.4byte	$LASF39
	.byte	0x4
	.byte	0x1
	.byte	0xa7
	.uleb128 0xa
	.4byte	$LASF40
	.byte	0x1
	.byte	0xa8
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x360
	.4byte	$LASF41
	.byte	0x4
	.byte	0x1
	.byte	0xaa
	.uleb128 0x14
	.4byte	$LASF42
	.byte	0x1
	.byte	0xab
	.4byte	0x5a
	.byte	0x4
	.byte	0xe
	.byte	0x12
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"LS1\000"
	.byte	0x1
	.byte	0xac
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x11
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF43
	.byte	0x1
	.byte	0xad
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF44
	.byte	0x1
	.byte	0xae
	.4byte	0x5a
	.byte	0x4
	.byte	0xe
	.byte	0x2
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"LS0\000"
	.byte	0x1
	.byte	0xaf
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF45
	.byte	0x1
	.byte	0xb0
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x0
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x37b
	.4byte	$LASF46
	.byte	0x4
	.byte	0x1
	.byte	0xb3
	.uleb128 0xa
	.4byte	$LASF47
	.byte	0x1
	.byte	0xb4
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x431
	.4byte	$LASF48
	.byte	0x4
	.byte	0x1
	.byte	0xb7
	.uleb128 0x14
	.4byte	$LASF49
	.byte	0x1
	.byte	0xb8
	.4byte	0x5a
	.byte	0x4
	.byte	0xe
	.byte	0x12
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF50
	.byte	0x1
	.byte	0xb9
	.4byte	0x5a
	.byte	0x4
	.byte	0x5
	.byte	0xd
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"SP\000"
	.byte	0x1
	.byte	0xba
	.4byte	0x5a
	.byte	0x4
	.byte	0x3
	.byte	0xa
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"L4F\000"
	.byte	0x1
	.byte	0xbb
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF51
	.byte	0x1
	.byte	0xbc
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF52
	.byte	0x1
	.byte	0xbd
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF53
	.byte	0x1
	.byte	0xbe
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"IP4\000"
	.byte	0x1
	.byte	0xbf
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"IP6\000"
	.byte	0x1
	.byte	0xc0
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF54
	.byte	0x1
	.byte	0xc1
	.4byte	0x5a
	.byte	0x4
	.byte	0x4
	.byte	0x0
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x476
	.4byte	$LASF55
	.byte	0x10
	.byte	0x1
	.byte	0xc4
	.uleb128 0xa
	.4byte	$LASF56
	.byte	0x1
	.byte	0xc5
	.4byte	0x2d2
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xa
	.4byte	$LASF57
	.byte	0x1
	.byte	0xc6
	.4byte	0x2ed
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0xa
	.4byte	$LASF58
	.byte	0x1
	.byte	0xc7
	.4byte	0x360
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xa
	.4byte	$LASF59
	.byte	0x1
	.byte	0xc8
	.4byte	0x37b
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.byte	0x0
	.uleb128 0x9
	.4byte	0x491
	.4byte	$LASF60
	.byte	0x4
	.byte	0x1
	.byte	0xcd
	.uleb128 0xa
	.4byte	$LASF61
	.byte	0x1
	.byte	0xce
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x504
	.4byte	$LASF62
	.byte	0x4
	.byte	0x1
	.byte	0xd1
	.uleb128 0x14
	.4byte	$LASF63
	.byte	0x1
	.byte	0xd2
	.4byte	0x5a
	.byte	0x4
	.byte	0xe
	.byte	0x12
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF64
	.byte	0x1
	.byte	0xd3
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x11
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF65
	.byte	0x1
	.byte	0xd4
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF66
	.byte	0x1
	.byte	0xd5
	.4byte	0x5a
	.byte	0x4
	.byte	0xe
	.byte	0x2
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF67
	.byte	0x1
	.byte	0xd6
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF45
	.byte	0x1
	.byte	0xd7
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x0
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x51f
	.4byte	$LASF68
	.byte	0x4
	.byte	0x1
	.byte	0xda
	.uleb128 0xa
	.4byte	$LASF69
	.byte	0x1
	.byte	0xdb
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x5b4
	.4byte	$LASF70
	.byte	0x4
	.byte	0x1
	.byte	0xde
	.uleb128 0x14
	.4byte	$LASF71
	.byte	0x1
	.byte	0xdf
	.4byte	0x5a
	.byte	0x4
	.byte	0x8
	.byte	0x18
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF72
	.byte	0x1
	.byte	0xe0
	.4byte	0x5a
	.byte	0x4
	.byte	0x4
	.byte	0x14
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF73
	.byte	0x1
	.byte	0xe1
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x13
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF74
	.byte	0x1
	.byte	0xe2
	.4byte	0x5a
	.byte	0x4
	.byte	0x2
	.byte	0x11
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"UDF\000"
	.byte	0x1
	.byte	0xe3
	.4byte	0x5a
	.byte	0x4
	.byte	0x5
	.byte	0xc
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF75
	.byte	0x1
	.byte	0xe4
	.4byte	0x5a
	.byte	0x4
	.byte	0x8
	.byte	0x4
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x15
	.ascii	"TSO\000"
	.byte	0x1
	.byte	0xe5
	.4byte	0x5a
	.byte	0x4
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x14
	.4byte	$LASF76
	.byte	0x1
	.byte	0xe6
	.4byte	0x5a
	.byte	0x4
	.byte	0x3
	.byte	0x0
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.4byte	0x5f9
	.4byte	$LASF77
	.byte	0x10
	.byte	0x1
	.byte	0xe9
	.uleb128 0xa
	.4byte	$LASF78
	.byte	0x1
	.byte	0xea
	.4byte	0x476
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xa
	.4byte	$LASF79
	.byte	0x1
	.byte	0xeb
	.4byte	0x491
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0xa
	.4byte	$LASF80
	.byte	0x1
	.byte	0xec
	.4byte	0x504
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xa
	.4byte	$LASF81
	.byte	0x1
	.byte	0xed
	.4byte	0x51f
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.byte	0x0
	.uleb128 0x16
	.4byte	0x66a
	.byte	0x1
	.4byte	$LASF85
	.byte	0x1
	.2byte	0x113
	.byte	0x1
	.4byte	$LFB16
	.4byte	$LFE16
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0x17
	.4byte	$LASF82
	.byte	0x1
	.2byte	0x112
	.4byte	0x5a
	.byte	0x1
	.byte	0x54
	.uleb128 0x17
	.4byte	$LASF83
	.byte	0x1
	.2byte	0x112
	.4byte	0x5a
	.byte	0x1
	.byte	0x55
	.uleb128 0x17
	.4byte	$LASF34
	.byte	0x1
	.2byte	0x112
	.4byte	0x66a
	.byte	0x1
	.byte	0x56
	.uleb128 0x18
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x114
	.4byte	0x5a
	.byte	0x1
	.byte	0x53
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x115
	.4byte	0x5a
	.byte	0x1
	.byte	0x57
	.uleb128 0x19
	.4byte	$LASF84
	.4byte	0x685
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.3
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x5a
	.uleb128 0x5
	.4byte	0x680
	.4byte	0x680
	.uleb128 0x6
	.4byte	0x6f
	.byte	0xc
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x86
	.uleb128 0x1a
	.4byte	0x670
	.uleb128 0x16
	.4byte	0x6fb
	.byte	0x1
	.4byte	$LASF86
	.byte	0x1
	.2byte	0x12c
	.byte	0x1
	.4byte	$LFB17
	.4byte	$LFE17
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0x17
	.4byte	$LASF82
	.byte	0x1
	.2byte	0x12b
	.4byte	0x5a
	.byte	0x1
	.byte	0x54
	.uleb128 0x17
	.4byte	$LASF83
	.byte	0x1
	.2byte	0x12b
	.4byte	0x5a
	.byte	0x1
	.byte	0x55
	.uleb128 0x17
	.4byte	$LASF87
	.byte	0x1
	.2byte	0x12b
	.4byte	0x5a
	.byte	0x1
	.byte	0x56
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x12d
	.4byte	0x5a
	.byte	0x1
	.byte	0x57
	.uleb128 0x18
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x12e
	.4byte	0x5a
	.byte	0x1
	.byte	0x53
	.uleb128 0x19
	.4byte	$LASF84
	.4byte	0x70b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.2
	.byte	0x0
	.uleb128 0x5
	.4byte	0x70b
	.4byte	0x680
	.uleb128 0x6
	.4byte	0x6f
	.byte	0xd
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x6fb
	.uleb128 0x1b
	.4byte	0x775
	.byte	0x1
	.4byte	$LASF88
	.byte	0x1
	.2byte	0x189
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB19
	.4byte	$LFE19
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0x17
	.4byte	$LASF89
	.byte	0x1
	.2byte	0x188
	.4byte	0x53
	.byte	0x1
	.byte	0x54
	.uleb128 0x1c
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x188
	.4byte	0x53
	.byte	0x1
	.byte	0x55
	.uleb128 0x17
	.4byte	$LASF34
	.byte	0x1
	.2byte	0x188
	.4byte	0x775
	.byte	0x1
	.byte	0x56
	.uleb128 0x1d
	.4byte	$LASF90
	.byte	0x1
	.2byte	0x18a
	.4byte	0x5a
	.byte	0x1
	.byte	0x57
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x18b
	.4byte	0x5a
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x53
	.uleb128 0x1e
	.4byte	0x7b1
	.4byte	$LASF93
	.byte	0x1
	.2byte	0x205
	.byte	0x1
	.4byte	$LFB21
	.4byte	$LFE21
	.4byte	$LSFDE6
	.byte	0x1
	.byte	0x6d
	.uleb128 0x18
	.ascii	"j\000"
	.byte	0x1
	.2byte	0x206
	.4byte	0x53
	.byte	0x1
	.byte	0x60
	.uleb128 0x1d
	.4byte	$LASF91
	.byte	0x1
	.2byte	0x207
	.4byte	0x5a
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.uleb128 0x16
	.4byte	0x8be
	.byte	0x1
	.4byte	$LASF92
	.byte	0x1
	.2byte	0x26d
	.byte	0x1
	.4byte	$LFB24
	.4byte	$LFE24
	.4byte	$LSFDE8
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x26c
	.4byte	0x1fd
	.byte	0x1
	.byte	0x61
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x26e
	.4byte	0x5a
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x18
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x26f
	.4byte	0x5a
	.byte	0x1
	.byte	0x68
	.uleb128 0x1f
	.4byte	0x82c
	.4byte	0x8be
	.4byte	$LBB2
	.4byte	$LBE2
	.uleb128 0x20
	.4byte	0x8cc
	.byte	0x1
	.byte	0x60
	.uleb128 0x20
	.4byte	0x8d6
	.byte	0x2
	.byte	0x91
	.sleb128 28
	.uleb128 0x21
	.4byte	$Ldebug_ranges0+0x0
	.uleb128 0x20
	.4byte	0x8cc
	.byte	0x1
	.byte	0x60
	.uleb128 0x20
	.4byte	0x8d6
	.byte	0x2
	.byte	0x91
	.sleb128 28
	.byte	0x0
	.byte	0x0
	.uleb128 0x1f
	.4byte	0x8b0
	.4byte	0x8e3
	.4byte	$LBB6
	.4byte	$LBE6
	.uleb128 0x22
	.4byte	0x8f5
	.uleb128 0x22
	.4byte	0x8ff
	.uleb128 0x22
	.4byte	0x90b
	.uleb128 0x20
	.4byte	0x917
	.byte	0x1
	.byte	0x63
	.uleb128 0x20
	.4byte	0x923
	.byte	0x1
	.byte	0x61
	.uleb128 0x20
	.4byte	0x92d
	.byte	0x1
	.byte	0x60
	.uleb128 0x23
	.4byte	0x943
	.4byte	$L84
	.uleb128 0x23
	.4byte	0x94b
	.4byte	$L87
	.uleb128 0x21
	.4byte	$Ldebug_ranges0+0x18
	.uleb128 0x22
	.4byte	0x8f5
	.uleb128 0x22
	.4byte	0x8ff
	.uleb128 0x22
	.4byte	0x90b
	.uleb128 0x20
	.4byte	0x917
	.byte	0x1
	.byte	0x63
	.uleb128 0x20
	.4byte	0x923
	.byte	0x1
	.byte	0x61
	.uleb128 0x20
	.4byte	0x92d
	.byte	0x1
	.byte	0x60
	.uleb128 0x23
	.4byte	0x943
	.4byte	$L84
	.uleb128 0x23
	.4byte	0x94b
	.4byte	$L87
	.byte	0x0
	.byte	0x0
	.uleb128 0x24
	.4byte	0x96f
	.4byte	$LBB22
	.4byte	$LBE22
	.byte	0x0
	.uleb128 0x25
	.4byte	0x8e3
	.4byte	$LASF94
	.byte	0x1
	.2byte	0x14a
	.byte	0x1
	.byte	0x1
	.uleb128 0x26
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x14b
	.4byte	0x5a
	.uleb128 0x26
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x14c
	.4byte	0x5a
	.byte	0x0
	.uleb128 0x27
	.4byte	0x954
	.4byte	$LASF95
	.byte	0x1
	.2byte	0x1b1
	.byte	0x1
	.4byte	0x8d
	.byte	0x1
	.uleb128 0x26
	.ascii	"p\000"
	.byte	0x1
	.2byte	0x1b2
	.4byte	0x8d
	.uleb128 0x28
	.4byte	$LASF96
	.byte	0x1
	.2byte	0x1b3
	.4byte	0x5a
	.uleb128 0x28
	.4byte	$LASF97
	.byte	0x1
	.2byte	0x1b4
	.4byte	0x37
	.uleb128 0x26
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x1b5
	.4byte	0x5a
	.uleb128 0x26
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x1b6
	.4byte	0x53
	.uleb128 0x26
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x1b7
	.4byte	0x954
	.uleb128 0x29
	.4byte	$LASF84
	.4byte	0x96a
	.byte	0x1
	.uleb128 0x2a
	.ascii	"err\000"
	.byte	0x1
	.2byte	0x1f2
	.uleb128 0x2a
	.ascii	"out\000"
	.byte	0x1
	.2byte	0x1f8
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x258
	.uleb128 0x5
	.4byte	0x96a
	.4byte	0x680
	.uleb128 0x6
	.4byte	0x6f
	.byte	0x13
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x95a
	.uleb128 0x2b
	.4byte	$LASF134
	.byte	0x1
	.2byte	0x22e
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	0x9f0
	.byte	0x1
	.4byte	$LASF98
	.byte	0x1
	.2byte	0x2a4
	.byte	0x1
	.4byte	$LFB26
	.4byte	$LFE26
	.4byte	$LSFDE10
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1d
	.4byte	$LASF99
	.byte	0x1
	.2byte	0x2a5
	.4byte	0x5a
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x2a6
	.4byte	0x53
	.byte	0x1
	.byte	0x60
	.uleb128 0x2c
	.4byte	0x9f0
	.4byte	$LBB28
	.4byte	$LBE28
	.uleb128 0x2d
	.4byte	0x9fe
	.uleb128 0x2d
	.4byte	0xa0a
	.uleb128 0x2e
	.4byte	$LBB29
	.4byte	$LBE29
	.uleb128 0x20
	.4byte	0xa16
	.byte	0x1
	.byte	0x52
	.uleb128 0x20
	.4byte	0xa22
	.byte	0x2
	.byte	0x91
	.sleb128 28
	.uleb128 0x20
	.4byte	0xa2e
	.byte	0x1
	.byte	0x61
	.uleb128 0x20
	.4byte	0xa3a
	.byte	0x1
	.byte	0x60
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x25
	.4byte	0xa47
	.4byte	$LASF100
	.byte	0x1
	.2byte	0x295
	.byte	0x1
	.byte	0x1
	.uleb128 0x2f
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x294
	.4byte	0x1fd
	.uleb128 0x30
	.4byte	$LASF26
	.byte	0x1
	.2byte	0x294
	.4byte	0x66a
	.uleb128 0x28
	.4byte	$LASF101
	.byte	0x1
	.2byte	0x296
	.4byte	0x2c7
	.uleb128 0x28
	.4byte	$LASF91
	.byte	0x1
	.2byte	0x297
	.4byte	0x5a
	.uleb128 0x28
	.4byte	$LASF102
	.byte	0x1
	.2byte	0x298
	.4byte	0x5a
	.uleb128 0x28
	.4byte	$LASF103
	.byte	0x1
	.2byte	0x299
	.4byte	0x30
	.byte	0x0
	.uleb128 0x31
	.4byte	0xacf
	.4byte	$LASF104
	.byte	0x1
	.2byte	0x2b7
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB27
	.4byte	$LFE27
	.4byte	$LSFDE12
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x2b6
	.4byte	0x1fd
	.byte	0x1
	.byte	0x54
	.uleb128 0x18
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x2b8
	.4byte	0x954
	.byte	0x1
	.byte	0x60
	.uleb128 0x1d
	.4byte	$LASF105
	.byte	0x1
	.2byte	0x2b9
	.4byte	0x954
	.byte	0x1
	.byte	0x61
	.uleb128 0x18
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x2ba
	.4byte	0x5a
	.byte	0x1
	.byte	0x63
	.uleb128 0x18
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x2bb
	.4byte	0x5a
	.byte	0x1
	.byte	0x55
	.uleb128 0x28
	.4byte	$LASF99
	.byte	0x1
	.2byte	0x2bc
	.4byte	0x5a
	.uleb128 0x26
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x2bc
	.4byte	0x5a
	.uleb128 0x32
	.4byte	$LASF106
	.byte	0x1
	.2byte	0x2d1
	.4byte	$L129
	.byte	0x0
	.uleb128 0x31
	.4byte	0xb6b
	.4byte	$LASF107
	.byte	0x1
	.2byte	0x2e6
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB28
	.4byte	$LFE28
	.4byte	$LSFDE14
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x2e5
	.4byte	0x1fd
	.byte	0x1
	.byte	0x54
	.uleb128 0x17
	.4byte	$LASF108
	.byte	0x1
	.2byte	0x2e5
	.4byte	0x223
	.byte	0x1
	.byte	0x62
	.uleb128 0x17
	.4byte	$LASF109
	.byte	0x1
	.2byte	0x2e5
	.4byte	0x53
	.byte	0x1
	.byte	0x61
	.uleb128 0x18
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x2e7
	.4byte	0x954
	.byte	0x1
	.byte	0x60
	.uleb128 0x1d
	.4byte	$LASF110
	.byte	0x1
	.2byte	0x2e8
	.4byte	0x954
	.byte	0x1
	.byte	0x54
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x2e9
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x1d
	.4byte	$LASF111
	.byte	0x1
	.2byte	0x2ea
	.4byte	0x53
	.byte	0x1
	.byte	0x64
	.uleb128 0x33
	.ascii	"out\000"
	.byte	0x1
	.2byte	0x314
	.4byte	$L138
	.uleb128 0x19
	.4byte	$LASF84
	.4byte	0xb7b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.0
	.byte	0x0
	.uleb128 0x5
	.4byte	0xb7b
	.4byte	0x680
	.uleb128 0x6
	.4byte	0x6f
	.byte	0xf
	.byte	0x0
	.uleb128 0x1a
	.4byte	0xb6b
	.uleb128 0x16
	.4byte	0xbc8
	.byte	0x1
	.4byte	$LASF112
	.byte	0x1
	.2byte	0x319
	.byte	0x1
	.4byte	$LFB29
	.4byte	$LFE29
	.4byte	$LSFDE16
	.byte	0x1
	.byte	0x6d
	.uleb128 0x17
	.4byte	$LASF103
	.byte	0x1
	.2byte	0x318
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x17
	.4byte	$LASF113
	.byte	0x1
	.2byte	0x318
	.4byte	0x53
	.byte	0x1
	.byte	0x60
	.uleb128 0x1d
	.4byte	$LASF91
	.byte	0x1
	.2byte	0x31a
	.4byte	0x5a
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.byte	0x0
	.uleb128 0x16
	.4byte	0xc1d
	.byte	0x1
	.4byte	$LASF114
	.byte	0x1
	.2byte	0x32c
	.byte	0x1
	.4byte	$LFB30
	.4byte	$LFE30
	.4byte	$LSFDE18
	.byte	0x1
	.byte	0x6d
	.uleb128 0x17
	.4byte	$LASF103
	.byte	0x1
	.2byte	0x32b
	.4byte	0x5a
	.byte	0x1
	.byte	0x54
	.uleb128 0x17
	.4byte	$LASF113
	.byte	0x1
	.2byte	0x32b
	.4byte	0x5a
	.byte	0x1
	.byte	0x55
	.uleb128 0x1d
	.4byte	$LASF91
	.byte	0x1
	.2byte	0x32d
	.4byte	0x5a
	.byte	0x1
	.byte	0x53
	.uleb128 0x1d
	.4byte	$LASF115
	.byte	0x1
	.2byte	0x32e
	.4byte	0x5a
	.byte	0x1
	.byte	0x52
	.byte	0x0
	.uleb128 0x16
	.4byte	0xc56
	.byte	0x1
	.4byte	$LASF116
	.byte	0x1
	.2byte	0x33e
	.byte	0x1
	.4byte	$LFB31
	.4byte	$LFE31
	.4byte	$LSFDE20
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x33d
	.4byte	0x1fd
	.byte	0x1
	.byte	0x54
	.uleb128 0x18
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x33f
	.4byte	0x5a
	.byte	0x1
	.byte	0x60
	.byte	0x0
	.uleb128 0x16
	.4byte	0xc8f
	.byte	0x1
	.4byte	$LASF117
	.byte	0x1
	.2byte	0x348
	.byte	0x1
	.4byte	$LFB32
	.4byte	$LFE32
	.4byte	$LSFDE22
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x347
	.4byte	0x1fd
	.byte	0x1
	.byte	0x54
	.uleb128 0x18
	.ascii	"reg\000"
	.byte	0x1
	.2byte	0x349
	.4byte	0x5a
	.byte	0x1
	.byte	0x60
	.byte	0x0
	.uleb128 0x1b
	.4byte	0xcca
	.byte	0x1
	.4byte	$LASF118
	.byte	0x1
	.2byte	0x352
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB33
	.4byte	$LFE33
	.4byte	$LSFDE24
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x351
	.4byte	0x1fd
	.byte	0x1
	.byte	0x61
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x353
	.4byte	0x53
	.byte	0x1
	.byte	0x60
	.byte	0x0
	.uleb128 0x16
	.4byte	0xcf5
	.byte	0x1
	.4byte	$LASF119
	.byte	0x1
	.2byte	0x35e
	.byte	0x1
	.4byte	$LFB34
	.4byte	$LFE34
	.4byte	$LSFDE26
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x35d
	.4byte	0x1fd
	.byte	0x1
	.byte	0x54
	.byte	0x0
	.uleb128 0x1b
	.4byte	0xd4c
	.byte	0x1
	.4byte	$LASF120
	.byte	0x1
	.2byte	0x36a
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB35
	.4byte	$LFE35
	.4byte	$LSFDE28
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1c
	.ascii	"bis\000"
	.byte	0x1
	.2byte	0x369
	.4byte	0x139
	.byte	0x1
	.byte	0x62
	.uleb128 0x18
	.ascii	"dev\000"
	.byte	0x1
	.2byte	0x36b
	.4byte	0x1fd
	.byte	0x1
	.byte	0x60
	.uleb128 0x1d
	.4byte	$LASF121
	.byte	0x1
	.2byte	0x36c
	.4byte	0x53
	.byte	0x1
	.byte	0x61
	.uleb128 0x33
	.ascii	"out\000"
	.byte	0x1
	.2byte	0x386
	.4byte	$L182
	.byte	0x0
	.uleb128 0x34
	.4byte	$LASF122
	.byte	0x1
	.byte	0xf0
	.4byte	0x5a
	.byte	0x5
	.byte	0x3
	.4byte	cur_rxd_idx
	.uleb128 0x34
	.4byte	$LASF123
	.byte	0x1
	.byte	0xf1
	.4byte	0x5a
	.byte	0x5
	.byte	0x3
	.4byte	cur_txd_idx
	.uleb128 0x34
	.4byte	$LASF124
	.byte	0x1
	.byte	0xf2
	.4byte	0xd7f
	.byte	0x5
	.byte	0x3
	.4byte	rx_ring
	.uleb128 0x7
	.byte	0x4
	.4byte	0x431
	.uleb128 0x34
	.4byte	$LASF125
	.byte	0x1
	.byte	0xf3
	.4byte	0xd96
	.byte	0x5
	.byte	0x3
	.4byte	tx_ring
	.uleb128 0x7
	.byte	0x4
	.4byte	0x5b4
	.uleb128 0x5
	.4byte	0xdac
	.4byte	0x954
	.uleb128 0x6
	.4byte	0x6f
	.byte	0x3f
	.byte	0x0
	.uleb128 0x34
	.4byte	$LASF126
	.byte	0x1
	.byte	0xf4
	.4byte	0xd9c
	.byte	0x5
	.byte	0x3
	.4byte	rxskbs
	.uleb128 0x34
	.4byte	$LASF127
	.byte	0x1
	.byte	0xf5
	.4byte	0xd9c
	.byte	0x5
	.byte	0x3
	.4byte	txskbs
	.uleb128 0x5
	.4byte	0xdde
	.4byte	0x5b4
	.uleb128 0x6
	.4byte	0x6f
	.byte	0x3f
	.byte	0x0
	.uleb128 0x34
	.4byte	$LASF128
	.byte	0x1
	.byte	0xf6
	.4byte	0xdce
	.byte	0x5
	.byte	0x3
	.4byte	tx_ring_cache
	.uleb128 0x5
	.4byte	0xdff
	.4byte	0x431
	.uleb128 0x6
	.4byte	0x6f
	.byte	0x3f
	.byte	0x0
	.uleb128 0x34
	.4byte	$LASF129
	.byte	0x1
	.byte	0xf7
	.4byte	0xdef
	.byte	0x5
	.byte	0x3
	.4byte	rx_ring_cache
	.uleb128 0x5
	.4byte	0xe23
	.4byte	0xe23
	.uleb128 0x35
	.4byte	0x6f
	.4byte	0x647ff
	.byte	0x0
	.uleb128 0x36
	.4byte	0x25
	.uleb128 0x34
	.4byte	$LASF130
	.byte	0x1
	.byte	0xf8
	.4byte	0xe39
	.byte	0x5
	.byte	0x3
	.4byte	sk_buf_pool
	.uleb128 0x36
	.4byte	0xe10
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
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x35
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x27
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
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
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
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
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
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
	.uleb128 0x5
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
	.uleb128 0x17
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1a
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1b
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
	.uleb128 0x5
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
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x1f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x21
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x22
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x23
	.uleb128 0xa
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x24
	.uleb128 0x1d
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x25
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x27
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x28
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x2a
	.uleb128 0xa
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0x0
	.byte	0x0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x2c
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x2d
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x2e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x30
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x32
	.uleb128 0xa
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x33
	.uleb128 0xa
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x34
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
	.uleb128 0x35
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x36
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0xfc
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0xe3f
	.4byte	0x5f9
	.ascii	"mii_mgr_read\000"
	.4byte	0x68a
	.ascii	"mii_mgr_write\000"
	.4byte	0x710
	.ascii	"rw_rf_reg\000"
	.4byte	0x7b1
	.ascii	"mt7620_eth_probe\000"
	.4byte	0x979
	.ascii	"mt7620_eth_link_change\000"
	.4byte	0xb80
	.ascii	"PHY_power_ops\000"
	.4byte	0xbc8
	.ascii	"PHY_led_ops\000"
	.4byte	0xc1d
	.ascii	"mt7620_start_eth\000"
	.4byte	0xc56
	.ascii	"mt7620_stop_eth\000"
	.4byte	0xc8f
	.ascii	"mt7620_eth_init\000"
	.4byte	0xcca
	.ascii	"mt7620_eth_halt\000"
	.4byte	0xcf5
	.ascii	"rt2880_eth_initialize\000"
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
	.section	.debug_ranges,"",@progbits
$Ldebug_ranges0:
	.4byte	$LBB3-$Ltext0
	.4byte	$LBE3-$Ltext0
	.4byte	$LBB5-$Ltext0
	.4byte	$LBE5-$Ltext0
	.4byte	0x0
	.4byte	0x0
	.4byte	$LBB7-$Ltext0
	.4byte	$LBE7-$Ltext0
	.4byte	$LBB21-$Ltext0
	.4byte	$LBE21-$Ltext0
	.4byte	$LBB19-$Ltext0
	.4byte	$LBE19-$Ltext0
	.4byte	$LBB17-$Ltext0
	.4byte	$LBE17-$Ltext0
	.4byte	$LBB15-$Ltext0
	.4byte	$LBE15-$Ltext0
	.4byte	$LBB13-$Ltext0
	.4byte	$LBE13-$Ltext0
	.4byte	$LBB11-$Ltext0
	.4byte	$LBE11-$Ltext0
	.4byte	$LBB9-$Ltext0
	.4byte	$LBE9-$Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",@progbits,1
$LASF25:
	.ascii	"iobase\000"
$LASF68:
	.ascii	"_PDMA_TXD_INFO3_\000"
$LASF116:
	.ascii	"mt7620_start_eth\000"
$LASF97:
	.ascii	"temp\000"
$LASF33:
	.ascii	"sk_buff_s\000"
$LASF11:
	.ascii	"bi_enetaddr\000"
$LASF58:
	.ascii	"rxd_info3\000"
$LASF62:
	.ascii	"_PDMA_TXD_INFO2_\000"
$LASF31:
	.ascii	"next\000"
$LASF61:
	.ascii	"SDP0\000"
$LASF24:
	.ascii	"enetaddr\000"
$LASF15:
	.ascii	"bi_memsize\000"
$LASF122:
	.ascii	"cur_rxd_idx\000"
$LASF98:
	.ascii	"mt7620_eth_link_change\000"
$LASF129:
	.ascii	"rx_ring_cache\000"
$LASF96:
	.ascii	"dma_size\000"
$LASF77:
	.ascii	"PDMA_txdesc\000"
$LASF67:
	.ascii	"LS0_bit\000"
$LASF130:
	.ascii	"sk_buf_pool\000"
$LASF133:
	.ascii	"/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tb"
	.ascii	"sboot/cpu/mt7620a\000"
$LASF88:
	.ascii	"rw_rf_reg\000"
$LASF81:
	.ascii	"txd_info4\000"
$LASF28:
	.ascii	"send\000"
$LASF92:
	.ascii	"mt7620_eth_probe\000"
$LASF108:
	.ascii	"packet\000"
$LASF65:
	.ascii	"BURST_bit\000"
$LASF64:
	.ascii	"LS1_bit\000"
$LASF18:
	.ascii	"bi_flashoffset\000"
$LASF57:
	.ascii	"rxd_info2\000"
$LASF59:
	.ascii	"rxd_info4\000"
$LASF36:
	.ascii	"LINK_DOWN\000"
$LASF123:
	.ascii	"cur_txd_idx\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF73:
	.ascii	"INSP\000"
$LASF126:
	.ascii	"rxskbs\000"
$LASF127:
	.ascii	"txskbs\000"
$LASF105:
	.ascii	"newskb\000"
$LASF132:
	.ascii	"mt7620_eth.c\000"
$LASF91:
	.ascii	"value\000"
$LASF35:
	.ascii	"used\000"
$LASF90:
	.ascii	"rfcsr\000"
$LASF16:
	.ascii	"bi_flashstart\000"
$LASF110:
	.ascii	"oldskb\000"
$LASF131:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF117:
	.ascii	"mt7620_stop_eth\000"
$LASF10:
	.ascii	"bi_ip_addr\000"
$LASF99:
	.ascii	"phystate\000"
$LASF55:
	.ascii	"PDMA_rxdesc\000"
$LASF42:
	.ascii	"PLEN1\000"
$LASF86:
	.ascii	"mii_mgr_write\000"
$LASF32:
	.ascii	"priv\000"
$LASF8:
	.ascii	"char\000"
$LASF125:
	.ascii	"tx_ring\000"
$LASF34:
	.ascii	"data\000"
$LASF39:
	.ascii	"_PDMA_RXD_INFO1_\000"
$LASF63:
	.ascii	"SDL1\000"
$LASF71:
	.ascii	"VPRI_VIDX\000"
$LASF6:
	.ascii	"long long int\000"
$LASF109:
	.ascii	"length\000"
$LASF89:
	.ascii	"write\000"
$LASF70:
	.ascii	"_PDMA_TXD_INFO4_\000"
$LASF17:
	.ascii	"bi_flashsize\000"
$LASF54:
	.ascii	"UN_USE1\000"
$LASF12:
	.ascii	"bi_arch_number\000"
$LASF104:
	.ascii	"mt7620_eth_recv\000"
$LASF37:
	.ascii	"LINK_UP\000"
$LASF94:
	.ascii	"mt7620_gsw_init\000"
$LASF66:
	.ascii	"SDL0\000"
$LASF85:
	.ascii	"mii_mgr_read\000"
$LASF46:
	.ascii	"_PDMA_RXD_INFO3_\000"
$LASF13:
	.ascii	"bi_boot_params\000"
$LASF102:
	.ascii	"linkmask\000"
$LASF41:
	.ascii	"_PDMA_RXD_INFO2_\000"
$LASF82:
	.ascii	"phy_addr\000"
$LASF19:
	.ascii	"uchar\000"
$LASF72:
	.ascii	"SIDX\000"
$LASF101:
	.ascii	"pLinkStatus\000"
$LASF9:
	.ascii	"bi_baudrate\000"
$LASF21:
	.ascii	"bd_info\000"
$LASF74:
	.ascii	"RESV\000"
$LASF51:
	.ascii	"L4VLD\000"
$LASF48:
	.ascii	"_PDMA_RXD_INFO4_\000"
$LASF44:
	.ascii	"PLEN0\000"
$LASF134:
	.ascii	"LANWANPartition\000"
$LASF124:
	.ascii	"rx_ring\000"
$LASF4:
	.ascii	"short int\000"
$LASF128:
	.ascii	"tx_ring_cache\000"
$LASF111:
	.ascii	"status\000"
$LASF100:
	.ascii	"mt7620_eth_linkck\000"
$LASF83:
	.ascii	"phy_register\000"
$LASF23:
	.ascii	"name\000"
$LASF52:
	.ascii	"TACK\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF118:
	.ascii	"mt7620_eth_init\000"
$LASF119:
	.ascii	"mt7620_eth_halt\000"
$LASF27:
	.ascii	"init\000"
$LASF112:
	.ascii	"PHY_power_ops\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF78:
	.ascii	"txd_info1\000"
$LASF79:
	.ascii	"txd_info2\000"
$LASF80:
	.ascii	"txd_info3\000"
$LASF14:
	.ascii	"bi_memstart\000"
$LASF30:
	.ascii	"halt\000"
$LASF38:
	.ascii	"LINKSTATUS\000"
$LASF107:
	.ascii	"mt7620_eth_send\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF20:
	.ascii	"bd_t\000"
$LASF49:
	.ascii	"FOE_Entry\000"
$LASF50:
	.ascii	"CRSN\000"
$LASF75:
	.ascii	"FP_BMAP\000"
$LASF115:
	.ascii	"pins\000"
$LASF26:
	.ascii	"state\000"
$LASF121:
	.ascii	"ret_val\000"
$LASF120:
	.ascii	"rt2880_eth_initialize\000"
$LASF40:
	.ascii	"PDP0\000"
$LASF53:
	.ascii	"IP4F\000"
$LASF60:
	.ascii	"_PDMA_TXD_INFO1_\000"
$LASF22:
	.ascii	"eth_device\000"
$LASF29:
	.ascii	"recv\000"
$LASF3:
	.ascii	"signed char\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF43:
	.ascii	"UN_USED\000"
$LASF87:
	.ascii	"write_data\000"
$LASF93:
	.ascii	"IsSwitchVlanTableBusy\000"
$LASF69:
	.ascii	"SDP1\000"
$LASF84:
	.ascii	"__func__\000"
$LASF113:
	.ascii	"optcode\000"
$LASF95:
	.ascii	"dma_descriptor_init\000"
$LASF56:
	.ascii	"rxd_info1\000"
$LASF45:
	.ascii	"DDONE_bit\000"
$LASF106:
	.ascii	"recvok\000"
$LASF76:
	.ascii	"TUI_CO\000"
$LASF114:
	.ascii	"PHY_led_ops\000"
$LASF47:
	.ascii	"PDP1\000"
$LASF103:
	.ascii	"port\000"
	.ident	"GCC: (GNU) 3.4.2"
