#include "all.h"


DETOUR(medicbot_ai_xbow_heal);
/*  */


static bool (*trampoline_CWeaponMedigun_IsAttachedToBuilding)(CWeaponMedigun* this);
static bool (*trampoline_CTFBotMedicHeal_IsReadyToDeployUber)(CTFBotMedicHeal* this, CWeaponMedigun const*);


static bool detour_CWeaponMedigun_IsAttachedToBuilding(CWeaponMedigun* this)
{
	if (DYNAMIC_CAST(this, CTFWeaponBase, CWeaponMedigun) == NULL) {
		return false;
	}
	
	return trampoline_CWeaponMedigun_IsAttachedToBuilding(this);
}

static bool detour_CTFBotMedicHeal_IsReadyToDeployUber(CTFBotMedicHeal* this, CWeaponMedigun const* medigun)
{
	if (DYNAMIC_CAST(medigun, CTFWeaponBase, CWeaponMedigun) == NULL) {
		return false;
	}
	
	return trampoline_CTFBotMedicHeal_IsReadyToDeployUber(this, medigun);
}



DETOUR_SETUP
{
	DETOUR_CREATE(CWeaponMedigun_IsAttachedToBuilding);
	DETOUR_CREATE(CTFBotMedicHeal_IsReadyToDeployUber);
}
