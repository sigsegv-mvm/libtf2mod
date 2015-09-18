#include "all.h"


PATCH(medicbot_ai_xbow_heal_part2);
/* protect the CWeaponMedigun::GetTargetRange vcall from being invoked on a
 * CTFCrossbow instance; the CTFCrossbow vtable doesn't even have an entry that
 * high, so the game would probably crash if we didn't work around this */


PATCH_CHECK
{
	uintptr_t off1 = vtable_find_offset("_ZTV14CWeaponMedigun",
		CWeaponMedigun_GetTargetRange);
	
	
	size_t check1_base = 0x1a55;
	uint8_t check1[] = {
		0x8b, 0x03,                         // +1A55  mov eax,DWORD PTR [ebx]
		0x89, 0x1c, 0x24,                   // +1A57  mov DWORD PTR [esp],ebx
		0xff, 0x90, CONV_LE(off1)           // +1A5A  call DWORD PTR [eax+GetTargetRange] CWeaponMedigun::GetTargetRange()
		0x8b, 0x55, 0x10,                   // +1A60  mov edx,DWORD PTR [ebp+0x10]
		0x89, 0xf9,                         // +1A63  mov ecx,edi
		0xd9, 0x9d, 0x34, 0xff, 0xff, 0xff, // +1A65  fstp DWORD PTR [ebp-0xcc]
	};
	
	
	bool result = true;
	if (!func_verify(CTFBotMedicHeal_Update,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	void *new_func = alloc_func(1);
	//pr_warn("medicbot_ai_xbow_heal_part2 new_func @ %08x\n",
	//	(uintptr_t)new_func);
	
	
	uintptr_t off1 = CALC_RELJMP(CTFBotMedicHeal_Update, 0x1a5a,
		new_func);
	
	
	size_t data1_base = 0x1a55;
	uint8_t data1[] = {
		0xe9, CONV_LE(off1)                 // +1A55  jmp new_func
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +1A5A  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // +1A60  nop x 6
		0x90, 0x90, 0x90, 0x90, 0x90,       // +1A66  nop x 5
	};
	
	
	uintptr_t off2 = (uintptr_t)typeinfo_for_CWeaponMedigun;
	
	uintptr_t off3 = (uintptr_t)typeinfo_for_CTFWeaponBase;
	
	uintptr_t off4 = CALC_RELJMP(new_func, 0x0020,
		__dynamic_cast_NULL_safe);
	
	uintptr_t off5 = 0x0046 - 0x0028;
	
	uintptr_t off6 = vtable_find_offset("_ZTV14CWeaponMedigun",
		CWeaponMedigun_GetTargetRange);
	
	uintptr_t off7 = CALC_RELJMP(new_func, 0x0046,
		(void *)((uintptr_t)CTFBotMedicHeal_Update + 0x1a6b));
	
	uintptr_t off8 = CALC_RELJMP(new_func, 0x0050,
		(void *)((uintptr_t)CTFBotMedicHeal_Update + 0x1a6b));
	
	
	/* try a dynamic_cast to CWeaponMedigun before we blindly call vtable offset
	 * 0x770 (which doesn't exist for CTFCrossbow) */
	size_t data2_base = 0x0000;
	uint8_t data2[] = {
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +0000  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, CONV_LE(off2)           // +0008  mov DWORD PTR [esp+0x8],ds:typeinfo_for_CWeaponMedigun
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off3)           // +0010  mov DWORD PTR [esp+0x4],ds:typeinfo_for_CTFWeaponBase
		0x89, 0x1c, 0x24,                               // +0018  mov DWORD PTR [esp],ebx
		0xe8, CONV_LE(off4)                             // +001B  call __dynamic_cast_NULL_safe
		
		0x85, 0xc0,                                     // +0020  test eax,eax
		0x0f, 0x84, CONV_LE(off5)                       // +0022  je L_xbow
		
	// L_medi:
		0x89, 0xc3,                                     // +0028  mov ebx,eax
		0x8b, 0x03,                                     // +002A  mov eax,DWORD PTR [ebx]
		0x89, 0x1c, 0x24,                               // +002C  mov DWORD PTR [esp],ebx
		0xff, 0x90, CONV_LE(off6)                       // +002F  call DWORD PTR [eax+GetTargetRange] CWeaponMedigun::GetTargetRange()
		0x8b, 0x55, 0x10,                               // +0035  mov edx,DWORD PTR [ebp+0x10]
		0x89, 0xf9,                                     // +0038  mov ecx,edi
		0xd9, 0x9d, 0x34, 0xff, 0xff, 0xff,             // +003A  fstp DWORD PTR [ebp-0xcc]
		0xe9, CONV_LE(off7)                             // +0040  jmp L_resume
		
	// L_xbow:
		0x8b, 0x55, 0x10,                               // +0046  mov edx,DWORD PTR [ebp+0x10]
		0x89, 0xf9,                                     // +0049  mov ecx,edi
		0xe9, CONV_LE(off8)                             // +004B  jmp L_resume
	};
	
	
	/* modify the original function to jump to our new function */
	func_write(CTFBotMedicHeal_Update,
		data1_base, sizeof(data1), data1);
	
	
	/* write the contents of the new function */
	memcpy(new_func, data2, sizeof(data2));
}
