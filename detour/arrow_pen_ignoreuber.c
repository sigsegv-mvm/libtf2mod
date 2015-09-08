#include "all.h"


DETOUR(arrow_pen_ignoreuber);
/* prevent arrow projectiles with projectile penetration from breaking on uber players */


static bool (*trampoline_CTFPlayerShared_IsInvulnerable)(CTFPlayerShared* this);


static func_t *func_CTFProjectile_Arrow_StrikeTarget_clone321;


static bool detour_CTFPlayerShared_IsInvulnerable(CTFPlayerShared* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* lie to the arrow projectile that we are never invuln */
	if (func_owns_addr(caller,
		func_CTFProjectile_Arrow_StrikeTarget_clone321)) {
		return false;
	}
	
	return trampoline_CTFPlayerShared_IsInvulnerable(this);
}


DETOUR_SETUP
{
	func_CTFProjectile_Arrow_StrikeTarget_clone321 =
		func_register(CTFProjectile_Arrow_StrikeTarget_clone321);
	
	
	DETOUR_CREATE(CTFPlayerShared_IsInvulnerable);
}
