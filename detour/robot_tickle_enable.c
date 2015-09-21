#include "all.h"


DETOUR(robot_tickle_enable);
/* allow non-MiniBoss robots to be tickled by the Holiday Punch */


static bool (*trampoline_CTFPlayer_CanBeForcedToLaugh)(CTFPlayer* this);


static bool detour_CTFPlayer_CanBeForcedToLaugh(CTFPlayer* this)
{
	/* only return false if the player is a MiniBoss MvM bot */
	return !(CTFGameRules_IsPVEModeActive(*g_pGameRules) &&
		vcall_CBasePlayer_IsBot(this) &&
		CTFPlayer_IsMiniBoss(this));
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CanBeForcedToLaugh);
	
	return true;
}
