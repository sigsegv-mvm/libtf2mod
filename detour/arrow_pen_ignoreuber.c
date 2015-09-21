#include "all.h"


DETOUR(arrow_pen_ignoreuber);
/* prevent arrow projectiles with projectile penetration from breaking on uber
 * players */


static bool (*trampoline_CTFPlayerShared_IsInvulnerable)(CTFPlayerShared* this);


static func_t *func_CTFProjectile_Arrow_StrikeTarget;


static bool detour_CTFPlayerShared_IsInvulnerable(CTFPlayerShared* this)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller2 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(1));
	
	/* lie to the arrow projectile that we are never invuln */
	if (func_owns_addr(caller1,
		func_CTFProjectile_Arrow_StrikeTarget) ||
		func_owns_addr(caller2,
		func_CTFProjectile_Arrow_StrikeTarget)) {
		return false;
	}
	
	return trampoline_CTFPlayerShared_IsInvulnerable(this);
}


DETOUR_SETUP
{
	func_CTFProjectile_Arrow_StrikeTarget =
		func_register(CTFProjectile_Arrow_StrikeTarget);
	
	DETOUR_CREATE(CTFPlayerShared_IsInvulnerable);
	
	return true;
}
