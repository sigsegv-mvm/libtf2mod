#include "all.h"


DETOUR(eh_medieval_disable);
/* disallow explosive headshot in Medieval Mode */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFSniperRifle::ExplosiveHeadShot */
	
	return true;
}
