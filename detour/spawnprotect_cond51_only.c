#include "all.h"


DETOUR(spawnprotect_cond51_only);
/* remove conds 5 and 8 from robot spawn protection, leaving only cond 51 */


static void (*trampoline_CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);


static void detour_CTFPlayerShared_AddCond(CTFPlayerShared* this, ETFCond cond, float duration, CBaseEntity* ent)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* ignore AddCond(5) and AddCond(8) from CTFBotMainAction::Update */
	if (func_owns_addr(CTFBotMainAction_Update, caller)) {
		if (cond == TFCOND_UBERCHARGED ||
			cond == TFCOND_UBERCHARGEFADING) {
			return;
		}
	}
	
	trampoline_CTFPlayerShared_AddCond(this, cond, duration, ent);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayerShared_AddCond);
}
