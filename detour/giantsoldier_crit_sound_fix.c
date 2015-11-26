#include "all.h"


DETOUR(giantsoldier_crit_sound_fix);
/* fix the sound "MvM.GiantSoldierRocketShootCrit" not being precached */


static void (*trampoline_CTFRocketLauncher_Precache)(CTFRocketLauncher* this);


static ConVar cvar_sigsegv_giantsoldier_crit_precache_fix;


static void detour_CTFRocketLauncher_Precache(CTFRocketLauncher* this)
{
	trampoline_CTFRocketLauncher_Precache(this);
	
	if (ConVar_GetInt(&cvar_sigsegv_giantsoldier_crit_precache_fix) != 0) {
		CBaseEntity_PrecacheScriptSound("MvM.GiantSoldierRocketShootCrit");
	}
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_sigsegv_giantsoldier_crit_precache_fix,
		"sigsegv_detour_giantsoldier_crit_sound_fix", "0", FCVAR_NOTIFY,
		"Detour: fix the sound \"MvM.GiantSoldierRocketShootCrit\" not being precached");
	
	DETOUR_CREATE(CTFRocketLauncher_Precache);
	
	return true;
}
