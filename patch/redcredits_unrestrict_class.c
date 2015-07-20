#include "all.h"


PATCH(redcredits_unrestrict_class);
/* allow red credits to drop for classes other than sniper */


static func_t *func1;


PATCH_INIT
{
	/* CTFPlayer::Event_Killed(CTakeDamageInfo const&) */
	func1 = func_register(
		"_ZN9CTFPlayer12Event_KilledERK15CTakeDamageInfo");
}


PATCH_CHECK
{
	size_t check1_base = 0x0837;
	uint8_t check1[] = {
		0x83, 0xb9, 0xac, 0x26, 0x00, 0x00, 0x02, // +0837  cmp DWORD PTR [ecx+0x26ac],0x02
		0x0f, 0x85, 0xfb, 0x00, 0x00, 0x00,       // +083E  jne +0xfb
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the jump */
	func_write_nop(func1, 0x083e, 6);
}
