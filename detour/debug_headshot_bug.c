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
}



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
