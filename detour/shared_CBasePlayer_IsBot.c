#include "all.h"


DETOUR(shared_CBasePlayer_IsBot);
/* shared detour for CBasePlayer::IsBot */


static bool (*trampoline_CBasePlayer_IsBot)(CBasePlayer* this);


static func_t *func_CTFKnife_PrimaryAttack;
static func_t *func_CObjectSapper_Spawn;


static bool detour_CBasePlayer_IsBot(CBasePlayer* this)
{
	if (detour_yer_nerf_disable.ok) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		
		/* lie to CTFKnife::PrimaryAttack saying the victim is never a bot */
		if (func_owns_addr(caller1,
			func_CTFKnife_PrimaryAttack)) {
			//pr_debug("CBasePlayer::IsBot called by CTFKnife::PrimaryAttack; "
			//	"returning FALSE\n");
			return false;
		}
	}
	
	
	if (detour_sapper_allow_multiple_active.ok) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		
		/* lie to CObjectSapper::Spawn that we are a bot so that it won't set
		 * the builder flag to make us switch away from the sapper after
		 * sapping */
		if (func_owns_addr(caller1,
			func_CObjectSapper_Spawn)) {
			return true;
		}
	}
	
	
	return trampoline_CBasePlayer_IsBot(this);
}


DETOUR_SETUP
{
	func_CTFKnife_PrimaryAttack =
		func_register(CTFKnife_PrimaryAttack);
	func_CObjectSapper_Spawn =
		func_register(CObjectSapper_Spawn);
	
	DETOUR_CREATE(CBasePlayer_IsBot);
	
	return true;
}
