#include "all.h"


PATCH(engiebot_nopush_telespawn);
/* when engineer bots teleport in, don't push red players away */


static func_t *func1;


PATCH_INIT
{
	/* CTFBotMvMEngineerTeleportSpawn::Update(CTFBot*, float) */
	func1 = func_register(
		"_ZN30CTFBotMvMEngineerTeleportSpawn6UpdateEP6CTFBotf");
}


PATCH_CHECK
{
	symbol_t sym1;
	symtab_func_name(&sym1,
		"_ZN12CTFGameRules18PushAllPlayersAwayERK6VectorffiP10CUtlVectorIP9CTFPlayer10CUtlMemoryIS5_iEE");
	uintptr_t off1 = calc_relative_jump(func1, 0x010d, dl_baseaddr + sym1.addr);
	
	
	size_t check1_base = 0x00e6;
	uint8_t check1[] = {
		0xc7, 0x44, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00, // +00E6  mov DWORD PTR [esp+0x14],0x0
		0xc7, 0x44, 0x24, 0x10, 0x02, 0x00, 0x00, 0x00, // +00EE  mov DWORD PTR [esp+0x10],0x2
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0xfa, 0x43, // +00F6  mov DWORD PTR [esp+0xc],0x43fa0000
		0xc7, 0x44, 0x24, 0x08, 0x00, 0x00, 0xc8, 0x43, // +00FE  mov DWORD PTR [esp+0x8],0x43c80000
		0x89, 0x5c, 0x24, 0x04,                         // +0106  mov DWORD PTR [esp+0x4],ebx
		0x89, 0x04, 0x24,                               // +010A  mov DWORD PTR [esp],eax
		0xe8, CONV_LE(off1)                             // +010D  call CTFGameRules::PushAllPlayersAway
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the call to CTFGameRules::PushAllPlayersAway */
	func_write_nop(func1, 0x010d, 5);
}
