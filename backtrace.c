#include "all.h"


static library_info_t runtime_libs[100];
static int runtime_lib_count;


static library_info_t *_get_runtime_lib(const struct dl_phdr_info *info)
{
	const char *path = info->dlpi_name;
	
	if (path == NULL || path[0] == '\0') {
		//pr_warn("%s: path null/empty, giving up\n", __func__);
		return NULL;
	}
	
	
	//pr_debug("%s: '%s'\n", __func__, path);
	
	for (int i = 0; i < runtime_lib_count; ++i) {
		if (strcmp(path, runtime_libs[i].path) == 0) {
			//pr_debug("  already exists\n");
			return runtime_libs + i;
		}
	}
	//pr_debug("  getting new one\n");
	
	library_info_t *lib = runtime_libs + runtime_lib_count;
	
	
	char *path_dir  = strdup(path);
	char *path_base = strdup(path);
	
	path_dir  = dirname(path_dir);
	path_base = basename(path_base);
	
	lib->path = path;
	lib->name = path_base;
	
	
	if ((lib->fd = open(lib->path, O_RDONLY)) == -1) {
		//warn("open('%s') failed", lib->name);
		return NULL;
	}
	
	if (fstat(lib->fd, &lib->stat) != 0) {
		//warn("fstat('%s') failed", lib->name);
		return NULL;
	}
	lib->size = lib->stat.st_size;
	
	if ((lib->map = mmap(NULL, lib->size, PROT_READ, MAP_PRIVATE, lib->fd, 0))
		== MAP_FAILED) {
		//warn("mmap('%s') failed", lib->name);
		return NULL;
	}
	
	lib->baseaddr = info->dlpi_addr;
	
	
	symtab_init(lib);
	
	
	++runtime_lib_count;
	assert(runtime_lib_count < (sizeof(runtime_libs) / sizeof(*runtime_libs)));
	
	return lib;
}


static uintptr_t find_addr;
static struct dl_phdr_info find_match;

static int _dl_iterate_callback(struct dl_phdr_info *info, size_t size,
	void *data)
{
	/* find the library that's most likely to own this address */
	if (info->dlpi_addr <= find_addr &&
		info->dlpi_addr > find_match.dlpi_addr) {
		find_match = *info;
	}
	
	return 0;
}


static bool _get_runtime_sym(symbol_t *sym, uintptr_t addr)
{
	find_addr = addr;
	memset(&find_match, 0, sizeof(find_match));
	
	dl_iterate_phdr(_dl_iterate_callback, NULL);
	
	
	library_info_t *lib = _get_runtime_lib(&find_match);
	if (lib != NULL) {
		return symtab_lookup_addr_range(lib, sym, STT_FUNC,
			addr - lib->baseaddr);
	}
	
	return false;
}


void print_backtrace(const char *from)
{
	uintptr_t entries[100];
	memset(entries, 0, sizeof(entries));
	
	int num_entries = backtrace((void **)entries,
		sizeof(entries) / sizeof(*entries));
	
	pr_warn("BACKTRACE in %s:\n", from);
	
	for (int i = 0; i < num_entries; ++i) {
		pr_info("  #%-2d  ", i + 1);
		pr_debug("%08x  ", entries[i]);
		
		symbol_t sym;
		if (symtab_func_addr_range_abs(&sym, entries[i]) ||
			_get_runtime_sym(&sym, entries[i])) {
			uintptr_t func_base = sym.lib->baseaddr + sym.addr;
			
			pr_debug("%s+0x%x  [%s]\n", try_demangle(sym.name),
				entries[i] - func_base,
				sym.lib->name);
		} else {
			pr_debug("???\n");
		}
	}
}
