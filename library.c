#include "all.h"


static const char *libs_wanted[] = {
	"engine_srv.so",
	"server_srv.so",
	"libtier0_srv.so",
};

#define NUM_LIBS (sizeof(libs_wanted) / sizeof(*libs_wanted))

static library_info_t libs[NUM_LIBS];


void lib_hook(const char *path, void *handle)
{
	char *path_dir  = strdup(path);
	char *path_base = strdup(path);
	
	path_dir  = dirname(path_dir);
	path_base = basename(path_base);
	
	
	const char *name = path_base;
	
	//pr_debug("lib_hook:\n  path '%s'\n  name '%s'\n  handle %08x\n",
	//	path, name, (uintptr_t)handle);
	
	library_info_t *lib = NULL;
	for (int i = 0; i < NUM_LIBS; ++i) {
		if (strcasecmp(name, libs_wanted[i]) == 0) {
			lib = libs + i;
			break;
		}
	}
	if (lib == NULL) {
		return;
	}
	
	//pr_debug("lib_hook:\n  using lib idx %d (NUM_LIBS = %d)\n",
	//	(lib - libs), NUM_LIBS);
	
	if (lib->name != NULL) {
		//warn("%s: path '%s' hooked twice!\n", __func__, path);
		return;
	}
	
	
	lib->name = name;
	
	if (strcmp(path_dir, ".") == 0) {
		char *fixed_path = malloc(1024);
		snprintf(fixed_path, 1024, "tf/bin/%s", path_base);
		lib->path = fixed_path;
	} else {
		lib->path = path;
	}
	
	if ((lib->fd = open(lib->path, O_RDONLY)) == -1) {
		err(1, "open('%s') failed", name);
	}
	
	if (fstat(lib->fd, &lib->stat) != 0) {
		err(1, "fstat('%s') failed", name);
	}
	lib->size = lib->stat.st_size;
	
	//pr_debug("lib_hook:\n  path '%s'\n  fd %d\n  size %d\n",
	//	lib->path, lib->fd, lib->size);
	
	if ((lib->map = mmap(NULL, lib->size, PROT_READ, MAP_PRIVATE, lib->fd, 0))
		== MAP_FAILED) {
		err(1, "mmap('%s') failed", name);
	}
	
	if (dlinfo(handle, RTLD_DI_LINKMAP, &lib->linkmap) != 0) {
		errx(1, "dlinfo('%s', RTLD_DI_LINKMAP) failed: %s", name, dlerror());
	}
	lib->baseaddr = lib->linkmap->l_addr;
	
	symtab_init(lib);
	
	if (strcmp(name, "server_srv.so") == 0) {
		symbols_init();
		detour_init.setup();
	}
}


library_info_t *lib_find(const char *name)
{
	for (library_info_t *lib = libs; lib != libs + NUM_LIBS; ++lib) {
		if (strcasecmp(name, lib->name) == 0) {
			return lib;
		}
	}
	return NULL;
}


library_info_t *lib_first(void)
{
	return libs;
}

library_info_t *lib_next(library_info_t *lib)
{
	if (++lib != libs + NUM_LIBS) {
		return lib;
	} else {
		return NULL;
	}
}
