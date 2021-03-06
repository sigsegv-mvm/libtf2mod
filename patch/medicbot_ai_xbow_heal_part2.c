#include "all.h"


PATCH(medicbot_ai_xbow_heal_part2);
/* protect the CWeaponMedigun::GetTargetRange vcall from being invoked on a
 * CTFCrossbow instance; the CTFCrossbow vtable doesn't even have an entry that
 * high, so the game would probably crash if we didn't work around this */


extern void asm_CTFBotMedicHeal_Update_GetTargetRange(void);


PATCH_CHECK
{
	uintptr_t off1 = vtable_find_offset("_ZTV14CWeaponMedigun",
		CWeaponMedigun_GetTargetRange);
	
	
	size_t check1_base = 0x1bf2;
	uint8_t check1[] = {
		0x8b, 0x03,                         // +1BF2  mov eax,DWORD PTR [ebx]
		0x89, 0x1c, 0x24,                   // +1BF4  mov DWORD PTR [esp],ebx
		0xff, 0x90, CONV_LE(off1)           // +1BF7  call DWORD PTR [eax+GetTargetRange] CWeaponMedigun::GetTargetRange()
		0x8b, 0x55, 0x10,                   // +1BFD  mov edx,DWORD PTR [ebp+0x10]
		0x89, 0xf9,                         // +1C00  mov ecx,edi
		0xd9, 0x9d, 0x40, 0xff, 0xff, 0xff, // +1C02  fstp DWORD PTR [ebp-0xc0]
	};
	
	
	bool result = true;
	if (!func_verify(CTFBotMedicHeal_Update,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	//pr_debug("CTFBotMedicHeal::Update patch #2 @ %08x\n",
	//	(uintptr_t)CTFBotMedicHeal_Update + 0xa155);
	//pr_debug("asm_CTFBotMedicHeal_Update_GetTargetRange @ %08x\n",
	//	(uintptr_t)asm_CTFBotMedicHeal_Update_GetTargetRange);
	
	
	uintptr_t voff_GetTargetRange = vtable_find_offset("_ZTV14CWeaponMedigun",
		CWeaponMedigun_GetTargetRange);
	
	uintptr_t rel_call = CALC_RELJMP(CTFBotMedicHeal_Update, 0x1bfc,
		asm_CTFBotMedicHeal_Update_GetTargetRange);
	
	
	size_t data1_base = 0x1bf2;
	uint8_t data1[] = {
		0xb8, CONV_LE(voff_GetTargetRange)  // +1BF2  mov eax,voff_GetTargetRange
		0xe8, CONV_LE(rel_call)             // +1BF7  call asm_CTFBotMedicHeal_Update_GetTargetRange
		0xd9, 0x9d, 0x40, 0xff, 0xff, 0xff, // +1BFC  fstp DWORD PTR [ebp-0xc0]
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +1C02  nop x 6
	};
	
	
	/* call asm_CTFBotMedicHeal_Update_GetTargetRange and let it figure this out */
	func_write(CTFBotMedicHeal_Update,
		data1_base, sizeof(data1), data1);
}
