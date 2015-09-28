#include "all.h"


DETOUR(sapper_cooldown_disable);
/* prevent the robo sapper from needing to recharge after being used */


static void (*trampoline_CTFPlayer_RemoveAmmo)(CTFPlayer* this, int, int);
static void (*trampoline_CTFWeaponBase_StartEffectBarRegen)(CTFWeaponBase* this);


static func_t *func_CTFWeaponBuilder_StartBuilding;


static void detour_CTFPlayer_RemoveAmmo(CTFPlayer* this, int amount, int type)
{
	/* refuse to actually remove player ammo if we're being asked to remove the
	 * robo sapper's ammo */
	if (type == TF_AMMO_GRENADES2 && amount == 1 &&
		CTFGameRules_IsPVEModeActive(*g_pGameRules)) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		
		if (func_owns_addr(caller1,
			func_CTFWeaponBuilder_StartBuilding)) {
			return;
		}
	}
	
	trampoline_CTFPlayer_RemoveAmmo(this, amount, type);
}

static void detour_CTFWeaponBase_StartEffectBarRegen(CTFWeaponBase* this)
{
	/* refuse to do the effect bar stuff for the robo sapper */
	if (vcall_CTFWeaponBase_GetWeaponID(this) == TF_WEAPON_BUILDER) {
		return;
	}
	
	trampoline_CTFWeaponBase_StartEffectBarRegen(this);
}


DETOUR_SETUP
{
	func_CTFWeaponBuilder_StartBuilding =
		func_register(CTFWeaponBuilder_StartBuilding);
	
	DETOUR_CREATE(CTFPlayer_RemoveAmmo);
	DETOUR_CREATE(CTFWeaponBase_StartEffectBarRegen);
	
	return true;
}
