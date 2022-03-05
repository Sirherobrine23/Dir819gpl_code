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
	.subsection	-1
	.align	2
$LC0:
	.ascii	"\000"
	.globl	mt7620a_btns
	.section	.data.rel.local,"aw",@progbits
	.align	2
	.type	mt7620a_btns, @object
	.size	mt7620a_btns, 96
mt7620a_btns:
	.word	0
	.word	12
	.word	0
	.word	$LC0
	.space	16
	.word	1
	.word	2
	.word	0
	.word	$LC0
	.space	16
	.word	5
	.space	28
	.globl	mt7620a_leds
	.data
	.align	2
	.type	mt7620a_leds, @object
	.size	mt7620a_leds, 112
mt7620a_leds:
	.word	7
	.word	72
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	8
	.word	39
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	3
	.word	40
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	23
	.word	161
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.globl	mt7620a_gpios
	.align	2
	.type	mt7620a_gpios, @object
	.size	mt7620a_gpios, 120
mt7620a_gpios:
	.word	0
	.word	-1342175704
	.word	-1342175708
	.word	-1342175712
	.word	-1342175732
	.word	-1342175744
	.word	1
	.word	-1342175664
	.word	-1342175668
	.word	-1342175672
	.word	-1342175676
	.word	-1342175688
	.word	2
	.word	-1342175624
	.word	-1342175628
	.word	-1342175632
	.word	-1342175636
	.word	-1342175648
	.word	3
	.word	-1342175584
	.word	-1342175588
	.word	-1342175592
	.word	-1342175596
	.word	-1342175608
	.word	4
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.file 1 "product.c"
	.file 2 "/home/guohongliang/work/819/DIR819/build/include/gpio.h"
	.file 3 "/home/guohongliang/work/819/DIR819/build/include/led.h"
	.file 4 "/home/guohongliang/work/819/DIR819/build/include/btn.h"
	.text
$Letext0:
	.section	.debug_info
	.4byte	0x46c
	.2byte	0x2
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$Ldebug_line0
	.4byte	$Letext0
	.4byte	$Ltext0
	.4byte	$LASF96
	.byte	0x1
	.4byte	$LASF97
	.4byte	$LASF98
	.uleb128 0x2
	.4byte	0x64
	.byte	0x4
	.byte	0x2
	.byte	0x3e
	.uleb128 0x3
	.4byte	$LASF0
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF1
	.sleb128 1
	.uleb128 0x3
	.4byte	$LASF2
	.sleb128 2
	.uleb128 0x3
	.4byte	$LASF3
	.sleb128 3
	.uleb128 0x3
	.4byte	$LASF4
	.sleb128 4
	.uleb128 0x3
	.4byte	$LASF5
	.sleb128 5
	.uleb128 0x3
	.4byte	$LASF6
	.sleb128 6
	.uleb128 0x3
	.4byte	$LASF7
	.sleb128 7
	.uleb128 0x3
	.4byte	$LASF8
	.sleb128 8
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF41
	.byte	0x2
	.byte	0x48
	.4byte	0x25
	.uleb128 0x5
	.4byte	$LASF9
	.byte	0x4
	.byte	0x7
	.uleb128 0x5
	.4byte	$LASF10
	.byte	0x1
	.byte	0x6
	.uleb128 0x6
	.ascii	"int\000"
	.byte	0x4
	.byte	0x5
	.uleb128 0x7
	.4byte	0xe5
	.4byte	$LASF61
	.byte	0x18
	.byte	0x2
	.byte	0x52
	.uleb128 0x8
	.4byte	$LASF11
	.byte	0x2
	.byte	0x53
	.4byte	0x64
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF12
	.byte	0x2
	.byte	0x54
	.4byte	0xe5
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF13
	.byte	0x2
	.byte	0x55
	.4byte	0xe5
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x8
	.4byte	$LASF14
	.byte	0x2
	.byte	0x56
	.4byte	0xe5
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x8
	.4byte	$LASF15
	.byte	0x2
	.byte	0x57
	.4byte	0xe5
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x8
	.4byte	$LASF16
	.byte	0x2
	.byte	0x58
	.4byte	0xe5
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.byte	0x0
	.uleb128 0x5
	.4byte	$LASF9
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.4byte	0x185
	.byte	0x4
	.byte	0x3
	.byte	0x22
	.uleb128 0x3
	.4byte	$LASF17
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF18
	.sleb128 1
	.uleb128 0x3
	.4byte	$LASF19
	.sleb128 2
	.uleb128 0x3
	.4byte	$LASF20
	.sleb128 3
	.uleb128 0x3
	.4byte	$LASF21
	.sleb128 4
	.uleb128 0x3
	.4byte	$LASF22
	.sleb128 5
	.uleb128 0x3
	.4byte	$LASF23
	.sleb128 6
	.uleb128 0x3
	.4byte	$LASF24
	.sleb128 7
	.uleb128 0x3
	.4byte	$LASF25
	.sleb128 8
	.uleb128 0x3
	.4byte	$LASF26
	.sleb128 9
	.uleb128 0x3
	.4byte	$LASF27
	.sleb128 10
	.uleb128 0x3
	.4byte	$LASF28
	.sleb128 11
	.uleb128 0x3
	.4byte	$LASF29
	.sleb128 12
	.uleb128 0x3
	.4byte	$LASF30
	.sleb128 13
	.uleb128 0x3
	.4byte	$LASF31
	.sleb128 14
	.uleb128 0x3
	.4byte	$LASF32
	.sleb128 15
	.uleb128 0x3
	.4byte	$LASF33
	.sleb128 16
	.uleb128 0x3
	.4byte	$LASF34
	.sleb128 17
	.uleb128 0x3
	.4byte	$LASF35
	.sleb128 18
	.uleb128 0x3
	.4byte	$LASF36
	.sleb128 19
	.uleb128 0x3
	.4byte	$LASF37
	.sleb128 20
	.uleb128 0x3
	.4byte	$LASF38
	.sleb128 21
	.uleb128 0x3
	.4byte	$LASF39
	.sleb128 22
	.uleb128 0x3
	.4byte	$LASF40
	.sleb128 23
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF42
	.byte	0x3
	.byte	0x3b
	.4byte	0xec
	.uleb128 0x2
	.4byte	0x1db
	.byte	0x4
	.byte	0x3
	.byte	0x3d
	.uleb128 0x3
	.4byte	$LASF43
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF44
	.sleb128 1
	.uleb128 0x3
	.4byte	$LASF45
	.sleb128 2
	.uleb128 0x3
	.4byte	$LASF46
	.sleb128 3
	.uleb128 0x3
	.4byte	$LASF47
	.sleb128 4
	.uleb128 0x3
	.4byte	$LASF48
	.sleb128 5
	.uleb128 0x3
	.4byte	$LASF49
	.sleb128 6
	.uleb128 0x3
	.4byte	$LASF50
	.sleb128 7
	.uleb128 0x3
	.4byte	$LASF51
	.sleb128 8
	.uleb128 0x3
	.4byte	$LASF52
	.sleb128 9
	.uleb128 0x3
	.4byte	$LASF53
	.sleb128 10
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF54
	.byte	0x3
	.byte	0x49
	.4byte	0x190
	.uleb128 0x2
	.4byte	0x1fb
	.byte	0x4
	.byte	0x3
	.byte	0x4b
	.uleb128 0x3
	.4byte	$LASF55
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF56
	.sleb128 1
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF57
	.byte	0x3
	.byte	0x4e
	.4byte	0x1e6
	.uleb128 0x2
	.4byte	0x21b
	.byte	0x4
	.byte	0x3
	.byte	0x51
	.uleb128 0x3
	.4byte	$LASF58
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF59
	.sleb128 1
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF60
	.byte	0x3
	.byte	0x54
	.4byte	0x206
	.uleb128 0x7
	.4byte	0x2cc
	.4byte	$LASF62
	.byte	0x1c
	.byte	0x3
	.byte	0x64
	.uleb128 0x8
	.4byte	$LASF63
	.byte	0x3
	.byte	0x65
	.4byte	0x185
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF64
	.byte	0x3
	.byte	0x66
	.4byte	0x7d
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF65
	.byte	0x3
	.byte	0x67
	.4byte	0x1fb
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x8
	.4byte	$LASF66
	.byte	0x3
	.byte	0x68
	.4byte	0x1db
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x8
	.4byte	$LASF67
	.byte	0x3
	.byte	0x69
	.4byte	0x21b
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x7
	.4byte	0x2af
	.4byte	$LASF68
	.byte	0xc
	.byte	0x3
	.byte	0x6a
	.uleb128 0x8
	.4byte	$LASF63
	.byte	0x3
	.byte	0x6f
	.4byte	0x1db
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF69
	.byte	0x3
	.byte	0x70
	.4byte	0x2e6
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF70
	.byte	0x3
	.byte	0x71
	.4byte	0x2e6
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x8
	.4byte	$LASF71
	.byte	0x3
	.byte	0x6a
	.4byte	0x2cc
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0x8
	.4byte	$LASF72
	.byte	0x3
	.byte	0x6b
	.4byte	0x2d2
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x278
	.uleb128 0xa
	.byte	0x4
	.uleb128 0xb
	.4byte	0x2e0
	.byte	0x1
	.uleb128 0xc
	.4byte	0x2e0
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x226
	.uleb128 0x9
	.byte	0x4
	.4byte	0x2d4
	.uleb128 0x2
	.4byte	0x319
	.byte	0x4
	.byte	0x4
	.byte	0x1a
	.uleb128 0x3
	.4byte	$LASF73
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF74
	.sleb128 1
	.uleb128 0x3
	.4byte	$LASF75
	.sleb128 2
	.uleb128 0x3
	.4byte	$LASF76
	.sleb128 3
	.uleb128 0x3
	.4byte	$LASF77
	.sleb128 4
	.uleb128 0x3
	.4byte	$LASF78
	.sleb128 5
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF79
	.byte	0x4
	.byte	0x21
	.4byte	0x2ec
	.uleb128 0x2
	.4byte	0x33f
	.byte	0x4
	.byte	0x4
	.byte	0x24
	.uleb128 0x3
	.4byte	$LASF80
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF81
	.sleb128 1
	.uleb128 0x3
	.4byte	$LASF82
	.sleb128 2
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF83
	.byte	0x4
	.byte	0x28
	.4byte	0x324
	.uleb128 0x2
	.4byte	0x35f
	.byte	0x4
	.byte	0x4
	.byte	0x2a
	.uleb128 0x3
	.4byte	$LASF84
	.sleb128 0
	.uleb128 0x3
	.4byte	$LASF85
	.sleb128 1
	.byte	0x0
	.uleb128 0x4
	.4byte	$LASF86
	.byte	0x4
	.byte	0x2d
	.4byte	0x34a
	.uleb128 0x7
	.4byte	0x3e7
	.4byte	$LASF87
	.byte	0x20
	.byte	0x4
	.byte	0x2f
	.uleb128 0x8
	.4byte	$LASF63
	.byte	0x4
	.byte	0x30
	.4byte	0x319
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x8
	.4byte	$LASF64
	.byte	0x4
	.byte	0x31
	.4byte	0x7d
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0x8
	.4byte	$LASF65
	.byte	0x4
	.byte	0x32
	.4byte	0x35f
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x8
	.4byte	$LASF88
	.byte	0x4
	.byte	0x33
	.4byte	0x3e7
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0x8
	.4byte	$LASF89
	.byte	0x4
	.byte	0x34
	.4byte	0x33f
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0x8
	.4byte	$LASF90
	.byte	0x4
	.byte	0x35
	.4byte	0x403
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0x8
	.4byte	$LASF91
	.byte	0x4
	.byte	0x36
	.4byte	0x7d
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0x8
	.4byte	$LASF92
	.byte	0x4
	.byte	0x37
	.4byte	0x7d
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x76
	.uleb128 0xd
	.4byte	0x3fd
	.byte	0x1
	.4byte	0x33f
	.uleb128 0xc
	.4byte	0x3fd
	.byte	0x0
	.uleb128 0x9
	.byte	0x4
	.4byte	0x36a
	.uleb128 0x9
	.byte	0x4
	.4byte	0x3ed
	.uleb128 0xe
	.4byte	0x419
	.4byte	0x84
	.uleb128 0xf
	.4byte	0x6f
	.byte	0x4
	.byte	0x0
	.uleb128 0x10
	.4byte	$LASF93
	.byte	0x1
	.byte	0x11
	.4byte	0x409
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	mt7620a_gpios
	.uleb128 0xe
	.4byte	0x43b
	.4byte	0x226
	.uleb128 0xf
	.4byte	0x6f
	.byte	0x3
	.byte	0x0
	.uleb128 0x10
	.4byte	$LASF94
	.byte	0x1
	.byte	0x19
	.4byte	0x42b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	mt7620a_leds
	.uleb128 0xe
	.4byte	0x45d
	.4byte	0x36a
	.uleb128 0xf
	.4byte	0x6f
	.byte	0x2
	.byte	0x0
	.uleb128 0x10
	.4byte	$LASF95
	.byte	0x1
	.byte	0x25
	.4byte	0x44d
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	mt7620a_btns
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
	.uleb128 0x3
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x42
	.2byte	0x2
	.4byte	$Ldebug_info0
	.4byte	0x470
	.4byte	0x419
	.ascii	"mt7620a_gpios\000"
	.4byte	0x43b
	.ascii	"mt7620a_leds\000"
	.4byte	0x45d
	.ascii	"mt7620a_btns\000"
	.4byte	0x0
	.section	.debug_str,"MS",@progbits,1
$LASF40:
	.ascii	"led_end\000"
$LASF20:
	.ascii	"led_internet\000"
$LASF84:
	.ascii	"BTN_LEVEL_LOW\000"
$LASF62:
	.ascii	"led_dev\000"
$LASF56:
	.ascii	"LED_GPIO_HIGH\000"
$LASF25:
	.ascii	"led_wps\000"
$LASF0:
	.ascii	"GPIO_GROUP0\000"
$LASF1:
	.ascii	"GPIO_GROUP1\000"
$LASF2:
	.ascii	"GPIO_GROUP2\000"
$LASF3:
	.ascii	"GPIO_GROUP3\000"
$LASF4:
	.ascii	"GPIO_GROUP4\000"
$LASF5:
	.ascii	"GPIO_GROUP5\000"
$LASF6:
	.ascii	"GPIO_GROUP6\000"
$LASF7:
	.ascii	"GPIO_GROUP7\000"
$LASF34:
	.ascii	"led_prov_alm\000"
$LASF69:
	.ascii	"activate\000"
$LASF97:
	.ascii	"product.c\000"
$LASF70:
	.ascii	"deactivate\000"
$LASF30:
	.ascii	"led_register\000"
$LASF11:
	.ascii	"group\000"
$LASF66:
	.ascii	"kernel_default\000"
$LASF60:
	.ascii	"led_boot_default\000"
$LASF79:
	.ascii	"btn_name\000"
$LASF9:
	.ascii	"unsigned int\000"
$LASF53:
	.ascii	"led_end_trig\000"
$LASF35:
	.ascii	"led_lan_1\000"
$LASF36:
	.ascii	"led_lan_2\000"
$LASF37:
	.ascii	"led_lan_3\000"
$LASF38:
	.ascii	"led_lan_4\000"
$LASF39:
	.ascii	"led_lan_5\000"
$LASF57:
	.ascii	"led_level\000"
$LASF47:
	.ascii	"led_dataflash_trig\000"
$LASF68:
	.ascii	"led_trigger\000"
$LASF58:
	.ascii	"LED_BOOT_OFF\000"
$LASF26:
	.ascii	"led_wps_green\000"
$LASF42:
	.ascii	"led_name\000"
$LASF67:
	.ascii	"boot_default\000"
$LASF73:
	.ascii	"btn_reset\000"
$LASF91:
	.ascii	"ignore\000"
$LASF16:
	.ascii	"isr_addr\000"
$LASF63:
	.ascii	"name\000"
$LASF65:
	.ascii	"level\000"
$LASF12:
	.ascii	"ctrl_addr\000"
$LASF22:
	.ascii	"led_internet_red\000"
$LASF71:
	.ascii	"cur_trig\000"
$LASF13:
	.ascii	"dir_addr\000"
$LASF21:
	.ascii	"led_internet_green\000"
$LASF14:
	.ascii	"data_addr\000"
$LASF78:
	.ascii	"btn_end\000"
$LASF15:
	.ascii	"edge_addr\000"
$LASF87:
	.ascii	"btn_dev\000"
$LASF17:
	.ascii	"led_power\000"
$LASF45:
	.ascii	"led_flash_trig\000"
$LASF88:
	.ascii	"iogroup\000"
$LASF74:
	.ascii	"btn_wps\000"
$LASF49:
	.ascii	"led_wps_error_trig\000"
$LASF31:
	.ascii	"led_phone_1\000"
$LASF32:
	.ascii	"led_phone_2\000"
$LASF75:
	.ascii	"btn_wps_5g\000"
$LASF19:
	.ascii	"led_power_red\000"
$LASF50:
	.ascii	"led_wps_overlap_trig\000"
$LASF46:
	.ascii	"led_flash_4hz_trig\000"
$LASF98:
	.ascii	"/home/guohongliang/work/819/DIR819/build.DIR-819/boot/tb"
	.ascii	"sboot/cpu/mt7620a\000"
$LASF54:
	.ascii	"trig_name\000"
$LASF77:
	.ascii	"btn_wlan\000"
$LASF94:
	.ascii	"mt7620a_leds\000"
$LASF43:
	.ascii	"led_off_trig\000"
$LASF95:
	.ascii	"mt7620a_btns\000"
$LASF93:
	.ascii	"mt7620a_gpios\000"
$LASF52:
	.ascii	"led_blinking_trig\000"
$LASF41:
	.ascii	"gpio_group\000"
$LASF44:
	.ascii	"led_on_trig\000"
$LASF18:
	.ascii	"led_power_green\000"
$LASF81:
	.ascii	"BTN_DOWN\000"
$LASF27:
	.ascii	"led_wps_red\000"
$LASF8:
	.ascii	"GPIO_GROUP_END\000"
$LASF76:
	.ascii	"btn_wps_and_reset\000"
$LASF24:
	.ascii	"led_wlan\000"
$LASF10:
	.ascii	"char\000"
$LASF23:
	.ascii	"led_usb\000"
$LASF82:
	.ascii	"BTN_START\000"
$LASF28:
	.ascii	"led_wps_yellow\000"
$LASF51:
	.ascii	"led_wps_success_trig\000"
$LASF55:
	.ascii	"LED_GPIO_LOW\000"
$LASF61:
	.ascii	"gpio_dev\000"
$LASF72:
	.ascii	"trigger_data\000"
$LASF33:
	.ascii	"led_line\000"
$LASF89:
	.ascii	"cur_status\000"
$LASF48:
	.ascii	"led_wps_inprogress_trig\000"
$LASF80:
	.ascii	"BTN_UP\000"
$LASF96:
	.ascii	"GNU C 3.4.2 -g\000"
$LASF90:
	.ascii	"get_status\000"
$LASF59:
	.ascii	"LED_BOOT_ON\000"
$LASF64:
	.ascii	"gpio\000"
$LASF92:
	.ascii	"index\000"
$LASF29:
	.ascii	"led_dsl\000"
$LASF85:
	.ascii	"BTN_LEVEL_HIGH\000"
$LASF86:
	.ascii	"btn_level\000"
$LASF83:
	.ascii	"btn_status\000"
	.ident	"GCC: (GNU) 3.4.2"
