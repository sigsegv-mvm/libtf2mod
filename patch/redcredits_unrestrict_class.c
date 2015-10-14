#include "all.h"


PATCH(redcredits_unrestrict_class);
/* allow red credits to drop for classes other than sniper */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CTFPlayer", "m_PlayerClass") +
		sendprop_offset("CTFPlayer", "m_iClass");
	
	
	size_t check1_base = 0x0877;
	uint8_t check1[] = {
		0x83, 0xb9, CONV_LE(off1) 0x02,     // +0877  cmp DWORD PTR [ecx+m_PlayerClass+m_iClass],TFCLASS_SNIPER
		0x0f, 0x85, 0xfb, 0x00, 0x00, 0x00, // +087E  jne +0xfb
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_Event_Killed,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the jump */
	func_write_nop(CTFPlayer_Event_Killed,
		0x087e, 6);
}
