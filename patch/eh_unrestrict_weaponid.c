#include "all.h"


PATCH(eh_unrestrict_weaponid);
/* allow explosive headshot on weapons that are not sniper rifles */


extern void asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH(void);


PATCH_CHECK
{
	uintptr_t off1 = vtable_find_offset("_ZTV13CTFWeaponBase",
		CTFWeaponBase_GetWeaponID);
	
	uintptr_t off2 = CALC_RELJMP(CTFPlayer_OnTakeDamage_Alive, 0x0ff8,
		WeaponID_IsSniperRifle);
	
	uintptr_t off3 = (uintptr_t)g_pGameRules;
	
	uintptr_t off4 = CALC_RELJMP(CTFPlayer_OnTakeDamage_Alive, 0x1085,
		CTFGameRules_GameModeUsesUpgrades);
	
	uintptr_t off5 = find_string(
		"server_srv.so", "explosive_sniper_shot", true);
	
	uintptr_t off6 = CALC_RELJMP(CTFPlayer_OnTakeDamage_Alive, 0x10c8,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off7 = CALC_RELJMP(CTFPlayer_OnTakeDamage_Alive, 0x10fb,
		CTFSniperRifle_ExplosiveHeadShot);
	
	
	size_t check1_base = 0x0fe5;
	uint8_t check1[] = {
		0x8b, 0x00,                         // +0FE5  mov eax,DWORD PTR [eax]
		0x89, 0x34, 0x24,                   // +0FE7  mov DWORD PTR [esp],esi
		0xff, 0x90, CONV_LE(off1)           // +0FEA  call DWORD PTR [eax+GetWeaponID] CTFWeaponBase::GetWeaponID
		0x89, 0x04, 0x24,                   // +0FF0  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off2)                 // +0FF3  call WeaponID_IsSniperRifle
		0x84, 0xc0,                         // +0FF8  test al,al
		0x0f, 0x84, 0xf5, 0xf4, 0xff, 0xff, // +0FFA  je -0xb0b
	};
	
	size_t check2_base = 0x1070;
	uint8_t check2[] = {
		0xa1, CONV_LE(off3)                             // +1070  mov eax,g_pGameRules
		0x85, 0xc0,                                     // +1075  test eax,eax
		0x0f, 0x84, 0x78, 0xf4, 0xff, 0xff,             // +1077  je -0xb88
		0x89, 0x04, 0x24,                               // +107D  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off4)                             // +1080  call CTFGameRules::GameModeUsesUpgrades
		0x84, 0xc0,                                     // +1085  test al,al
		0x0f, 0x84, 0x68, 0xf4, 0xff, 0xff,             // +1087  je -0xb98
		0x80, 0xbd, 0x5c, 0xff, 0xff, 0xff, 0x00,       // +108D  cmp BYTE PTR [ebp-0xa4],0x0
		0x0f, 0x84, 0x5b, 0xf4, 0xff, 0xff,             // +1094  je -0xba5
		0x8b, 0x95, 0x60, 0xff, 0xff, 0xff,             // +109A  mov edx,DWORD PTR [ebp-0xa0]
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +10A0  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +10A8  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off5)           // +10B0  mov DWORD PTR [esp+0x4],"explosive_sniper_shot"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +10B8  mov DWORD PTR [esp],0x0
		0x89, 0x54, 0x24, 0x08,                         // +10BF  mov DWORD PTR [esp+0x8],edx
		0xe8, CONV_LE(off6)                             // +10C3  call CAttributeManager::AttribHookValue<int>
		0x85, 0xc0,                                     // +10C8  test eax,eax
		0x0f, 0x84, 0x25, 0xf4, 0xff, 0xff,             // +10CA  je -0xbdb
		0x8b, 0x4d, 0x0c,                               // +10D0  mov ecx,DWORD PTR [ebp+0xc]
		0x8b, 0x41, 0x40,                               // +10D3  mov eax,DWORD PTR [ecx+0x40]
		0x83, 0xf8, 0x33,                               // +10D6  cmp eax,0x33
		0x0f, 0x85, 0xf5, 0x08, 0x00, 0x00,             // +10D9  jne +0x8f5
		0x8b, 0xb5, 0x60, 0xff, 0xff, 0xff,             // +10DF  mov esi,DWORD PTR [ebp-0xa0]
		0x89, 0x5c, 0x24, 0x08,                         // +10E5  mov DWORD PTR [esp+0x8],ebx
		0x8b, 0x85, 0x58, 0xff, 0xff, 0xff,             // +10E9  mov eax,DWORD PTR [ebp-0xa8]
		0x89, 0x74, 0x24, 0x04,                         // +10EF  mov DWORD PTR [esp+0x4],esi
		0x89, 0x04, 0x24,                               // +10F3  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off7)                             // +10F6  call CTFSniperRifle::ExplosiveHeadShot
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_OnTakeDamage_Alive,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFPlayer_OnTakeDamage_Alive,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	uintptr_t dst_rifle = (uintptr_t)CTFPlayer_OnTakeDamage_Alive + 0x1000;
	uintptr_t dst_other = (uintptr_t)CTFPlayer_OnTakeDamage_Alive + 0x1070;
	
	uintptr_t rel_call = CALC_RELJMP(CTFPlayer_OnTakeDamage_Alive, 0x0ff4,
		asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH);
	
	
	size_t data1_base = 0x0fe5;
	uint8_t data1[] = {
		0x68, CONV_LE(dst_rifle) // +0FE5  push dst_rifle
		0x68, CONV_LE(dst_other) // +0FEA  push dst_other
		0xe8, CONV_LE(rel_call)  // +0FEF  call asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH
		0x90, 0x90, 0x90, 0x90,  // +0FF4  nop x 4
		0x90, 0x90, 0x90, 0x90,  // +0FF8  nop x 4
		0x90, 0x90, 0x90, 0x90,  // +0FFC  nop x 4
	};
	
	
	/* call asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH and let it figure this out */
	func_write(CTFPlayer_OnTakeDamage_Alive,
		data1_base, sizeof(data1), data1);
}
