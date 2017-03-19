#include "all.h"


DETOUR(engiebot_check_build_placement);
/*  */


static bool (*trampoline_CObjectSentrygun_StartBuilding)(CObjectSentrygun* this, CBaseEntity*);


static func_t *func_CTFBotMvMEngineerBuildSentryGun_Update;
static func_t *func_CTFBotMvMEngineerBuildTeleportExit_Update;


static bool detour_CObjectSentrygun_StartBuilding(CObjectSentrygun* this, CBaseEntity* ent)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	if (func_owns_addr(caller,
		func_CTFBotMvMEngineerBuildSentryGun_Update)) {
		
		
		
		// set caller's hidden return ptr to a CONTINUE result
		
		// need to devise a way to double-return somehow,
		// without clobbering the callee-save registers
		
		// for now:
		// 
	}
	
	return trampoline_CObjectSentrygun_StartBuilding(this, ent);
}


// let's do a dual patch/detour:
// make the patch 


DETOUR_SETUP
{
	func_CTFBotMvMEngineerBuildSentryGun_Update =
		func_register(CTFBotMvMEngineerBuildSentryGun_Update);
	func_CTFBotMvMEngineerBuildTeleportExit_Update =
		func_register(CTFBotMvMEngineerBuildTeleportExit_Update);
	
	DETOUR_CREATE(CObjectSentrygun_StartBuilding);
	
	return true;
}
