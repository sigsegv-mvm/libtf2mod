#ifndef _LIBTF2MOD_X86_H
#define _LIBTF2MOD_X86_H


#define REG_EAX 0b000
#define REG_ECX 0b001
#define REG_EDX 0b010
#define REG_EBX 0b011
#define REG_ESP 0b100
#define REG_EBP 0b101
#define REG_ESI 0b110
#define REG_EDI 0b111

#define MOD_INDIRECT 0b00
#define MOD_DISP8    0b01
#define MOD_DISP32   0b10
#define MOD_REG      0b11

#define SIB_X1 0b00
#define SIB_X2 0b01
#define SIB_X4 0b10
#define SIB_X8 0b11


#define CONV_LE(_dword) \
	(uint8_t)((uint32_t)(_dword) >>  0), \
	(uint8_t)((uint32_t)(_dword) >>  8), \
	(uint8_t)((uint32_t)(_dword) >> 16), \
	(uint8_t)((uint32_t)(_dword) >> 24),


#define X86_MODRM(_mod, _reg, _rm) \
	((_mod << 6) | (_reg << 3) | (_rm << 0))

#define X86_SIB(_scale, _index, _base) \
	((_scale << 6) | (_index << 3) | (_base << 0))


#define MOV_ESP_DISP8_IMM(_disp8, _imm32) \
	0xc7, \
	X86_MODRM(MOD_DISP8, 0b000, REG_ESP), \
	X86_SIB(SIB_X1, REG_ESP, REG_ESP), \
	_disp8, \
	CONV_LE(_imm32),

#define MOV_ESP_DISP8_REG(_disp8, _reg) \
	0x89, \
	X86_MODRM(MOD_DISP8, _reg, REG_ESP), \
	X86_SIB(SIB_X1, REG_ESP, REG_ESP), \
	_disp8,

#define MOV_ESP_INDIR_REG(_reg) \
	0x89, \
	X86_MODRM(MOD_INDIRECT, _reg, REG_ESP), \
	X86_SIB(SIB_X1, REG_ESP, REG_ESP),


#endif
