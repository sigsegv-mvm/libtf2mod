#include "all.h"


DETOUR(engiebot_nonsolid_buildings);
/*  */


#if 0
static void (*trampoline_CObjectSentrygun_Spawn)(CObjectSentrygun* this);
static void (*trampoline_CObjectTeleporter_Spawn)(CObjectTeleporter* this);


static func_t *func_CTFBotMvMEngineerBuildSentryGun_Update;
static func_t *func_CTFBotMvMEngineerBuildTeleportExit_Update;


static void detour_CObjectSentrygun_Spawn(CObjectSentrygun* this)
{
	trampoline_CObjectSentrygun_Spawn(this);
	
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	if (func_owns_addr(caller,
		func_CTFBotMvMEngineerBuildSentryGun_Update)) {
		CBaseObject_SetSolidToPlayers(this, SOLID_TO_PLAYER_NO, true);
	}
}

static void detour_CObjectTeleporter_Spawn(CObjectTeleporter* this)
{
	trampoline_CObjectTeleporter_Spawn(this);
	
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	if (func_owns_addr(caller,
		func_CTFBotMvMEngineerBuildTeleportExit_Update)) {
		CBaseObject_SetSolidToPlayers(this, SOLID_TO_PLAYER_NO, true);
	}
}
#endif


static bool (*trampoline_CBaseObject_ShouldCollide)(CBaseObject* this, int, int);


static bool detour_CBaseObject_ShouldCollide(CBaseObject* this, int collisionGroup, int contentsMask)
{
	if (collisionGroup == COLLISION_GROUP_PLAYER_MOVEMENT) {
		if (CTFGameRules_IsPVEModeActive(*g_pGameRules)) {
			if (CBaseEntity_GetTeamNumber(this) == TF_TEAM_BLUE) {
				return false;
			}
		}
	}
	
	return trampoline_CBaseObject_ShouldCollide(this, collisionGroup, contentsMask);
}


DETOUR_SETUP
{
	/*func_CTFBotMvMEngineerBuildSentryGun_Update =
		func_register(CTFBotMvMEngineerBuildSentryGun_Update);
	func_CTFBotMvMEngineerBuildTeleportExit_Update =
		func_register(CTFBotMvMEngineerBuildTeleportExit_Update);
	
	DETOUR_CREATE(CObjectSentrygun_Spawn);
	DETOUR_CREATE(CObjectTeleporter_Spawn);*/
	
	DETOUR_CREATE(CBaseObject_ShouldCollide);
	
	return true;
}
