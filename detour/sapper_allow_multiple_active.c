#include "all.h"


DETOUR(sapper_allow_multiple_active);
/* remove the MvM-specific limitation that prevents spies from deploying their
 * sapper if a sapper object is already active somewhere on the map */


static int (*trampoline_CTFPlayer_GetNumObjects)(CTFPlayer* this, int, int);


static func_t *func_CTFPlayer_CanBuild;


static int detour_CTFPlayer_GetNumObjects(CTFPlayer* this, int type, int subtype)
{
	/* lie to CTFPlayer::CanBuild that we have no active sappers so that it will
	 * allow us to build another one */
	if (type == TFOBJECT_SAPPER &&
		CTFGameRules_IsPVEModeActive(*g_pGameRules)) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		
		if (func_owns_addr(caller1,
			func_CTFPlayer_CanBuild)) {
			return 0;
		}
	}
	
	return trampoline_CTFPlayer_GetNumObjects(this, type, subtype);
}


DETOUR_SETUP
{
	func_CTFPlayer_CanBuild =
		func_register(CTFPlayer_CanBuild);
	
	/* the CBasePlayer::IsBot detour is actually implemented in the shared
	 * detour for CBasePlayer::IsBot */
	
	DETOUR_CREATE(CTFPlayer_GetNumObjects);
	
	return true;
}
