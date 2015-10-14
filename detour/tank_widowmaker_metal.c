#include "all.h"


DETOUR(tank_widowmaker_metal);
/* make damage done to the tank by the Widowmaker return 33% metal */


static unknown_t (*trampoline_CTFTankBoss_OnTakeDamage_Alive)(CTFTankBoss* this, CTakeDamageInfo const*);


static unknown_t detour_CTFTankBoss_OnTakeDamage_Alive(CTFTankBoss* this, CTakeDamageInfo const* info)
{
	//pr_info("CTFTankBoss::OnTakeDamage_Alive\n");
	//pr_debug("  m_hWeapon %08x\n  m_hInflictor %08x\n",
	//	info->m_hWeapon, info->m_hInflictor);
	
	if (info->m_hWeapon != -1 && info->m_hInflictor != -1) {
		int idx_weapon    = conv_EHANDLE_to_entindex(info->m_hWeapon);
		int idx_inflictor = conv_EHANDLE_to_entindex(info->m_hInflictor);
		//pr_debug("  idx_weapon %d\n  idx_inflictor %d\n",
		//	idx_weapon, idx_inflictor);
		
		CBaseEntity* weapon    = CBaseEntity_Instance(INDEXENT(idx_weapon));
		CBaseEntity* inflictor = CBaseEntity_Instance(INDEXENT(idx_inflictor));
		//pr_debug("  weapon %08x\n  inflictor %08x\n",
		//	(uintptr_t)weapon, (uintptr_t)inflictor);
		
		CTFPlayer* player = DYNAMIC_CAST(inflictor, CBaseEntity, CTFPlayer);
		//pr_debug("  player %08x\n",
		//	(uintptr_t)player);
		
		if (weapon != NULL && player != NULL) {
			int attr = CAttributeManager_AttribHookValue_int(0,
				"add_onhit_addammo", weapon, NULL, true);
			//pr_debug("  attr %d\n  is_engie %s\n", attr,
			//	(CTFPlayer_IsPlayerClass(player, TFCLASS_ENGINEER) ?
			//		"HECK YES!" : "NOPE."));
			
			if (attr > 0 && CTFPlayer_IsPlayerClass(player, TFCLASS_ENGINEER)) {
				float flAmmo = info->m_flDamage * (float)attr / (100.0f * 3.0f);
				int iAmmo = (int)flAmmo;
				
				//pr_debug("  m_flDamage %f\n  flAmmo %f\n  iAmmo %d\n",
				//	info->m_flDamage, flAmmo, iAmmo);
				CTFPlayer_AddBuildResources(player, iAmmo);
			}
		}
	}
	
	return trampoline_CTFTankBoss_OnTakeDamage_Alive(this, info);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFTankBoss_OnTakeDamage_Alive);
	
	return true;
}
