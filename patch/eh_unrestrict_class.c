#include "all.h"


PATCH(eh_unrestrict_class);
/* allow explosive headshot on classes other than sniper */


PATCH_CHECK
{
	uintptr_t off1 = calc_relative_jump(CTFGameRules_CanUpgradeWithAttrib,
		0x0b0c, CTFPlayer_IsPlayerClass);
	
	
	size_t check1_base = 0x0a68;
	uint8_t check1[] = {
		0x66, 0x81, 0xff, 0x8b, 0x01,       // +0A68  cmp di,0x18b
		0x0f, 0x84, 0x8c, 0x00, 0x00, 0x00, // +0A6D  je +0x8c
	};
	
	size_t check2_base = 0x0aff;
	uint8_t check2[] = {
		0xc7, 0x44, 0x24, 0x04, 0x02, 0x00, 0x00, 0x00, // +0AFF  mov DWORD PTR [esp+0x4],0x2
		0x31, 0xdb,                                     // +0B07  xor ebx,ebx
		0x89, 0x34, 0x24,                               // +0B09  mov DWORD PTR [esp],esi
		0xe8, CONV_LE(off1)                             // +0B0C  call CTFPlayer::IsPlayerClass
		0x84, 0xc0,                                     // +0B11  test al,al
		0x0f, 0x84, 0x67, 0xf5, 0xff, 0xff,             // +0B13  je -0xa99
	};
	
	
	bool result = true;
	if (!func_verify(CTFGameRules_CanUpgradeWithAttrib,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFGameRules_CanUpgradeWithAttrib,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the conditional jump at +0B13 */
	func_write_nop(CTFGameRules_CanUpgradeWithAttrib, 0x0b13, 6);
}
