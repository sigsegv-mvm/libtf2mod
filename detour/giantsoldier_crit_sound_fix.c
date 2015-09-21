#include "all.h"


DETOUR(giantsoldier_crit_sound_fix);
/* fix the sound "MvM.GiantSoldierRocketShootCrit" not being precached */


static void (*trampoline_CTFRocketLauncher_Precache)(CTFRocketLauncher* this);


static void detour_CTFRocketLauncher_Precache(CTFRocketLauncher* this)
{
	trampoline_CTFRocketLauncher_Precache(this);
	
	CBaseEntity_PrecacheScriptSound("MvM.GiantSoldierRocketShootCrit");
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFRocketLauncher_Precache);
	
	return true;
}
