#include "all.h"


PATCH(bot_revivemarker_enable);
/* allow red team bots to drop revive markers */


PATCH_CHECK
{
	uintptr_t off1 = vtable_find_offset("_ZTV11CBasePlayer",
		CBasePlayer_IsBot);
	
	
	size_t check1_base = 0x0a82;
	uint8_t check1[] = {
		0x8b, 0x03,               // +0A82  mov eax,DWORD PTR [ebx]
		0x89, 0x1c, 0x24,         // +0A84  mov DWORD PTR [esp],ebx
		0xff, 0x90, CONV_LE(off1) // +0A87  call DWORD PTR [eax+IsBot] CBasePlayer::IsBot() const
		0x84, 0xc0,               // +0A8D  test al,al
		0x75, 0x4f,               // +0A8F  jne +0x4f
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_Event_Killed,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the conditional jump based on IsBot check */
	func_write_nop(CTFPlayer_Event_Killed, 0x0a8f, 2);
}
