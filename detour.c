#include "all.h"


detour_info_t *detours[] = {
	&detour_shared_CTFSniperRifle_ExplosiveHeadShot,
	&detour_shared_CBasePlayer_IsBot,
	&detour_shared_CTFPlayer_SpeakConceptIfAllowed,
	
	&detour_sentry_moveturret_decimate,
	//&detour_minisentry_quickbuild_health_fix,
	&detour_pushallplayersaway_disable,
	&detour_robot_tickle_enable,
	&detour_disposable_sentry_enable_health_upgrades,
	//&detour_wavestatus_teleporter_rtr_fix,
	//&detour_engiebot_ai_unsap,
	&detour_robot_headslide_disable,
	&detour_redcredits_doublecollect_fix,
	//&detour_spawnprotect_cond51_only,
	&detour_robot_gib_improvements,
	&detour_robot_gib_dissolve_fix,
	&detour_yer_nerf_disable,
	&detour_arrow_pen_ignoreuber,
	&detour_eh_medieval_disable,
	&detour_bot_multiclass_item_fix,
	&detour_mvm_chat_unrestrict,
	&detour_tank_destroy_blu_buildings,
//	&detour_wave_reset_countdown_fix,
	&detour_sentrybuster_roundwin_behavior_fix,
	&detour_eh_recursive_fix,
	//&detour_nextprimaryattack_unalias,
	&detour_stun_weapon_unhide_fix,
	&detour_sapper_allow_multiple_active,
	//&detour_bot_enemy_selection_tweak,
	&detour_eh_sydney_check_uber,
	&detour_loadout_allow_holiday_items,
	&detour_bot_stun_disallow_headmove,
	&detour_tank_widowmaker_metal,
	&detour_responses_unused_sapper,
	&detour_responses_unused_credits,
	&detour_responses_suppress_medicbot_shield,
	&detour_responses_suppress_giant_sentrybuster,
	//&detour_countdown_10second_sound_fix,
	//&detour_engiebot_nonsolid_buildings,
	&detour_engiebot_check_build_placement,
	&detour_event_popfile_perennial,
	
	//&detour_mini_dispenser,
	
	/*&detour_disposable_dispenser_part1,
	&detour_disposable_dispenser_part2,
	&detour_disposable_dispenser_part3,
	&detour_disposable_dispenser_part4,
	&detour_disposable_dispenser_part5,*/
	
	//&detour_mvm_extended_waveloss_time,
	//&detour_tank_minigun_resistance_disable,
	//&detour_sapper_cooldown_disable,
	//&detour_sapper_extended_duration,
	//&detour_sniperdot_nodestroy,
	
	&detour_medicbot_ai_xbow_heal,
	
//	&detour_perf_attr_nomunge,
	
	//&detour_diagnostics,
//	&detour_debug_wavecounts,
	//&detour_debug_rescueranger_pickup_range,
	//&detour_debug_gib_glitch,
	//&detour_debug_headshot_bug,
	//&detour_debug_spawn_without_weapons,
	//&detour_debug_readyup_missing_sounds,
	//&detour_debug_usermessage,
	//&detour_debug_revive,
	//&detour_debug_stats,
	&detour_debug_upgrades,
	//&detour_debug_damageinfo,
	//&detour_debug_changelevel,
	//&detour_debug_airblast,
	//&detour_debug_aimhead,
	//&detour_debug_gametype,
	//&detour_debug_rescueranger_trace,
	&detour_debug_addcond_removecond,
	&detour_debug_nextbot_input,
	&detour_debug_sentry_dmg_kills,
	//&detour_debug_spectator_bomb_carrier,
	&detour_debug_wavestatus_tele_count,
	//&detour_debug_onkilled,
	&detour_debug_player_attributes,
	&detour_debug_multidamage,
	
	&detour_debug_spawn_item_fail_trace,
	
	//&detour_profile_attributes,
	
	//&detour_reimplement_sv_showhitboxes,
	//&detour_reimplement_cond_reprogrammed,
	
#if CHEATS
	&detour_sapper_apply_reprogrammed,
	&detour_mvm_enable_dropped_weapons,
#endif
	
	//&detour_demoshield_tank_killeater_cheat,
	//&detour_override_locomotion_runspeed,
	//&detour_unused_attribute_classes,
	
	//&detour_canteen_override,
	//&detour_allow_class_change_during_wave,
	//&detour_tank_use_vcollide,
	
	&detour_force_spec_kill_bots,
	//&detour_disallow_deploy_when_ubered,
};


static int num_funcs = 0;
static func_t funcs[4096];


void detour_all(void)
{
	for (int i = 0; i < sizeof(detours) / sizeof(*detours); ++i) {
		detour_info_t *detour = detours[i];
		
		pr_special("SETUP: %s\n", detour->name);
		
		if (detour->setup()) {
			detour->ok = true;
		}
	}
}


func_t *func_register(void *pfunc)
{
	func_t *func;
	
	/* skip if function is already registered */
	for (func = funcs; func != funcs + num_funcs; ++func) {
		if (func->func_addr == (uintptr_t)pfunc) {
			return func;
		}
	}
	
	assert(num_funcs < (sizeof(funcs) / sizeof(*funcs)));
	func = funcs + num_funcs++;
	
	func->func_addr = (uintptr_t)pfunc;
	
	symbol_t sym;
	if (!symtab_func_addr_abs(&sym, (uintptr_t)pfunc)) {
		errx(1, "symtab_func_addr_abs_anylib(0x%08x) failed", func->func_addr);
	}
	
	func->name = sym.name;
	func->name_demangled = try_demangle(sym.name);
	func->func_size = sym.size;
	
	func->has_detour  = false;
	
	void *buf;
	if ((buf = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED) {
		err(1, "mmap for func '%s' trampoline failed", func->name_demangled);
	}
	func->trampoline_addr = (uintptr_t)buf;
	func->trampoline_size = PAGE_SIZE;
	
	//pr_debug("func_register %s:\n", func->name_demangled);
	//pr_debug("  addr %08x\n  size %08x\n", func->func_addr, func->func_size);
	/*func_dump(func);*/
	
	return func;
}


void *func_detour(void *pfunc, void *detour)
{
	func_t *func = func_register(pfunc);
	
	pr_debug("func_detour %08x %s\n", (uintptr_t)pfunc, func->name_demangled);
	
	assert(!func->has_detour);
	
	/* nop out the entire trampoline page first */
	memset((void *)func->trampoline_addr, 0x90, func->trampoline_size);
	
	/* copy the first 6+ bytes of the function over to the trampoline */
	size_t len = copy_bytes((uint8_t *)func->func_addr,
		(uint8_t *)func->trampoline_addr, 6);
	assert(len >= 6);
	assert(len <= 20);
	assert(len <= func->func_size);
	
	/* save the original bytes */
	func->restore_len = len;
	memcpy(func->restore_buf, (void *)func->func_addr, len);
	
	/* make the original function jump to the detour function */
	func_unprotect(func);
	*((uint8_t  *)(func->func_addr + 0x00)) = 0xff; // jmp far
	*((uint8_t  *)(func->func_addr + 0x01)) = 0x25; // m32
	*((uint32_t *)(func->func_addr + 0x02)) = (uint32_t)&func->detour_addr;
	memset((void *)func->func_addr + 6, 0x90, len - 6); // nop
	func_protect(func);
	
	func->trampoline_dest = func->func_addr + len;
	
	/* make the trampoline jump to the original function */
	*((uint8_t  *)(func->trampoline_addr + len + 0x00)) = 0xff; // jmp far
	*((uint8_t  *)(func->trampoline_addr + len + 0x01)) = 0x25; // m32
	*((uint32_t *)(func->trampoline_addr + len + 0x02)) =
		(uint32_t)&func->trampoline_dest;
	
	func->detour_addr = (uintptr_t)detour;
	func->has_detour  = true;
	
	/*pr_debug("%s\nstruct func @ %p\n"
		"func_addr       = 0x%08x\n"
		"detour_addr     = 0x%08x\n"
		"trampoline_addr = 0x%08x\n",
		__func__, func,
		func->func_addr,
		func->detour_addr,
		func->trampoline_addr);*/
	
	return (void *)func->trampoline_addr;
}

#if 0
void func_detour_disable(func_t *func, void *detour)
{
	assert(func->has_detour);
	assert(func->detour_addr == (uintptr_t)detour);
	
	assert(func->restore_len >= 6);
	assert(func->restore_len <= 20);
	assert(func->restore_len <= func->func_size);
	
	assert(func->trampoline_dest == func->func_addr + func->restore_len);
	
	/* restore the function to the way it was originally */
	func_unprotect(func);
	memcpy((void *)func->func_addr, func->restore_buf, func->restore_len);
	func_protect(func);
	
	func->has_detour = false;
}
#endif


#if 0
static void _func_copy(func_t *func)
{
	size_t len = func->real_size;
	
	void *buf;
	if ((buf = mmap(NULL, len, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED) {
		err(1, "mmap for function %s failed", func->name_demangled);
	}
	
	func->copy_addr = (uintptr_t)buf;
	func->copy_size = len;
	
	memcpy((void *)func->copy_addr, (void *)func->real_addr, func->real_size);
	mem_protect((void *)func->copy_addr, func->copy_size);
}

static void _func_detour(func_t *func)
{
	
	struct {
		uint8_t   padding[3];
		uint8_t   opcode;
		ptrdiff_t offset;
	} jmp;
	_Static_assert(sizeof(jmp) == 8, "sizeof(jmp) != 8");
	
	jmp.opcode = 0xE9;
	jmp.offset = (func->copy_addr - (func->real_addr + 5));
	
	mem_unprotect((void *)func->real_addr, func->real_size);
	memcpy((void *)func->real_addr, &jmp.opcode, 5);
	mem_protect((void *)func->real_addr, func->real_size);
}
#endif
