#include "all.h"


PATCH(mvm_enable_human_gibbing);
/* remove MvM-specific logic that prevents non-bots from gibbing */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CTFGameRulesProxy",
		"m_bPlayingMannVsMachine");
	
	
	size_t check1_base = 0x0040;
	uint8_t check1[] = {
		0x80, 0xba, CONV_LE(off1) 0x00, // +0040  cmp BYTE PTR [edx+m_bPlayingMannVsMachine],0x0
		0x75,                           // +0047  jne <byte:dontcare>
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_ShouldGib,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* remove the relative jump for MvM-specific gibbing logic */
	func_write_nop(CTFPlayer_ShouldGib,
		0x0047, 2);
}
