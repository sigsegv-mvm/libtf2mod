#include "all.h"


void* (*real_dlopen)(char const*, int);


void tf2mod_init(void)
{
	static bool already_init = false;
	if (already_init) {
		return;
	}
	already_init = true;
	
	
	pr_info("libtf2mod: initializing\n");
	
	
	pr_info("libtf2mod: getting vtable info\n");
	vtable_init();
	
	pr_info("libtf2mod: getting entprop info\n");
	entprop_init();
	
	
	pr_info("libtf2mod: applying patches\n");
	patch_all();
	
	/* patches MUST be done BEFORE detours to avoid problems! */
	
	pr_info("libtf2mod: enabling detours\n");
	detour_all();
	
	
	pr_info("libtf2mod: initializing convars\n");
	convar_init();
	
	
#if DUMP
	pr_info("libtf2mod: dumping ")
#endif
}


/* OVERRIDE: dlopen */
void* dlopen(const char* __file, int __mode)
{
	if (real_dlopen == NULL) {
		real_dlopen = dlsym(RTLD_NEXT, "dlopen");
	}
	
	void* handle = (*real_dlopen)(__file, __mode);
	
	if (__file != NULL && handle != NULL) {
		lib_hook(__file, handle);
	}
	
	return handle;
}
