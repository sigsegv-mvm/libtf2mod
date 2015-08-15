#ifndef _LIBTF2MOD_PATCH_H
#define _LIBTF2MOD_PATCH_H


#define PATCH_CHECK \
	static bool patch_check(void)
#define PATCH_APPLY \
	static void patch_apply(void)

#define PATCH(_name) \
	PATCH_CHECK; \
	PATCH_APPLY; \
	patch_info_t patch_ ## _name = { \
		.name  = #_name, \
		.check = &patch_check, \
		.apply = &patch_apply, \
	};


typedef struct {
	const char *name;
	
	bool (*check)(void);
	void (*apply)(void);
	
	bool ok;
} patch_info_t;


void patch_all(void);

void func_read(void *pfunc, size_t off, size_t len, uint8_t *dst);
bool func_verify(void *pfunc, size_t off, size_t len, const uint8_t *cmp);

void func_write(void *pfunc, size_t off, size_t len, const uint8_t *src);
void func_write_nop(void *pfunc, size_t off, size_t count);

void *alloc_func(size_t pages);


extern patch_info_t patch_eh_unrestrict_class;
extern patch_info_t patch_eh_unrestrict_projtype;
extern patch_info_t patch_eh_unrestrict_weaponid;
extern patch_info_t patch_eh_recursive_fix;
extern patch_info_t patch_arrow_pen_ignoreuber;
extern patch_info_t patch_human_deathyell_enable;
extern patch_info_t patch_sniperrifle_chargerate_uncap_stock;
extern patch_info_t patch_sniperrifle_chargerate_uncap_classic;
extern patch_info_t patch_bazaarbargain_head_uncap;
extern patch_info_t patch_nextprimaryattack_unalias;
extern patch_info_t patch_sentrygun_think_every_tick;
extern patch_info_t patch_redcredits_unrestrict_weaponid;
extern patch_info_t patch_redcredits_unrestrict_class;
extern patch_info_t patch_tank_shake_disable;
extern patch_info_t patch_currencypack_no_pull;
extern patch_info_t patch_disposable_sentry_enable_health_upgrades;
extern patch_info_t patch_giant_stomp_disable;
extern patch_info_t patch_bot_revivemarker_enable;
extern patch_info_t patch_deploybomb_suppress_output;
extern patch_info_t patch_engiebot_ai_repair_tele_under_construction;
extern patch_info_t patch_wavestatus_setactive_wrongarray_fix;
extern patch_info_t patch_mvm_gib_fix;


#endif
