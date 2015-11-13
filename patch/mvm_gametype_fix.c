#include "all.h"


PATCH(mvm_gametype_fix);
/* fix control point HUD not being visible due to Valve changing the value of
 * CTFGameRules::m_nGameType from TF_GAMETYPE_CP to TF_GAMETYPE_MVM */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CTFGameRulesProxy", "m_nGameType");
	
	
	size_t check1_base = 0x0df8;
	uint8_t check1[] = {
		0xc7, 0x45, 0xd8, CONV_LE(TF_GAMETYPE_MVM) // +0DF8  mov DWORD PTR [ebp-0x28],TF_GAMETYPE_MVM
		0xb9, 0x04, 0x00, 0x00, 0x00,              // +0DFF  mov ecx,0x4
		0xf3, 0xa6,                                // +0E04  rep cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	};
	
	size_t check2_base = 0x0e11;
	uint8_t check2[] = {
		0xc7, 0x83, CONV_LE(off1) CONV_LE(TF_GAMETYPE_MVM) // +0E11  mov DWORD PTR [this+m_nGameType],TF_GAMETYPE_MVM
	};
	
	
	bool result = true;
	if (!func_verify(CTFGameRules_Activate,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFGameRules_Activate,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	union {
		uint8_t  b[4];
		uint32_t i;
	} gametype = { .i = TF_GAMETYPE_CP };
	
	/* replace both instances of TF_GAMETYPE_MVM with TF_GAMETYPE_CP */
	func_write(CTFGameRules_Activate, 0x0dfb, sizeof(gametype), gametype.b);
	func_write(CTFGameRules_Activate, 0x0e17, sizeof(gametype), gametype.b);
}
