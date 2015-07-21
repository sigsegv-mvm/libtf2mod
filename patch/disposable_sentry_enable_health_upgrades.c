#include "all.h"


PATCH(disposable_sentry_enable_health_upgrades);
/* make building health upgrades increase disposable mini-sentry health */


PATCH_INIT
{
	
}


PATCH_CHECK
{
	size_t check1_base = 0x0030;
	uint8_t check1[] = {
		0x80, 0xbb, 0x0f, 0x0a, 0x00, 0x00, 0x00, // +0030  cmp BYTE PTR [ebx+0xa0f],0x0
		0x74, 0x27,                               // +0037  je +0x27
		0x80, 0xbb, 0x0e, 0x0a, 0x00, 0x00, 0x00, // +0039  cmp BYTE PTR [ebx+0xa0e],0x0
		0x74, 0x58,                               // +0040  je +0x58
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
