#include "all.h"


DETOUR(scorchshot_airblast_disable);
/* limit the new Scorch Shot's annoying new ability to airblast robots all over
 * the place to non-MiniBosses only */


static unknown_t (*trampoline_CTFPlayer_ApplyAirBlastImpulse)(CTFPlayer* this, Vector const*);


static func_t *func_CTFProjectile_Flare_Explode;


static unknown_t detour_CTFPlayer_ApplyAirBlastImpulse(CTFPlayer* this, Vector const* vec)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* when a flare tries to airblast a MiniBoss robot, do nothing */
	if (func_owns_addr(caller,
		func_CTFProjectile_Flare_Explode) &&
		CTFGameRules_IsPVEModeActive(*g_pGameRules) &&
		vcall_CBasePlayer_IsBot(this) &&
		CTFPlayer_IsMiniBoss(this)) {
		return 0;
	}
	
	return trampoline_CTFPlayer_ApplyAirBlastImpulse(this, vec);
}


DETOUR_SETUP
{
	func_CTFProjectile_Flare_Explode =
		func_register(CTFProjectile_Flare_Explode);
	
	
	DETOUR_CREATE(CTFPlayer_ApplyAirBlastImpulse);
}
