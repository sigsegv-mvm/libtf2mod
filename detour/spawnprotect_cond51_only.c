#include "all.h"


DETOUR(spawnprotect_cond51_only);
/* remove conds 5 and 8 from robot spawn protection, leaving only cond 51 */


static void (*trampoline_CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);


static func_t *func_CTFBotMainAction_Update;


static void detour_CTFPlayerShared_AddCond(CTFPlayerShared* this, ETFCond cond, float duration, CBaseEntity* ent)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* ignore AddCond(5) and AddCond(8) from CTFBotMainAction::Update */
	if (func_owns_addr(caller,
		func_CTFBotMainAction_Update)) {
		if (cond == TF_COND_INVULNERABLE ||
			cond == TF_COND_INVULNERABLE_WEARINGOFF) {
			return;
		}
	}
	
	trampoline_CTFPlayerShared_AddCond(this, cond, duration, ent);
}


DETOUR_SETUP
{
	func_CTFBotMainAction_Update =
		func_register(CTFBotMainAction_Update);
	
	DETOUR_CREATE(CTFPlayerShared_AddCond);
	
	return true;
}
