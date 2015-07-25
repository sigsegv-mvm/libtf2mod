#include "all.h"


PATCH(eh_unrestrict_projtype);
/* allow explosive headshot on weapons with projectile type other than bullet */


PATCH_CHECK
{
	size_t check1_base = 0x0b2d;
	uint8_t check1[] = {
		0x8b, 0x55, 0xcc,                   // +0B2D  mov edx,DWORD PTR [ebp-0x34]
		0x8b, 0x02,                         // +0B30  mov eax,DWORD PTR [edx]
		0x89, 0x14, 0x24,                   // +0B32  mov DWORD PTR [esp],edx
		0xff, 0x90, 0x14, 0x07, 0x00, 0x00, // +0B35  call DWORD PTR [eax+0x714]
		0x83, 0xe8, 0x01,                   // +0B3B  sub eax,0x1
		0x0f, 0x94, 0xc3,                   // +0B3E  sete bl
		0xe9, 0x3a, 0xf5, 0xff, 0xff,       // +0B41  jmp -0xa16
	};
	
	
	bool result = true;
	if (!func_verify(CTFGameRules_CanUpgradeWithAttrib,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	size_t data1_base = 0x0b2d;
	uint8_t data1[] = {
		0xb8, 0x01, 0x00, 0x00, 0x00, // +0B2D  mov eax,0x1
		0x90, 0x90, 0x90, 0x90, 0x90, // +0B32  nop nop nop nop nop
		0x90, 0x90, 0x90, 0x90,       // +0B37  nop nop nop nop
	};
	
	
	/* replace the function call with mov eax,0x00000001 and some NOP's */
	func_write(CTFGameRules_CanUpgradeWithAttrib,
		data1_base, sizeof(data1), data1);
}
