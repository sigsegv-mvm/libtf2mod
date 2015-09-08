#include "all.h"


DETOUR(yer_nerf_disable);
/* remove the bot-specific Your Eternal Reward functionality nerfs */


static bool (*trampoline_CBasePlayer_IsBot)(CBasePlayer* this);
static bool (*trampoline_NextBotPlayer_CTFPlayer_IsBot)(CBasePlayer* this);


static func_t *func_CTFKnife_PrimaryAttack;


static bool detour_CBasePlayer_IsBot(CBasePlayer* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	
	/* lie to CTFKnife::PrimaryAttack saying the victim is never a bot */
	if (func_owns_addr(caller,
		func_CTFKnife_PrimaryAttack)) {
		//pr_debug("CBasePlayer::IsBot called by CTFKnife::PrimaryAttack; "
		//	"returning FALSE\n");
		return false;
	}
	
	
	return trampoline_CBasePlayer_IsBot(this);
}

static bool detour_NextBotPlayer_CTFPlayer_IsBot(CBasePlayer* this)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	
	/* lie to CTFKnife::PrimaryAttack saying the victim is never a bot */
	if (func_owns_addr(caller,
		func_CTFKnife_PrimaryAttack)) {
		//pr_debug("NextBotPlayer<CTFPlayer>::IsBot "
		//	"called by CTFKnife::PrimaryAttack; returning FALSE\n");
		return false;
	}
	
	
	return trampoline_NextBotPlayer_CTFPlayer_IsBot(this);
}


DETOUR_SETUP
{
	func_CTFKnife_PrimaryAttack =
		func_register(CTFKnife_PrimaryAttack);
	
	
	DETOUR_CREATE(CBasePlayer_IsBot);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_IsBot);
}
