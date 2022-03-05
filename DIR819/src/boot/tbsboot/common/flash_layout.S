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
	.ascii	"The backup config data has lost!\n\000"
	.align	2
$LC1:
	.ascii	"recover to backup config!\n\000"
	.align	2
$LC2:
	.ascii	"OK\000"
	.text
	.align	2
	.globl	item_repeat2
	.ent	item_repeat2
	.type	item_repeat2, @function
item_repeat2:
$LFB14:
	.file 1 "flash_layout.c"
	.loc 1 172 0
	.frame	$sp,64,$31		# vars= 8, regs= 7/0, args= 16, gp= 8
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-64
$LCFI0:
	sw	$31,56($sp)
$LCFI1:
	sw	$21,52($sp)
$LCFI2:
	sw	$20,48($sp)
$LCFI3:
	sw	$19,44($sp)
$LCFI4:
	sw	$18,40($sp)
$LCFI5:
	sw	$17,36($sp)
$LCFI6:
	sw	$16,32($sp)
$LCFI7:
	.cprestore	16
	.loc 1 177 0
	li	$2,-2082865152			# 0xffffffff83da0000
	sw	$2,24($sp)
	lw	$2,%got(info)($28)
	.loc 1 174 0
	move	$16,$0
	li	$7,65535			# 0xffff
	lw	$4,0($2)
	lw	$6,12($4)
	addiu	$5,$4,12
	move	$3,$4
$L4:
	addiu	$5,$5,4
	.loc 1 182 0
	lw	$2,0($5)
	addiu	$16,$16,1
	addiu	$3,$3,4
	subu	$2,$2,$6
	sltu	$2,$7,$2
	beq	$2,$0,$L4
	sll	$20,$16,2

	.loc 1 186 0
	lw	$5,16($3)
	lw	$7,20($3)
	lw	$25,%call16(flash_read_buf)($28)
	addiu	$6,$sp,24
	jalr	$25
	subu	$7,$7,$5

	lw	$28,16($sp)
	.loc 1 188 0
	lw	$25,%call16(is_ok)($28)
	.loc 1 186 0
	lw	$21,%got(info)($28)
	.loc 1 188 0
	jalr	$25
	lw	$4,24($sp)

	lw	$28,16($sp)
	bne	$2,$0,$L5
	lw	$25,%call16(printf)($28)

	.loc 1 191 0
	lw	$4,%got($LC0)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC0)

	lw	$28,16($sp)
	.loc 1 192 0
	b	$L1
	li	$2,8			# 0x8

$L5:
	.loc 1 196 0
	lw	$4,%got($LC1)($28)
	.loc 1 204 0
	lw	$19,%got($LC2)($28)
	.loc 1 196 0
	jalr	$25
	addiu	$4,$4,%lo($LC1)

	lw	$28,16($sp)
	.loc 1 203 0
	lw	$4,0($21)
	addiu	$6,$16,1
	lw	$25,%call16(flash_erase)($28)
	jalr	$25
	move	$5,$16

	lw	$28,16($sp)
	.loc 1 204 0
	lw	$16,0($21)
	addiu	$4,$19,%lo($LC2)
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addu	$16,$20,$16

	lw	$28,16($sp)
	lw	$18,16($16)
	addiu	$4,$19,%lo($LC2)
	lw	$25,%call16(strlen)($28)
	lw	$16,0($21)
	jalr	$25
	addu	$18,$18,$2

	lw	$3,0($21)
	lw	$28,16($sp)
	addu	$16,$20,$16
	addu	$3,$20,$3
	lw	$25,%call16(strlen)($28)
	lw	$5,12($3)
	lw	$17,12($16)
	lw	$16,16($3)
	addiu	$4,$19,%lo($LC2)
	addu	$17,$17,$2
	jalr	$25
	subu	$16,$16,$5

	lw	$28,16($sp)
	move	$5,$17
	subu	$6,$16,$2
	lw	$25,%call16(flash_write)($28)
	jalr	$25
	move	$4,$18

	lw	$28,16($sp)
	.loc 1 205 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$19,%lo($LC2)

	lw	$3,0($21)
	lw	$28,16($sp)
	addiu	$4,$19,%lo($LC2)
	addu	$3,$20,$3
	lw	$25,%call16(flash_write)($28)
	lw	$5,12($3)
	jalr	$25
	move	$6,$2

	lw	$28,16($sp)
	.loc 1 212 0
	li	$2,7			# 0x7
$L1:
	.loc 1 213 0
	lw	$31,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
$LFE14:
	.end	item_repeat2
	.rdata
	.align	2
	.type	__FUNCTION__.0, @object
	.size	__FUNCTION__.0, 11
__FUNCTION__.0:
	.ascii	"item_check\000"
	.section	.rodata.str1.4
	.align	2
$LC3:
	.ascii	"[%s:%d]:The config data has lost! try to recover from ba"
	.ascii	"ck up config\n\000"
	.align	2
$LC4:
	.ascii	"[%s:%d]: The backup config has lost !!!\n\000"
	.align	2
$LC5:
	.ascii	"[%s:%d]:The item data has lost! try to recover from back"
	.ascii	" up config\n\000"
	.align	2
$LC6:
	.ascii	"[%s:%d]: The item %s has lost !!!\n\000"
	.text
	.align	2
	.globl	item_check
	.ent	item_check
	.type	item_check, @function
item_check:
$LFB15:
	.loc 1 230 0
	.frame	$sp,64,$31		# vars= 8, regs= 7/0, args= 16, gp= 8
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-64
$LCFI8:
	sw	$31,56($sp)
$LCFI9:
	sw	$21,52($sp)
$LCFI10:
	sw	$20,48($sp)
$LCFI11:
	sw	$19,44($sp)
$LCFI12:
	sw	$18,40($sp)
$LCFI13:
	sw	$17,36($sp)
$LCFI14:
	sw	$16,32($sp)
$LCFI15:
	.cprestore	16
	.loc 1 243 0
	lw	$21,%got(info)($28)
	.loc 1 238 0
	li	$2,-2082865152			# 0xffffffff83da0000
	sw	$2,28($sp)
	lw	$4,0($21)
	.loc 1 233 0
	move	$19,$0
	li	$8,65535			# 0xffff
	lw	$7,12($4)
	addiu	$3,$4,12
	move	$6,$4
$L12:
	addiu	$3,$3,4
	.loc 1 243 0
	lw	$5,0($3)
	addiu	$19,$19,1
	addiu	$6,$6,4
	subu	$2,$5,$7
	sltu	$2,$8,$2
	beq	$2,$0,$L12
	sll	$20,$19,2

	.loc 1 247 0
	lw	$7,16($6)
	lw	$25,%call16(flash_read_buf)($28)
	addiu	$6,$sp,28
	jalr	$25
	subu	$7,$7,$5

	lw	$28,16($sp)
	.loc 1 250 0
	lw	$25,%call16(is_ok)($28)
	jalr	$25
	lw	$4,28($sp)

	bne	$2,$0,$L13
	lw	$28,16($sp)

	.loc 1 252 0
	lw	$16,%got(__FUNCTION__.0)($28)
	lw	$4,%got($LC3)($28)
	lw	$25,%call16(printf)($28)
	addiu	$5,$16,%lo(__FUNCTION__.0)
	addiu	$4,$4,%lo($LC3)
	jalr	$25
	li	$6,252			# 0xfc

	lw	$28,16($sp)
	.loc 1 255 0
	lw	$25,%call16(item_repeat2)($28)
	jalr	$25
	nop

	li	$3,8			# 0x8
	lw	$28,16($sp)
	.loc 1 260 0
	.loc 1 255 0
	bne	$2,$3,$L9
	move	$4,$0

	.loc 1 257 0
	lw	$4,%got($LC4)($28)
	lw	$25,%call16(printf)($28)
	addiu	$5,$16,%lo(__FUNCTION__.0)
	addiu	$4,$4,%lo($LC4)
	b	$L35
	li	$6,257			# 0x101

$L13:
	.loc 1 268 0
	lw	$4,%got($LC2)($28)
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC2)

	lw	$28,16($sp)
	move	$17,$2
	.loc 1 349 0
	lw	$2,%got(info)($28)
	lw	$2,0($2)
$L33:
	addu	$2,$20,$2
	lw	$3,12($2)
	lw	$2,16($2)
	addiu	$4,$17,5
	subu	$2,$2,$3
	sltu	$2,$2,$4
	.loc 1 273 0
	.loc 1 349 0
	bne	$2,$0,$L16
	lw	$2,28($sp)

	.loc 1 273 0
	addu	$16,$2,$17
	.loc 1 275 0
	lbu	$7,4($16)
	li	$2,255			# 0xff
	andi	$4,$7,0x00ff
	.loc 1 277 0
	.loc 1 275 0
	bne	$4,$2,$L17
	lw	$2,%got(info)($28)

	.loc 1 277 0
	sll	$3,$19,2
	lw	$25,%call16(check_addr_null)($28)
	lw	$2,0($2)
	move	$4,$16
	addu	$3,$3,$2
	lw	$2,12($3)
	lw	$5,16($3)
	subu	$5,$5,$2
	jalr	$25
	subu	$5,$5,$17

	li	$3,1			# 0x1
	bne	$2,$3,$L16
	lw	$28,16($sp)

	.loc 1 279 0
	lw	$16,%got(__FUNCTION__.0)($28)
	lw	$4,%got($LC5)($28)
	lw	$25,%call16(printf)($28)
	addiu	$5,$16,%lo(__FUNCTION__.0)
	addiu	$4,$4,%lo($LC5)
	jalr	$25
	li	$6,279			# 0x117

	lw	$28,16($sp)
	.loc 1 281 0
	lw	$25,%call16(item_repeat2)($28)
	jalr	$25
	nop

	li	$3,8			# 0x8
	bne	$2,$3,$L16
	lw	$28,16($sp)

	.loc 1 283 0
	lw	$4,%got($LC4)($28)
	lw	$25,%call16(printf)($28)
	addiu	$5,$16,%lo(__FUNCTION__.0)
	addiu	$4,$4,%lo($LC4)
	b	$L35
	li	$6,283			# 0x11b

$L17:
	.loc 1 297 0
	lbu	$5,3($16)
	lbu	$6,2($16)
	andi	$2,$5,0x00ff
	sll	$2,$2,8
	andi	$3,$6,0x00ff
	or	$2,$2,$3
	.loc 1 301 0
	.loc 1 297 0
	beq	$2,$0,$L36
	lw	$25,%call16(item_repeat2)($28)

	beq	$4,$0,$L20
	li	$2,34			# 0x22

	beq	$4,$2,$L20
	li	$2,17			# 0x11

	.loc 1 315 0
	.loc 1 297 0
	beq	$4,$2,$L37
	andi	$3,$7,0x00ff

	.loc 1 301 0
	lw	$25,%call16(item_repeat2)($28)
$L36:
	jalr	$25
	nop

	li	$3,8			# 0x8
	bne	$2,$3,$L16
	lw	$28,16($sp)

	.loc 1 303 0
	lw	$4,%got($LC4)($28)
	lw	$5,%got(__FUNCTION__.0)($28)
	lw	$25,%call16(printf)($28)
	addiu	$4,$4,%lo($LC4)
	addiu	$5,$5,%lo(__FUNCTION__.0)
	jalr	$25
	li	$6,303			# 0x12f

	.loc 1 305 0
	b	$L16
	lw	$28,16($sp)

$L20:
	.loc 1 315 0
	andi	$3,$7,0x00ff
$L37:
	.loc 1 317 0
	.loc 1 315 0
	bne	$3,$0,$L23
	andi	$2,$5,0x00ff

	.loc 1 317 0
	b	$L34
	andi	$3,$6,0x00ff

$L23:
	.loc 1 323 0
	li	$2,34			# 0x22
	bne	$3,$2,$L24
	nop

	.loc 1 325 0
	.loc 1 327 0
	b	$L15
	addiu	$17,$17,6

$L24:
	.loc 1 331 0
	li	$2,17			# 0x11
	.loc 1 333 0
	.loc 1 331 0
	bne	$3,$2,$L15
	lw	$25,%call16(crc16)($28)

	.loc 1 333 0
	andi	$5,$5,0x00ff
	andi	$2,$6,0x00ff
	sll	$5,$5,8
	addiu	$18,$16,5
	move	$4,$18
	or	$5,$5,$2
	jalr	$25
	addiu	$6,$sp,24

	.loc 1 334 0
	lbu	$2,1($16)
	lbu	$3,0($16)
	lhu	$4,24($sp)
	sll	$2,$2,8
	or	$2,$2,$3
	.loc 1 333 0
	.loc 1 334 0
	bne	$4,$2,$L26
	lw	$28,16($sp)

	.loc 1 336 0
	lbu	$2,3($16)
	lbu	$3,2($16)
$L34:
	sll	$2,$2,8
	or	$2,$2,$3
	addiu	$3,$2,5
	andi	$3,$3,0x1
	addu	$2,$2,$3
	addu	$2,$17,$2
	.loc 1 338 0
	b	$L15
	addiu	$17,$2,5

$L26:
	.loc 1 342 0
	lw	$16,%got(__FUNCTION__.0)($28)
	lw	$4,%got($LC6)($28)
	lw	$25,%call16(printf)($28)
	move	$7,$18
	addiu	$4,$4,%lo($LC6)
	addiu	$5,$16,%lo(__FUNCTION__.0)
	jalr	$25
	li	$6,342			# 0x156

	lw	$28,16($sp)
	.loc 1 344 0
	lw	$25,%call16(item_repeat2)($28)
	jalr	$25
	nop

	li	$3,8			# 0x8
	bne	$2,$3,$L16
	lw	$28,16($sp)

	.loc 1 346 0
	lw	$4,%got($LC4)($28)
	lw	$25,%call16(printf)($28)
	addiu	$5,$16,%lo(__FUNCTION__.0)
	addiu	$4,$4,%lo($LC4)
	li	$6,346			# 0x15a
$L35:
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 347 0
	b	$L9
	li	$4,9			# 0x9

$L15:
	.loc 1 349 0
	b	$L33
	lw	$2,0($21)

$L16:
	.loc 1 360 0
	move	$4,$0
$L9:
	.loc 1 361 0
	lw	$31,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	move	$2,$4
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
$LFE15:
	.end	item_check
	.section	.rodata.str1.4
	.align	2
$LC7:
	.ascii	"syn config to bak ok!\n\000"
	.text
	.align	2
	.globl	config_synTo_bak
	.ent	config_synTo_bak
	.type	config_synTo_bak, @function
config_synTo_bak:
$LFB16:
	.loc 1 375 0
	.frame	$sp,64,$31		# vars= 8, regs= 8/0, args= 16, gp= 8
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-64
$LCFI16:
	sw	$31,60($sp)
$LCFI17:
	sw	$22,56($sp)
$LCFI18:
	sw	$21,52($sp)
$LCFI19:
	sw	$20,48($sp)
$LCFI20:
	sw	$19,44($sp)
$LCFI21:
	sw	$18,40($sp)
$LCFI22:
	sw	$17,36($sp)
$LCFI23:
	sw	$16,32($sp)
$LCFI24:
	.cprestore	16
	.loc 1 388 0
	lw	$21,%got(info)($28)
	.loc 1 383 0
	li	$2,-2082865152			# 0xffffffff83da0000
	sw	$2,24($sp)
	lw	$4,0($21)
	.loc 1 377 0
	move	$20,$0
	li	$6,65535			# 0xffff
	lw	$5,12($4)
	addiu	$3,$4,12
$L41:
	addiu	$3,$3,4
	.loc 1 388 0
	lw	$2,0($3)
	addiu	$20,$20,1
	subu	$2,$2,$5
	sltu	$2,$6,$2
	beq	$2,$0,$L41
	sll	$19,$20,2

	.loc 1 395 0
	lw	$25,%call16(flash_erase)($28)
	addiu	$5,$20,1
	jalr	$25
	addiu	$6,$20,2

	lw	$28,16($sp)
	.loc 1 399 0
	lw	$16,0($21)
	lw	$22,%got($LC2)($28)
	lw	$25,%call16(strlen)($28)
	addu	$16,$19,$16
	jalr	$25
	addiu	$4,$22,%lo($LC2)

	.loc 1 404 0
	lw	$4,0($21)
	.loc 1 399 0
	lw	$28,16($sp)
	lw	$8,16($16)
	.loc 1 404 0
	addu	$3,$19,$4
	lw	$5,12($3)
	lw	$7,16($3)
	lw	$25,%call16(flash_read_buf)($28)
	addiu	$6,$sp,24
	subu	$7,$7,$5
	.loc 1 399 0
	.loc 1 404 0
	jalr	$25
	addu	$18,$8,$2

	lw	$28,16($sp)
	.loc 1 405 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$22,%lo($LC2)

	lw	$28,16($sp)
	move	$17,$2
$L53:
	.loc 1 455 0
	lw	$2,0($21)
	addiu	$4,$17,5
	addu	$2,$19,$2
	lw	$3,12($2)
	lw	$2,16($2)
	subu	$2,$2,$3
	sltu	$2,$2,$4
	.loc 1 410 0
	.loc 1 455 0
	bne	$2,$0,$L43
	lw	$2,24($sp)

	.loc 1 410 0
	addu	$16,$2,$17
	.loc 1 412 0
	lbu	$3,4($16)
	li	$2,255			# 0xff
	.loc 1 418 0
	.loc 1 412 0
	bne	$3,$2,$L44
	lw	$25,%call16(strlen)($28)

	.loc 1 418 0
	jalr	$25
	addiu	$4,$22,%lo($LC2)

	lw	$28,16($sp)
	sll	$5,$20,2
	addiu	$4,$22,%lo($LC2)
	lw	$3,%got(info)($28)
	lw	$25,%call16(flash_write)($28)
	move	$6,$2
	lw	$3,0($3)
	addu	$5,$5,$3
	jalr	$25
	lw	$5,16($5)

	.loc 1 423 0
	b	$L43
	lw	$28,16($sp)

$L44:
	.loc 1 433 0
	.loc 1 426 0
	bne	$3,$0,$L45
	li	$2,34			# 0x22

	.loc 1 428 0
	lbu	$2,3($16)
	lbu	$3,2($16)
	sll	$2,$2,8
	or	$2,$2,$3
	addiu	$3,$2,5
	andi	$3,$3,0x1
	addu	$2,$2,$3
	addu	$2,$17,$2
	.loc 1 430 0
	b	$L53
	addiu	$17,$2,5

$L45:
	.loc 1 440 0
	.loc 1 433 0
	bne	$3,$2,$L46
	li	$2,17			# 0x11

	.loc 1 435 0
	.loc 1 437 0
	b	$L53
	addiu	$17,$17,6

$L46:
	.loc 1 446 0
	lw	$25,%call16(flash_write)($28)
	move	$5,$18
	.loc 1 440 0
	bne	$3,$2,$L53
	move	$4,$16

	.loc 1 446 0
	lbu	$6,3($16)
	lbu	$2,2($16)
	sll	$6,$6,8
	or	$6,$6,$2
	addiu	$2,$6,5
	andi	$2,$2,0x1
	addu	$6,$6,$2
	jalr	$25
	addiu	$6,$6,5

	.loc 1 453 0
	lbu	$3,3($16)
	lbu	$2,2($16)
	.loc 1 446 0
	lw	$28,16($sp)
	.loc 1 453 0
	sll	$3,$3,8
	or	$3,$3,$2
	addiu	$2,$3,5
	andi	$2,$2,0x1
	addu	$3,$3,$2
	.loc 1 454 0
	addu	$2,$18,$3
	.loc 1 453 0
	addu	$3,$17,$3
	.loc 1 454 0
	addiu	$18,$2,5
	.loc 1 453 0
	b	$L53
	addiu	$17,$3,5

$L43:
	.loc 1 461 0
	lw	$4,%got($LC7)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC7)

	lw	$28,16($sp)
	.loc 1 465 0
	lw	$31,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
$LFE16:
	.end	config_synTo_bak
	.section	.rodata.str1.4
	.align	2
$LC8:
	.ascii	"!!!!!!!!! item_get: can not find %s item!!!!!!!!!!\n\000"
	.text
	.align	2
	.globl	item_get
	.ent	item_get
	.type	item_get, @function
item_get:
$LFB17:
	.loc 1 481 0
	.frame	$sp,64,$31		# vars= 8, regs= 8/0, args= 16, gp= 8
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-64
$LCFI25:
	sw	$31,60($sp)
$LCFI26:
	sw	$22,56($sp)
$LCFI27:
	sw	$21,52($sp)
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
	.cprestore	16
	.loc 1 492 0
	lw	$16,%got(info)($28)
	.loc 1 487 0
	li	$2,-2082865152			# 0xffffffff83da0000
	.loc 1 481 0
	move	$21,$4
	lw	$8,0($16)
	move	$22,$6
	.loc 1 487 0
	sw	$2,24($sp)
	lw	$7,12($8)
	.loc 1 481 0
	move	$19,$5
	.loc 1 483 0
	move	$6,$0
	li	$9,65535			# 0xffff
	addiu	$3,$8,12
	move	$4,$8
$L57:
	addiu	$3,$3,4
	.loc 1 492 0
	lw	$5,0($3)
	addiu	$6,$6,1
	addiu	$4,$4,4
	subu	$2,$5,$7
	sltu	$2,$9,$2
	beq	$2,$0,$L57
	sll	$20,$6,2

	.loc 1 496 0
	lw	$7,16($4)
	lw	$25,%call16(flash_read_buf)($28)
	move	$4,$8
	subu	$7,$7,$5
	jalr	$25
	addiu	$6,$sp,24

	lw	$28,16($sp)
	.loc 1 497 0
	lw	$4,%got($LC2)($28)
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC2)

	lw	$28,16($sp)
	move	$17,$2
$L70:
	.loc 1 548 0
	lw	$2,0($16)
	addiu	$4,$17,5
	addu	$2,$20,$2
	lw	$3,12($2)
	lw	$2,16($2)
	subu	$2,$2,$3
	sltu	$2,$2,$4
	.loc 1 502 0
	.loc 1 548 0
	bne	$2,$0,$L59
	lw	$2,24($sp)

	.loc 1 502 0
	addu	$18,$2,$17
	.loc 1 505 0
	lbu	$3,4($18)
	li	$2,255			# 0xff
	.loc 1 552 0
	.loc 1 505 0
	beq	$3,$2,$L54
	li	$2,4			# 0x4

	.loc 1 519 0
	.loc 1 511 0
	beq	$3,$0,$L64
	li	$2,34			# 0x22

	.loc 1 530 0
	lw	$25,%call16(strcmp)($28)
	addiu	$4,$18,5
	.loc 1 519 0
	bne	$3,$2,$L62
	move	$5,$19

	.loc 1 521 0
	.loc 1 523 0
	b	$L70
	addiu	$17,$17,6

$L62:
	.loc 1 527 0
	li	$2,17			# 0x11
	bne	$3,$2,$L63
	nop

	.loc 1 530 0
	jalr	$25
	nop

	bne	$2,$0,$L64
	lw	$28,16($sp)

	.loc 1 533 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	move	$4,$19

	lw	$28,16($sp)
	lbu	$16,3($18)
	lbu	$3,2($18)
	lw	$25,%call16(strlen)($28)
	move	$4,$19
	sll	$16,$16,8
	or	$16,$16,$3
	jalr	$25
	addu	$17,$18,$2

	lw	$28,16($sp)
	subu	$16,$16,$2
	addiu	$17,$17,6
	lw	$25,%call16(memcpy)($28)
	addiu	$6,$16,-1
	move	$4,$21
	jalr	$25
	move	$5,$17

	lw	$28,16($sp)
	.loc 1 534 0
	lbu	$16,3($18)
	lbu	$2,2($18)
	lw	$25,%call16(strlen)($28)
	sll	$16,$16,8
	move	$4,$19
	jalr	$25
	or	$16,$16,$2

	lw	$28,16($sp)
	subu	$16,$16,$2
	addiu	$16,$16,-1
	.loc 1 536 0
	move	$2,$0
	.loc 1 534 0
	.loc 1 536 0
	b	$L54
	sh	$16,0($22)

$L64:
	.loc 1 540 0
	lbu	$2,3($18)
	lbu	$3,2($18)
	sll	$2,$2,8
	or	$2,$2,$3
	addiu	$3,$2,5
	andi	$3,$3,0x1
	addu	$2,$2,$3
	addu	$2,$17,$2
	.loc 1 542 0
	b	$L70
	addiu	$17,$2,5

$L63:
	.loc 1 547 0
	lw	$4,%got($LC8)($28)
	lw	$25,%call16(printf)($28)
	move	$5,$19
	jalr	$25
	addiu	$4,$4,%lo($LC8)

	lw	$28,16($sp)
$L59:
	.loc 1 552 0
	li	$2,4			# 0x4
$L54:
	.loc 1 553 0
	lw	$31,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
$LFE17:
	.end	item_get
	.section	.rodata.str1.4
	.align	2
$LC9:
	.ascii	"llconfig\000"
	.align	2
$LC10:
	.ascii	"kernel_offset=0x%x,rootfs_offset=0x%x\n\000"
	.align	2
$LC11:
	.ascii	"system supports single image and \000"
	.align	2
$LC12:
	.ascii	"version is %s\n\000"
	.text
	.align	2
	.globl	sysdata_get
	.ent	sysdata_get
	.type	sysdata_get, @function
sysdata_get:
$LFB12:
	.loc 1 88 0
	.frame	$sp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
$LCFI34:
	sw	$31,36($sp)
$LCFI35:
	sw	$16,32($sp)
$LCFI36:
	.cprestore	16
	.loc 1 95 0
	lw	$5,%got($LC9)($28)
	lw	$25,%call16(item_get)($28)
	addiu	$6,$sp,24
	addiu	$5,$5,%lo($LC9)
	.loc 1 88 0
	.loc 1 95 0
	jalr	$25
	move	$16,$4

	lw	$28,16($sp)
	.loc 1 133 0
	li	$3,1			# 0x1
	.loc 1 123 0
	lw	$4,%got($LC10)($28)
	lw	$25,%call16(printf)($28)
	.loc 1 95 0
	bne	$2,$0,$L71
	addiu	$4,$4,%lo($LC10)

	.loc 1 123 0
	lw	$6,8($16)
	jalr	$25
	lw	$5,4($16)

	lw	$28,16($sp)
	.loc 1 124 0
	lw	$4,%got($LC11)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC11)

	lw	$28,16($sp)
	.loc 1 126 0
	addiu	$5,$16,100
	lw	$4,%got($LC12)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC12)

	lw	$28,16($sp)
	.loc 1 129 0
	lw	$25,%call16(prepare_tags)($28)
	jalr	$25
	nop

	lw	$28,16($sp)
	.loc 1 131 0
	move	$3,$0
$L71:
	.loc 1 134 0
	lw	$31,36($sp)
	lw	$16,32($sp)
	move	$2,$3
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
$LFE12:
	.end	sysdata_get
	.align	2
	.globl	item_repeat
	.ent	item_repeat
	.type	item_repeat, @function
item_repeat:
$LFB19:
	.loc 1 749 0
	.frame	$sp,72,$31		# vars= 8, regs= 10/0, args= 16, gp= 8
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-72
$LCFI37:
	sw	$31,68($sp)
$LCFI38:
	sw	$fp,64($sp)
$LCFI39:
	sw	$23,60($sp)
$LCFI40:
	sw	$22,56($sp)
$LCFI41:
	sw	$21,52($sp)
$LCFI42:
	sw	$20,48($sp)
$LCFI43:
	sw	$19,44($sp)
$LCFI44:
	sw	$18,40($sp)
$LCFI45:
	sw	$17,36($sp)
$LCFI46:
	sw	$16,32($sp)
$LCFI47:
	.cprestore	16
	.loc 1 762 0
	lw	$21,%got(info)($28)
	.loc 1 757 0
	li	$2,-2082865152			# 0xffffffff83da0000
	sw	$2,24($sp)
	lw	$4,0($21)
	.loc 1 751 0
	move	$18,$0
	.loc 1 753 0
	move	$23,$0
	lw	$5,12($4)
	li	$6,65535			# 0xffff
	addiu	$3,$4,12
$L76:
	addiu	$3,$3,4
	.loc 1 762 0
	lw	$2,0($3)
	addiu	$18,$18,1
	subu	$2,$2,$5
	sltu	$2,$6,$2
	beq	$2,$0,$L76
	sll	$20,$18,2

	.loc 1 769 0
	lw	$25,%call16(flash_erase)($28)
	addiu	$fp,$18,1
	move	$5,$fp
	jalr	$25
	addiu	$6,$18,2

	lw	$28,16($sp)
	.loc 1 773 0
	lw	$16,0($21)
	lw	$22,%got($LC2)($28)
	lw	$25,%call16(strlen)($28)
	addu	$16,$20,$16
	jalr	$25
	addiu	$4,$22,%lo($LC2)

	.loc 1 778 0
	lw	$4,0($21)
	.loc 1 773 0
	lw	$28,16($sp)
	lw	$8,16($16)
	.loc 1 778 0
	addu	$3,$20,$4
	lw	$5,12($3)
	lw	$7,16($3)
	lw	$25,%call16(flash_read_buf)($28)
	addiu	$6,$sp,24
	subu	$7,$7,$5
	.loc 1 773 0
	.loc 1 778 0
	jalr	$25
	addu	$19,$8,$2

	lw	$28,16($sp)
	.loc 1 779 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$22,%lo($LC2)

	lw	$28,16($sp)
	move	$17,$2
$L90:
	.loc 1 833 0
	lw	$2,0($21)
	addiu	$4,$17,5
	addu	$2,$20,$2
	lw	$3,12($2)
	lw	$2,16($2)
	subu	$2,$2,$3
	sltu	$2,$2,$4
	.loc 1 784 0
	.loc 1 833 0
	bne	$2,$0,$L78
	lw	$2,24($sp)

	.loc 1 784 0
	addu	$16,$2,$17
	.loc 1 786 0
	lbu	$7,4($16)
	li	$2,255			# 0xff
	andi	$4,$7,0x00ff
	.loc 1 792 0
	.loc 1 786 0
	bne	$4,$2,$L79
	lw	$25,%call16(strlen)($28)

	.loc 1 792 0
	jalr	$25
	addiu	$4,$22,%lo($LC2)

	lw	$28,16($sp)
	sll	$5,$18,2
	addiu	$4,$22,%lo($LC2)
	lw	$3,%got(info)($28)
	lw	$25,%call16(flash_write)($28)
	move	$6,$2
	lw	$3,0($3)
	addu	$5,$5,$3
	jalr	$25
	lw	$5,16($5)

	.loc 1 797 0
	b	$L78
	lw	$28,16($sp)

$L79:
	.loc 1 799 0
	lbu	$6,3($16)
	lbu	$5,2($16)
	andi	$2,$6,0x00ff
	sll	$2,$2,8
	andi	$3,$5,0x00ff
	or	$2,$2,$3
	beq	$2,$0,$L78
	nop

	beq	$4,$0,$L80
	li	$2,34			# 0x22

	beq	$4,$2,$L80
	li	$2,17			# 0x11

	bne	$4,$2,$L78
	nop

$L80:
	.loc 1 804 0
	andi	$3,$7,0x00ff
	.loc 1 806 0
	.loc 1 804 0
	bne	$3,$0,$L82
	andi	$2,$6,0x00ff

	.loc 1 806 0
	andi	$3,$5,0x00ff
	sll	$2,$2,8
	or	$2,$2,$3
	addiu	$3,$2,5
	andi	$3,$3,0x1
	addu	$2,$2,$3
	addu	$2,$17,$2
	.loc 1 808 0
	b	$L90
	addiu	$17,$2,5

$L82:
	.loc 1 811 0
	li	$2,34			# 0x22
	.loc 1 818 0
	.loc 1 811 0
	bne	$3,$2,$L83
	li	$2,17			# 0x11

	.loc 1 813 0
	.loc 1 815 0
	b	$L90
	addiu	$17,$17,6

$L83:
	.loc 1 824 0
	.loc 1 818 0
	bne	$3,$2,$L90
	andi	$6,$6,0x00ff

	.loc 1 824 0
	andi	$2,$5,0x00ff
	sll	$6,$6,8
	or	$6,$6,$2
	addiu	$2,$6,5
	andi	$2,$2,0x1
	lw	$25,%call16(flash_write)($28)
	addu	$6,$6,$2
	move	$5,$19
	move	$4,$16
	jalr	$25
	addiu	$6,$6,5

	.loc 1 831 0
	lbu	$3,3($16)
	lbu	$2,2($16)
	.loc 1 824 0
	lw	$28,16($sp)
	.loc 1 831 0
	sll	$3,$3,8
	or	$3,$3,$2
	addiu	$2,$3,5
	andi	$2,$2,0x1
	addu	$3,$3,$2
	.loc 1 833 0
	addu	$4,$23,$3
	.loc 1 831 0
	addu	$2,$17,$3
	.loc 1 832 0
	addu	$3,$19,$3
	.loc 1 831 0
	addiu	$17,$2,5
	.loc 1 832 0
	addiu	$19,$3,5
	.loc 1 833 0
	b	$L90
	addiu	$23,$4,5

$L78:
	.loc 1 843 0
	lw	$20,%got(info)($28)
	lw	$25,%call16(flash_erase)($28)
	move	$6,$fp
	lw	$4,0($20)
	.loc 1 852 0
	lw	$19,%got($LC2)($28)
	.loc 1 843 0
	jalr	$25
	move	$5,$18

	lw	$28,16($sp)
	.loc 1 852 0
	lw	$16,0($20)
	addiu	$4,$19,%lo($LC2)
	lw	$25,%call16(strlen)($28)
	sll	$18,$18,2
	jalr	$25
	addu	$16,$18,$16

	lw	$28,16($sp)
	lw	$16,16($16)
	lw	$17,0($20)
	lw	$25,%call16(strlen)($28)
	addiu	$4,$19,%lo($LC2)
	jalr	$25
	addu	$16,$16,$2

	lw	$28,16($sp)
	addu	$17,$18,$17
	lw	$5,12($17)
	lw	$25,%call16(flash_write)($28)
	move	$6,$23
	addu	$5,$5,$2
	jalr	$25
	move	$4,$16

	lw	$28,16($sp)
	.loc 1 869 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$19,%lo($LC2)

	lw	$3,0($20)
	lw	$28,16($sp)
	addiu	$4,$19,%lo($LC2)
	addu	$18,$18,$3
	lw	$25,%call16(flash_write)($28)
	lw	$5,12($18)
	jalr	$25
	move	$6,$2

	lw	$28,16($sp)
	.loc 1 874 0
	lw	$31,68($sp)
	lw	$fp,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	li	$2,7			# 0x7
	j	$31
	addiu	$sp,$sp,72

	.set	macro
	.set	reorder
$LFE19:
	.end	item_repeat
	.rdata
	.align	2
$LC13:
	.ascii	"\000\000"
	.text
	.align	2
	.globl	item_save
	.ent	item_save
	.type	item_save, @function
item_save:
$LFB18:
	.loc 1 570 0
	.frame	$sp,88,$31		# vars= 24, regs= 10/0, args= 16, gp= 8
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-88
$LCFI48:
	sw	$31,84($sp)
$LCFI49:
	sw	$fp,80($sp)
$LCFI50:
	sw	$23,76($sp)
$LCFI51:
	sw	$22,72($sp)
$LCFI52:
	sw	$21,68($sp)
$LCFI53:
	sw	$20,64($sp)
$LCFI54:
	sw	$19,60($sp)
$LCFI55:
	sw	$18,56($sp)
$LCFI56:
	sw	$17,52($sp)
$LCFI57:
	sw	$16,48($sp)
$LCFI58:
	.cprestore	16
	.loc 1 586 0
	lw	$19,%got(info)($28)
	.loc 1 570 0
	andi	$6,$6,0xffff
	.loc 1 581 0
	li	$2,-2082865152			# 0xffffffff83da0000
	lw	$8,0($19)
	.loc 1 570 0
	sw	$4,88($sp)
	sw	$6,44($sp)
	lw	$7,12($8)
	.loc 1 581 0
	sw	$2,40($sp)
	.loc 1 570 0
	move	$fp,$5
	.loc 1 573 0
	move	$21,$0
	.loc 1 574 0
	move	$22,$0
	li	$6,65535			# 0xffff
	addiu	$3,$8,12
	move	$4,$8
$L94:
	addiu	$3,$3,4
	.loc 1 586 0
	lw	$5,0($3)
	addiu	$21,$21,1
	addiu	$4,$4,4
	subu	$2,$5,$7
	sltu	$2,$6,$2
	beq	$2,$0,$L94
	sll	$16,$21,2

	.loc 1 589 0
	lw	$7,16($4)
	lw	$25,%call16(flash_read_buf)($28)
	move	$4,$8
	subu	$7,$7,$5
	jalr	$25
	addiu	$6,$sp,40

	lw	$28,16($sp)
	.loc 1 590 0
	lw	$2,%got($LC2)($28)
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$2,%lo($LC2)

	move	$17,$2
	.loc 1 644 0
	lw	$2,0($19)
	.loc 1 590 0
	lw	$28,16($sp)
	.loc 1 644 0
	addiu	$4,$17,5
	addu	$2,$16,$2
	lw	$3,12($2)
	lw	$2,16($2)
	subu	$2,$2,$3
	sltu	$2,$2,$4
$L119:
	.loc 1 595 0
	.loc 1 644 0
	bne	$2,$0,$L96
	lw	$2,40($sp)

	.loc 1 595 0
	addu	$18,$2,$17
	.loc 1 598 0
	lbu	$7,4($18)
	li	$2,255			# 0xff
	andi	$4,$7,0x00ff
	.loc 1 654 0
	.loc 1 598 0
	beq	$4,$2,$L122
	lw	$25,%call16(strlen)($28)

	.loc 1 603 0
	lbu	$6,3($18)
	lbu	$5,2($18)
	andi	$2,$6,0x00ff
	sll	$2,$2,8
	andi	$3,$5,0x00ff
	or	$2,$2,$3
	.loc 1 651 0
	.loc 1 603 0
	beq	$2,$0,$L123
	li	$19,-2082340864			# 0xffffffff83e20000

	beq	$4,$0,$L98
	li	$2,34			# 0x22

	beq	$4,$2,$L98
	li	$2,17			# 0x11

	.loc 1 653 0
	.loc 1 603 0
	bne	$4,$2,$L124
	li	$2,17

$L98:
	.loc 1 607 0
	andi	$3,$7,0x00ff
	.loc 1 609 0
	.loc 1 607 0
	bne	$3,$0,$L100
	andi	$2,$6,0x00ff

	.loc 1 609 0
	b	$L120
	andi	$3,$5,0x00ff

$L100:
	.loc 1 614 0
	li	$2,34			# 0x22
	bne	$3,$2,$L101
	nop

	.loc 1 616 0
	.loc 1 618 0
	b	$L95
	addiu	$17,$17,6

$L101:
	.loc 1 621 0
	li	$2,17			# 0x11
	.loc 1 644 0
	.loc 1 621 0
	bne	$3,$2,$L125
	lw	$2,%got(info)($28)

	.loc 1 624 0
	lw	$25,%call16(strcmp)($28)
	addiu	$4,$18,5
	jalr	$25
	move	$5,$fp

	bne	$2,$0,$L103
	lw	$28,16($sp)

	.loc 1 626 0
	lw	$2,%got(info)($28)
	sll	$3,$21,2
	lw	$4,0($2)
	sll	$2,$22,2
	addu	$5,$sp,$2
	addu	$3,$3,$4
	lw	$2,12($3)
	lw	$3,40($sp)
	addiu	$22,$22,1
	addu	$2,$2,$18
	subu	$2,$2,$3
	addiu	$2,$2,4
	sw	$2,32($5)
	.loc 1 629 0
	li	$2,2			# 0x2
	.loc 1 635 0
	.loc 1 629 0
	bne	$22,$2,$L103
	lw	$25,%call16(flash_write)($28)

	.loc 1 635 0
	lw	$5,32($sp)
	.loc 1 631 0
	sb	$0,26($sp)
	.loc 1 635 0
	addiu	$4,$sp,26
	jalr	$25
	li	$6,1			# 0x1

	.loc 1 639 0
	lw	$2,36($sp)
	.loc 1 635 0
	lw	$28,16($sp)
	.loc 1 640 0
	li	$22,1			# 0x1
	.loc 1 639 0
	sw	$2,32($sp)
$L103:
	.loc 1 644 0
	lbu	$2,3($18)
	lbu	$3,2($18)
$L120:
	sll	$2,$2,8
	or	$2,$2,$3
	addiu	$3,$2,5
	andi	$3,$3,0x1
	addu	$2,$2,$3
	addu	$2,$17,$2
	addiu	$17,$2,5
$L95:
	lw	$2,%got(info)($28)
$L125:
	sll	$3,$21,2
	addiu	$5,$17,5
	lw	$2,0($2)
	addu	$3,$3,$2
	lw	$4,12($3)
	lw	$2,16($3)
	subu	$2,$2,$4
	b	$L119
	sltu	$2,$2,$5

$L96:
	.loc 1 654 0
	lw	$25,%call16(strlen)($28)
$L122:
	.loc 1 651 0
	li	$19,-2082340864			# 0xffffffff83e20000
$L123:
	.loc 1 653 0
	li	$2,17
$L124:
	.loc 1 654 0
	move	$4,$fp
	.loc 1 653 0
	.loc 1 654 0
	jalr	$25
	sb	$2,4($19)

	lw	$28,16($sp)
	addiu	$16,$19,5
	move	$6,$2
	lw	$25,%call16(memcpy)($28)
	move	$5,$fp
	jalr	$25
	move	$4,$16

	lw	$28,16($sp)
	.loc 1 655 0
	move	$4,$fp
	lw	$25,%call16(strlen)($28)
	.loc 1 662 0
	lw	$23,%got(info)($28)
	.loc 1 655 0
	jalr	$25
	sll	$20,$21,2

	lw	$28,16($sp)
	addu	$2,$2,$19
	li	$6,1			# 0x1
	lw	$5,%got($LC13)($28)
	lw	$25,%call16(memcpy)($28)
	addiu	$4,$2,5
	jalr	$25
	addiu	$5,$5,%lo($LC13)

	lw	$28,16($sp)
	.loc 1 656 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	move	$4,$fp

	lw	$28,16($sp)
	lw	$5,88($sp)
	lw	$6,44($sp)
	lw	$25,%call16(memcpy)($28)
	addu	$2,$2,$19
	jalr	$25
	addiu	$4,$2,6

	lw	$28,16($sp)
	.loc 1 657 0
	lw	$25,%call16(strlen)($28)
	jalr	$25
	move	$4,$fp

	lw	$3,44($sp)
	lw	$28,16($sp)
	.loc 1 658 0
	move	$4,$16
	.loc 1 657 0
	addu	$2,$2,$3
	addiu	$2,$2,1
	andi	$2,$2,0xffff
	srl	$3,$2,8
	.loc 1 658 0
	lw	$25,%call16(crc16)($28)
	sll	$5,$3,8
	.loc 1 657 0
	andi	$2,$2,0xff
	.loc 1 658 0
	or	$5,$5,$2
	.loc 1 657 0
	sb	$3,3($19)
	.loc 1 658 0
	addiu	$6,$sp,24
	.loc 1 657 0
	.loc 1 658 0
	jalr	$25
	sb	$2,2($19)

	.loc 1 659 0
	lhu	$5,24($sp)
	.loc 1 662 0
	lw	$3,0($23)
	lbu	$4,3($19)
	lbu	$6,2($19)
	.loc 1 659 0
	srl	$2,$5,8
	sb	$2,1($19)
	sb	$5,0($19)
	.loc 1 662 0
	addu	$3,$20,$3
	sll	$4,$4,8
	or	$4,$4,$6
	lw	$5,12($3)
	lw	$3,16($3)
	addiu	$2,$4,5
	andi	$2,$2,0x1
	addu	$4,$4,$2
	subu	$3,$3,$5
	subu	$3,$3,$17
	addiu	$4,$4,5
	sltu	$3,$3,$4
	.loc 1 658 0
	.loc 1 662 0
	beq	$3,$0,$L106
	lw	$28,16($sp)

	.loc 1 665 0
	lw	$25,%call16(item_repeat)($28)
	.loc 1 669 0
	.loc 1 665 0
	jalr	$25
	move	$22,$0

	.loc 1 667 0
	lw	$4,0($23)
	.loc 1 665 0
	lw	$28,16($sp)
	.loc 1 667 0
	addiu	$6,$sp,40
	addu	$2,$20,$4
	lw	$5,12($2)
	lw	$7,16($2)
	lw	$25,%call16(flash_read_buf)($28)
	jalr	$25
	subu	$7,$7,$5

	lw	$28,16($sp)
	.loc 1 668 0
	lw	$2,%got($LC2)($28)
	lw	$25,%call16(strlen)($28)
	jalr	$25
	addiu	$4,$2,%lo($LC2)

	move	$17,$2
	.loc 1 689 0
	lw	$2,0($23)
	.loc 1 668 0
	lw	$28,16($sp)
	.loc 1 689 0
	addiu	$4,$17,5
	addu	$2,$20,$2
	lw	$3,12($2)
	lw	$2,16($2)
	subu	$2,$2,$3
	sltu	$2,$2,$4
$L121:
	.loc 1 684 0
	.loc 1 689 0
	bne	$2,$0,$L108
	lw	$25,%call16(strcmp)($28)

	.loc 1 673 0
	lw	$2,40($sp)
	.loc 1 684 0
	move	$5,$fp
	.loc 1 673 0
	addu	$18,$2,$17
	.loc 1 676 0
	lbu	$3,4($18)
	li	$2,255			# 0xff
	.loc 1 684 0
	.loc 1 676 0
	beq	$3,$2,$L108
	addiu	$4,$18,5

	.loc 1 681 0
	li	$2,17			# 0x11
	.loc 1 689 0
	.loc 1 681 0
	bne	$3,$2,$L126
	lw	$2,%got(info)($28)

	.loc 1 684 0
	jalr	$25
	nop

	.loc 1 686 0
	sll	$3,$22,2
	.loc 1 684 0
	lw	$28,16($sp)
	.loc 1 686 0
	sll	$4,$21,2
	.loc 1 684 0
	bne	$2,$0,$L111
	addu	$5,$sp,$3

	.loc 1 686 0
	lw	$2,%got(info)($28)
	lw	$3,40($sp)
	addiu	$22,$22,1
	lw	$2,0($2)
	addu	$2,$4,$2
	lw	$2,12($2)
	addu	$2,$2,$18
	subu	$2,$2,$3
	addiu	$2,$2,4
	sw	$2,32($5)
$L111:
	.loc 1 689 0
	lbu	$2,3($18)
	lbu	$3,2($18)
	sll	$2,$2,8
	or	$2,$2,$3
	addiu	$3,$2,5
	andi	$3,$3,0x1
	addu	$2,$2,$3
	addu	$2,$17,$2
	addiu	$17,$2,5
	lw	$2,%got(info)($28)
$L126:
	sll	$3,$21,2
	addiu	$5,$17,5
	lw	$2,0($2)
	addu	$3,$3,$2
	lw	$4,12($3)
	lw	$2,16($3)
	subu	$2,$2,$4
	b	$L121
	sltu	$2,$2,$5

$L108:
	.loc 1 696 0
	lw	$2,%got(info)($28)
	lbu	$4,3($19)
	lbu	$5,2($19)
	lw	$3,0($2)
	sll	$2,$21,2
	sll	$4,$4,8
	addu	$2,$2,$3
	or	$4,$4,$5
	lw	$3,16($2)
	lw	$5,12($2)
	addiu	$2,$4,5
	andi	$2,$2,0x1
	addu	$4,$4,$2
	subu	$3,$3,$5
	subu	$3,$3,$17
	addiu	$4,$4,5
	sltu	$3,$3,$4
	.loc 1 699 0
	.loc 1 696 0
	bne	$3,$0,$L91
	li	$2,6			# 0x6

$L106:
	.loc 1 707 0
	lw	$2,%got(info)($28)
	sll	$3,$21,2
	lbu	$6,3($19)
	lw	$2,0($2)
	lbu	$4,2($19)
	lw	$5,40($sp)
	addu	$3,$3,$2
	lw	$2,12($3)
	lw	$25,%call16(flash_write)($28)
	sll	$6,$6,8
	addu	$2,$2,$18
	or	$6,$6,$4
	subu	$5,$2,$5
	addiu	$6,$6,5
	jalr	$25
	li	$4,-2082340864			# 0xffffffff83e20000

	.loc 1 712 0
	li	$2,1			# 0x1
	.loc 1 707 0
	.loc 1 712 0
	bne	$22,$2,$L114
	lw	$28,16($sp)

	.loc 1 718 0
	lw	$25,%call16(flash_write)($28)
	lw	$5,32($sp)
	.loc 1 714 0
	sb	$0,26($sp)
	.loc 1 718 0
	addiu	$4,$sp,26
	jalr	$25
	li	$6,1			# 0x1

	lw	$28,16($sp)
$L114:
	.loc 1 724 0
	move	$2,$0
$L91:
	.loc 1 725 0
	lw	$31,84($sp)
	lw	$fp,80($sp)
	lw	$23,76($sp)
	lw	$22,72($sp)
	lw	$21,68($sp)
	lw	$20,64($sp)
	lw	$19,60($sp)
	lw	$18,56($sp)
	lw	$17,52($sp)
	lw	$16,48($sp)
	j	$31
	addiu	$sp,$sp,88

	.set	macro
	.set	reorder
$LFE18:
	.end	item_save
	.align	2
	.globl	sysdata_save
	.ent	sysdata_save
	.type	sysdata_save, @function
sysdata_save:
$LFB13:
	.loc 1 149 0
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 16, gp= 8
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI59:
	sw	$31,24($sp)
$LCFI60:
	.cprestore	16
	.loc 1 151 0
	lw	$5,%got($LC9)($28)
	lw	$25,%call16(item_save)($28)
	li	$6,188			# 0xbc
	jalr	$25
	addiu	$5,$5,%lo($LC9)

	lw	$28,16($sp)
	.loc 1 156 0
	lw	$31,24($sp)
	sltu	$2,$0,$2
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
$LFE13:
	.end	sysdata_save
	.section	.rodata.str1.4
	.align	2
$LC14:
	.ascii	"update failure! Your image is too long !\n\000"
	.align	2
$LC15:
	.ascii	"Calculated checksum is %x\n\000"
	.align	2
$LC16:
	.ascii	"Checksum validation failed! you should translate image a"
	.ascii	"gain!\n\000"
	.align	2
$LC17:
	.ascii	"wlan_cfg\000"
	.align	2
$LC18:
	.ascii	"\n"
	.ascii	"bak the 2.4G gain len %d, ret %d\n\000"
	.align	2
$LC19:
	.ascii	"wlan_cfg5g\000"
	.align	2
$LC20:
	.ascii	"\n"
	.ascii	"bak the 5G gain len %d, ret %d\n\000"
	.align	2
$LC21:
	.ascii	"\n"
	.ascii	"Erasing flash\000"
	.align	2
$LC22:
	.ascii	"\n"
	.ascii	"Burning flash\000"
	.align	2
$LC23:
	.ascii	".\000"
	.align	2
$LC24:
	.ascii	"\n\000"
	.align	2
$LC25:
	.ascii	"\n"
	.ascii	"save the 2.4G gain\n\000"
	.align	2
$LC26:
	.ascii	"\n"
	.ascii	"save the 5G gain\n\000"
	.align	2
$LC27:
	.ascii	"\n"
	.ascii	"System update completely! Restarting system!\n\000"
	.text
	.align	2
	.globl	flash_update_bin
	.ent	flash_update_bin
	.type	flash_update_bin, @function
flash_update_bin:
$LFB20:
	.loc 1 897 0
	.frame	$sp,72,$31		# vars= 8, regs= 10/0, args= 16, gp= 8
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-72
$LCFI61:
	sw	$31,68($sp)
$LCFI62:
	sw	$fp,64($sp)
$LCFI63:
	sw	$23,60($sp)
$LCFI64:
	sw	$22,56($sp)
$LCFI65:
	sw	$21,52($sp)
$LCFI66:
	sw	$20,48($sp)
$LCFI67:
	sw	$19,44($sp)
$LCFI68:
	sw	$18,40($sp)
$LCFI69:
	sw	$17,36($sp)
$LCFI70:
	sw	$16,32($sp)
$LCFI71:
	.cprestore	16
	.loc 1 908 0
	lw	$17,%got(szWlan2g)($28)
	lw	$25,%call16(memset)($28)
	.loc 1 906 0
	li	$2,512
	.loc 1 897 0
	move	$20,$4
	sll	$19,$5,24
	.loc 1 908 0
	addiu	$4,$17,%lo(szWlan2g)
	move	$5,$0
	li	$6,512			# 0x200
	.loc 1 906 0
	sh	$2,26($sp)
	.loc 1 908 0
	jalr	$25
	sh	$2,24($sp)

	lw	$28,16($sp)
	.loc 1 909 0
	move	$5,$0
	li	$6,512			# 0x200
	lw	$18,%got(szWlan5g)($28)
	lw	$25,%call16(memset)($28)
	.loc 1 897 0
	sra	$19,$19,24
	.loc 1 909 0
	jalr	$25
	addiu	$4,$18,%lo(szWlan5g)

	lw	$28,16($sp)
	.loc 1 899 0
	move	$fp,$0
	.loc 1 900 0
	move	$23,$0
	.loc 1 912 0
	lw	$3,%got(info)($28)
	.loc 1 907 0
	move	$21,$0
	.loc 1 912 0
	lw	$2,0($3)
	lw	$2,0($2)
	sltu	$2,$2,$20
	.loc 1 907 0
	.loc 1 912 0
	beq	$2,$0,$L130
	move	$22,$0

	.loc 1 914 0
	lw	$4,%got($LC14)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC14)

	lw	$28,16($sp)
	.loc 1 916 0
	b	$L129
	li	$2,2			# 0x2

$L130:
	.loc 1 950 0
	.loc 1 918 0
	bne	$19,$0,$L144
	li	$2,2			# 0x2

	.loc 1 921 0
	lw	$2,%got(load_addr)($28)
	.loc 1 924 0
	lw	$25,%call16(tbs_calc_sum_addr)($28)
	addiu	$5,$sp,28
	.loc 1 921 0
	lw	$2,0($2)
	.loc 1 924 0
	addiu	$6,$20,-4
	move	$4,$2
	.loc 1 921 0
	addu	$2,$2,$20
	.loc 1 924 0
	jalr	$25
	lw	$16,-4($2)

	.loc 1 926 0
	lw	$5,28($sp)
	.loc 1 924 0
	.loc 1 926 0
	beq	$5,$16,$L131
	lw	$28,16($sp)

	.loc 1 928 0
	lw	$4,%got($LC15)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC15)

	lw	$28,16($sp)
	.loc 1 929 0
	lw	$4,%got($LC16)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC16)

	lw	$28,16($sp)
	.loc 1 931 0
	b	$L129
	li	$2,1			# 0x1

$L131:
	.loc 1 950 0
	li	$2,2			# 0x2
$L144:
	.loc 1 952 0
	.loc 1 950 0
	beq	$19,$2,$L133
	lw	$5,%got($LC17)($28)

	.loc 1 952 0
	lw	$25,%call16(item_get)($28)
	addiu	$4,$17,%lo(szWlan2g)
	addiu	$5,$5,%lo($LC17)
	jalr	$25
	addiu	$6,$sp,24

	lw	$28,16($sp)
	.loc 1 953 0
	lhu	$5,24($sp)
	move	$6,$2
	lw	$4,%got($LC18)($28)
	lw	$25,%call16(printf)($28)
	.loc 1 952 0
	move	$21,$2
	.loc 1 953 0
	jalr	$25
	addiu	$4,$4,%lo($LC18)

	lw	$28,16($sp)
	.loc 1 954 0
	addiu	$4,$18,%lo(szWlan5g)
	addiu	$6,$sp,26
	lw	$5,%got($LC19)($28)
	lw	$25,%call16(item_get)($28)
	jalr	$25
	addiu	$5,$5,%lo($LC19)

	lw	$28,16($sp)
	.loc 1 955 0
	lhu	$5,26($sp)
	move	$6,$2
	lw	$4,%got($LC20)($28)
	lw	$25,%call16(printf)($28)
	.loc 1 954 0
	move	$22,$2
	.loc 1 955 0
	jalr	$25
	addiu	$4,$4,%lo($LC20)

	lw	$28,16($sp)
$L133:
	.loc 1 959 0
	lw	$4,%got($LC21)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC21)

	lw	$28,16($sp)
	.loc 1 966 0
	move	$5,$0
	lw	$2,%got(info)($28)
	lw	$25,%call16(flash_erase)($28)
	lw	$4,0($2)
	lhu	$6,4($4)
	jalr	$25
	addiu	$6,$6,-1

	lw	$28,16($sp)
	.loc 1 970 0
	lw	$4,%got($LC22)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC22)

	.loc 1 993 0
	beq	$20,$0,$L143
	lw	$28,16($sp)

	move	$18,$0
$L138:
	.loc 1 975 0
	lw	$6,%got(info)($28)
	lw	$3,0($6)
	lhu	$2,4($3)
	addiu	$2,$2,-1
	.loc 1 977 0
	.loc 1 975 0
	bne	$23,$2,$L136
	addu	$5,$18,$3

	.loc 1 977 0
	lw	$2,12($3)
	lw	$3,0($3)
	lw	$4,12($5)
	addu	$2,$2,$3
	b	$L137
	subu	$17,$2,$4

$L136:
	.loc 1 981 0
	lw	$3,12($5)
	lw	$2,16($5)
	subu	$17,$2,$3
$L137:
	.loc 1 986 0
	lw	$2,0($6)
	lw	$16,%got(load_addr)($28)
	lw	$25,%call16(flash_write)($28)
	addu	$2,$18,$2
	lw	$4,0($16)
	lw	$5,12($2)
	move	$6,$17
	.loc 1 990 0
	.loc 1 986 0
	jalr	$25
	addu	$fp,$fp,$17

	lw	$28,16($sp)
	.loc 1 991 0
	lw	$2,0($16)
	.loc 1 992 0
	addiu	$23,$23,1
	.loc 1 993 0
	lw	$4,%got($LC23)($28)
	lw	$25,%call16(printf)($28)
	.loc 1 991 0
	addu	$2,$2,$17
	sw	$2,0($16)
	.loc 1 993 0
	jalr	$25
	addiu	$4,$4,%lo($LC23)

	sltu	$2,$fp,$20
	addiu	$18,$18,4
	bne	$2,$0,$L138
	lw	$28,16($sp)

$L143:
	.loc 1 995 0
	lw	$4,%got($LC24)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC24)

	.loc 1 998 0
	li	$2,2			# 0x2
	.loc 1 995 0
	.loc 1 998 0
	beq	$19,$2,$L139
	lw	$28,16($sp)

	.loc 1 1000 0
	bne	$21,$0,$L140
	lhu	$3,24($sp)

	li	$2,512			# 0x200
	.loc 1 1002 0
	.loc 1 1000 0
	bne	$3,$2,$L140
	lw	$5,%got($LC17)($28)

	.loc 1 1002 0
	lw	$4,%got(szWlan2g)($28)
	lw	$25,%call16(item_save)($28)
	addiu	$4,$4,%lo(szWlan2g)
	addiu	$5,$5,%lo($LC17)
	jalr	$25
	li	$6,512			# 0x200

	lw	$28,16($sp)
	.loc 1 1003 0
	lw	$4,%got($LC25)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC25)

	lw	$28,16($sp)
$L140:
	.loc 1 1006 0
	bne	$22,$0,$L139
	lhu	$3,26($sp)

	li	$2,512			# 0x200
	.loc 1 1008 0
	.loc 1 1006 0
	bne	$3,$2,$L139
	lw	$5,%got($LC19)($28)

	.loc 1 1008 0
	lw	$4,%got(szWlan5g)($28)
	lw	$25,%call16(item_save)($28)
	addiu	$4,$4,%lo(szWlan5g)
	addiu	$5,$5,%lo($LC19)
	jalr	$25
	li	$6,512			# 0x200

	lw	$28,16($sp)
	.loc 1 1009 0
	lw	$4,%got($LC26)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC26)

	lw	$28,16($sp)
$L139:
	.loc 1 1014 0
	lw	$4,%got($LC27)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC27)

	lw	$28,16($sp)
	.loc 1 1017 0
	move	$4,$0
	move	$5,$0
	lw	$25,%call16(do_reset)($28)
	move	$6,$0
	jalr	$25
	move	$7,$0

	lw	$28,16($sp)
	.loc 1 1019 0
	move	$2,$0
$L129:
	.loc 1 1020 0
	lw	$31,68($sp)
	lw	$fp,64($sp)
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
$LFE20:
	.end	flash_update_bin
	.section	.rodata.str1.4
	.align	2
$LC28:
	.ascii	"imgs\000"
	.align	2
$LC29:
	.ascii	"Update failure !\n"
	.ascii	"System is %s ,but you down a %s image!\n\000"
	.align	2
$LC30:
	.ascii	"Please translate a %s IMG file!\n\000"
	.align	2
$LC31:
	.ascii	"sysc\000"
	.align	2
$LC32:
	.ascii	"update failure! Because your update image is too long !\n"
	.ascii	"\000"
	.align	2
$LC33:
	.ascii	"clear\000"
	.align	2
$LC34:
	.ascii	"tbs_app_cfg\000"
	.align	2
$LC35:
	.ascii	"System update completely! Restarting system!\n\000"
	.text
	.align	2
	.globl	flash_update_img
	.ent	flash_update_img
	.type	flash_update_img, @function
flash_update_img:
$LFB21:
	.loc 1 1047 0
	.frame	$sp,64,$31		# vars= 8, regs= 8/0, args= 16, gp= 8
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-64
$LCFI72:
	sw	$31,60($sp)
$LCFI73:
	sw	$22,56($sp)
$LCFI74:
	sw	$21,52($sp)
$LCFI75:
	sw	$20,48($sp)
$LCFI76:
	sw	$19,44($sp)
$LCFI77:
	sw	$18,40($sp)
$LCFI78:
	sw	$17,36($sp)
$LCFI79:
	sw	$16,32($sp)
$LCFI80:
	.cprestore	16
	.loc 1 1063 0
	lw	$2,%got(load_addr)($28)
	.loc 1 1065 0
	lw	$25,%call16(tbs_calc_sum_addr)($28)
	.loc 1 1047 0
	move	$3,$6
	.loc 1 1063 0
	lw	$2,0($2)
	.loc 1 1047 0
	move	$19,$5
	.loc 1 1048 0
	move	$18,$4
	.loc 1 1065 0
	addiu	$5,$sp,24
	move	$4,$2
	addiu	$6,$6,-4
	.loc 1 1063 0
	addu	$2,$2,$3
	.loc 1 1047 0
	move	$22,$7
	.loc 1 1063 0
	.loc 1 1065 0
	jalr	$25
	lw	$16,-4($2)

	.loc 1 1067 0
	lw	$5,24($sp)
	.loc 1 1065 0
	.loc 1 1067 0
	beq	$5,$16,$L146
	lw	$28,16($sp)

	.loc 1 1069 0
	lw	$4,%got($LC15)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC15)

	lw	$28,16($sp)
	.loc 1 1070 0
	lw	$4,%got($LC16)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC16)

	lw	$28,16($sp)
	.loc 1 1072 0
	b	$L145
	li	$2,1			# 0x1

$L146:
	.loc 1 1092 0
	lw	$17,%got($LC28)($28)
	lw	$25,%call16(strcmp)($28)
	.loc 1 1075 0
	lw	$2,4($18)
	.loc 1 1092 0
	addiu	$16,$18,24
	move	$4,$16
	addiu	$5,$17,%lo($LC28)
	.loc 1 1075 0
	.loc 1 1092 0
	jalr	$25
	addu	$21,$18,$2

	beq	$2,$0,$L147
	lw	$28,16($sp)

	.loc 1 1094 0
	lw	$4,%got($LC29)($28)
	lw	$25,%call16(printf)($28)
	move	$6,$16
	addiu	$4,$4,%lo($LC29)
	jalr	$25
	addiu	$5,$17,%lo($LC28)

	lw	$28,16($sp)
	.loc 1 1095 0
	addiu	$5,$17,%lo($LC28)
	lw	$4,%got($LC30)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC30)

	lw	$28,16($sp)
	.loc 1 1097 0
	b	$L145
	li	$2,4			# 0x4

$L147:
	.loc 1 1103 0
	lw	$25,%call16(is_sysdata)($28)
	jalr	$25
	move	$4,$19

	bne	$2,$0,$L148
	lw	$28,16($sp)

	.loc 1 1105 0
	lw	$25,%call16(memset)($28)
	li	$6,188			# 0xbc
	move	$4,$19
	jalr	$25
	move	$5,$0

	.loc 1 1109 0
	li	$2,16842752			# 0x1010000
	ori	$2,$2,0xa8c0
	.loc 1 1105 0
	lw	$28,16($sp)
	.loc 1 1109 0
	sw	$2,24($19)
	.loc 1 1112 0
	li	$2,2
	sb	$2,45($19)
	.loc 1 1113 0
	li	$2,3
	sb	$2,46($19)
	.loc 1 1114 0
	li	$2,4
	.loc 1 1118 0
	lw	$25,%call16(strcpy)($28)
	.loc 1 1114 0
	sb	$2,47($19)
	.loc 1 1115 0
	li	$2,5
	sb	$2,48($19)
	.loc 1 1116 0
	li	$2,6
	.loc 1 1118 0
	addiu	$4,$19,68
	addiu	$5,$18,48
	.loc 1 1116 0
	sb	$2,49($19)
	.loc 1 1111 0
	.loc 1 1118 0
	jalr	$25
	sb	$0,44($19)

	lw	$28,16($sp)
	.loc 1 1119 0
	addiu	$4,$19,184
	.loc 1 1121 0
	move	$17,$0
	.loc 1 1119 0
	lw	$5,%got($LC31)($28)
	.loc 1 1123 0
	lw	$16,%got(info)($28)
	.loc 1 1119 0
	lw	$25,%call16(strcpy)($28)
	jalr	$25
	addiu	$5,$5,%lo($LC31)

	lw	$4,0($16)
	lw	$28,16($sp)
	li	$6,65535			# 0xffff
	lw	$5,12($4)
	addiu	$3,$4,12
$L151:
	addiu	$3,$3,4
	.loc 1 1123 0
	lw	$2,0($3)
	subu	$2,$2,$5
	sltu	$2,$6,$2
	beq	$2,$0,$L151
	addiu	$17,$17,1

	.loc 1 1129 0
	lw	$25,%call16(flash_erase)($28)
	move	$5,$17
	jalr	$25
	addiu	$6,$17,1

	.loc 1 1144 0
	lw	$3,0($16)
	.loc 1 1133 0
	addiu	$17,$17,2
	.loc 1 1144 0
	sll	$2,$17,2
	addu	$2,$2,$3
	lw	$2,12($2)
	lw	$3,12($3)
	.loc 1 1129 0
	lw	$28,16($sp)
	.loc 1 1144 0
	subu	$2,$2,$3
	sw	$2,4($19)
$L148:
	.loc 1 1161 0
	lw	$25,%call16(strcpy)($28)
	addiu	$4,$19,100
	jalr	$25
	addiu	$5,$18,80

	lw	$28,16($sp)
	.loc 1 1162 0
	addiu	$4,$19,52
	lw	$25,%call16(strcpy)($28)
	jalr	$25
	addiu	$5,$18,32

	lw	$28,16($sp)
	.loc 1 1252 0
	lw	$4,4($19)
	lw	$6,20($18)
	lw	$2,%got(info)($28)
	lw	$3,0($2)
	lw	$2,0($3)
	subu	$2,$2,$4
	sltu	$2,$2,$6
	.loc 1 1254 0
	.loc 1 1252 0
	beq	$2,$0,$L152
	lw	$25,%call16(printf)($28)

	.loc 1 1254 0
	lw	$4,%got($LC32)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC32)

	lw	$28,16($sp)
	.loc 1 1256 0
	b	$L145
	li	$2,2			# 0x2

$L152:
	.loc 1 1259 0
	.loc 1 1262 0
	beq	$4,$0,$L169
	move	$17,$0

	lw	$5,12($3)
	addiu	$3,$3,12
$L155:
	addiu	$3,$3,4
	lw	$2,0($3)
	subu	$2,$2,$5
	sltu	$2,$2,$4
	bne	$2,$0,$L155
	addiu	$17,$17,1

$L169:
	.loc 1 1265 0
	move	$16,$17
	.loc 1 1266 0
	move	$20,$0
	.loc 1 1275 0
	beq	$6,$0,$L157
	sll	$3,$17,2

	lw	$2,%got(info)($28)
	lw	$2,0($2)
	addu	$3,$3,$2
	lhu	$2,4($2)
	lw	$5,12($3)
	addiu	$3,$3,12
	addiu	$4,$2,-1
$L159:
	.loc 1 1270 0
	beq	$16,$4,$L157
	addiu	$3,$3,4

	.loc 1 1275 0
	lw	$2,0($3)
	subu	$2,$2,$5
	sltu	$2,$2,$6
	bne	$2,$0,$L159
	addiu	$16,$16,1

$L157:
	.loc 1 1278 0
	lw	$4,%got($LC21)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC21)

	lw	$28,16($sp)
	.loc 1 1282 0
	move	$6,$16
	move	$5,$17
	lw	$2,%got(info)($28)
	lw	$25,%call16(flash_erase)($28)
	jalr	$25
	lw	$4,0($2)

	lw	$28,16($sp)
	.loc 1 1286 0
	lw	$4,%got($LC22)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC22)

	.loc 1 1308 0
	lw	$2,20($18)
	.loc 1 1286 0
	.loc 1 1308 0
	beq	$2,$0,$L172
	lw	$28,16($sp)

	sll	$16,$17,2
$L164:
	.loc 1 1290 0
	lw	$6,%got(info)($28)
	lw	$3,0($6)
	lhu	$2,4($3)
	addiu	$2,$2,-1
	.loc 1 1292 0
	.loc 1 1290 0
	bne	$17,$2,$L162
	addu	$5,$16,$3

	.loc 1 1292 0
	lw	$2,12($3)
	lw	$3,0($3)
	lw	$4,12($5)
	addu	$2,$2,$3
	b	$L163
	subu	$3,$2,$4

$L162:
	.loc 1 1296 0
	lw	$3,12($5)
	lw	$2,16($5)
	subu	$3,$2,$3
$L163:
	.loc 1 1301 0
	lw	$2,0($6)
	lw	$25,%call16(flash_write)($28)
	move	$4,$21
	addu	$2,$16,$2
	lw	$5,12($2)
	move	$6,$3
	.loc 1 1305 0
	addu	$20,$20,$3
	.loc 1 1306 0
	.loc 1 1301 0
	jalr	$25
	addu	$21,$21,$3

	lw	$28,16($sp)
	.loc 1 1307 0
	addiu	$17,$17,1
	addiu	$16,$16,4
	.loc 1 1308 0
	lw	$4,%got($LC23)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC23)

	lw	$2,20($18)
	sltu	$2,$20,$2
	bne	$2,$0,$L164
	lw	$28,16($sp)

$L172:
	.loc 1 1310 0
	lw	$4,%got($LC24)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC24)

	.loc 1 1312 0
	lw	$4,8($18)
	lw	$2,4($19)
	lw	$3,4($18)
	.loc 1 1310 0
	lw	$28,16($sp)
	.loc 1 1312 0
	addu	$2,$2,$4
	subu	$2,$2,$3
	sw	$2,8($19)
	.loc 1 1313 0
	lw	$2,0($18)
	sw	$2,32($19)
	.loc 1 1314 0
	lw	$2,20($18)
	.loc 1 1318 0
	beq	$22,$0,$L165
	sw	$2,28($19)

	.loc 1 1320 0
	lw	$4,%got($LC33)($28)
	lw	$5,%got($LC34)($28)
	lw	$25,%call16(item_save)($28)
	addiu	$4,$4,%lo($LC33)
	addiu	$5,$5,%lo($LC34)
	jalr	$25
	li	$6,5			# 0x5

	lw	$28,16($sp)
$L165:
	.loc 1 1323 0
	lw	$25,%call16(sysdata_save)($28)
	jalr	$25
	move	$4,$19

	lw	$28,16($sp)
	.loc 1 1324 0
	lw	$4,%got($LC35)($28)
	lw	$25,%call16(printf)($28)
	jalr	$25
	addiu	$4,$4,%lo($LC35)

	lw	$28,16($sp)
	.loc 1 1327 0
	move	$4,$0
	move	$5,$0
	lw	$25,%call16(do_reset)($28)
	move	$6,$0
	jalr	$25
	move	$7,$0

	lw	$28,16($sp)
	.loc 1 1329 0
	move	$2,$0
$L145:
	.loc 1 1330 0
	lw	$31,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
$LFE21:
	.end	flash_update_img
	.local	szWlan2g
	.comm	szWlan2g,512,4
	.local	szWlan5g
	.comm	szWlan5g,512,4
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
	.4byte	$LFB14
	.4byte	$LFE14-$LFB14
	.byte	0x4
	.4byte	$LCFI0-$LFB14
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	$LCFI7-$LCFI0
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
$LEFDE0:
$LSFDE2:
	.4byte	$LEFDE2-$LASFDE2
$LASFDE2:
	.4byte	$Lframe0
	.4byte	$LFB15
	.4byte	$LFE15-$LFB15
	.byte	0x4
	.4byte	$LCFI8-$LFB15
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	$LCFI15-$LCFI8
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
$LEFDE2:
$LSFDE4:
	.4byte	$LEFDE4-$LASFDE4
$LASFDE4:
	.4byte	$Lframe0
	.4byte	$LFB16
	.4byte	$LFE16-$LFB16
	.byte	0x4
	.4byte	$LCFI16-$LFB16
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	$LCFI24-$LCFI16
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
	.uleb128 0x16
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
	.4byte	$LFB17
	.4byte	$LFE17-$LFB17
	.byte	0x4
	.4byte	$LCFI25-$LFB17
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	$LCFI33-$LCFI25
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
	.uleb128 0x16
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
	.4byte	$LFB12
	.4byte	$LFE12-$LFB12
	.byte	0x4
	.4byte	$LCFI34-$LFB12
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.4byte	$LCFI36-$LCFI34
	.byte	0x11
	.uleb128 0x10
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE8:
$LSFDE10:
	.4byte	$LEFDE10-$LASFDE10
$LASFDE10:
	.4byte	$Lframe0
	.4byte	$LFB19
	.4byte	$LFE19-$LFB19
	.byte	0x4
	.4byte	$LCFI37-$LFB19
	.byte	0xe
	.uleb128 0x48
	.byte	0x4
	.4byte	$LCFI47-$LCFI37
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
	.uleb128 0x1e
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE10:
$LSFDE12:
	.4byte	$LEFDE12-$LASFDE12
$LASFDE12:
	.4byte	$Lframe0
	.4byte	$LFB18
	.4byte	$LFE18-$LFB18
	.byte	0x4
	.4byte	$LCFI48-$LFB18
	.byte	0xe
	.uleb128 0x58
	.byte	0x4
	.4byte	$LCFI58-$LCFI48
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
	.uleb128 0x1e
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE12:
$LSFDE14:
	.4byte	$LEFDE14-$LASFDE14
$LASFDE14:
	.4byte	$Lframe0
	.4byte	$LFB13
	.4byte	$LFE13-$LFB13
	.byte	0x4
	.4byte	$LCFI59-$LFB13
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI60-$LCFI59
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -2
	.align	2
$LEFDE14:
$LSFDE16:
	.4byte	$LEFDE16-$LASFDE16
$LASFDE16:
	.4byte	$Lframe0
	.4byte	$LFB20
	.4byte	$LFE20-$LFB20
	.byte	0x4
	.4byte	$LCFI61-$LFB20
	.byte	0xe
	.uleb128 0x48
	.byte	0x4
	.4byte	$LCFI71-$LCFI61
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
	.uleb128 0x1e
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE16:
$LSFDE18:
	.4byte	$LEFDE18-$LASFDE18
$LASFDE18:
	.4byte	$Lframe0
	.4byte	$LFB21
	.4byte	$LFE21-$LFB21
	.byte	0x4
	.4byte	$LCFI72-$LFB21
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	$LCFI80-$LCFI72
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
	.uleb128 0x16
	.sleb128 -2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 -1
	.align	2
$LEFDE18:
	.align	0
	.file 2 "/home/zhangtianchuan/Gpl819/DIR819/build/include/flash_layout.h"
	.file 3 "/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tbsboot/include/common.h"
	.file 4 "/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tbsboot/include/types.h"
	.file 5 "/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tbsboot/include/flash.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x9dc
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF88
	.byte	0x1
	.4byte	$LASF89
	.4byte	$LASF90
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
	.byte	0x4
	.byte	0x14
	.4byte	0x3e
	.uleb128 0x2
	.4byte	$LASF10
	.byte	0x4
	.byte	0x16
	.4byte	0x37
	.uleb128 0x3
	.4byte	$LASF5
	.byte	0x4
	.byte	0x7
	.uleb128 0x5
	.4byte	0xdd
	.2byte	0x530
	.byte	0x5
	.byte	0x32
	.uleb128 0x6
	.4byte	$LASF11
	.byte	0x5
	.byte	0x21
	.4byte	0x7a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x6
	.4byte	$LASF12
	.byte	0x5
	.byte	0x22
	.4byte	0x6f
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x6
	.4byte	$LASF13
	.byte	0x5
	.byte	0x23
	.4byte	0x7a
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x6
	.4byte	$LASF14
	.byte	0x5
	.byte	0x24
	.4byte	0xdd
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x6
	.4byte	$LASF15
	.byte	0x5
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
	.byte	0x5
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
	.byte	0x2
	.byte	0x85
	.uleb128 0x6
	.4byte	$LASF18
	.byte	0x2
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
	.byte	0x2
	.byte	0x85
	.4byte	0x171
	.uleb128 0xa
	.4byte	0x29d
	.byte	0xbc
	.byte	0x2
	.byte	0xa1
	.uleb128 0x6
	.4byte	$LASF20
	.byte	0x2
	.byte	0x89
	.4byte	0x198
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.ascii	"ip\000"
	.byte	0x2
	.byte	0x8a
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0x6
	.4byte	$LASF21
	.byte	0x2
	.byte	0x8b
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.uleb128 0x6
	.4byte	$LASF22
	.byte	0x2
	.byte	0x8c
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0x6
	.4byte	$LASF23
	.byte	0x2
	.byte	0x8d
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0x6
	.4byte	$LASF24
	.byte	0x2
	.byte	0x8e
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.uleb128 0xb
	.ascii	"mac\000"
	.byte	0x2
	.byte	0x8f
	.4byte	0x11a
	.byte	0x2
	.byte	0x10
	.uleb128 0x2c
	.uleb128 0x6
	.4byte	$LASF25
	.byte	0x2
	.byte	0x90
	.4byte	0x30
	.byte	0x2
	.byte	0x10
	.uleb128 0x32
	.uleb128 0x6
	.4byte	$LASF26
	.byte	0x2
	.byte	0x91
	.4byte	0x30
	.byte	0x2
	.byte	0x10
	.uleb128 0x33
	.uleb128 0x6
	.4byte	$LASF27
	.byte	0x2
	.byte	0x92
	.4byte	0x12a
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.uleb128 0x6
	.4byte	$LASF28
	.byte	0x2
	.byte	0x93
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x44
	.uleb128 0x6
	.4byte	$LASF29
	.byte	0x2
	.byte	0x94
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x64
	.uleb128 0x6
	.4byte	$LASF30
	.byte	0x2
	.byte	0x97
	.4byte	0x12a
	.byte	0x3
	.byte	0x10
	.uleb128 0x84
	.uleb128 0x6
	.4byte	$LASF31
	.byte	0x2
	.byte	0x98
	.4byte	0x14a
	.byte	0x3
	.byte	0x10
	.uleb128 0x94
	.uleb128 0x6
	.4byte	$LASF32
	.byte	0x2
	.byte	0x9a
	.4byte	0x10a
	.byte	0x3
	.byte	0x10
	.uleb128 0x98
	.uleb128 0xb
	.ascii	"sn\000"
	.byte	0x2
	.byte	0x9b
	.4byte	0x15a
	.byte	0x3
	.byte	0x10
	.uleb128 0xa4
	.uleb128 0xb
	.ascii	"tag\000"
	.byte	0x2
	.byte	0xa0
	.4byte	0x14a
	.byte	0x3
	.byte	0x10
	.uleb128 0xb8
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF33
	.byte	0x2
	.byte	0xa1
	.4byte	0x1a3
	.uleb128 0xa
	.4byte	0x369
	.byte	0x90
	.byte	0x2
	.byte	0xb9
	.uleb128 0x6
	.4byte	$LASF34
	.byte	0x2
	.byte	0xab
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x6
	.4byte	$LASF35
	.byte	0x2
	.byte	0xac
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x6
	.4byte	$LASF36
	.byte	0x2
	.byte	0xad
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x6
	.4byte	$LASF37
	.byte	0x2
	.byte	0xae
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x6
	.4byte	$LASF38
	.byte	0x2
	.byte	0xaf
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x6
	.4byte	$LASF39
	.byte	0x2
	.byte	0xb0
	.4byte	0x5a
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0x6
	.4byte	$LASF40
	.byte	0x2
	.byte	0xb1
	.4byte	0x369
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0x6
	.4byte	$LASF27
	.byte	0x2
	.byte	0xb2
	.4byte	0x12a
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0x6
	.4byte	$LASF28
	.byte	0x2
	.byte	0xb3
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x30
	.uleb128 0x6
	.4byte	$LASF29
	.byte	0x2
	.byte	0xb4
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x50
	.uleb128 0x6
	.4byte	$LASF30
	.byte	0x2
	.byte	0xb6
	.4byte	0x12a
	.byte	0x2
	.byte	0x10
	.uleb128 0x70
	.uleb128 0x6
	.4byte	$LASF31
	.byte	0x2
	.byte	0xb7
	.4byte	0x14a
	.byte	0x3
	.byte	0x10
	.uleb128 0x80
	.uleb128 0x6
	.4byte	$LASF32
	.byte	0x2
	.byte	0xb8
	.4byte	0x10a
	.byte	0x3
	.byte	0x10
	.uleb128 0x84
	.byte	0x0
	.uleb128 0x7
	.4byte	0x379
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x85
	.byte	0x7
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF41
	.byte	0x2
	.byte	0xb9
	.4byte	0x2a8
	.uleb128 0xc
	.4byte	0x3ad
	.4byte	$LASF44
	.byte	0x24
	.byte	0x2
	.byte	0xce
	.uleb128 0x6
	.4byte	$LASF28
	.byte	0x2
	.byte	0xcf
	.4byte	0x13a
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x6
	.4byte	$LASF42
	.byte	0x2
	.byte	0xd0
	.4byte	0x14a
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.byte	0x0
	.uleb128 0x2
	.4byte	$LASF43
	.byte	0x2
	.byte	0xd2
	.4byte	0x384
	.uleb128 0xd
	.4byte	0x3f3
	.4byte	$LASF45
	.byte	0x5
	.byte	0x2
	.2byte	0x11a
	.uleb128 0xe
	.ascii	"crc\000"
	.byte	0x2
	.2byte	0x11b
	.4byte	0x3e
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xe
	.ascii	"len\000"
	.byte	0x2
	.2byte	0x11c
	.4byte	0x3e
	.byte	0x2
	.byte	0x10
	.uleb128 0x2
	.uleb128 0xf
	.4byte	$LASF46
	.byte	0x2
	.2byte	0x11d
	.4byte	0x30
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.byte	0x0
	.uleb128 0xd
	.4byte	0x42e
	.4byte	$LASF47
	.byte	0x5
	.byte	0x2
	.2byte	0x121
	.uleb128 0xe
	.ascii	"hdr\000"
	.byte	0x2
	.2byte	0x122
	.4byte	0x3b8
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xf
	.4byte	$LASF48
	.byte	0x2
	.2byte	0x123
	.4byte	0x42e
	.byte	0x2
	.byte	0x10
	.uleb128 0x5
	.uleb128 0xf
	.4byte	$LASF49
	.byte	0x2
	.2byte	0x124
	.4byte	0x43d
	.byte	0x2
	.byte	0x10
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x7
	.4byte	0x43d
	.4byte	0x30
	.uleb128 0x10
	.4byte	0x85
	.byte	0x0
	.uleb128 0x7
	.4byte	0x44c
	.4byte	0x30
	.uleb128 0x10
	.4byte	0x85
	.byte	0x0
	.uleb128 0x11
	.4byte	$LASF50
	.byte	0x2
	.2byte	0x126
	.4byte	0x3f3
	.uleb128 0x12
	.byte	0x4
	.4byte	0x30
	.uleb128 0x13
	.byte	0x4
	.uleb128 0x12
	.byte	0x4
	.4byte	0x16a
	.uleb128 0x3
	.4byte	$LASF51
	.byte	0x8
	.byte	0x4
	.uleb128 0x14
	.4byte	0x4a6
	.byte	0x1
	.4byte	$LASF53
	.byte	0x1
	.byte	0xac
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB14
	.4byte	$LFE14
	.4byte	$LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0x15
	.ascii	"i\000"
	.byte	0x1
	.byte	0xae
	.4byte	0x5a
	.byte	0x1
	.byte	0x60
	.uleb128 0x16
	.4byte	$LASF52
	.byte	0x1
	.byte	0xaf
	.4byte	0x458
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.byte	0x0
	.uleb128 0x14
	.4byte	0x522
	.byte	0x1
	.4byte	$LASF54
	.byte	0x1
	.byte	0xe6
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB15
	.4byte	$LFE15
	.4byte	$LSFDE2
	.byte	0x1
	.byte	0x6d
	.uleb128 0x16
	.4byte	$LASF47
	.byte	0x1
	.byte	0xe7
	.4byte	0x522
	.byte	0x1
	.byte	0x60
	.uleb128 0x16
	.4byte	$LASF55
	.byte	0x1
	.byte	0xe8
	.4byte	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x15
	.ascii	"i\000"
	.byte	0x1
	.byte	0xe9
	.4byte	0x5a
	.byte	0x1
	.byte	0x63
	.uleb128 0x15
	.ascii	"sum\000"
	.byte	0x1
	.byte	0xea
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x16
	.4byte	$LASF52
	.byte	0x1
	.byte	0xeb
	.4byte	0x458
	.byte	0x2
	.byte	0x91
	.sleb128 28
	.uleb128 0x17
	.4byte	$LASF46
	.byte	0x1
	.byte	0xec
	.4byte	0x16a
	.uleb128 0x18
	.4byte	$LASF56
	.4byte	0x53d
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__FUNCTION__.0
	.byte	0x0
	.uleb128 0x12
	.byte	0x4
	.4byte	0x44c
	.uleb128 0x7
	.4byte	0x538
	.4byte	0x538
	.uleb128 0x9
	.4byte	0x85
	.byte	0xa
	.byte	0x0
	.uleb128 0x19
	.4byte	0x16a
	.uleb128 0x19
	.4byte	0x528
	.uleb128 0x1a
	.4byte	0x5b4
	.byte	0x1
	.4byte	$LASF57
	.byte	0x1
	.2byte	0x177
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB16
	.4byte	$LFE16
	.4byte	$LSFDE4
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1b
	.4byte	$LASF47
	.byte	0x1
	.2byte	0x178
	.4byte	0x522
	.byte	0x1
	.byte	0x60
	.uleb128 0x1c
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x179
	.4byte	0x5a
	.byte	0x1
	.byte	0x64
	.uleb128 0x1c
	.ascii	"sum\000"
	.byte	0x1
	.2byte	0x17a
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x1d
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x17b
	.4byte	0x5a
	.uleb128 0x1b
	.4byte	$LASF52
	.byte	0x1
	.2byte	0x17c
	.4byte	0x458
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x1b
	.4byte	$LASF58
	.byte	0x1
	.2byte	0x17d
	.4byte	0x5a
	.byte	0x1
	.byte	0x62
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x636
	.byte	0x1
	.4byte	$LASF59
	.byte	0x1
	.2byte	0x1e1
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB17
	.4byte	$LFE17
	.4byte	$LSFDE6
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1e
	.4byte	$LASF49
	.byte	0x1
	.2byte	0x1e0
	.4byte	0x45e
	.byte	0x1
	.byte	0x65
	.uleb128 0x1e
	.4byte	$LASF60
	.byte	0x1
	.2byte	0x1e0
	.4byte	0x460
	.byte	0x1
	.byte	0x63
	.uleb128 0x1f
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x1e0
	.4byte	0x636
	.byte	0x1
	.byte	0x66
	.uleb128 0x1b
	.4byte	$LASF47
	.byte	0x1
	.2byte	0x1e2
	.4byte	0x522
	.byte	0x1
	.byte	0x62
	.uleb128 0x1c
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x1e3
	.4byte	0x5a
	.byte	0x1
	.byte	0x56
	.uleb128 0x1c
	.ascii	"sum\000"
	.byte	0x1
	.2byte	0x1e4
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x1b
	.4byte	$LASF52
	.byte	0x1
	.2byte	0x1e5
	.4byte	0x458
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.byte	0x0
	.uleb128 0x12
	.byte	0x4
	.4byte	0x3e
	.uleb128 0x14
	.4byte	0x677
	.byte	0x1
	.4byte	$LASF61
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB12
	.4byte	$LFE12
	.4byte	$LSFDE8
	.byte	0x1
	.byte	0x6d
	.uleb128 0x20
	.4byte	$LASF62
	.byte	0x1
	.byte	0x57
	.4byte	0x677
	.byte	0x1
	.byte	0x60
	.uleb128 0x16
	.4byte	$LASF63
	.byte	0x1
	.byte	0x5c
	.4byte	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.byte	0x0
	.uleb128 0x12
	.byte	0x4
	.4byte	0x29d
	.uleb128 0x1a
	.4byte	0x6f1
	.byte	0x1
	.4byte	$LASF64
	.byte	0x1
	.2byte	0x2ed
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB19
	.4byte	$LFE19
	.4byte	$LSFDE10
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1b
	.4byte	$LASF47
	.byte	0x1
	.2byte	0x2ee
	.4byte	0x522
	.byte	0x1
	.byte	0x60
	.uleb128 0x1c
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x2ef
	.4byte	0x5a
	.byte	0x1
	.byte	0x62
	.uleb128 0x1c
	.ascii	"sum\000"
	.byte	0x1
	.2byte	0x2f0
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x1c
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x2f1
	.4byte	0x5a
	.byte	0x1
	.byte	0x67
	.uleb128 0x1b
	.4byte	$LASF52
	.byte	0x1
	.2byte	0x2f2
	.4byte	0x458
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x1b
	.4byte	$LASF58
	.byte	0x1
	.2byte	0x2f3
	.4byte	0x5a
	.byte	0x1
	.byte	0x63
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x7bd
	.byte	0x1
	.4byte	$LASF65
	.byte	0x1
	.2byte	0x23a
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB18
	.4byte	$LFE18
	.4byte	$LSFDE12
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1e
	.4byte	$LASF49
	.byte	0x1
	.2byte	0x239
	.4byte	0x45e
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.uleb128 0x1e
	.4byte	$LASF60
	.byte	0x1
	.2byte	0x239
	.4byte	0x460
	.byte	0x1
	.byte	0x6e
	.uleb128 0x1f
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x239
	.4byte	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 44
	.uleb128 0x1b
	.4byte	$LASF47
	.byte	0x1
	.2byte	0x23b
	.4byte	0x522
	.byte	0x1
	.byte	0x62
	.uleb128 0x1b
	.4byte	$LASF66
	.byte	0x1
	.2byte	0x23c
	.4byte	0x522
	.byte	0x1
	.byte	0x63
	.uleb128 0x1c
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x23d
	.4byte	0x5a
	.byte	0x1
	.byte	0x65
	.uleb128 0x1c
	.ascii	"j\000"
	.byte	0x1
	.2byte	0x23e
	.4byte	0x5a
	.byte	0x1
	.byte	0x66
	.uleb128 0x1c
	.ascii	"sum\000"
	.byte	0x1
	.2byte	0x23f
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x1b
	.4byte	$LASF55
	.byte	0x1
	.2byte	0x240
	.4byte	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x1b
	.4byte	$LASF46
	.byte	0x1
	.2byte	0x241
	.4byte	0x16a
	.byte	0x2
	.byte	0x91
	.sleb128 26
	.uleb128 0x1b
	.4byte	$LASF52
	.byte	0x1
	.2byte	0x242
	.4byte	0x458
	.byte	0x2
	.byte	0x91
	.sleb128 40
	.uleb128 0x1b
	.4byte	$LASF67
	.byte	0x1
	.2byte	0x243
	.4byte	0x7bd
	.byte	0x2
	.byte	0x91
	.sleb128 32
	.byte	0x0
	.uleb128 0x7
	.4byte	0x7cd
	.4byte	0x5a
	.uleb128 0x9
	.4byte	0x85
	.byte	0x1
	.byte	0x0
	.uleb128 0x14
	.4byte	0x7fa
	.byte	0x1
	.4byte	$LASF68
	.byte	0x1
	.byte	0x95
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB13
	.4byte	$LFE13
	.4byte	$LSFDE14
	.byte	0x1
	.byte	0x6d
	.uleb128 0x20
	.4byte	$LASF62
	.byte	0x1
	.byte	0x94
	.4byte	0x677
	.byte	0x1
	.byte	0x54
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x8c4
	.byte	0x1
	.4byte	$LASF69
	.byte	0x1
	.2byte	0x381
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB20
	.4byte	$LFE20
	.4byte	$LSFDE16
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1e
	.4byte	$LASF70
	.byte	0x1
	.2byte	0x380
	.4byte	0x5a
	.byte	0x1
	.byte	0x64
	.uleb128 0x1e
	.4byte	$LASF71
	.byte	0x1
	.2byte	0x380
	.4byte	0x16a
	.byte	0x1
	.byte	0x63
	.uleb128 0x1b
	.4byte	$LASF72
	.byte	0x1
	.2byte	0x382
	.4byte	0x53
	.byte	0x1
	.byte	0x61
	.uleb128 0x1c
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x383
	.4byte	0x53
	.byte	0x1
	.byte	0x6e
	.uleb128 0x1c
	.ascii	"end\000"
	.byte	0x1
	.2byte	0x384
	.4byte	0x53
	.byte	0x1
	.byte	0x67
	.uleb128 0x21
	.4byte	$LASF73
	.byte	0x1
	.2byte	0x385
	.4byte	0x8c4
	.uleb128 0x1b
	.4byte	$LASF55
	.byte	0x1
	.2byte	0x386
	.4byte	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 28
	.uleb128 0x1b
	.4byte	$LASF74
	.byte	0x1
	.2byte	0x387
	.4byte	0x5a
	.byte	0x1
	.byte	0x60
	.uleb128 0x1b
	.4byte	$LASF75
	.byte	0x1
	.2byte	0x38a
	.4byte	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x1b
	.4byte	$LASF76
	.byte	0x1
	.2byte	0x38a
	.4byte	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 26
	.uleb128 0x1b
	.4byte	$LASF77
	.byte	0x1
	.2byte	0x38b
	.4byte	0x53
	.byte	0x1
	.byte	0x65
	.uleb128 0x1b
	.4byte	$LASF78
	.byte	0x1
	.2byte	0x38b
	.4byte	0x53
	.byte	0x1
	.byte	0x66
	.byte	0x0
	.uleb128 0x12
	.byte	0x4
	.4byte	0x3ad
	.uleb128 0x1a
	.4byte	0x986
	.byte	0x1
	.4byte	$LASF79
	.byte	0x1
	.2byte	0x417
	.byte	0x1
	.4byte	0x53
	.4byte	$LFB21
	.4byte	$LFE21
	.4byte	$LSFDE18
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1e
	.4byte	$LASF49
	.byte	0x1
	.2byte	0x416
	.4byte	0x458
	.byte	0x1
	.byte	0x65
	.uleb128 0x1e
	.4byte	$LASF80
	.byte	0x1
	.2byte	0x416
	.4byte	0x677
	.byte	0x1
	.byte	0x63
	.uleb128 0x1e
	.4byte	$LASF70
	.byte	0x1
	.2byte	0x416
	.4byte	0x5a
	.byte	0x1
	.byte	0x53
	.uleb128 0x1e
	.4byte	$LASF81
	.byte	0x1
	.2byte	0x416
	.4byte	0x53
	.byte	0x1
	.byte	0x66
	.uleb128 0x1b
	.4byte	$LASF82
	.byte	0x1
	.2byte	0x418
	.4byte	0x986
	.byte	0x1
	.byte	0x62
	.uleb128 0x1b
	.4byte	$LASF14
	.byte	0x1
	.2byte	0x41a
	.4byte	0x5a
	.byte	0x1
	.byte	0x61
	.uleb128 0x1c
	.ascii	"end\000"
	.byte	0x1
	.2byte	0x41b
	.4byte	0x5a
	.byte	0x1
	.byte	0x60
	.uleb128 0x1c
	.ascii	"len\000"
	.byte	0x1
	.2byte	0x41c
	.4byte	0x53
	.byte	0x1
	.byte	0x64
	.uleb128 0x1b
	.4byte	$LASF72
	.byte	0x1
	.2byte	0x41d
	.4byte	0x53
	.byte	0x1
	.byte	0x53
	.uleb128 0x1b
	.4byte	$LASF55
	.byte	0x1
	.2byte	0x41e
	.4byte	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x1b
	.4byte	$LASF83
	.byte	0x1
	.2byte	0x41f
	.4byte	0x5a
	.byte	0x1
	.byte	0x60
	.byte	0x0
	.uleb128 0x12
	.byte	0x4
	.4byte	0x379
	.uleb128 0x22
	.4byte	$LASF84
	.byte	0x3
	.byte	0x84
	.4byte	0x7a
	.byte	0x1
	.byte	0x1
	.uleb128 0x22
	.4byte	$LASF85
	.byte	0x3
	.byte	0xe0
	.4byte	0x9a6
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.byte	0x4
	.4byte	0xff
	.uleb128 0x7
	.4byte	0x9bd
	.4byte	0x30
	.uleb128 0x8
	.4byte	0x85
	.2byte	0x1ff
	.byte	0x0
	.uleb128 0x16
	.4byte	$LASF86
	.byte	0x1
	.byte	0x3f
	.4byte	0x9ac
	.byte	0x5
	.byte	0x3
	.4byte	szWlan2g
	.uleb128 0x16
	.4byte	$LASF87
	.byte	0x1
	.byte	0x40
	.4byte	0x9ac
	.byte	0x5
	.byte	0x3
	.4byte	szWlan5g
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
	.uleb128 0x5
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x16
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
	.uleb128 0x12
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.4byte	0xb9
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x9e0
	.4byte	0x46d
	.ascii	"item_repeat2\000"
	.4byte	0x4a6
	.ascii	"item_check\000"
	.4byte	0x542
	.ascii	"config_synTo_bak\000"
	.4byte	0x5b4
	.ascii	"item_get\000"
	.4byte	0x63c
	.ascii	"sysdata_get\000"
	.4byte	0x67d
	.ascii	"item_repeat\000"
	.4byte	0x6f1
	.ascii	"item_save\000"
	.4byte	0x7cd
	.ascii	"sysdata_save\000"
	.4byte	0x7fa
	.ascii	"flash_update_bin\000"
	.4byte	0x8ca
	.ascii	"flash_update_img\000"
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
$LASF35:
	.ascii	"kernel_offset\000"
$LASF13:
	.ascii	"flash_id\000"
$LASF24:
	.ascii	"second_image_checksum\000"
$LASF30:
	.ascii	"model_name\000"
$LASF79:
	.ascii	"flash_update_img\000"
$LASF26:
	.ascii	"image_mark\000"
$LASF80:
	.ascii	"sys_data\000"
$LASF56:
	.ascii	"__FUNCTION__\000"
$LASF29:
	.ascii	"version\000"
$LASF25:
	.ascii	"endian\000"
$LASF18:
	.ascii	"zone_offset\000"
$LASF67:
	.ascii	"item_repeat_addr\000"
$LASF66:
	.ascii	"item_data\000"
$LASF65:
	.ascii	"item_save\000"
$LASF77:
	.ascii	"iRet2g\000"
$LASF45:
	.ascii	"item_hdr\000"
$LASF50:
	.ascii	"item_t\000"
$LASF84:
	.ascii	"load_addr\000"
$LASF31:
	.ascii	"region\000"
$LASF55:
	.ascii	"checksum\000"
$LASF27:
	.ascii	"board_id\000"
$LASF7:
	.ascii	"long long unsigned int\000"
$LASF86:
	.ascii	"szWlan2g\000"
$LASF43:
	.ascii	"image_bin_tail_t\000"
$LASF68:
	.ascii	"sysdata_save\000"
$LASF69:
	.ascii	"flash_update_bin\000"
$LASF88:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF78:
	.ascii	"iRet5g\000"
$LASF39:
	.ascii	"image_len\000"
$LASF89:
	.ascii	"flash_layout.c\000"
$LASF62:
	.ascii	"syscfg\000"
$LASF38:
	.ascii	"rootfs_size\000"
$LASF41:
	.ascii	"update_hdr_t\000"
$LASF17:
	.ascii	"char\000"
$LASF12:
	.ascii	"sector_count\000"
$LASF16:
	.ascii	"flash_info_t\000"
$LASF34:
	.ascii	"image_checksum\000"
$LASF76:
	.ascii	"eprom5gLen\000"
$LASF42:
	.ascii	"bin_type\000"
$LASF6:
	.ascii	"long long int\000"
$LASF44:
	.ascii	"bin_tail\000"
$LASF11:
	.ascii	"size\000"
$LASF21:
	.ascii	"first_image_len\000"
$LASF37:
	.ascii	"kernel_size\000"
$LASF19:
	.ascii	"flash_layout_t\000"
$LASF8:
	.ascii	"uchar\000"
$LASF57:
	.ascii	"config_synTo_bak\000"
$LASF49:
	.ascii	"data\000"
$LASF60:
	.ascii	"item_name\000"
$LASF87:
	.ascii	"szWlan5g\000"
$LASF4:
	.ascii	"short int\000"
$LASF75:
	.ascii	"epromLen\000"
$LASF52:
	.ascii	"item_sdram\000"
$LASF64:
	.ascii	"item_repeat\000"
$LASF20:
	.ascii	"layout\000"
$LASF46:
	.ascii	"avail\000"
$LASF33:
	.ascii	"sys_config_t\000"
$LASF36:
	.ascii	"rootfs_offset\000"
$LASF73:
	.ascii	"image_bin_tail\000"
$LASF10:
	.ascii	"ulong\000"
$LASF23:
	.ascii	"second_image_len\000"
$LASF83:
	.ascii	"img_file_checksum\000"
$LASF72:
	.ascii	"block\000"
$LASF53:
	.ascii	"item_repeat2\000"
$LASF48:
	.ascii	"name\000"
$LASF14:
	.ascii	"start\000"
$LASF5:
	.ascii	"unsigned int\000"
$LASF90:
	.ascii	"/home/zhangtianchuan/Gpl819/DIR819/build.DIR-819/boot/tb"
	.ascii	"sboot/common\000"
$LASF81:
	.ascii	"clearcfg\000"
$LASF59:
	.ascii	"item_get\000"
$LASF61:
	.ascii	"sysdata_get\000"
$LASF1:
	.ascii	"long unsigned int\000"
$LASF63:
	.ascii	"item_len\000"
$LASF32:
	.ascii	"swversion\000"
$LASF85:
	.ascii	"info\000"
$LASF15:
	.ascii	"protect\000"
$LASF70:
	.ascii	"file_size\000"
$LASF0:
	.ascii	"unsigned char\000"
$LASF9:
	.ascii	"ushort\000"
$LASF71:
	.ascii	"force_mark\000"
$LASF58:
	.ascii	"addr\000"
$LASF22:
	.ascii	"first_image_checksum\000"
$LASF47:
	.ascii	"item\000"
$LASF54:
	.ascii	"item_check\000"
$LASF74:
	.ascii	"bin_file_checksum\000"
$LASF3:
	.ascii	"signed char\000"
$LASF2:
	.ascii	"short unsigned int\000"
$LASF51:
	.ascii	"double\000"
$LASF28:
	.ascii	"product\000"
$LASF82:
	.ascii	"update_hdr\000"
$LASF40:
	.ascii	"img_type\000"
	.ident	"GCC: (GNU) 3.4.2"
