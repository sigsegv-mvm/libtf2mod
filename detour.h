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


typedef struct {
	const char *name;
	
	void (*setup)(void);
} detour_info_t;


void detour_all(void);

func_t *func_register(const char *name);

void func_detour_enable(func_t *func, void *detour);
void func_detour_disable(func_t *func, void *detour);


extern detour_info_t detour_sentryrotate_every_third_tick;
extern detour_info_t detour_minisentry_quickbuild_health_fix;
extern detour_info_t detour_mini_dispenser;

extern detour_info_t detour_disposable_dispenser_part1;
extern detour_info_t detour_disposable_dispenser_part2;
extern detour_info_t detour_disposable_dispenser_part3;
extern detour_info_t detour_disposable_dispenser_part4;
extern detour_info_t detour_disposable_dispenser_part5;


#endif
