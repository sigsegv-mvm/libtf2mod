#include "all.h"


DETOUR(eh_sydney_check_uber);
/* disallow the Sydney Sleeper to trigger explosive headshot if the primary
 * target is invulnerable */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFSniperRifle::ExplosiveHeadShot */
	
	return true;
}
