#include "all.h"


DETOUR(shared_CTFSniperRifle_ExplosiveHeadShot);
/* shared detour for CTFSniperRifle::ExplosiveHeadShot */


static void (*trampoline_CTFSniperRifle_ExplosiveHeadShot)(CTFSniperRifle* this, CTFPlayer*, CTFPlayer*);


static func_t *func_CTFPlayer_OnTakeDamage_Alive;


static void detour_CTFSniperRifle_ExplosiveHeadShot(CTFSniperRifle* this, CTFPlayer* sniper, CTFPlayer* victim)
{
	if (detour_eh_medieval_disable.ok) {
		/* only call CTFSniperRifle::ExplosiveHeadShot if
		 * g_pGameRules->m_bPlayingMedieval is false */
		if (*prop_CTFGameRules_m_bPlayingMedieval(*g_pGameRules)) {
			return;
		}
	}
	
	
	if (detour_eh_recursive_fix.ok) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		uintptr_t caller1_frame = (uintptr_t)__builtin_frame_address(1);
		
		if (func_owns_addr(caller1,
			func_CTFPlayer_OnTakeDamage_Alive)) {
			const CTakeDamageInfo* info =
				*(CTakeDamageInfo **)(caller1_frame + 0xc);
			
			/* don't allow CTFSniperRifle::ExplosiveHeadShot to be triggered by
			 * bleed damage */
			if (info->m_iDamageCustom == TF_CUSTOM_BLEEDING) {
				return;
			}
		}
	}
	
	
	if (detour_eh_sydney_check_uber.ok) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		
		if (func_owns_addr(caller1,
			func_CTFPlayer_OnTakeDamage_Alive)) {
			CTFPlayerShared* shared = prop_CTFPlayer_m_Shared(victim);
			
			/* don't allow CTFSniperRifle::ExplosiveHeadShot to be triggered by
			 * the Sydney Sleeper if the primary target is invulnerable */
			if (CTFPlayerShared_IsInvulnerable(shared)) {
				return;
			}
		}
	}
	
	
	trampoline_CTFSniperRifle_ExplosiveHeadShot(this, sniper, victim);
}


DETOUR_SETUP
{
	func_CTFPlayer_OnTakeDamage_Alive =
		func_register(CTFPlayer_OnTakeDamage_Alive);
	
	DETOUR_CREATE(CTFSniperRifle_ExplosiveHeadShot);
	
	return true;
}
