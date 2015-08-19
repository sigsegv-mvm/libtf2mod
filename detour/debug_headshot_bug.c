#include "all.h"


DETOUR(debug_headshot_bug);
/*  */


static bool (*trampoline_CTFSniperRifle_CanFireCriticalShot)(CTFSniperRifle* this, bool);
static bool (*trampoline_CTFWeaponBase_AreRandomCritsEnabled)(CTFWeaponBase* this);
static bool (*trampoline_CTFWeaponBase_CalcIsAttackCritical)(CTFWeaponBase* this);
static bool (*trampoline_CTFWeaponBase_CalcIsAttackCriticalHelper)(CTFWeaponBase* this);
static bool (*trampoline_CTFWeaponBase_CalcIsAttackCriticalHelperNoCrits)(CTFWeaponBase* this);
static bool (*trampoline_CTFWeaponBase_CanBeCritBoosted)(CTFWeaponBase* this);
static bool (*trampoline_CTFWeaponBase_CanFireCriticalShot)(CTFWeaponBase* this, bool);
static bool (*trampoline_CTFWeaponBase_CanFireRandomCriticalShot)(CTFWeaponBase* this, float);
static bool (*trampoline_CTFGameRules_IsPVEModeControlled)(CTFGameRules* this, CBaseEntity*);
static unknown_t (*trampoline_CTFPlayer_FireBullet)(CTFPlayer* this, CTFWeaponBase*, FireBulletsInfo_t const*, bool, int, int);
static unknown_t (*trampoline_CTFPlayer_TraceAttack)(CTFPlayer* this, CTakeDamageInfo const*, Vector const*, CGameTrace*, CDmgAccumulator*);


static bool detour_CTFSniperRifle_CanFireCriticalShot(CTFSniperRifle* this, bool b1)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	
	bool result = trampoline_CTFSniperRifle_CanFireCriticalShot(this, b1);
	pr_debug("CTFSniperRifle[e:%d|t:%d]::CanFireCriticalShot(%s): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		(b1 ? "TRUE" : "FALSE"),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_AreRandomCritsEnabled(CTFWeaponBase* this)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_AreRandomCritsEnabled(this);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::AreRandomCritsEnabled(): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_CalcIsAttackCritical(CTFWeaponBase* this)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_CalcIsAttackCritical(this);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::CalcIsAttackCritical(): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_CalcIsAttackCriticalHelper(CTFWeaponBase* this)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_CalcIsAttackCriticalHelper(this);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::CalcIsAttackCriticalHelper(): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_CalcIsAttackCriticalHelperNoCrits(CTFWeaponBase* this)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_CalcIsAttackCriticalHelperNoCrits(this);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::CalcIsAttackCriticalHelperNoCrits(): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_CanBeCritBoosted(CTFWeaponBase* this)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_CanBeCritBoosted(this);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::CanBeCritBoosted(): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_CanFireCriticalShot(CTFWeaponBase* this, bool b1)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_CanFireCriticalShot(this, b1);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::CanFireCriticalShot(%s): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		(b1 ? "TRUE" : "FALSE"),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFWeaponBase_CanFireRandomCriticalShot(CTFWeaponBase* this, float f1)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(this);
	
	
	bool result = trampoline_CTFWeaponBase_CanFireRandomCriticalShot(this, f1);
	pr_debug("CTFWeaponBase[e:%d|t:%d|w:%d:%s]::CanFireRandomCriticalShot(%.2f): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(this),
		weaponid,
		get_string_for_weaponid(weaponid),
		f1,
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static bool detour_CTFGameRules_IsPVEModeControlled(CTFGameRules* this, CBaseEntity* ent)
{
	int entindex = ENTINDEX(ent);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)ent);
	}
	
	
	bool result = trampoline_CTFGameRules_IsPVEModeControlled(this, ent);
	pr_debug("CTFGameRules::IsPVEModeControlled(e:%d|t:%d): %s\n",
		entindex,
		CBaseEntity_GetTeamNumber(ent),
		(result ? "TRUE" : "FALSE"));
	
	return result;
}

static unknown_t detour_CTFPlayer_FireBullet(CTFPlayer* this, CTFWeaponBase* weapon, FireBulletsInfo_t const* info, bool b1, int i1, int i2)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	int weapon_entindex = ENTINDEX(weapon);
	if (weapon_entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)weapon);
	}
	int weaponid = vcall_CTFWeaponBase_GetWeaponID(weapon);
	
	
	pr_info("CTFPlayer::FireBullet\n");
	pr_debug(
		"  player entindex:              %d\n"
		"  weapon entindex:              %d\n"
		"  weapon ID:                    %d %s\n"
		"  b1:                           %s\n"
		"  i1:                           %08x\n"
		"  i2:                           %08x\n"
		"  info->m_iShots:               %d\n"
		"  info->m_vecSrc:               % .2e % .2e % .2e\n"
		"  info->m_vecDirShooting:       % .2e % .2e % .2e\n"
		"  info->m_vecSpread:            % .2e % .2e % .2e\n"
		"  info->m_flDistance:           %.1f\n"
		"  info->m_iAmmoType:            %08x\n"
		"  info->m_iTracerFreq:          %08x\n"
		"  info->m_flDamage:             %.1f\n"
		"  info->m_iPlayerDamage:        %08x\n"
		"  info->m_nFlags:               %08x\n"
		"  info->m_flDamageForceScale:   %.1f\n"
		"  info->m_pAttacker:            %d %08x\n"
		"  info->m_pAdditionalIgnoreEnt: %d %08x\n"
		"  info->m_bPrimaryAttack:       %s\n",
		entindex,
		weapon_entindex,
		weaponid,
		get_string_for_weaponid(weaponid),
		(b1 ? "TRUE" : "FALSE"),
		i1, i2,
		info->m_iShots,
		info->m_vecSrc.x, info->m_vecSrc.y, info->m_vecSrc.z,
		info->m_vecDirShooting.x, info->m_vecDirShooting.y, info->m_vecDirShooting.z,
		info->m_vecSpread.x, info->m_vecSpread.y, info->m_vecSpread.z,
		info->m_flDistance,
		info->m_iAmmoType,
		info->m_iTracerFreq,
		info->m_flDamage,
		info->m_iPlayerDamage,
		info->m_nFlags,
		info->m_flDamageForceScale,
		ENTINDEX(info->m_pAttacker), (uintptr_t)info->m_pAttacker,
		ENTINDEX(info->m_pAdditionalIgnoreEnt), (uintptr_t)info->m_pAdditionalIgnoreEnt,
		(info->m_bPrimaryAttack ? "TRUE" : "FALSE"));
	
	
	return trampoline_CTFPlayer_FireBullet(this, weapon, info, b1, i1, i2);
}

static unknown_t detour_CTFPlayer_TraceAttack(CTFPlayer* this, CTakeDamageInfo const* info, Vector const* vec, CGameTrace* trace, CDmgAccumulator* accum)
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
	
	
	pr_info("CTFPlayer::TraceAttack\n");
	pr_debug(
		"  player entindex:             %d\n"
		"  info->m_vecDamageForce:      % .2e % .2e % .2e\n"
		"  info->m_vecDamagePosition:   % .2e % .2e % .2e\n"
		"  info->m_vecReportedPosition: % .2e % .2e % .2e\n"
		"  info->m_hInflictor:          %08x\n"
		"  info->m_hAttacker:           %08x\n"
		"  info->m_hWeapon:             %08x (ID: %d %s)\n"
		"  info->m_flDamage:            %.1f\n"
		"  info->m_flMaxDamage:         %.1f\n"
		"  info->m_flBaseDamage:        %.1f\n"
		"  info->m_bitsDamageType:      %08x (%s)\n"
		"  info->m_iDamageCustom:       %d (%s)\n"
		"  info->m_iDamageStats:        %08x\n"
		"  trace->startpos:             % .2e % .2e % .2e\n"
		"  trace->endpos:               % .2e % .2e % .2e\n"
		"  trace->plane.normal:         % .2e % .2e % .2e\n"
		"  trace->plane.dist:           %.1f\n"
		"  trace->plane.type:           %02x\n"
		"  trace->plane.signbits:       %02x\n"
		"  trace->fraction:             %.2f\n"
		"  trace->contents:             %08x\n"
		"  trace->dispFlags:            %04x\n"
		"  trace->allsolid:             %s\n"
		"  trace->startsolid:           %s\n"
		"  trace->fractionleftsolid:    %.2f\n"
		"  trace->surface.name:         '%s'\n"
		"  trace->surface.surfaceProps: %04x\n"
		"  trace->surface.flags:        %04x\n"
		"  trace->hitgroup:             %08x\n"
		"  trace->physicsbone:          %04x\n"
		"  trace->m_pEnt:               %d\n"
		"  trace->hitbox                %08x\n",
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
		info->m_iDamageStats,
		trace->base.startpos.x, trace->base.startpos.y, trace->base.startpos.z,
		trace->base.endpos.x, trace->base.endpos.y, trace->base.endpos.z,
		trace->base.plane.normal.x, trace->base.plane.normal.y, trace->base.plane.normal.z,
		trace->base.plane.dist,
		trace->base.plane.type,
		trace->base.plane.signbits,
		trace->base.fraction,
		trace->base.contents,
		trace->base.dispFlags,
		(trace->base.allsolid ? "TRUE" : "FALSE"),
		(trace->base.startsolid ? "TRUE" : "FALSE"),
		trace->fractionleftsolid,
		trace->surface.name,
		trace->surface.surfaceProps,
		trace->surface.flags,
		trace->hitgroup,
		trace->physicsbone,
		ENTINDEX(trace->m_pEnt),
		trace->hitbox);
	
	
	return trampoline_CTFPlayer_TraceAttack(this, info, vec, trace, accum);
}



DETOUR_SETUP
{
	DETOUR_CREATE(CTFSniperRifle_CanFireCriticalShot);
	DETOUR_CREATE(CTFWeaponBase_AreRandomCritsEnabled);
	DETOUR_CREATE(CTFWeaponBase_CalcIsAttackCritical);
	DETOUR_CREATE(CTFWeaponBase_CalcIsAttackCriticalHelper);
	DETOUR_CREATE(CTFWeaponBase_CalcIsAttackCriticalHelperNoCrits);
	DETOUR_CREATE(CTFWeaponBase_CanBeCritBoosted);
	DETOUR_CREATE(CTFWeaponBase_CanFireCriticalShot);
	DETOUR_CREATE(CTFWeaponBase_CanFireRandomCriticalShot);
	DETOUR_CREATE(CTFGameRules_IsPVEModeControlled);
	DETOUR_CREATE(CTFPlayer_FireBullet);
	DETOUR_CREATE(CTFPlayer_TraceAttack);
}


// TODO: struct for
// CDmgAccumulator


// detour these functions:
// bool CTFSniperRifle::CanFireCriticalShot(bool)
// bool CTFWeaponBase::AreRandomCritsEnabled()
// bool CTFWeaponBase::CalcIsAttackCritical()
// bool CTFWeaponBase::CalcIsAttackCriticalHelper()
// bool CTFWeaponBase::CalcIsAttackCriticalHelperNoCrits()
// bool CTFWeaponBase::CanBeCritBoosted()
// bool CTFWeaponBase::CanFireCriticalShot(bool)
// bool CTFWeaponBase::CanFireRandomCriticalShot(float)
// bool CTFGameRules::IsPVEModeControlled(CBaseEntity*)
// in detours:
// - print ENTINDEX(this)
// - print team number
// - print stringified weaponid (use vcall_CTFWeaponBase_GetWeaponID)
// in IsPVEModeControlled:
// - print ENTINDEX(this)
// - print team number

// find where sniper rifles create their CTakeDamageInfo and pass it to TakeDamage(...)
// look at CTFGameRules for anything crit or headshot related

// search:
// headshot
// 

// who calls CTFGameRules::IsPVEModeControlled?
//  CTFWeaponBase::CalcIsAttackCritical(void)
//  CTFWeaponBase::CanFireCriticalShot(bool)
//  CBaseObject::CheckUpgradeOnHit(CTFPlayer *)
//  CTFProjectile_Arrow::StrikeTarget(mstudiobbox_t *,CBaseEntity *) [clone]
