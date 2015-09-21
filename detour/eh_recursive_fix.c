#include "all.h"


DETOUR(eh_recursive_fix);
/* check for bleed damage and disallow it from causing explosive headshots */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFSniperRifle::ExplosiveHeadShot */
	
	return true;
}
