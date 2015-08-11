#include "all.h"


PATCH(disposable_sentry_enable_health_upgrades);
/* make CBaseObject::GetMaxHealthForLevel always apply attribute
 * "mult_engy_building_health", even for disposable sentries */


PATCH_CHECK
{
	uintptr_t off1 = sendprop_offset("CBaseObject", "m_bDisposableBuilding");
	
	uintptr_t off2 = sendprop_offset("CBaseObject", "m_bMiniBuilding");
	
	
	size_t check1_base = 0x0030;
	uint8_t check1[] = {
		0x80, 0xbb, CONV_LE(off1) 0x00, // +0030  cmp BYTE PTR [ebx+m_bDisposableBuilding],0x0
		0x74, 0x27,                     // +0037  je +0x27
		0x80, 0xbb, CONV_LE(off2) 0x00, // +0039  cmp BYTE PTR [ebx+m_bMiniBuilding],0x0
		0x74, 0x58,                     // +0040  je +0x58
	};
	
	
	bool result = true;
	if (!func_verify(CBaseObject_GetMaxHealthForCurrentLevel,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* always jump to the block that applies the building health attr */
	size_t data1_base = 0x0030;
	uint8_t data1[] = {
		0xe9, 0x2b, 0x00, 0x00, 0x00, // +0030  jmp +0x2b
		0x90, 0x90, 0x90, 0x90, 0x90, // +0035  nop nop nop nop nop
		0x90, 0x90, 0x90, 0x90, 0x90, // +003A  nop nop nop nop nop
		0x90, 0x90, 0x90,             // +003F  nop nop nop
	};
	
	
	func_write(CBaseObject_GetMaxHealthForCurrentLevel,
		data1_base, sizeof(data1), data1);
}
