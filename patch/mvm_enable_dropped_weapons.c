#include "all.h"


PATCH(mvm_enable_dropped_weapons);
/*  */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CTFGameRulesProxy",
		"m_bPlayingMannVsMachine");
	
	
	size_t check1_base = 0x0013;
	uint8_t check1[] = {
		0x80, 0xb8, CONV_LE(off1) 0x00, // +0013  cmp BYTE PTR [eax+m_bPlayingMannVsMachine],0x0
		0x0f, 0x85,                     // +001A  jne +0x????????
	};
	
	
	bool result = true;
	if (!func_verify(CTFDroppedWeapon_Create,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the MvM gamemode conditional jump */
	func_write_nop(CTFDroppedWeapon_Create, 0x001a, 6);
}
