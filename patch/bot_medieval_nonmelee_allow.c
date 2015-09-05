#include "all.h"


PATCH(bot_medieval_nonmelee_allow);
/* remove the code that forces bots to switch to their melee weapon when they
 * spawn in a medieval mode game (which prevents them from using medieval mode
 * primary/secondary weapons) */


PATCH_CHECK
{
	uintptr_t off1 = (uintptr_t)g_pGameRules;
	
	uintptr_t off2 = sendprop_offset("CTFGameRulesProxy", "m_bPlayingMedieval");
	
	
	size_t check1_base = 0x00b0;
	uint8_t check1[] = {
		0xa1, CONV_LE(off1)             // +00B0  mov eax,ds:g_pGameRules
		0x80, 0xbb, CONV_LE(off2) 0x00, // +00B5  cmp byte ptr [eax+m_bPlayingMedieval],0x0
		0x75, 0xbb,                     // +00BC  jnz -0x45
	};
	
	
	bool result = true;
	if (!func_verify(CTFBot_EquipRequiredWeapon,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the conditional jump at +00BC */
	func_write_nop(CTFBot_EquipRequiredWeapon, 0x00bc, 2);
}
