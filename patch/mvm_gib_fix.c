#include "all.h"


PATCH(mvm_gib_fix);
/* remove MvM-specific logic (that overrides CTFRagdoll::m_bGib) from
 * CTFPlayer::CreateRagdollEntity */

/* Not only is this block of logic completely redundant (CTFBot::ShouldGib was
 * added specifically to make sure that giants gib and non-giants don't gib),
 * it is also responsible for breaking all gibs in MvM mode, in addition to
 * causing the "floating cosmetics while spectating" glitch.
 * 
 * My best guess here is that since CTFPlayer::Event_Killed calls
 * this->ShouldGib() and then passes it to CTFPlayer::CreateRagdollEntity,
 * it may also be doing other things with the result of ShouldGib(); and if
 * CTFPlayer::CreateRagdollEntity messes with CTFRagdoll::m_bGib behind its
 * back, then inconsistencies will happen. */


PATCH_CHECK
{
	uintptr_t off1 = (uintptr_t)g_pGameRules;
	
	//uintptr_t off2 = sendprop_offset("CTFGameRules",
	//	"m_bPlayingMannVsMachine");
	uintptr_t off2 = 0x99a;
	
	
	size_t check1_base = 0x008d;
	uint8_t check1[] = {
		0xa1, CONV_LE(off1) // +008D  mov eax,ds:g_pGameRules
		0x85, 0xc0,         // +0092  test eax,eax
		0x74,               // +0094  je <byte:dontcare>
	};
	
	size_t check2_base = 0x0096;
	uint8_t check2[] = {
		0x80, 0xb8, CONV_LE(off2) 0x00, // +0096  cmp BYTE PTR [eax+m_bPlayingMannVsMachine],0x0
		0x0f, 0x85,                     // +009D  jne <dword:dontcare>
	};
	
	
	bool result = true;
	if (!func_verify(CTFPlayer_CreateRagdollEntity,
		check1_base, sizeof(check1), check1)) result = false;
	if (!func_verify(CTFPlayer_CreateRagdollEntity,
		check2_base, sizeof(check2), check2)) result = false;
	return result;
}


PATCH_APPLY
{
	/* remove the relative jump for MvM-specific gibbing logic */
	func_write_nop(CTFPlayer_CreateRagdollEntity,
		0x009d, 6);
}
