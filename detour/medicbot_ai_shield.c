#include "all.h"


DETOUR(medicbot_ai_shield);
/* make the medicbot AI manually attempt to enable their medigun shield */


static unknown_struct_t (*trampoline_CTFBotMedicHeal_Update)(CTFBotMedicHeal* this, CTFBot*, float);


static unknown_struct_t detour_CTFBotMedicHeal_Update(CTFBotMedicHeal* this, CTFBot* bot, float f1)
{
	//pr_info("CTFBotMedicHeal::Update\n");
	
	
	CTFWeaponBase* weapon;
	CWeaponMedigun* medigun;
	
	if ((weapon = CTFPlayer_GetActiveTFWeapon(bot)) == NULL) {
		//pr_debug("  active weapon is NULL\n");
		goto skip_shield;
	}
	
	if ((medigun = DYNAMIC_CAST(weapon,
		CTFWeaponBase, CWeaponMedigun)) == NULL) {
		//pr_debug("  active weapon is not a medigun\n");
		goto skip_shield;
	}
	
	if (CAttributeManager_AttribHookValue_int(0, "generate_rage_on_heal",
		medigun, NULL, true) <= 0) {
		//pr_debug("  medigun doesn't have shield attribute\n");
		goto skip_shield);
	}
	
	//pr_debug("  calling CWeaponMedigun::CreateMedigunShield\n");
	CWeaponMedigun_CreateMedigunShield(medigun);
	
	
skip_shield:
	return trampoline_CTFBotMedicHeal_Update(this, bot, f1);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFBotMedicHeal_Update);
}
