#include "all.h"


PATCH(eh_unrestrict_weaponid);
/* allow explosive headshot on weapons that are not sniper rifles */


PATCH_INIT
{
	
}


PATCH_CHECK
{
	uintptr_t off1 = calc_relative_jump(CTFPlayer_OnTakeDamage_Alive, 0x1003,
		WeaponID_IsSniperRifle);
	
	uintptr_t off2 = (uintptr_t)g_pGameRules;
	
	uintptr_t off3 = calc_relative_jump(CTFPlayer_OnTakeDamage_Alive, 0x1081,
		CTFGameRules_GameModeUsesUpgrades);
	
	uintptr_t off4 = dl_baseaddr + find_string("explosive_sniper_shot");
	
	uintptr_t off5 = calc_relative_jump(CTFPlayer_OnTakeDamage_Alive, 0x10c4,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off6 = calc_relative_jump(CTFPlayer_OnTakeDamage_Alive, 0x10f1,
		CTFSniperRifle_ExplosiveHeadShot);
	
	
	size_t check1_base = 0x1000;
	uint8_t check1[] = {
		0x89, 0x04, 0x24,                   // +1000  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off1)                 // +1003  call WeaponID_IsSniperRifle
		0x84, 0xc0,                         // +1008  test al,al
		0x0f, 0x84, 0xd9, 0xf4, 0xff, 0xff, // +100A  je -0xb27
	};
	
	size_t check2_base = 0x1071;
	uint8_t check2[] = {
		0xa1, CONV_LE(off2)                             // +1071  mov eax,g_pGameRules
		0x85, 0xc0,                                     // +1076  test eax,eax
		0x0f, 0x84, 0x6b, 0xf4, 0xff, 0xff,             // +1078  je -0xb95
		0x89, 0x04, 0x24,                               // +107E  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off3)                             // +1081  call CTFGameRules::GameModeUsesUpgrades
		0x84, 0xc0,                                     // +1086  test al,al
		0x0f, 0x84, 0x5b, 0xf4, 0xff, 0xff,             // +1088  je -0xba5
		0x80, 0xbd, 0x60, 0xff, 0xff, 0xff, 0x00,       // +108E  cmp BYTE PTR [ebp-0xa0],0x0
		0x0f, 0x84, 0x4e, 0xf4, 0xff, 0xff,             // +1095  je -0xbb2
		0x8b, 0x8d, 0x64, 0xff, 0xff, 0xff,             // +109B  mov ecx,DWORD PTR [ebp-0x9c]
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +10A1  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +10A9  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off4)           // +10B1  mov DWORD PTR [esp+0x4],"explosive_sniper_shot"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +10B9  mov DWORD PTR [esp],0x0
		0x89, 0x4c, 0x24, 0x08,                         // +10C0  mov DWORD PTR [esp+0x8],ecx
		0xe8, CONV_LE(off5)                             // +10C4  call CAttributeManager::AttribHookValue<int>
		0x85, 0xc0,                                     // +10C9  test eax,eax
		0x0f, 0x84, 0x18, 0xf4, 0xff, 0xff,             // +10CB  je -0xbe8
		0x8b, 0x55, 0x0c,                               // +10D1  mov edx,DWORD PTR [ebp+0xc]
		0x8b, 0x42, 0x40,                               // +10D4  mov eax,DWORD PTR [edx+0x40]
		0x83, 0xf8, 0x33,                               // +10D7  cmp eax,0x33
		0x0f, 0x85, 0xe4, 0x08, 0x00, 0x00,             // +10DA  jne +0x8e4
		0x8b, 0x8d, 0x64, 0xff, 0xff, 0xff,             // +10E0  mov ecx,DWORD PTR [ebp-0x9c]
		0x89, 0x5c, 0x24, 0x08,                         // +10E6  mov DWORD PTR [esp+0x8],ebx
		0x89, 0x3c, 0x24,                               // +10EA  mov DWORD PTR [esp],edi
		0x89, 0x4c, 0x24, 0x04,                         // +10ED  mov DWORD PTR [esp+0x4],ecx
		0xe8, CONV_LE(off6)                             // +10F1  call CTFSniperRifle::ExplosiveHeadShot
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
	/* modify the conditional jump at 0x100a so it jumps to 0x1071 */
	size_t data1_base = 0x100c;
	uint8_t data1[] = {
		0x61, 0x00, 0x00, 0x00
	};
	
	
	func_write(CTFPlayer_OnTakeDamage_Alive,
		data1_base, sizeof(data1), data1);
}
