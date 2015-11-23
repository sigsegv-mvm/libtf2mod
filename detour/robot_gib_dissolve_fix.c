#include "all.h"


DETOUR(robot_gib_dissolve_fix);
/* Problems:
 * 1. TF_CUSTOM_PLASMA (Cow Mangler and medic shield) turns giants into small
 *    ragdolls that don't do the dissolving effect
 * 2. TF_CUSTOM_PLASMA_CHARGED (Cow Mangler charged shot) makes robots gib,
 *    which looks silly for certain bot classes that only have 0-1 gibs
 * Solutions:
 * 1. For giants, change PLASMA -> PLASMA_CHARGED
 * 2. For classes missing gibs, change PLASMA_CHARGED -> PLASMA */


static void (*trampoline_CTFPlayer_CreateRagdollEntity)(CTFPlayer* this, bool, bool, bool, bool, bool, bool, bool, bool, int, bool);
static unknown_t (*trampoline_CTFPlayer_Event_Killed)(CTFPlayer* this, CTakeDamageInfo const*);


static void detour_CTFPlayer_CreateRagdollEntity(CTFPlayer* this, bool bShouldGib, bool bBurning, bool bUberDrop, bool bOnGround, bool bYER, bool bGold, bool bIce, bool bAsh, int m_iDamageCustom, bool bClassic)
{
	/* only meddle with this stuff for MvM robots on BLU team */
	if ((m_iDamageCustom == TF_CUSTOM_PLASMA || 
		m_iDamageCustom == TF_CUSTOM_PLASMA_CHARGED) &&
		CTFGameRules_IsPVEModeActive(*g_pGameRules) &&
		CBaseEntity_GetTeamNumber(this) == TF_TEAM_BLUE) {
		
		float *m_flModelScale = prop_CBaseAnimating_m_flModelScale(this);
		bool is_giant = (CTFPlayer_IsMiniBoss(this) || *m_flModelScale > 1.0f);
		
		/* for giants:
		 * change the custom damage effect from TF_CUSTOM_PLASMA (which does not
		 * work properly) to TF_CUSTOM_PLASMA_CHARGED (which looks similar, but
		 * uses gibs and actually works properly) */
		if (is_giant && m_iDamageCustom == TF_CUSTOM_PLASMA) {
			m_iDamageCustom = TF_CUSTOM_PLASMA_CHARGED;
		}
		
		
		bool is_engie  = CTFPlayer_IsPlayerClass(this, TF_CLASS_ENGINEER);
		bool is_medic  = CTFPlayer_IsPlayerClass(this, TF_CLASS_MEDIC);
		bool is_sniper = CTFPlayer_IsPlayerClass(this, TF_CLASS_SNIPER);
		bool is_spy    = CTFPlayer_IsPlayerClass(this, TF_CLASS_SPY);
		
		/* for non-giants that have 0-1 gibs:
		 * change the custom damage effect from TF_CUSTOM_PLASMA_CHARGED (which
		 * relies on gibs, which this model doesn't have) to TF_CUSTOM_PLASMA
		 * (which looks similar, but doesn't rely on gibs to look good) */
		if (!is_giant && m_iDamageCustom == TF_CUSTOM_PLASMA_CHARGED &&
			(is_engie || is_medic || is_sniper || is_spy)) {
			m_iDamageCustom = TF_CUSTOM_PLASMA;
		}
	}
	
	
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	//pr_info("CTFPlayer::CreateRagdollEntity\n");
	//pr_debug(
	//	"  player entindex: %d\n"
	//	"  bShouldGib:      %x\n"
	//	"  bBurning:        %x\n"
	//	"  bUberDrop:       %x\n"
	//	"  bOnGround:       %x\n"
	//	"  bYER:            %x\n"
	//	"  bGold:           %x\n"
	//	"  bIce:            %x\n"
	//	"  bAsh:            %x\n"
	//	"  m_iDamageCustom: %d\n"
	//	"  bClassic:        %x\n",
	//	entindex,
	//	bShouldGib,
	//	bBurning,
	//	bUberDrop,
	//	bOnGround,
	//	bYER,
	//	bGold,
	//	bIce,
	//	bAsh,
	//	m_iDamageCustom,
	//	bClassic);
	
	
	trampoline_CTFPlayer_CreateRagdollEntity(this, bShouldGib, bBurning, bUberDrop, bOnGround, bYER, bGold, bIce, bAsh, m_iDamageCustom, bClassic);
}


static unknown_t detour_CTFPlayer_Event_Killed(CTFPlayer* this, CTakeDamageInfo const* info)
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
	
	
	pr_info("CTFPlayer::Event_Killed\n");
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
	
	
	return trampoline_CTFPlayer_Event_Killed(this, info);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CreateRagdollEntity);
	
	//DETOUR_CREATE(CTFPlayer_Event_Killed);
	
	return true;
}
