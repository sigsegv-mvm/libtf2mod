#include "all.h"


PATCH(perf_attr_premunge_mvm);
/* modify the few attribute references that actually needed
 * GlobalAttrModifier_MvMAttribHookMunger so that the strings they reference
 * will already have the "__mvm" suffix applied */


static const char *premunged_attrs_mvm[] = {
	"bot_custom_jump_particle__mvm",
	"attack_not_cancel_charge__mvm",
};


PATCH_CHECK
{
	void *check1_func = CTFBotLocomotion_Jump;
	void *check2_func = CTFWearableDemoShield_EndSpecialAction;
	void *check3_func = CTFWearableDemoShield_EndSpecialAction;
	
	
	uintptr_t off_str1 = find_string("server_srv.so",
		"bot_custom_jump_particle", true);
	uintptr_t off_str2 = find_string("server_srv.so",
		"attack_not_cancel_charge", true);
	
	uintptr_t off1_call1 = CALC_RELJMP(check1_func, 0x00ab,
		CAttributeManager_AttribHookValue_int);
	
	uintptr_t off2_call1 = CALC_RELJMP(check2_func, 0x00fe,
		AllocPooledString_StaticConstantStringPointer);
	
	
	size_t check1_base = 0x0083;
	uint8_t check1[] = {
		0xc7, 0x44, 0x24, 0x10, 0x01, 0x00, 0x00, 0x00, // +0083  mov DWORD PTR [esp+0x10],0x1
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +008B  mov DWORD PTR [esp+0xc],0x0
		0x89, 0x5c, 0x24, 0x08,                         // +0093  mov DWORD PTR [esp+0x8],ebx
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str1)       // +0097  mov DWORD PTR [esp+0x4],str "bot_custom_jump_particle"
		0xc7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00,       // +009F  mov DWORD PTR [esp],0x0
		0xe8, CONV_LE(off1_call1)                       // +00A6  call CAttributeManager::AttribHookValue<int>
	};
	
	size_t check2_base = 0x00ee;
	uint8_t check2[] = {
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off_str2) // +00EE  mov DWORD PTR [esp+0x4],str "attack_not_cancel_charge"
		0x89, 0x04, 0x24,                         // +00F6  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off2_call1)                 // +00F9  call AllocPooledString_StaticConstantStringPointer
	};
	
	size_t check3_base = 0x0185;
	uint8_t check3[] = {
		0xc7, 0x04, 0x24, CONV_LE(off_str2) // +0185  mov DWORD PTR [esp],str "attack_not_cancel_charge"
		0xff, 0x54, 0x38, 0x04,             // +018C  call DWORD PTR [eax+edi*1+0x4]
	};
	
	
	bool result = true;
	if (!func_verify(check1_func,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(check2_func,
		check2_base, sizeof(check2), check2)) result = false;
	if (!func_verify(check3_func,
		check3_base, sizeof(check3), check3)) result = false;
	return result;
}


PATCH_APPLY
{
	union {
		const char *ptr;
		uint8_t     bytes[4];
	} str;
	
	
	str.ptr = premunged_attrs_mvm[0];
	func_write(CTFBotLocomotion_Jump, 0x009b, 4, str.bytes);
	
	str.ptr = premunged_attrs_mvm[1];
	func_write(CTFWearableDemoShield_EndSpecialAction, 0x00f2, 4, str.bytes);
	func_write(CTFWearableDemoShield_EndSpecialAction, 0x0188, 4, str.bytes);
}
