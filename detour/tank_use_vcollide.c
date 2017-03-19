#include "all.h"


DETOUR(tank_use_vcollide);
/*  */


static int (*trampoline_CBaseEntity_TakeDamage)(CBaseEntity* this, CTakeDamageInfo const*);
static void (*trampoline_CTFBaseBoss_ResolvePlayerCollision)(CTFBaseBoss* this, CTFPlayer*);
static void (*trampoline_CTFTankBoss_Spawn)(CTFTankBoss* this);


static ConVar cvar_damage_bypass;
static ConVar cvar_resolveplayercollision_bypass;
static ConVar cvar_solidtype;


static func_t *func_CTFTankBoss_TankBossThink;


static int detour_CBaseEntity_TakeDamage(CBaseEntity* this, CTakeDamageInfo const* info)
{
	if (ConVar_GetInt(&cvar_damage_bypass) != 0) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1,
			func_CTFTankBoss_TankBossThink)) {
			return 0;
		}
	}
	
	return trampoline_CBaseEntity_TakeDamage(this, info);
}

static void detour_CTFBaseBoss_ResolvePlayerCollision(CTFBaseBoss* this, CTFPlayer* player)
{
	if (ConVar_GetInt(&cvar_resolveplayercollision_bypass) == 0) {
		trampoline_CTFBaseBoss_ResolvePlayerCollision(this, player);
	}
}

static void detour_CTFTankBoss_Spawn(CTFTankBoss* this)
{
	trampoline_CTFTankBoss_Spawn(this);
	
	CCollisionProperty *m_Collision = prop_CBaseEntity_m_Collision(this);
	CCollisionProperty_SetSolid(m_Collision, ConVar_GetInt(&cvar_solidtype));
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_damage_bypass,
		"sigsegv_tank_damage_bypass", "0", FCVAR_NOTIFY,
		"Bypass CBaseEntity::TakeDamage from CTFTankBoss::TankBossThink");
	ConVar_ctor(&cvar_resolveplayercollision_bypass,
		"sigsegv_tank_resolveplayercollision_bypass", "0", FCVAR_NOTIFY,
		"Bypass CTFBaseBoss::ResolvePlayerCollision");
	ConVar_ctor(&cvar_solidtype,
		"sigsegv_tank_solidtype", "2", FCVAR_NOTIFY,
		"Override CTFTankBoss SolidType");
	
	func_CTFTankBoss_TankBossThink =
		func_register(CTFTankBoss_TankBossThink);
	
	DETOUR_CREATE(CBaseEntity_TakeDamage);
	DETOUR_CREATE(CTFBaseBoss_ResolvePlayerCollision);
	DETOUR_CREATE(CTFTankBoss_Spawn);
	
	return true;
}
