const struct TestCase TEST_CASES[] = {
	{
		.name = "nop",
		.data = { 0x4e71 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "addi with no overflow or carry",
		.data = { 0x0600, 0x007f },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0000007f, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "addi with no overflow but negative",
		.data = { 0x0600, 0x0080 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000081, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "addi with overflow",
		.data = { 0x0600, 0x007f },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "addi with carry",
		.data = { 0x0600, 0x0080 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "adda immediate",
		.data = { 0xd0fc, 0xf800 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0xfffff800, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "adda register",
		.data = { 0xd0c0 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0000f800, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0000f800, .d1 = 0x00000000, .a0 = 0xfffff800, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "andi with sr",
		.data = { 0x027c, 0xf8ff },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "asl",
		.data = { 0xe300 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000002, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "asr",
		.data = { 0xe200 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000081, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000000c0, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "blt with jump",
		.data = { 0x6d08 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x0000000a, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "blt with jump",
		.data = { 0x6d08 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "bchg not zero",
		.data = { 0x0841, 0x0007 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x000000ff, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x0000007f, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "bchg zero",
		.data = { 0x0841, 0x0007 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000080, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "bra 8-bit",
		.data = { 0x60e0 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0xffffffe2, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi equal",
		.data = { 0x0c00, 0x0020 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000020, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000020, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi greater than",
		.data = { 0x0c00, 0x0030 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000020, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000020, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi less than",
		.data = { 0x0c00, 0x0010 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000020, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000020, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi no overflow",
		.data = { 0x0c00, 0x007f },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi no overflow, already negative",
		.data = { 0x0c40, 0x8001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi with overflow",
		.data = { 0x0c00, 0x0080 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi with overflow 2",
		.data = { 0x0c40, 0x8001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi no carry",
		.data = { 0x0c00, 0x0001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000000ff, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000000ff, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "cmpi with carry",
		.data = { 0x0c00, 0x00ff },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "divu",
		.data = { 0x80fc, 0x0245 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00040000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x007101c3, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "eori",
		.data = { 0xb380 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xaaaa5555, .d1 = 0x55aa55aa, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xff0000ff, .d1 = 0x55aa55aa, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "exg",
		.data = { 0xc189 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x12345678, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x87654321, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x87654321, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x12345678, .mem = 0x00000000, },
	},
	{
		.name = "ext",
		.data = { 0x4880 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000000cb, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0000ffcb, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "ext",
		.data = { 0x48c0 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000000cb, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000000cb, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "muls",
		.data = { 0xc1fc, 0x0276 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000200, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0004ec00, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "movel",
		.data = { 0x2200 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xfedcba98, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xfedcba98, .d1 = 0xfedcba98, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "movea",
		.data = { 0x2040 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xfedcba98, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xfedcba98, .d1 = 0x00000000, .a0 = 0xfedcba98, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "movem word to target",
		.data = { 0x4890, 0x0003 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0xefef5678, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0xefef5678, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0x12345678, },
	},
	{
		.name = "movem long to target",
		.data = { 0x48d0, 0x0001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xabcd1234, },
	},
	{
		.name = "movem long from target",
		.data = { 0x4cd0, 0x0001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xabcd1234, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xabcd1234, },
	},
	{
		.name = "movem word from target inc",
		.data = { 0x4c98, 0x0001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xffffffff, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xabcd1234, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xffffabcd, .d1 = 0x00000000, .a0 = 0x00001236, .a1 = 0x00000000, .mem = 0xabcd1234, },
	},
	{
		.name = "movem long to target dec",
		.data = { 0x48e0, 0x8000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0x00000000, .a0 = 0x00001238, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xabcd1234, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xabcd1234, },
	},
	{
		.name = "movep word to even memory",
		.data = { 0x0188, 0x0000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000055aa, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xffffffff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000055aa, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0x55ffaaff, },
	},
	{
		.name = "movep word to odd memory",
		.data = { 0x0188, 0x0001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000055aa, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xffffffff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000055aa, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xff55ffaa, },
	},
	{
		.name = "movep long to even memory upper",
		.data = { 0x01c8, 0x0000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xaabbccdd, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xffffffff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xaabbccdd, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xaaffbbff, },
	},
	{
		.name = "movep long to even memory lower",
		.data = { 0x01c8, 0x0000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xaabbccdd, .d1 = 0x00000000, .a0 = 0x00001230, .a1 = 0x00000000, .mem = 0xffffffff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xaabbccdd, .d1 = 0x00000000, .a0 = 0x00001230, .a1 = 0x00000000, .mem = 0xccffddff, },
	},
	{
		.name = "movep word from even memory",
		.data = { 0x0108, 0x0000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0x55ffaaff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000055aa, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0x55ffaaff, },
	},
	{
		.name = "movep word from odd memory",
		.data = { 0x0108, 0x0001 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xff55ffaa, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x000055aa, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xff55ffaa, },
	},
	{
		.name = "movep long from even memory upper",
		.data = { 0x0148, 0x0000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xaaffbbff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0xaabb0000, .d1 = 0x00000000, .a0 = 0x00001234, .a1 = 0x00000000, .mem = 0xaaffbbff, },
	},
	{
		.name = "movep long from even memory lower",
		.data = { 0x0148, 0x0000 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00001230, .a1 = 0x00000000, .mem = 0xccffddff, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0000ccdd, .d1 = 0x00000000, .a0 = 0x00001230, .a1 = 0x00000000, .mem = 0xccffddff, },
	},
	{
		.name = "neg",
		.data = { 0x4440 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x0000ff80, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "ori",
		.data = { 0x0008, 0x00ff },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x000000ff, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "ori with sr",
		.data = { 0x007c, 0x00aa },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000004, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "rol",
		.data = { 0xe318 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "ror",
		.data = { 0xe218 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "roxl",
		.data = { 0xe310 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "roxr",
		.data = { 0xe210 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000000, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "roxl two bits",
		.data = { 0xe510 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
	{
		.name = "roxr two bits",
		.data = { 0xe410 },
		.init = {.pc = 0x00000000, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000001, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
		.fini = {.pc = 0x00000002, .ssp = 0x00000000, .usp = 0x00000000, .d0 = 0x00000080, .d1 = 0x00000000, .a0 = 0x00000000, .a1 = 0x00000000, .mem = 0x00000000, },
	},
};