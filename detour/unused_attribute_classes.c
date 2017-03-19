#include "all.h"


DETOUR(unused_attribute_classes);
/*  */


static float (*trampoline_CAttributeManager_ApplyAttributeFloatWrapper)(CAttributeManager* this, float, CBaseEntity*, string_t, CUtlVector*);


static ConVar cvar_sigsegv_detour_attrclass_ability_master_sniper;
static ConVar cvar_sigsegv_detour_attrclass_build_small_sentries;
static ConVar cvar_sigsegv_detour_attrclass_firing_forward_pull;
static ConVar cvar_sigsegv_detour_attrclass_mod_projectile_heat_seek_power;
static ConVar cvar_sigsegv_detour_attrclass_mod_soldier_buff_range;
static ConVar cvar_sigsegv_detour_attrclass_mod_teleporter_speed_boost;
static ConVar cvar_sigsegv_detour_attrclass_mult_dispenser_rate;
static ConVar cvar_sigsegv_detour_attrclass_mult_dmg_vs_same_class;
static ConVar cvar_sigsegv_detour_attrclass_mvm_sentry_ammo;


static float detour_CAttributeManager_ApplyAttributeFloatWrapper(CAttributeManager* this, float val, CBaseEntity* ent, string_t name, CUtlVector* v)
{
	if (name.pszValue != NULL) {
		if (strcasecmp(name.pszValue, "ability_master_sniper") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_ability_master_sniper);
		}
		if (strcasecmp(name.pszValue, "build_small_sentries") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_build_small_sentries);
		}
		if (strcasecmp(name.pszValue, "firing_forward_pull") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_firing_forward_pull);
		}
		if (strcasecmp(name.pszValue, "mod_projectile_heat_seek_power") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_mod_projectile_heat_seek_power);
		}
		if (strcasecmp(name.pszValue, "mod_soldier_buff_range") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_mod_soldier_buff_range);
		}
		if (strcasecmp(name.pszValue, "mod_teleporter_speed_boost") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_mod_teleporter_speed_boost);
		}
		if (strcasecmp(name.pszValue, "mult_dispenser_rate") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_mult_dispenser_rate);
		}
		if (strcasecmp(name.pszValue, "mult_dmg_vs_same_class") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_mult_dmg_vs_same_class);
		}
		if (strcasecmp(name.pszValue, "mvm_sentry_ammo") == 0) {
			return ConVar_GetFloat(&cvar_sigsegv_detour_attrclass_mvm_sentry_ammo);
		}
	}
	
	return trampoline_CAttributeManager_ApplyAttributeFloatWrapper(this, val, ent, name, v);
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_ability_master_sniper,
		"sigsegv_detour_attrclass_ability_master_sniper",
		"0", FCVAR_NOTIFY,
		"Detour attribute class 'ability_master_sniper'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_build_small_sentries,
		"sigsegv_detour_attrclass_build_small_sentries",
		"0", FCVAR_NOTIFY,
		"Detour attribute class 'build_small_sentries'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_firing_forward_pull,
		"sigsegv_detour_attrclass_firing_forward_pull",
		"0.0", FCVAR_NOTIFY,
		"Detour attribute class 'firing_forward_pull'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_mod_projectile_heat_seek_power,
		"sigsegv_detour_attrclass_mod_projectile_heat_seek_power",
		"0.0", FCVAR_NOTIFY,
		"Detour attribute class 'mod_projectile_heat_seek_power'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_mod_soldier_buff_range,
		"sigsegv_detour_attrclass_mod_soldier_buff_range",
		"1.0", FCVAR_NOTIFY,
		"Detour attribute class 'mod_soldier_buff_range'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_mod_teleporter_speed_boost,
		"sigsegv_detour_attrclass_mod_teleporter_speed_boost",
		"0", FCVAR_NOTIFY,
		"Detour attribute class 'mod_teleporter_speed_boost'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_mult_dispenser_rate,
		"sigsegv_detour_attrclass_mult_dispenser_rate",
		"1.0", FCVAR_NOTIFY,
		"Detour attribute class 'mult_dispenser_rate'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_mult_dmg_vs_same_class,
		"sigsegv_detour_attrclass_mult_dmg_vs_same_class",
		"1.0", FCVAR_NOTIFY,
		"Detour attribute class 'mult_dmg_vs_same_class'");
	ConVar_ctor(&cvar_sigsegv_detour_attrclass_mvm_sentry_ammo,
		"sigsegv_detour_attrclass_mvm_sentry_ammo",
		"1.0", FCVAR_NOTIFY,
		"Detour attribute class 'mvm_sentry_ammo'");
	
	DETOUR_CREATE(CAttributeManager_ApplyAttributeFloatWrapper);
	
	return true;
}
