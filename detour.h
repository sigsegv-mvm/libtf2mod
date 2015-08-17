#ifndef _LIBTF2MOD_DETOUR_H
#define _LIBTF2MOD_DETOUR_H


#define DETOUR_SETUP \
	static void detour_setup(void)

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
	
	void (*setup)(void);
} detour_info_t;


void detour_all(void);

func_t *func_register(void *pfunc);

void *func_detour(void *pfunc, void *detour);
//void func_detour_enable(func_t *func, void *detour);
//void func_detour_disable(func_t *func, void *detour);

bool func_owns_addr(void *pfunc, uintptr_t addr);


extern detour_info_t detour_init;

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
extern detour_info_t detour_scorchshot_airblast_disable;
extern detour_info_t detour_yer_nerf_disable;

extern detour_info_t detour_mini_dispenser;

extern detour_info_t detour_disposable_dispenser_part1;
extern detour_info_t detour_disposable_dispenser_part2;
extern detour_info_t detour_disposable_dispenser_part3;
extern detour_info_t detour_disposable_dispenser_part4;
extern detour_info_t detour_disposable_dispenser_part5;

extern detour_info_t detour_diagnostics;
extern detour_info_t detour_wavecounts_debug;
extern detour_info_t detour_debug_rescueranger_pickup_range;
extern detour_info_t detour_debug_gib_glitch;
extern detour_info_t detour_debug_headshot_bug;


#endif
