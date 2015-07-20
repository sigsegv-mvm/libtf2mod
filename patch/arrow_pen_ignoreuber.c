#include "all.h"


PATCH(arrow_pen_ignoreuber);
/* prevent arrow projectiles with projectile penetration from breaking on uber players */


static func_t *func1;


PATCH_INIT
{
	/* CTFProjectileArrow::StrikeTarget(mstudiobbox_t*, CBaseEntity*) [clone .part.323] */
	func1 = func_register(
		"_ZN19CTFProjectile_Arrow12StrikeTargetEP13mstudiobbox_tP11CBaseEntity.part.323");
}


PATCH_CHECK
{
	size_t check1_base = 0x0020;
	uint8_t check1[] = {
		0x8b, 0x01,                         // +0020  mov eax,DWORD PTR [ecx]
		0x89, 0x0c, 0x24,                   // +0022  mov DWORD PTR [esp],ecx
		0xff, 0x90, 0x44, 0x01, 0x00, 0x00, // +0025  call DWORD PTR [eax+0x144]
		0x84, 0xc0,                         // +002B  test al,al
		0x0f, 0x85, 0xfd, 0x04, 0x00, 0x00, // +002D  jne +0x4df
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the jump when invuln is detected */
	func_write_nop(func1, 0x002d, 6);
}
