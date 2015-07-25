#include "all.h"


PATCH(redcredits_unrestrict_class);
/* allow red credits to drop for classes other than sniper */


PATCH_CHECK
{
	size_t check1_base = 0x0837;
	uint8_t check1[] = {
		0x83, 0xb9, 0xc0, 0x26, 0x00, 0x00, 0x02, // +0837  cmp DWORD PTR [ecx+0x26c0],0x02
		0x0f, 0x85, 0xfb, 0x00, 0x00, 0x00,       // +083E  jne +0xfb
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
		0x083e, 6);
}
