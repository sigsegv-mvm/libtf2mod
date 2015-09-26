#include "all.h"


DETOUR(nextprimaryattack_unalias);
/* calculate m_flNextPrimaryAttack based on previous value rather than "now";
 * only do this for miniguns though, to avoid problems
 * (e.g. sniper rifles spitting out multiple shots at once) */


static void (*trampoline_CTFWeaponBaseGun_PrimaryAttack)(CTFWeaponBaseGun* this);


static void detour_CTFWeaponBaseGun_PrimaryAttack(CTFWeaponBaseGun* this)
{
	float *m_flNextPrimaryAttack =
		prop_CTFWeaponBaseGun_m_flNextPrimaryAttack(this);
	float t_before = *m_flNextPrimaryAttack;
	
	trampoline_CTFWeaponBaseGun_PrimaryAttack(this);
	
	/* only meddle with miniguns */
	if (vcall_CTFWeaponBase_GetWeaponID(this) == TF_WEAPON_MINIGUN) {
		/* sure hope this doesn't change during this detour */
		float t_now = (*gpGlobals)->curtime;
		
		/* figure out what the firing interval must have been */
		float t_after = *m_flNextPrimaryAttack;
		float dt_primary = t_after - t_now;
		
		/* recalculate m_flNextPrimaryAttack based on its previous value
		 * (t_before) rather than based on t_now */
		float t_unaliased = t_before + dt_primary;
		
		pr_info("CTFWeaponBaseGun::PrimaryAttack: %08x is minigun!\n",
			(uintptr_t)this);
		pr_debug(
			"  t_before:    %7.3f\n"
			"  t_after:     %7.3f\n"
			"  t_now:       %7.3f\n"
			"  dt_primary:  %7.3f\n"
			"  t_unaliased: %7.3f\n",
			t_before, t_after, t_now, dt_primary, t_unaliased);
		
		/* apply and notify state change if necessary */
		if (*m_flNextPrimaryAttack != t_unaliased) {
			CBaseEntity_NetworkStateChanged(this, m_flNextPrimaryAttack);
			*m_flNextPrimaryAttack = t_unaliased;
		}
	}
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFWeaponBaseGun_PrimaryAttack);
	
	return true;
}
