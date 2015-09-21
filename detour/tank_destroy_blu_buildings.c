#include "all.h"


DETOUR(tank_destroy_blu_buildings);
/* allow CTFTankBoss to do damage to friendly buildings that it runs over */


static bool (*trampoline_CBaseEntity_InSameTeam)(CBaseEntity* this, CBaseEntity*);


static func_t *func_CBaseObject_OnTakeDamage;


static bool detour_CBaseEntity_InSameTeam(CBaseEntity* this, CBaseEntity* that)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	/* if the damager is a CTFTankBoss, then lie that the building is always on
	 * the opposite team, regardless of which team it's actually on */
	if (CTFGameRules_IsPVEModeActive(*g_pGameRules) &&
		func_owns_addr(caller1, func_CBaseObject_OnTakeDamage) &&
		DYNAMIC_CAST(that, CBaseEntity, CTFTankBoss) != NULL) {
		return false;
	} else {
		return trampoline_CBaseEntity_InSameTeam(this, that);
	}
}


DETOUR_SETUP
{
	func_CBaseObject_OnTakeDamage =
		func_register(CBaseObject_OnTakeDamage);
	
	DETOUR_CREATE(CBaseEntity_InSameTeam);
	
	return true;
}
