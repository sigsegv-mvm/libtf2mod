#include "all.h"


void            *dl_handle   = NULL;
struct link_map *dl_linkmap  = NULL;
uintptr_t        dl_baseaddr = NULL;


void tf2mod_init(void)
{
	pr_info("libtf2mod: initializing\n");
	
	pr_info("libtf2mod: getting handle for server_srv.so\n");
	if (dlinfo(dl_handle, RTLD_DI_LINKMAP, &dl_linkmap) != 0) {
		errx(1, "dlinfo(server_srv.so, RTLD_DI_LINKMAP) failed: %s", dlerror());
	}
	dl_baseaddr = dl_linkmap->l_addr;
	
	pr_info("libtf2mod: preparing symbol table\n");
	symtab_init("tf/bin/server_srv.so");
	
	
	pr_info("libtf2mod: applying patches\n");
	patch_all();
	
	/* patches MUST be done BEFORE detours to avoid problems! */
	
	pr_info("libtf2mod: enabling detours\n");
	detour_all();
}


/* OVERRIDE: dlopen */
void* dlopen(const char* __file, int __mode)
{
	void* (*real_dlopen)(const char*, int) = dlsym(RTLD_NEXT, "dlopen");
	void* handle = (*real_dlopen)(__file, __mode);
	
	if (handle != NULL && strcasestr(__file, "server_srv.so") != NULL) {
		static bool already_loaded = false;
		
		if (!already_loaded) {
			dl_handle = handle;
			tf2mod_init();
		}
		
		already_loaded = true;
	}
	
	return handle;
}
