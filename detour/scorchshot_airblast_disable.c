#include "all.h"


DETOUR(scorchshot_airblast_disable);
/* limit the new Scorch Shot's annoying new ability to airblast robots all over
 * the place to non-MiniBosses only */


static unknown_t (*trampoline_CTFPlayer_ApplyAirBlastImpulse)(CTFPlayer* this, Vector const*);


static unknown_t detour_CTFPlayer_ApplyAirBlastImpulse(CTFPlayer* this, Vector const* vec)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* when a flare tries to airblast someone, ignore it */
	if (func_owns_addr(CTFProjectile_Flare_Explode, caller) &&
		CTFGameRules_IsPVEModeActive(*g_pGameRules) &&
		vcall_CBasePlayer_IsBot(this) &&
		CTFPlayer_IsMiniBoss(this)) {
		return 0;
	}
	
	return trampoline_CTFPlayer_ApplyAirBlastImpulse(this, vec);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_ApplyAirBlastImpulse);
}
