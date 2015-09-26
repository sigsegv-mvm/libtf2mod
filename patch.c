#include "all.h"


patch_info_t *patches[] = {
	&patch_eh_unrestrict_class,
	&patch_eh_unrestrict_projtype,
	&patch_eh_unrestrict_weaponid,
	&patch_human_deathyell_enable,
	&patch_sniperrifle_chargerate_uncap_stock,
	&patch_sniperrifle_chargerate_uncap_classic,
	//&patch_bazaarbargain_head_uncap,
	&patch_sentrygun_think_every_tick,
	&patch_redcredits_unrestrict_weaponid,
	&patch_redcredits_unrestrict_class,
	&patch_disposable_sentry_enable_health_upgrades,
	&patch_giant_stomp_disable,
	&patch_deploybomb_suppress_output,
	&patch_engiebot_ai_repair_tele_under_construction,
	&patch_mvm_gib_fix,
	&patch_playerupgrade_sell_fix,
	&patch_bot_medieval_nonmelee_allow,
	&patch_eyelander_overheal_decay_fix,
	&patch_currencypack_no_pull,
	
	//&patch_tank_shake_disable,
	//&patch_bot_revivemarker_enable,
	&patch_medicbot_ai_xbow_heal_part1,
	&patch_medicbot_ai_xbow_heal_part2,
	
	&patch_perf_attr_premunge_mvm,
	&patch_perf_attr_premunge_halloween,
};


void patch_check_all(void)
{
	for (int i = 0; i < sizeof(patches) / sizeof(*patches); ++i) {
		patch_info_t *patch = patches[i];
		
		pr_special("CHECK: %s\n", patch->name);
		
		if (patch->check()) {
			patch->ok = true;
		}
	}
}

void patch_apply_all(void)
{
	for (int i = 0; i < sizeof(patches) / sizeof(*patches); ++i) {
		patch_info_t *patch = patches[i];
		
		if (patch->ok) {
			pr_special("APPLY: %s\n", patch->name);
			patch->apply();
		} else {
			pr_warn("SKIP: %s\n", patch->name);
		}
	}
}


void patch_all(void)
{
	patch_check_all();
	patch_apply_all();
}


void func_read(void *pfunc, size_t off, size_t len, void *dst)
{
	func_t *func = func_register(pfunc);
	
	assert(off + len <= func->func_size);
	uintptr_t where = func->func_addr + off;
	
	memcpy(dst, (void *)where, len);
}

bool func_verify(void *pfunc, size_t off, size_t len, const void *cmp)
{
	func_t *func = func_register(pfunc);
	
	if (off + len > func->func_size) {
		pr_err("func_verify failed for func '%s':\n", func->name_demangled);
		
		pr_err("bounds check failed: %u + %u > %u\n",
			off, len, func->func_size);
		
		return false;
	}
	
	uintptr_t where = func->func_addr + off;
	
	if (memcmp((void *)where, cmp, len) != 0) {
		pr_err("func_verify failed for func '%s':\n", func->name_demangled);
		
		pr_err("should be:\n");
		mem_dump(cmp, len, false);
		
		pr_err("actual:\n");
		mem_dump((void *)where, len, false);
		
		pr_err("differences at:\n");
		for (int i = 0; i < len; ++i) {
			if (((uint8_t *)cmp)[i] != ((uint8_t *)where)[i]) {
				pr_info("%02x ", i);
			}
		}
		pr_info("\n");
		
		return false;
	}
	
	return true;
}


void func_write(void *pfunc, size_t off, size_t len, const void *src)
{
	func_t *func = func_register(pfunc);
	
	assert(off + len <= func->func_size);
	uintptr_t where = func->func_addr + off;
	
	func_unprotect(func);
	memcpy((void *)where, src, len);
	func_protect(func);
}

void func_write_nop(void *pfunc, size_t off, size_t count)
{
	func_t *func = func_register(pfunc);
	
	assert(off + count <= func->func_size);
	uintptr_t where = func->func_addr + off;
	
	func_unprotect(func);
	memset((void *)where, 0x90, count);
	func_protect(func);
}


void *alloc_func(size_t pages)
{
	void *buf;
	if ((buf = mmap(NULL, pages * PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED) {
		err(1, "mmap in %s failed", __func__);
	}
	
	return buf;
}
