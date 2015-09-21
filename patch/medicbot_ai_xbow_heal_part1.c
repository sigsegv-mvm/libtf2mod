#include "all.h"


PATCH(medicbot_ai_xbow_heal_part1);
/* in CTFBotMedicHeal::Update, if the dynamic cast from CTFWeaponBase to
 * CWeaponMedigun fails, don't give up; instead, try to dynamic cast to
 * CTFCrossbow, and if that succeeds, then jump back into the healing code
 * (skipping some of the earlier medigun-specific code blocks) */


extern void asm_CTFBotMedicHeal_Update_EnableXbow(void);


PATCH_CHECK
{
	uintptr_t off1 = (uintptr_t)typeinfo_for_CWeaponMedigun;
	
	uintptr_t off2 = (uintptr_t)typeinfo_for_CTFWeaponBase;
	
	uintptr_t off3 = CALC_RELJMP(CTFBotMedicHeal_Update, 0x08e1,
		__dynamic_cast);
	
	uintptr_t off4 = (uintptr_t)g_pGameRules;
	
	uintptr_t off5 = vtable_find_offset("_ZTV12CTFGameRules",
		CTFGameRules_IsInTraining);
	
	
	size_t check1_base = 0x08c1;
	uint8_t check1[] = {
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +08C1  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, CONV_LE(off1)           // +08C9  mov DWORD PTR [esp+0x8],ds:typeinfo_for_CWeaponMedigun
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off2)           // +08D1  mov DWORD PTR [esp+0x4],ds:typeinfo_for_CTFWeaponBase
		0x89, 0x04, 0x24,                               // +08D9  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off3)                             // +08DC  call __dynamic_cast
		0xc6, 0x85, 0x58, 0xff, 0xff, 0xff, 0x00,       // +08E1  mov BYTE PTR [ebp-0xa8],0x0
		0x85, 0xc0,                                     // +08E8  test eax,eax
		0x89, 0xc3,                                     // +08EA  mov ebx,eax
		0xc6, 0x85, 0x60, 0xff, 0xff, 0xff, 0x01,       // +08EC  mov BYTE PTR [ebp-0xa0],0x1
		0x0f, 0x84, 0x47, 0x01, 0x00, 0x00,             // +08F3  je +0x147
	};
	
	size_t check2_base = 0x0a40;
	uint8_t check2[] = {
		0x8b, 0xbd, 0x70, 0xff, 0xff, 0xff, // +0A40  mov edi,DWORD PTR [ebp-0x90]
		0x85, 0xff,                         // +0A46  test edi,edi
		0x74, 0x16,                         // +0A48  je +0x16
	};
	
	size_t check3_base = 0x19fd;
	uint8_t check3[] = {
		0xa1, CONV_LE(off4)       // +19FD  mov eax,ds:g_pGameRules
		0x8b, 0x10,               // +19E2  mov edx,DWORD PTR [eax]
		0x89, 0x04, 0x24,         // +19E4  mov DWORD PTR [esp],eax
		0xff, 0x92, CONV_LE(off5) // +19E7  call DWORD PTR [edx+IsInTraining] CTFGameRules::IsInTraining
	};
	
	
	bool result = true;
	if (!func_verify(CTFBotMedicHeal_Update,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFBotMedicHeal_Update,
		check2_base, sizeof(check2), check2)) result = false;
	if (!func_verify(CTFBotMedicHeal_Update,
		check3_base, sizeof(check3), check3)) result = false;
	return result;
}


PATCH_APPLY
{
	pr_err("CTFBotMedicHeal::Update patch #1 @ %08x\n",
		(uintptr_t)CTFBotMedicHeal_Update + 0x08c1);
	pr_err("asm_CTFBotMedicHeal_Update_EnableXbow @ %08x\n",
		(uintptr_t)asm_CTFBotMedicHeal_Update_EnableXbow);
	
	
	uintptr_t dst_medi = (uintptr_t)CTFBotMedicHeal_Update + 0x08f9;
	uintptr_t dst_xbow = (uintptr_t)CTFBotMedicHeal_Update + 0x19fd;
	uintptr_t dst_fail = (uintptr_t)CTFBotMedicHeal_Update + 0x0a40;
	
	uintptr_t rel_call = CALC_RELJMP(CTFBotMedicHeal_Update, 0x08d5,
		asm_CTFBotMedicHeal_Update_EnableXbow);
	
	
	size_t data1_base = 0x08c1;
	uint8_t data1[] = {
		0x68, CONV_LE(dst_medi) // +08C1  push dst_medi
		0x68, CONV_LE(dst_xbow) // +08C6  push dst_xbow
		0x68, CONV_LE(dst_fail) // +08CB  push dst_fail
		0xe8, CONV_LE(rel_call) // +08D0  call asm_CTFBotMedicHeal_Update_EnableXbow
		0x90, 0x90, 0x90, 0x90, // +08D5  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08D9  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08DD  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08E1  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08E5  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08E9  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08ED  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08F1  nop x 4
		0x90, 0x90, 0x90, 0x90, // +08F5  nop x 4
	};
	
	
	/* call asm_CTFBotMedicHeal_Update_EnableXbow and let it figure this out */
	func_write(CTFBotMedicHeal_Update,
		data1_base, sizeof(data1), data1);
}
