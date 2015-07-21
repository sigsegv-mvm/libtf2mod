#include "all.h"


DETOUR(pushallplayersaway_disable);
/* disable the functionality of CTFGameRules::PushAllPlayersAway
 * (used by engiebot behaviors to push players when they spawn and build) */


static unknown_t (*trampoline_CTFGameRules_PushAllPlayersAway)(CTFGameRules* this, Vector const*, float, float, int, CUtlVector*);


static unknown_t detour_CTFGameRules_PushAllPlayersAway(CTFGameRules* this, Vector const* loc, float f1, float f2, int i1, CUtlVector* players)
{
	/* do absolutely nothing */
	return 0;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFGameRules_PushAllPlayersAway);
}
