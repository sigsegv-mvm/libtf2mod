#include "all.h"


PATCH(eyelander_overheal_decay_fix);
/* don't allow CTFSword::OnDecapitation to set the overheal decay duration
 * multiplier to 0.25 */


PATCH_CHECK
{
	/* sadly this offset isn't totally public */
	uintptr_t off1 = sendprop_offset("CTFPlayer", "m_Shared") + 0x01a8;
	
	union {
		float    f;
		uint32_t dw;
	} mult = { .f = 0.25f };
	
	
	size_t check1_base = 0x0140;
	uint8_t check1[] = {
		0xc7, 0x83, CONV_LE(off1) CONV_LE(mult.dw) // +0140 mov DWORD PTR [ebx+m_Shared+0x854],0.25f
	};
	
	
	bool result = true;
	if (!func_verify(CTFSword_OnDecapitation,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the assignment to the decay duration multiplier */
	func_write_nop(CTFSword_OnDecapitation, 0x0140, 10);
}
