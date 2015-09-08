#include "all.h"


PATCH(perf_attr_premunge_halloween);
/* modify the few attribute references that actually needed
 * GlobalAttrModifier_TFHalloweenAttribHookMunger so that the strings they
 * reference will already have the "__halloween" suffix applied */


static const char *premunged_attrs_halloween[] = {
	"halloween_pumpkin_explosions__halloween",
	"halloween_green_flames__halloween",
	"halloween_death_ghosts__halloween",
};


PATCH_CHECK
{
	void *check1_func = CTFWeaponBaseGrenadeProj_Explode;
	void *check2_func = CTFBaseRocket_Explode;
	void *check3_func = CTFStickBomb_Smack;
	void *check4_func = CTFPlayerShared_ConditionGameRulesThink;
	void *check5_func = CTFPlayer_Event_KilledOther;
	
	
	uintptr_t off_str1 = find_string("server_srv.so",
		"halloween_pumpkin_explosions", true);
	uintptr_t off_str2 = find_string("server_srv.so",
		"halloween_green_flames", true);
	uintptr_t off_str3 = find_string("server_srv.so",
		"halloween_death_ghosts", true);
	
	uintptr_t off1_call1 = CALC_RELJMP(check1_func, 0x016b,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off2_call1 = CALC_RELJMP(check2_func, 0x010b,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off3_call1 = CALC_RELJMP(check3_func, 0x013b,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off4_call1 = CALC_RELJMP(check4_func, 0x2402,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off5_call1 = CALC_RELJMP(check5_func, 0x0509,
		CAttributeManager_AttribHookValue_int);
	
	
	size_t check1_base = 0x0143;
	uint8_t check1[] = {
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +0143  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +014B  mov DWORD PTR [esp+0xc],0x0
		0x89, 0x4c, 0x24, 0x08,                         // +0153  mov DWORD PTR [esp+0x8],ecx
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str1)       // +0157  mov DWORD PTR [esp+0x4],str "halloween_pumpkin_explosions"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +015F  mov DWORD PTR [esp],0x0
		0xe8, CONV_LE(off1_call1)                       // +0166  call CAttributeManager::AttribHookValue<int>
	};
	
	size_t check2_base = 0x00e3;
	uint8_t check2[] = {
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +00E3  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +00EB  mov DWORD PTR [esp+0xc],0x0
		0x89, 0x44, 0x24, 0x08,                         // +00F3  mov DWORD PTR [esp+0x8],eax
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str1)       // +00F7  mov DWORD PTR [esp+0x4],str "halloween_pumpkin_explosions"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +00FF  mov DWORD PTR [esp],0x0
		0xe8, CONV_LE(off2_call1)                       // +0106  call CAttributeManager::AttribHookValue<int>
	};
	
	size_t check3_base = 0x0113;
	uint8_t check3[] = {
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +0113  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +011B  mov DWORD PTR [esp+0xc],0x0
		0x89, 0x5c, 0x24, 0x08,                         // +0123  mov DWORD PTR [esp+0x8],ebx
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str1)       // +0127  mov DWORD PTR [esp+0x4],str "halloween_pumpkin_explosions"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +012F  mov DWORD PTR [esp],0x0
		0xe8, CONV_LE(off3_call1)                       // +0136  call CAttributeManager::AttribHookValue<int>
	};
	
	size_t check4_base = 0x23da;
	uint8_t check4[] = {
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +23DA  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +23E2  mov DWORD PTR [esp+0xc],0x0
		0x89, 0x4c, 0x24, 0x08,                         // +23EA  mov DWORD PTR [esp+0x8],ecx
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str2)       // +23EE  mov DWORD PTR [esp+0x4],str "halloween_green_flames"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +23F6  mov DWORD PTR [esp],0x0
		0xe8, CONV_LE(off4_call1)                       // +23FD  call CAttributeManager::AttribHookValue<int>
	};
	
	size_t check5_base = 0x04e1;
	uint8_t check5[] = {
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +04E1  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +04E9  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str3)       // +04F1  mov DWORD PTR [esp+0x4],str "halloween_death_ghosts"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +04F9  mov DWORD PTR [esp],0x0
		0x89, 0x44, 0x24, 0x08,                         // +0500  mov DWORD PTR [esp+0x8],eax
		0xe8, CONV_LE(off5_call1)                       // +0504  call CAttributeManager::AttribHookValue<int>
	};
	
	
	bool result = true;
	if (!func_verify(check1_func,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(check2_func,
		check2_base, sizeof(check2), check2)) result = false;
	if (!func_verify(check3_func,
		check3_base, sizeof(check3), check3)) result = false;
	if (!func_verify(check4_func,
		check4_base, sizeof(check4), check4)) result = false;
	if (!func_verify(check5_func,
		check5_base, sizeof(check5), check5)) result = false;
	return result;
}


PATCH_APPLY
{
	union {
		const char *ptr;
		uint8_t     bytes[4];
	} str;
	
	
	str.ptr = premunged_attrs_halloween[0];
	func_write(CTFWeaponBaseGrenadeProj_Explode, 0x015b, 4, str.bytes);
	func_write(CTFBaseRocket_Explode,            0x00fb, 4, str.bytes);
	func_write(CTFStickBomb_Smack,               0x012b, 4, str.bytes);
	
	str.ptr = premunged_attrs_halloween[1];
	func_write(CTFPlayerShared_ConditionGameRulesThink, 0x23f2, 4, str.bytes);
	
	str.ptr = premunged_attrs_halloween[2];
	func_write(CTFPlayer_Event_KilledOther, 0x04f5, 4, str.bytes);
}
