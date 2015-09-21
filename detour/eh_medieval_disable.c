#include "all.h"


DETOUR(eh_medieval_disable);
/* disallow explosive headshot in Medieval Mode */


static void (*trampoline_CTFSniperRifle_ExplosiveHeadShot)(CTFSniperRifle* this, CTFPlayer*, CTFPlayer*);


static void detour_CTFSniperRifle_ExplosiveHeadShot(CTFSniperRifle* this, CTFPlayer* p1, CTFPlayer* p2)
{
	/* only call CTFSniperRifle::ExplosiveHeadShot if
	 * g_pGameRules->m_bPlayingMedieval is false */
	if (!*prop_CTFGameRules_m_bPlayingMedieval(*g_pGameRules)) {
		trampoline_CTFSniperRifle_ExplosiveHeadShot(this, p1, p2);
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFSniperRifle_ExplosiveHeadShot);
	
	return true;
}
