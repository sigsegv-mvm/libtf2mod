#include "all.h"


DETOUR(pushallplayersaway_disable);
/* disable the functionality of CTFGameRules::PushAllPlayersAway
 * (used by engiebot behaviors to push players when they spawn and build) */


static void (*trampoline_CTFGameRules_PushAllPlayersAway)(CTFGameRules* this, Vector const*, float, float, int, CUtlVector*);


static void detour_CTFGameRules_PushAllPlayersAway(CTFGameRules* this, Vector const* loc, float f1, float f2, int i1, CUtlVector* players)
{
	/* do absolutely nothing */
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFGameRules_PushAllPlayersAway);
	
	return true;
}
