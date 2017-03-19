#include "all.h"


DETOUR(canteen_override);
/*  */


static float (*trampoline_CAttributeManager_ApplyAttributeFloatWrapper)(CAttributeManager* this, float, CBaseEntity*, string_t, CUtlVector*);
static void (*trampoline_CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);
static void (*trampoline_CTFPlayerShared_RemoveCond)(CTFPlayerShared* this, ETFCond, bool);


static ConVar cvar_sigsegv_detour_override_canteen_enable;
static ConVar cvar_sigsegv_detour_override_canteen_condition;
static ConVar cvar_sigsegv_detour_override_canteen_duration;


static func_t *func_CTFPowerupBottle_ReapplyProvision;


static float detour_CAttributeManager_ApplyAttributeFloatWrapper(CAttributeManager* this, float val, CBaseEntity* ent, string_t name, CUtlVector* v)
{
	if (ConVar_GetInt(&cvar_sigsegv_detour_override_canteen_enable) != 0) {
		if (name.pszValue != NULL) {
			if (strcasecmp(name.pszValue, "powerup_duration") == 0) {
				return ConVar_GetFloat(&cvar_sigsegv_detour_override_canteen_duration);
			}
		}
	}
	
	return trampoline_CAttributeManager_ApplyAttributeFloatWrapper(this, val, ent, name, v);
}

static void detour_CTFPlayerShared_AddCond(CTFPlayerShared* this, ETFCond cond, float duration, CBaseEntity* provider)
{
	if (ConVar_GetInt(&cvar_sigsegv_detour_override_canteen_enable) != 0 &&
		cond == TF_COND_CRITBOOSTED_USER_BUFF) {
		
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1, func_CTFPowerupBottle_ReapplyProvision)) {
			
			cond = ConVar_GetInt(&cvar_sigsegv_detour_override_canteen_condition);
			cl_con_printf("[AddCond]    overriding condition: %3d %s\n",
				cond, get_string_for_condition(cond));
		}
	}
	
	trampoline_CTFPlayerShared_AddCond(this, cond, duration, provider);
}

static void detour_CTFPlayerShared_RemoveCond(CTFPlayerShared* this, ETFCond cond, bool b1)
{
	if (ConVar_GetInt(&cvar_sigsegv_detour_override_canteen_enable) != 0 &&
		cond == TF_COND_CRITBOOSTED_USER_BUFF) {
		
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		if (func_owns_addr(caller1, func_CTFPowerupBottle_ReapplyProvision)) {
			
			cond = ConVar_GetInt(&cvar_sigsegv_detour_override_canteen_condition);
			cl_con_printf("[RemoveCond] overriding condition: %3d %s\n",
				cond, get_string_for_condition(cond));
		}
	}
	
	trampoline_CTFPlayerShared_RemoveCond(this, cond, b1);
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_sigsegv_detour_override_canteen_enable,
		"sigsegv_detour_override_canteen_enable", "0", FCVAR_NOTIFY,
		"Detour: canteen override: enable flag");
	ConVar_ctor(&cvar_sigsegv_detour_override_canteen_condition,
		"sigsegv_detour_override_canteen_condition", "34", FCVAR_NOTIFY,
		"Detour: canteen override: condition number");
	ConVar_ctor(&cvar_sigsegv_detour_override_canteen_duration,
		"sigsegv_detour_override_canteen_duration", "5.0", FCVAR_NOTIFY,
		"Detour: canteen override: duration");
	
	func_CTFPowerupBottle_ReapplyProvision =
		func_register(CTFPowerupBottle_ReapplyProvision);
	
	DETOUR_CREATE(CAttributeManager_ApplyAttributeFloatWrapper);
	DETOUR_CREATE(CTFPlayerShared_AddCond);
	DETOUR_CREATE(CTFPlayerShared_RemoveCond);
	
	return true;
}
