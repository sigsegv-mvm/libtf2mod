#include "all.h"


DETOUR(medicbot_ai_xbow_heal);
/* prevent certain CWeaponMedigun-specific functions from being called with
 * CTFCrossbow* class instance pointers or null pointers */


static bool (*trampoline_CWeaponMedigun_IsAttachedToBuilding)(CWeaponMedigun* this);
static bool (*trampoline_CTFBotMedicHeal_IsReadyToDeployUber)(CTFBotMedicHeal* this, CWeaponMedigun const*);


static bool detour_CWeaponMedigun_IsAttachedToBuilding(CWeaponMedigun* this)
{
	//pr_info("CTFWeaponMedigun::IsAttachedToBuilding\n");
	
	//pr_debug("  this = %08x\n", (uintptr_t)this);
	if (this == NULL ||
		DYNAMIC_CAST(this, CTFWeaponBase, CWeaponMedigun) == NULL) {
		//pr_debug("  is CWeaponMedigun: FALSE\n");
		return false;
	}
	//pr_debug("  is CWeaponMedigun: TRUE\n");
	
	return trampoline_CWeaponMedigun_IsAttachedToBuilding(this);
}

static bool detour_CTFBotMedicHeal_IsReadyToDeployUber(CTFBotMedicHeal* this, CWeaponMedigun const* medigun)
{
	//pr_info("CTFWeaponMedigun::IsReadyToDeployUber\n");
	
	//pr_debug("  this = %08x\n", (uintptr_t)this);
	//pr_debug("  medigun = %08x\n", (uintptr_t)medigun);
	assert(this != NULL);
	if (medigun == NULL ||
		DYNAMIC_CAST(medigun, CTFWeaponBase, CWeaponMedigun) == NULL) {
		//pr_debug("  is CWeaponMedigun: FALSE\n");
		return false;
	}
	//pr_debug("  is CWeaponMedigun: TRUE\n");
	
	return trampoline_CTFBotMedicHeal_IsReadyToDeployUber(this, medigun);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CWeaponMedigun_IsAttachedToBuilding);
	DETOUR_CREATE(CTFBotMedicHeal_IsReadyToDeployUber);
	
	return true;
}
