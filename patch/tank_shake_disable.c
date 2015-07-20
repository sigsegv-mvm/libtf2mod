#include "all.h"


PATCH(tank_shake_disable);
/* disable screen shake caused by being near the tank */


static func_t *func1;


PATCH_INIT
{
	/* CTFTankBoss::TankBossThink() */
	func1 = func_register(
		"_ZN11CTFTankBoss13TankBossThinkEv");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_func_name(&sym1,
		"_Z16UTIL_ScreenShakeRK6Vectorffff14ShakeCommand_tb");
	uintptr_t off1 = calc_relative_jump(func1, 0x0aac, dl_baseaddr + sym1.addr);
	
	
	size_t check1_base = 0x0a94;
	uint8_t check1[] = {
		0xc7, 0x44, 0x24, 0x08, 0x00, 0x00, 0xa0, 0x40, // +0A94  mov DWORD PTR [esp+0x8],0x40a00000
		0xc7, 0x44, 0x24, 0x04, 0x00, 0x00, 0x00, 0x40, // +0A9C  mov DWORD PTR [esp+0x4],0x40000000
		0x89, 0x04, 0x24,                               // +0AA4  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off1)                             // +0AA7  call UTIL_ScreenShake
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the function call */
	func_write_nop(func1, 0x0a94, 24);
}
