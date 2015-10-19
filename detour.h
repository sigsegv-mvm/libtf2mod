#ifndef _LIBTF2MOD_DETOUR_H
#define _LIBTF2MOD_DETOUR_H


#define DETOUR_SETUP \
	static bool detour_setup(void)

#define DETOUR(_name) \
	DETOUR_SETUP; \
	detour_info_t detour_ ## _name = { \
		.name  = #_name, \
		.setup = &detour_setup, \
	};

#define DETOUR_CREATE(_func) \
	trampoline_ ## _func = func_detour(_func, detour_ ## _func)


typedef struct {
	const char *name;
	
	bool (*setup)(void);
	
	bool ok;
} detour_info_t;


void detour_all(void);

func_t *func_register(void *pfunc);

void *func_detour(void *pfunc, void *detour);
//void func_detour_enable(func_t *func, void *detour);
//void func_detour_disable(func_t *func, void *detour);


static inline bool func_owns_addr(uintptr_t addr, const func_t *func)
{
	uintptr_t addr_begin = func->func_addr;
	uintptr_t addr_end   = func->func_addr + func->func_size;
	
	return (addr >= addr_begin && addr < addr_end);
}


extern detour_info_t detour_init;

extern detour_info_t detour_shared_CTFSniperRifle_ExplosiveHeadShot;
extern detour_info_t detour_shared_CBasePlayer_IsBot;
extern detour_info_t detour_shared_CTFPlayer_SpeakConceptIfAllowed;

extern detour_info_t detour_sentry_moveturret_decimate;
extern detour_info_t detour_minisentry_quickbuild_health_fix;
extern detour_info_t detour_pushallplayersaway_disable;
extern detour_info_t detour_robot_tickle_enable;
extern detour_info_t detour_giantsoldier_crit_sound_fix;
extern detour_info_t detour_disposable_sentry_enable_health_upgrades;
extern detour_info_t detour_wavestatus_teleporter_rtr_fix;
extern detour_info_t detour_engiebot_ai_unsap;
extern detour_info_t detour_robot_headslide_disable;
extern detour_info_t detour_redcredits_doublecollect_fix;
extern detour_info_t detour_spawnprotect_cond51_only;
extern detour_info_t detour_robot_gib_improvements;
extern detour_info_t detour_robot_gib_dissolve_fix;
extern detour_info_t detour_yer_nerf_disable;
extern detour_info_t detour_arrow_pen_ignoreuber;
extern detour_info_t detour_medishield_teamskin_enable;
extern detour_info_t detour_eh_medieval_disable;
extern detour_info_t detour_bot_multiclass_item_fix;
extern detour_info_t detour_mvm_chat_unrestrict;
extern detour_info_t detour_tank_destroy_blu_buildings;
extern detour_info_t detour_wave_reset_countdown_fix;
extern detour_info_t detour_sentrybuster_roundwin_behavior_fix;
extern detour_info_t detour_eh_recursive_fix;
extern detour_info_t detour_nextprimaryattack_unalias;
extern detour_info_t detour_soundemitter_override_force_precache;
extern detour_info_t detour_sapper_allow_multiple_active;
extern detour_info_t detour_eh_sydney_check_uber;
extern detour_info_t detour_loadout_allow_holiday_items;
extern detour_info_t detour_tank_widowmaker_metal;
extern detour_info_t detour_responses_sapper;
extern detour_info_t detour_responses_credits;

extern detour_info_t detour_mini_dispenser;

extern detour_info_t detour_disposable_dispenser_part1;
extern detour_info_t detour_disposable_dispenser_part2;
extern detour_info_t detour_disposable_dispenser_part3;
extern detour_info_t detour_disposable_dispenser_part4;
extern detour_info_t detour_disposable_dispenser_part5;

extern detour_info_t detour_mvm_extended_waveloss_time;
extern detour_info_t detour_tank_minigun_resistance_disable;
extern detour_info_t detour_sapper_cooldown_disable;
extern detour_info_t detour_sapper_extended_duration;
extern detour_info_t detour_sniperdot_nodestroy;
extern detour_info_t detour_sapper_apply_reprogrammed;

extern detour_info_t detour_medicbot_ai_xbow_heal;
extern detour_info_t detour_medicbot_ai_shield;

extern detour_info_t detour_perf_attr_nomunge;

extern detour_info_t detour_diagnostics;
extern detour_info_t detour_debug_wavecounts;
extern detour_info_t detour_debug_rescueranger_pickup_range;
extern detour_info_t detour_debug_gib_glitch;
extern detour_info_t detour_debug_headshot_bug;
extern detour_info_t detour_debug_spawn_without_weapons;
extern detour_info_t detour_debug_readyup_missing_sounds;
extern detour_info_t detour_debug_usermessage;
extern detour_info_t detour_debug_revive;
extern detour_info_t detour_debug_stats;
extern detour_info_t detour_debug_upgrades;
extern detour_info_t detour_debug_damageinfo;
extern detour_info_t detour_debug_changelevel;
extern detour_info_t detour_debug_airblast;
extern detour_info_t detour_debug_aimhead;

extern detour_info_t detour_debug_spawn_item_fail_trace;

extern detour_info_t detour_profile_attributes;

extern detour_info_t detour_reimplement_sv_showhitboxes;
extern detour_info_t detour_reimplement_cond_reprogrammed;


#endif
