#include "all.h"


DETOUR(debug_damageinfo);
/*  */


static unknown_t (*trampoline_CTFPlayer_OnTakeDamage)(CTFPlayer* this, CTakeDamageInfo const*);


static unknown_t detour_CTFPlayer_OnTakeDamage(CTFPlayer* this, CTakeDamageInfo const* info)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = 0;
	int weapon_entindex = conv_EHANDLE_to_entindex(info->m_hWeapon);
	CBaseEntity* ent;
	CTFWeaponBase *weapon;
	if ((ent = UTIL_EntityByIndex(weapon_entindex)) != NULL) {
		if ((weapon = DYNAMIC_CAST(ent, CBaseEntity, CTFWeaponBase)) != NULL) {
			weaponid = vcall_CTFWeaponBase_GetWeaponID(weapon);
		}
	}
	
	
	pr_info("CTFPlayer::OnTakeDamage\n");
	pr_debug(
		"  player entindex:       %d\n"
		"  m_vecDamageForce:      % .2e % .2e % .2e\n"
		"  m_vecDamagePosition:   % .2e % .2e % .2e\n"
		"  m_vecReportedPosition: % .2e % .2e % .2e\n"
		"  m_hInflictor:          %08x\n"
		"  m_hAttacker:           %08x\n"
		"  m_hWeapon:             %08x (ID: %d %s)\n"
		"  m_flDamage:            %.1f\n"
		"  m_flMaxDamage:         %.1f\n"
		"  m_flBaseDamage:        %.1f\n"
		"  m_bitsDamageType:      %08x (%s)\n"
		"  m_iDamageCustom:       %d (%s)\n"
		"  m_iDamageStats:        %08x\n",
		entindex,
		info->m_vecDamageForce.x,
		info->m_vecDamageForce.y,
		info->m_vecDamageForce.z,
		info->m_vecDamagePosition.x,
		info->m_vecDamagePosition.y,
		info->m_vecDamagePosition.z,
		info->m_vecReportedPosition.x,
		info->m_vecReportedPosition.y,
		info->m_vecReportedPosition.z,
		conv_EHANDLE_to_entindex(info->m_hInflictor),
		conv_EHANDLE_to_entindex(info->m_hAttacker),
		weapon_entindex,
		weaponid,
		get_string_for_weaponid(weaponid),
		info->m_flDamage,
		info->m_flMaxDamage,
		info->m_flBaseDamage,
		info->m_bitsDamageType,
		get_string_for_damagebits(info->m_bitsDamageType),
		info->m_iDamageCustom,
		get_string_for_customkill(info->m_iDamageCustom),
		info->m_iDamageStats);
	
	
	return trampoline_CTFPlayer_OnTakeDamage(this, info);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_OnTakeDamage);
	
	return true;
}
