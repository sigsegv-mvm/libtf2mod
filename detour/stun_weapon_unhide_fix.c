#include "all.h"


DETOUR(stun_weapon_unhide_fix);
/* players entering full-stun have their weapons hidden; but when they leave
 * full-stun, their weapons are not unhidden
 * 
 * fix this by hooking CTFPlayerShared::OnRemoveStunned, checking if the player
 * is coming out of control stun, and unhiding the weapon if so */


static void (*trampoline_CTFPlayerShared_OnRemoveStunned)(CTFPlayerShared* this);


static void detour_CTFPlayerShared_OnRemoveStunned(CTFPlayerShared* this)
{
	//int *m_iStunIndex = prop_CTFPlayerShared_m_iStunIndex(this);
	int *m_iStunFlags = prop_CTFPlayerShared_m_iStunFlags(this);
	
	pr_info("CTFPlayerShared::OnRemoveStunned\n");
	pr_debug(
		"  this:         %08x\n"
	//	"  m_iStunIndex: %08x\n"
		"  m_iStunFlags: %08x\n",
		(uintptr_t)this, /**m_iStunIndex,*/ *m_iStunFlags);
	
	/* check if the player was just in a state of control stun */
	if (/**m_iStunIndex >= 0 &&*/
		(*m_iStunFlags & TF_STUNFLAG_BONKSTUCK) != 0) {
		CBaseCombatWeapon* weapon = CTFPlayerShared_GetActiveTFWeapon(this);
		pr_debug("  weapon:       %08x\n", (uintptr_t)weapon);
		if (weapon != NULL) {
			vcall_CBaseCombatWeapon_SetWeaponVisible(weapon, true);
		}
	}
	
	trampoline_CTFPlayerShared_OnRemoveStunned(this);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayerShared_OnRemoveStunned);
	
	return true;
}
