#include "all.h"


PATCH(engiebot_ai_repair_tele_under_construction);
/* make engiebots stop ignoring their teleporter if it's damaged while under
 * construction; this is part of the RTR fix */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset(
		"CBaseObject", "m_bBuilding");
	
	
	size_t check1_base = 0x03d8;
	uint8_t check1[] = {
		0x80, 0xb8, CONV_LE(off1)     0x00, // +03D8  cmp BYTE PTR [eax+m_bBuilding],0x0
		0x0f, 0x85, 0xec, 0x02, 0x00, 0x00, // +03DF  jne +0x2ec
	};
	
	
	bool result = true;
	if (!func_verify(CTFBotMvMEngineerIdle_Update,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* remove the teleporter-specific m_bBuilding check */
	func_write_nop(CTFBotMvMEngineerIdle_Update,
		0x03d8, 13);
}
